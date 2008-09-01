// ==============================================================
// dataLogger.c
// This is code implements a fully DMA driven UART writer to
// be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures UART 2
// at a predefined baud rate, then initializes a circular buffer,
// configures the DMA and starts the service. 
// The main function logData writes data to UART2 in the predefined
// comm protocol. 
// 
// Code by: Mariano I. Lizarraga
// First Revision: Aug 26 2008 @ 21:15
// =========================================================

#include "apDefinitions.h"
#include "circBuffer.h"
#include "gpsSplit.h"
#include <p33fxxxx.h>
#include <uart.h>

struct CircBuffer com2Buffer;
CBRef logBuffer;
unsigned int BufferA[LOGSEND] __attribute__((space(dma))) = {0};

void loggerInit (void){
	// initialize the circular buffer
	logBuffer = (struct CircBuffer* )&com2Buffer;
	newCircBuffer(logBuffer);
	
	// DMA0REQ Register
	// ================
	DMA0REQ = 0x001F;
	
	// DMA0PAD Register
	// ================
	DMA0PAD = (volatile unsigned int) &U2TXREG;

	// DMA0CON Register
	// ================
	DMA0CONbits.AMODE   = 0;        // Register Indirect with post-increment
	DMA0CONbits.MODE    = 1;        // One-shot, No Ping-Pong Mode	
	DMA0CONbits.DIR     = 1;        // Read from RAM and send to Periphereal
	DMA0CONbits.SIZE    = 0;        // Word Data Transfer

	// DMA0CNT Register
	// ==============
	DMA0CNT = LOGSEND-1;

	// DMA0STA Register
	// ================
	DMA0STA= __builtin_dmaoffset(BufferA);

	// Enable DMA0 TX interrupts
	IFS0bits.DMA0IF  = 0;			// Clear DMA Interrupt Flag
	IEC0bits.DMA0IE  = 1;			// Enable DMA interrupt
	
	// Configure and open the port;
	// U2MODE Register
	// ==============
	U2MODEbits.ABAUD	= 0;		// Disable autobaud
	U2MODEbits.PDSEL	= 0;		// No parity 8 bit
	U2MODEbits.STSEL	= 0;		// 1 stop bit
	U2MODEbits.BRGH 	= 0;		// Low speed mode
	
	// U1BRG Register
	// ==============
	U2BRG = LOG_UBRG;				// Set the baud rate for data logger


	// U1STA Register
	// ==============
	U2STAbits.UTXISEL0	= 0;		// generate interrupt on every char
	U2STAbits.UTXISEL1	= 0;		// for the DMA
	U2STAbits.URXISEL	= 0;		// RX interrupt irrelevant
	U2STAbits.OERR		= 0;		// clear overun error
	
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
		
	IEC4bits.U2EIE 		= 0;	
}

void assembleMsg(unsigned char* rawData , unsigned char size, char type, unsigned char* protMsg ){
	unsigned char i;
	// start the header
	*(protMsg+0) = DOLLAR;
	*(protMsg+1) = AT;
	*(protMsg+2) = type;
	*(protMsg+3) = size;
	for( i = 0; i < size; i += 1 )
	{
		*(protMsg+i+4) = *(rawData +i);
	}
	*(protMsg+size+4) = STAR;
	*(protMsg+size+5) = getChecksum(protMsg, (size+5));	
}

void copyBufferToDMA (void){
	unsigned char i;
	for(  i = 0; i < LOGSEND; i += 1 )
	{
		BufferA[i] = (unsigned int) readFront(logBuffer);
	}
}


/*
	logData is the implementation of the outgoing Comunications 		
	protocol it is geared to prepare the data either for the data 
	logger or the communications device (radio modem). It uses a 
	static variable to monitor at which samples the outgoing messages 
	are queued in the circular buffer for DMA transmision.
*/
void logData (unsigned char* rawData, unsigned char* data4SPI){
	// sample period variable
	static unsigned char samplePeriod = 0;
	// temp var to store the assembled message
	unsigned char tmpBuf [MAXLOGLEN] ={0}, tmpParameter[MAXLOGLEN] ={0}, i, newData= 0;
	
	
	switch (samplePeriod){
		case 8:
			// assemble the CPU load data for protocol sending	
			assembleMsg(&rawData[LOAD_START], LOADMSG_LEN, LOADMSG_ID, tmpBuf);
			// set the total data out for SPI
			data4SPI[0] = LOADMSG_LEN+6; 
			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < LOADMSG_LEN+6; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}
			newData = (getLength(logBuffer)>= LOGSEND)?1:0;
			break;
		case 5:			
			for( i = 0; i < RAWMSG_LEN; i += 1 ){
				tmpParameter[i] = rawData[RAW_START+i];
			}
			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(tmpParameter, RAWMSG_LEN, RAWMSG_ID, tmpBuf);
			// set the total data out for SPI			
			data4SPI[0] = RAWMSG_LEN+6; 			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < RAWMSG_LEN+6; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}
			newData = (getLength(logBuffer)>= LOGSEND)?1:0;
			
			break;
		case 10:
			// assemble the data for protocol sending
			assembleMsg(&rawData[GPS_START], GPSMSG_LEN, GPSMSG_ID, tmpBuf);
			// set the total data out for SPI
			data4SPI[0] = GPSMSG_LEN+6; 
			// add it to the circular buffer and SPI queue
			for( i = 0; i < GPSMSG_LEN+6; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}
			writeBack(logBuffer,getLength(logBuffer));			
			newData = 1;		
			break;
	}
	
	// increment/overflow the samplePeriod counter
	samplePeriod = (samplePeriod >= 6)? 0: samplePeriod + 1;
	
	
	// if the interrupt catched up with the circularBuffer
	// and new data was added then turn on the 
	if(!DMA0CONbits.CHEN && newData){
		copyBufferToDMA();
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}

}


void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    // Clear the DMA0 Interrupt Flag;
    IFS0bits.DMA0IF  = 0;		
	//putsUART2((unsigned int *)"Transmision in interrupt\n\r\0");
	
	// if there are more bytes to send
	if(getLength(logBuffer)>= LOGSEND)
	{
		//putsUART2((unsigned int *)"Transmision in interrupt\n\r\0");
		copyBufferToDMA();
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}
    
}

void __attribute__ ((interrupt, no_auto_psv)) _U2ErrInterrupt(void)
{
	IFS4bits.U2EIF = 0; // Clear the UART2 Error Interrupt Flag
}

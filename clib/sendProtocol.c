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
// First Revision: Sep 1st 2008 @ 13:21
// =========================================================

#include "apDefinitions.h"
#include "circBuffer.h"
#include "protDecoder.h"
#include <p33fxxxx.h>
#include <uart.h>
#include <string.h>

struct CircBuffer com2Buffer;
CBRef commProtBuffer;
unsigned int BufferA[MAXSEND] __attribute__((space(dma))) = {0};

void commProtInit (void){
	// initialize the circular buffer
	commProtBuffer = (struct CircBuffer* )&com2Buffer;
	newCircBuffer(commProtBuffer);
	
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

void copyBufferToDMA (unsigned char size){
	unsigned char i;
	for(  i = 0; i < size; i += 1 )
	{
		BufferA[i] = (unsigned int) readFront(commProtBuffer);
	}
}

void mergeMessages(unsigned char* dataIn, unsigned char* dataOut){

	unsigned int totalData = 0;
	 
	if (dataIn[0]>0){
		// copy the first data stream
		memcpy(&dataOut[1],&dataIn[1], dataIn[0]);
		totalData += dataIn[0];
	}
/*	
	if(dataIn[GSMSG_IDX]>0){
		// copy the second stream
		memcpy(&dataOut[totalData+1], &dataIn[GSMSG_IDX+1], dataIn[GSMSG_IDX]);
		totalData += dataIn[GSMSG_IDX];
	}
	
	if(dataIn[AKMSG_IDX]>0){
		// copy the second stream
		memcpy(&dataOut[totalData+1], &dataIn[AKMSG_IDX+1], dataIn[AKMSG_IDX]);
		totalData += dataIn[AKMSG_IDX];
	}
*/
	dataOut[0]= totalData;	
}

void txProtocol(unsigned char* protData){
	unsigned char bufLen,i;
		
	// add the data to the circular buffer
	for(i = 1; i <= protData[0]; i += 1 )
	{
		writeBack(commProtBuffer, protData[i] );
	}
	
	// get the Length of the logBuffer
	bufLen = getLength(commProtBuffer);

	// if the interrupt catched up with the circularBuffer
	// and new data was added then turn on the DMA 
	if(!(DMA0CONbits.CHEN) && (bufLen>0)){
		// Configure the bytes to send
		DMA0CNT =  bufLen<= (MAXSEND-1)? bufLen-1: MAXSEND-1;	
		// copy the buffer to the DMA channel outgoing buffer
		copyBufferToDMA((unsigned char) DMA0CNT+1);
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}
	
	//protParseDecode(protData);
}


void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    // Clear the DMA0 Interrupt Flag;
    IFS0bits.DMA0IF  = 0;		
	
	// if there are more bytes to send
	/*if(getLength(commProtBuffer)>= LOGSEND)
	{
		copyBufferToDMA();
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}
    */
}

void __attribute__ ((interrupt, no_auto_psv)) _U2ErrInterrupt(void)
{
	IFS4bits.U2EIF = 0; // Clear the UART2 Error Interrupt Flag
}

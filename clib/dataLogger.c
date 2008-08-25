#include "apDefinitions.h"
#include "circBuffer.h"
#include "gpsSplit.h"
#include <p33fxxxx.h>
#include <uart.h>

struct CircBuffer com2Buffer;
CBRef logBuffer;
unsigned char U2TxLogger[LOGSEND] __attribute__((space(dma)));

void initLogger (void){
		// initialize the circular buffer
	logBuffer = (struct CircBuffer* )&com2Buffer;
	newCircBuffer(logBuffer);
	
	// Configure and open the port;
	// U2MODE Register
	// ==============
	U2MODEbits.UARTEN	= 0;		// Disable the port		
	U2MODEbits.USIDL 	= 0;		// Stop on idle
	U2MODEbits.IREN		= 0;		// No IR decoder
	U2MODEbits.RTSMD	= 0;		// Ready to send mode (irrelevant)
	U2MODEbits.UEN		= 0;		// Only RX and TX
	U2MODEbits.WAKE		= 1;		// Enable at startup
	U2MODEbits.LPBACK	= 0;		// Disable loopback
	U2MODEbits.ABAUD	= 0;		// Disable autobaud
	U2MODEbits.URXINV	= 0;		// Normal operation (high is idle)
	U2MODEbits.PDSEL	= 0;		// No parity 8 bit
	U2MODEbits.STSEL	= 0;		// 1 stop bit
	U2MODEbits.BRGH 	= 0;		// Low speed mode
	
	// U1STA Register
	// ==============
	U2STAbits.UTXISEL0	= 0;		// generate interrupt on every char
	U2STAbits.UTXISEL1	= 0;		// for the DMA
	U2STAbits.URXISEL	= 0;		// RX interrupt irrelevant
	U2STAbits.OERR		= 0;		// clear overun error
	
	// U1BRG Register
	// ==============
	U2BRG = LOG_UBRG;				// Set the baud rate for data logger

	// DMA4CON Register
	// ================
	DMA4CONbits.CHEN    = 0;        // Disable DMA
	DMA4CONbits.SIZE    = 1;        // Byte Data Transfer
	DMA4CONbits.DIR     = 1;        // Read from RAM and send to Periphereal
	DMA4CONbits.HALF    = 0;        // Interrupt at the end of the block
	DMA4CONbits.NULLW   = 0;        // No Null Data periphereal write
	DMA4CONbits.AMODE   = 0;        // Register Indirect with post-increment
	DMA4CONbits.MODE    = 1;        // One-shot, No Ping-Pong Mode
	
	// DMA4CNT Register
	// ==============
	DMA4CNT = LOGSEND-1;
	
	// DMA4REQ Register
	// ================
	DMA4REQbits.IRQSEL = 0x1F;
	
	// DMA4PAD Register
	// ================
	DMA4PAD = (volatile unsigned int) &U2TXREG;

	// DMA4STA Register
	// ================
	DMA4STA= __builtin_dmaoffset(U2TxLogger);
	
	// Enable DMA4 TX interrupts
    IFS2bits.DMA4IF = 0;
    IEC2bits.DMA4IE = 0;
	
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX

}

void assembleMsg(unsigned char* rawData, unsigned char size, char type, unsigned char * protMsg){
	unsigned char i;
	// start the header
	protMsg[0] = DOLLAR;
	protMsg[1] = AT;
	protMsg[2] = type;
	protMsg[3] = size;
	for( i = 0; i < size; i += 1 )
	{
		protMsg[i+4] = rawData[i];
	}
	protMsg[size+3] = STAR;
	protMsg[size+4] = getChecksum(protMsg, (size+5));	
}

void copyBufferToDMA (void){
	unsigned char i;
	for(  i = 0; i < LOG_SEND; i += 1 )
	{
		U2TxLogger[i] = readFront(logBuffer);
	}
}

void logData (unsigned char* rawData){
	unsigned char tmpBuf [GPSMSG_LEN + 5] ={0}, i;
	
	// assemble the data for protocol sending
	assembleMsg(rawData, GPSMSG_LEN, GPSMSG_ID, tmpBuf);
	
	// add it to the circular buffer
	for( i = 0; i < GPSMSG_LEN+5; i += 1 ){
		writeBack(logBuffer,tmpBuf[i]);
	}
	
	// if the interrupt catched up with the circularBuffer
	if(DMA4CONbits.CHEN == 0){
		copyBufferToDMA();
		// Enable the DMA
		DMA4CONbits.CHEN == 1;
		// Init the transmission
		DMA4REQbits.FORCE == 1;
	}	
}


void __attribute__((interrupt, no_auto_psv)) _DMA4Interrupt(void)
{
    // Clear the DMA4 Interrupt Flag;
    IFS2bits.DMA4IF = 0;		

	// if there are more bytes to send
	if(getLength(logBuffer)>= LOG_SEND)
	{
		copyBufferToDMA();
		// Enable the DMA
		DMA4CONbits.CHEN == 1;
		// Init the transmission
		DMA4REQbits.FORCE == 1;
	}
    
}
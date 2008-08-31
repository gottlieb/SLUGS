// ==============================================================
// bufferedUart.c
// This is code implements a fully interrupt driven UART reader to
// be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures UART 1
// at a predefined baud rate, then initializes a circular buffer,
// configures the interrupt and starts the service. 
// The main function gpsRead returns an array where byte 0 indicates
// how many new bytes were read, and byte m indicates how many remain
// in the buffer.
// 
// Code by: Mariano I. Lizarraga
// First Revision: Aug 21 2008 @ 21:15
// ==============================================================

#include "circBuffer.h"
#include "apDefinitions.h"
#include <p33fxxxx.h>
#include <uart.h>

struct CircBuffer com1Buffer;
CBRef uartBuffer;

void gpsSentenceConfig(void){
	int i,j;
	unsigned char chMsgs [] = "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n\0";
	unsigned char chBaudRt [] = "$PMTK251,19200*22\r\n\0";
	
	// Put some huge delays to wait for GPS power-up without the need of a timer
	for( i = 0; i < 250; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}
	
	putsUART1((unsigned int *)chMsgs);
	while(BusyUART1());	

	// Put some huge delays to wait for GPS power-up without the need of a timer
	for( i = 0; i < 150; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}
	putsUART1((unsigned int *)chBaudRt);
	while(BusyUART1());
	
}

void gpsFreqConfig(void){
	unsigned char chFreq [] = "$PMTK300,200,0,0,0,0*2F\r\n\0";	
	putsUART1((unsigned int *)chFreq);
	while(BusyUART1());	
}



// UART and Buffer initialization
void uartInit (void){
	// initialize the circular buffer
	uartBuffer = (struct CircBuffer* )&com1Buffer;
	newCircBuffer(uartBuffer);
	
	// Configure and open the port;
	// U1MODE Register
	// ==============
	U1MODEbits.UARTEN	= 0;		// Disable the port		
	U1MODEbits.USIDL 	= 0;		// Stop on idle
	U1MODEbits.IREN		= 0;		// No IR decoder
	U1MODEbits.RTSMD	= 0;		// Ready to send mode (irrelevant)
	U1MODEbits.UEN		= 0;		// Only RX and TX
	U1MODEbits.WAKE		= 1;		// Enable at startup
	U1MODEbits.LPBACK	= 0;		// Disable loopback
	U1MODEbits.ABAUD	= 0;		// Disable autobaud
	U1MODEbits.URXINV	= 0;		// Normal operation (high is idle)
	U1MODEbits.PDSEL	= 0;		// No parity 8 bit
	U1MODEbits.STSEL	= 0;		// 1 stop bit
	U1MODEbits.BRGH 	= 0;		// Low speed mode
	
	// U1STA Register
	// ==============
	U1STAbits.URXISEL	= 2;		// RX interrupt when 3 chars are in
	U1STAbits.OERR		= 0;		// clear overun error
	
	// U1BRG Register
	// ==============
	U1BRG = UCSCAP_UBRGI;			// Set the baud rate for initial config of GPS

	// Enable the port;
	U1MODEbits.UARTEN	= 1;		// Enable the port	
	U1STAbits.UTXEN		= 1;		// Enable TX
	
	// wait for the UART to settle
	int i;
	for( i = 0; i < 32700; i += 1 )
	{
		Nop();
	}

	// Configure the GPS sentences and change the baud Rate
	gpsSentenceConfig();
	
	// Disable the port and TX;
	U1MODEbits.UARTEN	= 0;		// Disable the port	
	
	// U1BRG Register
	// ==============
	U1BRG = UCSCAP_UBRGF;			// Set the baud rate for operation of GPS	
	
	// Enable the port;
	U1MODEbits.UARTEN	= 1;		// Enable the port	
	U1STAbits.UTXEN		= 1;		// Enable TX
	
	for( i = 0; i < 32700; i += 1 )
	{
		Nop();
	}
	
	// Configure the frequency to 5 Hz
	gpsFreqConfig();
	
	// Disable the port and TX;
	U1MODEbits.UARTEN	= 0;		// Disable the port	


	// Initialize the Interrupt  
  	IPC2bits.U1RXIP   = 6;    		// Interrupt priority 6  
  	IFS0bits.U1RXIF   = 0;    		// Clear the interrupt flag
  	IEC0bits.U1RXIE   = 1;    		// Enable interrupts
 
  	// Enable the port;
	U1STAbits.UTXEN		= 0;		// Disable TX	
  	U1MODEbits.UARTEN	= 1;		// Enable the port		
}


// Interrupt service routine for U1 GPS port
void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void){
 
	// Read the buffer while it has data
	// and add it to the circular buffer
	while(U1STAbits.URXDA == 1){
		writeBack(uartBuffer, (unsigned char)U1RXREG);
	}
	
	// If there was an overun error clear it and continue
	if (U1STAbits.OERR == 1){
		U1STAbits.OERR = 0;
	}
	
	// clear the interrupt
	IFS0bits.U1RXIF = 0;
}

void gpsRead(unsigned char* gpsChunk){
	// fix the data length so if the interrupt adds data
	// during execution of this block, it will be read
	// until the next gpsRead
	unsigned char tmpLen = getLength(uartBuffer), i=0;
	
	// if the buffer has more data than the max size
	if (tmpLen > CSIZE -2){
		// set the new to the max
		gpsChunk[0] = CSIZE -2;
		// set the remaining to the len - max
		gpsChunk[CSIZE-1] = tmpLen - (CSIZE -2);
	}else{
		// set the new to the actual len
		gpsChunk[0] = tmpLen;
		// no remaining data in the buffer
		gpsChunk[CSIZE-1] = 0;
	}
	
	// read the data 
	for(i = 1; i <= gpsChunk[0]; i += 1 )
	{
		gpsChunk[i] = readFront(uartBuffer);
	}
}


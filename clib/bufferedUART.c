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

struct CircBuffer com1Buffer;
CBRef uartBuffer;

// UART and Buffer initialization
void uartInit (void){
	// initialize the circular buffer
	uartBuffer = (struct CircBuffer* )&com1Buffer;
	newCircBuffer(uartBuffer);
	
	// Initialize the Interrupt	
	IPC2bits.U1RXIP 	= 6;		// Interrupt priority 6	
	IFS0bits.U1RXIF 	= 0;		// Clear the interrupt flag
	IEC0bits.U1RXIE 	= 1;		// Enable interrupts
	
	// Configure and open the port;
	// U1MODE Register
	// ==============
	U1MODEbits.UARTEN	= 0;		// Disable the port		
	U1MODEbits.USIDL 	= 1;		// Stop on idle
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
	//U1STAbits.UTXISEL	= 0;		// irrelevant no TX for gps
	U1STAbits.UTXINV	= 0;		// 
	U1STAbits.UTXBRK	= 0;		//
	U1STAbits.UTXEN		= 0;		// disable TX
	U1STAbits.UTXBF		= 0;		// clear TX buffer
	U1STAbits.TRMT		= 0;		// TX Buffer empty
	U1STAbits.URXISEL	= 2;		// RX interrupt when 3 chars are in
	U1STAbits.ADDEN		= 0;		// Irrelevant, working in 8 bits
	U1STAbits.OERR		= 0;		// clear overun error
	
	// U1BRG Register
	// ==============
	U1BRG = UCSCAP_UBRG;				// Set the baud rate

	// Enable the port;
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
	
	
	if (tmpLen > CSIZE -2){
		gpsChunk[0] = CSIZE -2;
		gpsChunk[CSIZE-1] = tmpLen - (CSIZE -2);
	}else{
		gpsChunk[0] = tmpLen;
		gpsChunk[CSIZE-1] = 0;
	}
	
	// read the data 
	for(i = 1; i <= tmpLen; i += 1 )
	{
		gpsChunk[i] = readFront(uartBuffer);
	}
}


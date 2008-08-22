// ==============================================================
// bufferedUart.c
// This is code implements a fully interrupt driven UART reader to
// be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures UART 1
// at a predefined baud rate, then initializes a circular buffer,
// configures the interrupt and starts the service. 
// The main function readGPS returns an array where byte 0 indicates
// how many new bytes were read, and byte m indicates how many remain
// in the buffer.
// 
// Code by: Mariano I. Lizarraga
// First Revision: Aug 21 2008 @ 21:15
// ==============================================================

#include <uart.h>
#include "circBuffer.h"
#include "apDefinitions.h"

struct CircBuffer com1Buffer;
cBRef uartBuffer;

// UART and Buffer initialization
void uartInit (void){
	// initialize the circular buffer
	uartBuffer = &com1Buffer;
	newCircBuffer(uartBuffer);
	
	// Configure the port;
	OpenUART1( 	UART_EN &			// Enable the UART
				UART_IDLE_STOP &	// Stop on idle
				UART_RX_TX &		// Use the normal pins (not alt)
				UART_EN_WAKE &		// Enable at startup
				UART_DIS_LOOPBACK &	// Disable loopback
				UART_DIS_ABAUD &	// Disable capture module
				UART_NO_PAR_8BIT &	// No parity 8 bits
				UART_1_STOPBIT,		// 1 stop bit
				UART_TX_DISABLE &	// Disable TX, no transimission
				UART_IN_RX_3_4_FULL & // Set the RX interrupt when 3 bytes on register
				UART_ADR_DETECT_DIS & // Disable address detect
				UART_RX_OVERRUN_CLEAR, // clear overrun flag
				UCSCAP_UBRG);
	
	// Initialize the Interrupt
	ConfigIntUART1(	UART_RX_INT_EN &		// Enable interrupts
					UART_RX_INT_PR3 &		// Interrupt priority 3
					UART_TX_INT_DIS &		// Disable TX interrupts
					UART_TX_INT_PRI0);		// TX interrupt priority irrelevant
}


// Interrupt service routine
void __attribute__((__interrupt__, no_auto_psv)) _COM1Interrupt(void){
 
 
}


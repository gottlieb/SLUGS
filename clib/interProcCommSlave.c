/*
The MIT License

Copyright (c) 2009 UCSC Autonomous Systems Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

// ==============================================================
// interProcCommSlave.c
// This is code implements via SPI the interprocessor communications
// to be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures SPI1 as slave
// for the control MCU at 10 MHZ; it then initializes a circular buffer. 
// The main functions are: 1.- readIpc which reads the circularBuffer
// filled by the SPI interrupt and sends the data for processing.
// 2.- SPI1 interrupt gets bytes from the master MCU. It stores bytes in
// a circular buffer
// 
// Code by: Mariano I. Lizarraga
// First Revision: Sep 1st 2008 @ 21:15
// =========================================================
#include "interProcCommSlave.h"

//Structure arrays for incomming data
//struct tGpsData gpsDataBuffer [3];
//struct tRawData rawDataBuffer [3];
//unsigned char currentBuffer = 0, lastBuffer =2;

// Global Circular buffer
struct CircBuffer spiBuffer;
CBRef protBuffer;


void spiSlaveInit(void){
	// Initialize the circular buffer
	protBuffer = &spiBuffer;
	newCircBuffer (protBuffer);
	
	// Configure the Analog pins B2, and SPI pins as digital.
    // This  is done as work-around for a bug in the
    // dspic blockset version 0.98d
    AD1PCFGLbits.PCFG2 	= 1;
	AD2PCFGLbits.PCFG2 	= 1;
	TRISFbits.TRISF7 	= 1;	
	TRISFbits.TRISF8 	= 0;
	TRISBbits.TRISB2 	= 1;
	
	
    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0;    //Internal Serial Clock is Enabled.
    SPI1CON1bits.DISSDO = 0;    //SDOx pin is controlled by the module.
    SPI1CON1bits.MODE16 = 0;    //Communication is byte-wide (8 bits).
    SPI1CON1bits.SMP    = 0;    //Cleared in slave mode.
    SPI1CON1bits.CKE    = 0;    //Serial output data changes on transition from
                                //Idle clock state to active clock state
    SPI1CON1bits.CKP    = 0;    //Idle state for clock is a low level;
                                //active state is a high level
    SPI1CON1bits.SSEN   = 1;    // SS Used in slave mode    
    SPI1CON1bits.MSTEN  = 0;    //Slave Mode Enabled
    
    // Configure the clock for 10 MHz
    SPI1CON1bits.SPRE   = 7;    //Secondary prescaler to 1:1
    SPI1CON1bits.PPRE   = 2;    //Primary prescaler 4:1
    
    
    // Enable the module 
    SPI1STATbits.SPIROV = 0;    //Clear overflow bit
    SPI1STATbits.SPIEN  = 1;    //Enable SPI Module

    
    // clear the interrupt flag
    IFS0bits.SPI1IF 	= 0;
    // clear the error flag
    IFS0bits.SPI1EIF	= 0;
    // clear the overflow flag
	SPI1STATbits.SPIROV = 0;
    
    // Enable the interrupts
    IPC2bits.SPI1IP 	= 6;
    IEC0bits.SPI1EIE	= 1;
    IEC0bits.SPI1IE		= 1; 
    
    INTCON1bits.NSTDIS	= 1;
}

void readIpc (unsigned char* bufferedData){
	// fix the data length so if the interrupt adds data
	// during execution of this block, it will be read
	// until the next readIpc
	unsigned int tmpLen = getLength(protBuffer);
	
	
	unsigned int i=0;
	unsigned int availBytes = 0, sendMore = 0;
	unsigned char failureTrue = 0;
	
	//static unsigned long long timeStamp = 0;
	
	
	// Set the output size accordingly
	bufferedData[0] = (tmpLen > MAXLOGLEN)? MAXLOGLEN: tmpLen;
	
	// TODO: Remove debugging info from readIPC
	//if ((timeStamp % 1000)== 0){
	//	printToUart2("T: %6.0f\n\r\0",(float) timeStamp*0.01);
	//}
	//timeStamp++;
		
	// write the data 
	for(i = 1; i <= bufferedData[0]; i += 1 )
	{
		bufferedData[i] = readFront(protBuffer);
	}
	
	
	if (getOverflow(protBuffer)>0){
		// disable the SPI module
		SPI1STATbits.SPIEN  = 0;    
    
    	// Disable the interrupts
    	IEC0bits.SPI1IE		= 0; 
    	IFS0bits.SPI1IF 	= 0;
		
    	printToUart2("\n=== %s =====\n\r\n\r\n\r", "BEGIN DUMP ");
    	//printToUart2("Ts: %f\n\r\0",(float) timeStamp*0.01);
    	printToUart2("Ovrflw: %d\n\r", getOverflow(protBuffer));
 		printToUart2("Head: %d\n\r", readHead(protBuffer));
		printToUart2("Tail: %d\n\r", readTail(protBuffer));
		printToUart2("Len: %d\n\r", getLength(protBuffer));
		printToUart2("Siz: %d\n\r", protBuffer->size);
   	
    	
    	for(i = 0; i <BSIZE; i ++ )
    	{
    		printToUart2("%d ", protBuffer->buffer[i]);
    	}

    	printToUart2("\n=== %s =====\n\r\n\r\n\r", "END ");
    	
    	// Empty the buffer
		makeEmpty(protBuffer);


    	// Enable the interrupts
    	IFS0bits.SPI1IF 	= 0;
    	IEC0bits.SPI1IE		= 1; 

		// Enable the SPI module
		SPI1STATbits.SPIEN  = 1;    

	}
		
}

// Interrupt service routine for SPI1 Slave 
void __attribute__((__interrupt__, no_auto_psv)) _SPI1Interrupt(void){
 	// if we received a byte
 	if (SPI1STATbits.SPIRBF == 1){
 		// put the received data in the circular buffer 
		writeBack(protBuffer, (unsigned char)SPI1BUF);
	}

	// clear the interrupt
	 IFS0bits.SPI1IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _SPI1ErrInterrupt(void){
    // clear the overflow flag
	SPI1STATbits.SPIROV = 0;

    // clear the error flag
    IFS0bits.SPI1EIF	= 0;
	
}

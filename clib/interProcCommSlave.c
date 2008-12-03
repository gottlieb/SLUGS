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
#include "apDefinitions.h"
#include "circBuffer.h"
#include <string.h>
#include <p33fxxxx.h>
#include <spi.h>
#include <uart.h>
#include <stdlib.h>
#include <stdarg.h>

//Structure arrays for incomming data
struct tGpsData gpsDataBuffer [3];
struct tRawData rawDataBuffer [3];
//unsigned char currentBuffer = 0, lastBuffer =2;
unsigned char spiDidInit = 0;

// Global Circular buffer
struct CircBuffer spiBuffer;
CBRef protBuffer;

void printToUart2 (const char *fmt, ...){
	va_list ap;
	char buf [300];
	
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end (ap);
	putsUART2((unsigned int*)buf);
}

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

    
    // Enable the interrupts
    IFS0bits.SPI1IF 	= 0;
    IPC2bits.SPI1IP 	= 6;
    IEC0bits.SPI1IE		= 1; 
    spiDidInit =1;
}


void readIpc (unsigned char* bufferedData){
	// fix the data length so if the interrupt adds data
	// during execution of this block, it will be read
	// until the next readIpc
	unsigned int tmpHead = readHead(protBuffer);
	unsigned int tmpTail = readTail(protBuffer);
	unsigned int tmpLen = getLength(protBuffer);
	unsigned int i=0;
	unsigned int availBytes = 0, sendMore = 0;
	unsigned char failureTrue = 0;
	
	static unsigned long long timeStamp = 0;
	
	// Set the output size accordingly
	bufferedData[0] = (tmpLen > (MAXLOGLEN-1))? (MAXLOGLEN-1): tmpLen;
	
	if ((timeStamp % 1000)== 0){
		printToUart2("%f\n\r\0",(float) timeStamp*0.01);
		if (spiDidInit) printToUart2("=== %s ===\n\r", "SPI INIT");
	}
	timeStamp++;

/*	if (!(tmpLen == 64 || tmpLen == 75 || tmpLen == 81 
		|| tmpLen == 89 || tmpLen == 95 || tmpLen == 98)){
			printToUart2("=== %s ===\n\r", "FAILURE");
			printToUart2("Ts: %f\n\r\0",(float) timeStamp*0.01);
			printToUart2("+++ %s +++\n\r", "Buffer Data");
			printToUart2("TmpLen: %d\n\r", tmpLen);
			printToUart2("bD[0]: %d\n\r", bufferedData[0]);
			printToUart2("Head: %d\n\r", tmpHead);
			printToUart2("Tail: %d\n\r", tmpTail);
			printToUart2("Ovrfl: %d\n\r", getOverflow(protBuffer));
			printToUart2("++ %s++\n\r", "SPI");
			failureTrue = 1;
	}
    
*/	
	// write the data 
	for(i = 1; i <= bufferedData[0]; i += 1 )
	{
		bufferedData[i] = readFront(protBuffer);
		if (failureTrue){
			printToUart2("%d\n\r", bufferedData[i]);
		}
	}
    

/*	// do a second run just in case
	tmpLen = getLength(protBuffer);
	
	// if more data was written during the reading
	if (tmpLen > 0 ){
		
		// check how many more bytes you can send
		availBytes = (MAXLOGLEN-1) - bufferedData[0];
		
		if (failureTrue){
			printToUart2("++ %s +\n\r", "2 Run" );
			printToUart2("TmpLen: %d\n\r", tmpLen);
			printToUart2("Head: %d\n\r", readHead(protBuffer));
			printToUart2("Tail: %d\n\r", readTail(protBuffer));
			printToUart2("Ovrflw: %d\n\r", getOverflow(protBuffer));
			printToUart2("bD[0]: %d\n\r", bufferedData[0]);
			printToUart2("avail: %d\n\r", availBytes);

		}
		
		// if you still have space in this run
		if (availBytes>0){
			
			// if we have available bytes and are less the the remaining bytes
			sendMore =  (tmpLen <= availBytes)? tmpLen: availBytes;
			if (failureTrue){
				printToUart2("++++ %s +++\n\r", "Avail > 0");
				printToUart2("Send More: %d\n\r", sendMore);
				printToUart2("++++ %s +++\n\r", "sent 2");
			}
		
			// write the data 
			for(i = bufferedData[0]+1; i <= bufferedData[0]+1+sendMore; i += 1 )
			{
				bufferedData[i] = readFront(protBuffer);
				if (failureTrue){
					printToUart2("%d\n\r", bufferedData[i]);
				}
			}

			// Set the output size accordingly
			bufferedData[0] = bufferedData[0]+sendMore;			
			if (failureTrue){
				printToUart2("+++ %s ++\n\r", "final ");
				printToUart2("bD[0]: %d\n\r", bufferedData[0]);
			}
				
		}
		
	}*/

	
	// SPI Debug
	/*memset(&bufferedData[99],0,10);
	
	bufferedData[99]  = tmpLen;
	bufferedData[100] = getLength(protBuffer); 
	bufferedData[101] = bufferedData[0];
	bufferedData[102] = sendMore;
	bufferedData[103] = getOverflow(protBuffer);*/
	
	
	if (getOverflow(protBuffer)>0){
		// disable the SPI module
		SPI1STATbits.SPIEN  = 0;    
    
    	// Disable the interrupts
    	IFS0bits.SPI1IF 	= 0;
    	IEC0bits.SPI1IE		= 0; 
		
    	printToUart2("Ovrflw: %d\n\r", getOverflow(protBuffer));
    	
    	// Empty the buffer
		makeEmpty(protBuffer);

    	// Enable the interrupts
    	IFS0bits.SPI1IF 	= 0;
    	IEC0bits.SPI1IE		= 1; 

		// Enable the SPI module
		SPI1STATbits.SPIEN  = 1;    

	}
	
	if (failureTrue){
		printToUart2("=== %s =====\n\r\n\r\n\r", "END ");
	}
	
}



// Interrupt service routine for SPI1 Slave 
void __attribute__((__interrupt__, no_auto_psv)) _SPI1Interrupt(void){
 	//static unsigned char spiBufIdx = 1; 
 	//unsigned char dataRead;
	//putsUART2((unsigned int*)"+");	
 	// if we received a byte
 	if (SPI1STATbits.SPIRBF == 1){
 		// put the received data in the circular buffer 
		writeBack(protBuffer, (unsigned char)SPI1BUF);
		//putsUART2((unsigned int*)".");
	}
	// clear the interrupt
	 IFS0bits.SPI1IF = 0;
}



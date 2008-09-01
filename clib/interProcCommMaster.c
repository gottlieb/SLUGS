// ==============================================================
// interProcComm.c
// This is code implements via SPI the interprocessor communications
// to be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures SPI1 as slave
// for the control MCU and master for the sensor MCU, both 
// at 10 MHZ; it then initializes a circular buffer. 
// The main functions are: 1.- spiSend writes data to SPI1 in the predefined
// comm protocol. This will be implemented in the master (sensor) MCU.
// 2.- SPI1 interrupt gets bytes from the master MCU. It stores bytes in
// two buffers in ping-pong mode (ala DMA) 
// Note that by the nature of the SPI buses BOTH modules (slave and master)
// send and receive data simultaneously. This is advantage is used to 
// let the slave know what byte the master is expecting thus allowing an
// efective two-way communication
// 
// Code by: Mariano I. Lizarraga
// First Revision: Aug 27 2008 @ 21:15
// =========================================================
#include "apDefinitions.h"
#include "circBuffer.h"
#include <p33fxxxx.h>
#include <spi.h>

void spiMasterInit(void){
	// Configure the Analog pins B2 as digital.
    // This  is done as work-around for a bug in the
    // dspic blockset version 0.98d
    AD1PCFGLbits.PCFG2 	= 1;
	AD2PCFGLbits.PCFG2 	= 1;
	TRISFbits.TRISF7 	= 1;
	TRISFbits.TRISF8 	= 0;
	TRISBbits.TRISB2 	= 0;
	LATBbits.LATB2 		= 1;


    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0;    //Internal Serial Clock is Enabled.
    SPI1CON1bits.DISSDO = 0;    //SDOx pin is controlled by the module.
    SPI1CON1bits.MODE16 = 0;    //Communication is byte-wide (8 bits).
    SPI1CON1bits.SMP    = 0;    //Sample at the middle .
    SPI1CON1bits.CKE    = 0;    //Serial output data changes on transition from
                                //Idle clock state to active clock state
    SPI1CON1bits.CKP    = 0;    //Idle state for clock is a low level;
                                //active state is a high level
    SPI1CON1bits.SSEN   = 0;    // SS not Used ( Master mode)    
    SPI1CON1bits.MSTEN  = 1;    //Master Mode Enabled
    
    // Configure the clock for 10 MHz
    SPI1CON1bits.SPRE   = 7;    //Secondary prescaler to 1:1
    SPI1CON1bits.PPRE   = 2;    //Primary prescaler 4:1
    
    
    // Enable the module 
    SPI1STATbits.SPIROV  = 0;   //Clear overflow bit
    SPI1STATbits.SPIEN   = 1;   //Enable SPI Module
    
}

void spiSend(unsigned char * data2Send){
	unsigned char i;
	unsigned int rcvdIdx = 0;
	//static unsigned char sendSPIData = 1; 
	
	// Send the amount of data received via SPI
	for(i = 1; i <= data2Send[0]; i += 1 )
	{
		WriteSPI1(data2Send[i]);
		while(!DataRdySPI1());
		rcvdIdx = ReadSPI1();		
	}
}

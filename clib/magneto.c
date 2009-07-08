#include "magneto.h"

/*
The endianess of the dsPIC was determined with an experiment as follows

	placeTest.chData[0] = 1;
	placeTest.chData[1] = 0;
	
	
	placeTest2.chData[0] = 0;
	placeTest2.chData[1] = 1;
	
	printToUart2("%u\t %u\n\r",placeTest.usData, placeTest2.usData);
	The Above line produces:
		1		256
	therefore, chData[0]= LSB and chData[1]=MSB

*/

unsigned char i2c1State;		// State Machine State
unsigned char reg2Config;		// Register to config

// Declared global to avoid having them be static 
// inside the interrupt
tShortToChar currentMag;		// placeholder for current mag reading
unsigned char byteRead, wordRead; // current byte and word read
unsigned char byteCount;		// Count the number of bytes received


void magDebugUartConfig(void){
	// Configure and open the port;
	// U2MODE Register
	// ==============
	U2MODEbits.ABAUD	= 0;		// Disable autobaud
	U2MODEbits.PDSEL	= 0;		// No parity 8 bit
	U2MODEbits.STSEL	= 0;		// 1 stop bit
	U2MODEbits.BRGH 	= 0;		// Low speed mode
	
	// U2STA Register
	// ==============
	U2STAbits.UTXISEL0	= 0;		// generate interrupt on every char
	U2STAbits.UTXISEL1	= 0;		// for the DMA
	U2STAbits.URXISEL	= 0;		// RX interrupt with every char
	U2STAbits.OERR		= 0;		// clear overun error

	// U2BRG Register
	// ==============
	U2BRG = LOG_UBRG;				// Set the baud rate for data logger

	// Initialize the Interrupt  
  	// ========================
	IPC7bits.U2RXIP   = 5;    		// Interrupt priority 6  
  	IFS1bits.U2RXIF   = 0;    		// Clear the interrupt flag
  	IEC1bits.U2RXIE   = 0;    		// Disable interrupts
  		
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
		
	IEC4bits.U2EIE 		= 0;	
}

void magnetoInit (void){
	//magDebugUartConfig();
	//printToUart2("Starting %s\n\r","sequence");
	
	
	// Configure the I2C bus
	I2C1CONbits.A10M = 0;		// 7 bit address
	I2C1BRG =	363;			// I2CBRG = 363. 100Khz for a 40 Mhz clock
	
	
	
	// Configure the Interrupts
	IFS1bits.MI2C1IF = 0;		// Clear the master interrupt
	IFS1bits.SI2C1IF = 0;		// Clear the slave interrupt

	IEC1bits.MI2C1IE = 1;		// Enable the interrupts
	IPC4bits.MI2C1IP = 7;		// Highest Prority
	
	// turn on the I2C Module
	I2C1CONbits.I2CEN = 1;
	
	// Initialize the state machine
	i2c1State = CONFIG_IDLE;
	// Select the register to configure
	reg2Config = REGISTER_A;
	
	//printToUart2("Starting %s\n\r","I2C");
	
	// Wait 5 mS
	dummyDelay();
	
	// Change the mode to 50 Hz
	// ========================
	// Start The Bus
	i2c1Start();
	// Wait for the bus stop
	// this signal that the whole config went trhough
	while(i2c1State != CONFIG_IDLE){
		printToUart2("Out of Int: %d\n\r",i2c1State);
		//byteRead++;
	}
	
	//printToUart2("Changed To %s\n\r","50 HZ");

	// Wait 5 mS
	dummyDelay();
	
	
	// Change the gain
	// ===============
	// Change the register to config
	reg2Config = REGISTER_B;
	// Start The Bus
	i2c1Start();
	// Wait for the bus stop
	// this signal that the whole config went trhough
	while(i2c1State != CONFIG_IDLE){
		printToUart2("Out of 2nd I: %d\n\r",i2c1State);
	}

	printToUart2("Changed To %s\n\r","0.7 Gain");
	
	// Wait 5 mS
	dummyDelay();
	
	
	
	// Change the mode to continous
	// ============================
	// Change the register to config
	reg2Config = MODE_REGISTER;
	// Start The Bus
	i2c1Start();
	// Wait for the bus stop
	// this signal that the whole config went trhough
	while(i2c1State != READ_IDLE){
		printToUart2("Out of 3rd I: %d\n\r",i2c1State);
		//byteRead++;
	}
	
	//printToUart2("Changed To %s\n\r","Contrinous");

	// Wait 5 mS
	dummyDelay();
	
	// Initialize the variables
	byteRead = 1;
	wordRead = 0;
	byteCount = 0;
}

void startMagRead (void) {
	i2c1State = READ_IDLE;
	byteRead = 1;
	wordRead = 0;
	byteCount = 0;
	i2c1Start();
	
}

void readMag (unsigned char idx, short val){
	static tShortToChar magReading[3];
	
	magReading[idx].shData	= val;
	//printToUart2("%u.-\t %d\n\r", idx, val);
	
	if (idx == 2){
		rawControlData.magX.shData = magReading[0].shData;
		rawControlData.magY.shData = magReading[1].shData;
		rawControlData.magZ.shData = magReading[2].shData;
		
		//printToUart2("%d\t %d\t %d\n\r",magReading[0].shData, magReading[1].shData,magReading[2].shData);
	}
}

void getMag (short * magVals){
	static unsigned char readMagVar = 1;
	
	magVals[0] =  rawControlData.magX.shData;
	magVals[1] =  rawControlData.magY.shData;
	magVals[2] =  rawControlData.magZ.shData;
	// printToUart2("%u\t %u\t %u\n\r",magVals[0], magVals[1],magVals[2]);
	
	// After reporting the data start the reading for the next cycle
	// called every other time since the mags refresh @ 50 Hz
	#ifndef NO_MAGNETO
		if (readMagVar) {startMagRead();}
	#endif
	// flip the read flag
	readMagVar = (readMagVar == 1)? 0: 1;
	
}

// I2C Primitives
// ==============

void i2c1Start(void){
	// Change the mode to start
	i2c1State = (i2c1State == CONFIG_IDLE)? CONFIG_START : READ_START;
	// Start the bus
	I2C1CONbits.SEN =1;  
}

void i2c1Stop(void){
	// Change the mode to start
	i2c1State = (i2c1State == CONFIG_DONE)? CONFIG_STOP : READ_STOP;
	// Stop the bus
	I2C1CONbits.PEN =1;  
}
void i2c1Write(unsigned char byte2write){
	// Send the data
	I2C1TRN = byte2write;
}

// Interrupt Service Routine (State Machine Implementation)
// =========================

void __attribute__((__interrupt__, no_auto_psv)) _MI2C1Interrupt(void){		
	switch (i2c1State) {
		case CONFIG_START:
			if (!I2C1CONbits.SEN){
				// change the state
				i2c1State = CONFIG_IDTX;
				// Send the address to write
				i2c1Write(MAG_WRITE);
			}
		break;
		case CONFIG_IDTX:
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = CONFIG_REG_TX;
				// send the register address
				i2c1Write(reg2Config);
			}
		break;
		case CONFIG_REG_TX:
			if (!I2C1STATbits.ACKSTAT){
				i2c1State = CONFIG_VAL_TX;				
				if (reg2Config==REGISTER_A){
					// send the actual configuration for 50Hz
					i2c1Write(MODE_50_HZ);
				} else {
					// send the configuration for continuous sampling
					i2c1Write(MODE_CONTINUOS);
				}
			}
		break;
		case CONFIG_VAL_TX:
			if (!I2C1STATbits.ACKSTAT){
				i2c1State = CONFIG_DONE;
				// Send a bus Stop
				i2c1Stop();
			}
		break;
		case CONFIG_STOP:
			if (!I2C1CONbits.PEN){
				if (reg2Config!=MODE_REGISTER){
					// Set the Config to idle, wait for next config
					i2c1State = CONFIG_IDLE;
				} else {
					// Ready to read magnetometer data
					i2c1State = READ_IDLE;
				}	
			}
		break;
		case READ_START:
			if (!I2C1CONbits.SEN){
				// change the state
				i2c1State = READ_IDTX;
				// Send the address to write
				i2c1Write(MAG_READ);
			}		
		break;
		case READ_IDTX:
			//if (!I2C1CONbits.RSEN){
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = READ_DATA;
				// Start Clocking Data
				I2C1CONbits.RCEN = 1;
			}		
		break;	
		case READ_DATA:
			if (I2C1STATbits.RBF){
				//printToUart2("br:%d wr:%d dc:%d\n\r",byteRead, wordRead,byteCount);
				byteCount++;
				// read the received Data
				if (byteCount < 7) {
					currentMag.chData[byteRead] = (unsigned char)I2C1RCV;
					//printToUart2("byte:%d\n\r", I2C1RCV);
				} else {
					wordRead= (unsigned char)I2C1RCV;
					byteRead = 1;
					//printToUart2("ignored:%d\n\r", I2C1RCV);
				}
				
				// if we just read a word (i.e. byteRead == 1)
				if(byteRead == 0)
				{
					//printToUart2("%u\n\r",currentMag.usData);
					readMag(wordRead,currentMag.shData);
					wordRead++;
				}
				
				// flip the byte
				byteRead = byteRead == 0? 1 : 0;
				
				//if (wordRead >= 3){
				if (byteCount >= 7 ){
					// Done Generate a NACK 
					I2C1CONbits.ACKDT = 1;
		            I2C1CONbits.ACKEN = 1;
				} else {
					// Generate the AKN
					I2C1CONbits.ACKDT = 0;
            		I2C1CONbits.ACKEN = 1;
				}
			} else if (!I2C1STATbits.ACKSTAT){
				//if (wordRead < 3){
				if (byteCount < 7){
					// Enable reading
					I2C1CONbits.RCEN = 1;					
				} else {
					// change the state
					i2c1State = READ_DONE;
					i2c1Stop();					
				}	
			}
		break;	
		case READ_STOP:
			if (!I2C1CONbits.PEN){
				// Ready to read next magnetometer data
				i2c1State = READ_IDLE;				
			}
		break;	
	}
	//
	IFS1bits.MI2C1IF = 0;			// Clear the master interrupt
	I2C1STATbits.IWCOL = 0;			// Clear the collision flag just in case		
}

void dummyDelay (void) {
	unsigned int i, j;
	// Put some huge delays to wait for Magnetometer power-up 
	// without the need of a timer
	// 5 milliseconds are expected for power-up
	// @ 40Mhz requires aprox 200,000 nops
	for( i = 0; i < 7; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}
}


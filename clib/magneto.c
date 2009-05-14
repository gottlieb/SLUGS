#include "magneto.h"

// Current state Variable
unsigned char i2c1State;
unsigned char reg2Config;
tShortToChar currentMag;	
unsigned char byteRead, wordRead;
unsigned char debugCount;
tShortToChar  magReading[3];

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
	magDebugUartConfig();
	
	printToUart2("Starting %s\n\r","sequence");
	unsigned int i, j;
	
	
	// Configure the I2C bus
	I2C1CONbits.A10M = 0;		// 7 bit address
	I2C1BRG =	63;				// I2CBRG = 63. 400Khz for a 40 Mhz clock
	
	
	
	// Configure the Interrupts
	IFS1bits.MI2C1IF = 0;		// Clear the master interrupt
	IFS1bits.SI2C1IF = 0;		// Clear the slave interrupt

	IEC1bits.MI2C1IE = 1;		// Enable the interrupts
	
	// turn on the I2C Module
	I2C1CONbits.I2CEN = 1;
	
	// Initialize the state machine
	i2c1State = CONFIG_IDLE;
	reg2Config = 0x00;
	
	printToUart2("Starting %s\n\r","I2C");

	// Put some huge delays to wait for Magnetometer power-up without the need of a timer
	// 5 milliseconds are expected for power-up
	for( i = 0; i < 15; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}
	
	// Change the mode to 50 Hz
	
	// Start The Bus
	i2c1Start();
	// Wait for the bus stop
	// this signal that the whole config went trhough
	while(i2c1State != CONFIG_IDLE){
		printToUart2("Out of Int: %d\n\r",i2c1State);
	}
	
	printToUart2("Changed To %s\n\r","50 HZ");

	// Put some huge delays to wait for Magnetometer power-up without the need of a timer
	// 5 milliseconds are expected for power-up
	for( i = 0; i < 15; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}	
	
	// Change the gain
	// Change the register to config
	reg2Config = 0x01;
	// Start The Bus
	i2c1Start();
	// Wait for the bus stop
	// this signal that the whole config went trhough
	while(i2c1State != CONFIG_IDLE){
		printToUart2("Out of 2nd I: %d\n\r",i2c1State);
	}

	// Put some huge delays to wait for Magnetometer power-up without the need of a timer
	// 5 milliseconds are expected for power-up
	for( i = 0; i < 15; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}	
	
	printToUart2("Changed To %s\n\r","0.7 Gain");
	


	// Change the mode to continous
	// Change the register to config
	reg2Config = 0x02;
	// Start The Bus
	i2c1Start();
	// Wait for the bus stop
	// this signal that the whole config went trhough
	while(i2c1State != READ_IDLE){
		printToUart2("Out of 3rd I: %d\n\r",i2c1State);
	}

	// Put some huge delays to wait for Magnetometer power-up without the need of a timer
	// 5 milliseconds are expected for power-up
	for( i = 0; i < 15; i += 1 ){
		for( j = 0; j < 32700; j += 1 )
		{
			Nop();
		}
	}	
	
	printToUart2("Changed To %s\n\r","Contrinous");





	byteRead = 1;
	wordRead = 0;
	debugCount = 0;
}

void startMagRead (void) {
	i2c1State = READ_IDLE;
	byteRead = 1;
	wordRead = 0;
	debugCount = 0;
	i2c1Start();
	
}

void readMag (unsigned char idx, short val){
	magReading[idx].shData	= val;
	
	if (idx == 2){
		/*rawControlData.magX.usData = magReading[0].usData;
		rawControlData.magY.usData = magReading[1].usData;
		rawControlData.magZ.usData = magReading[2].usData;*/
		//printToUart2("==dc:%u\n\r", debugCount);
		printToUart2("%d\t %d\t %d\n\r",magReading[0].shData, magReading[1].shData,magReading[2].shData);
	}
}

void getMag (short * magVals){
	//tUnsignedShortToChar placeTest, placeTest2;
	
	magVals[0] =  magReading[0].shData;
	magVals[1] =  magReading[1].shData;
	magVals[2] =  magReading[2].shData;
	//printToUart2("%u\t %u\t %u\n\r",magVals[0], magVals[1],magVals[2]);
	
	/*placeTest.chData[0] = 1;
	placeTest.chData[1] = 0;
	
	
	placeTest2.chData[0] = 0;
	placeTest2.chData[1] = 1;
		
	
	printToUart2("%u\t %u\n\r",placeTest.usData, placeTest2.usData);
	The Above line produces:
		1		256
	therefore, chData[0]= LSB and chData[1]=MSB
	*/
	
	startMagRead();
}

// I2C Primitives
// ==============

void i2c1Start(void){
	// Change the mode to start
	i2c1State = i2c1State == CONFIG_IDLE? CONFIG_START : READ_START;
	// Start the bus
	I2C1CONbits.SEN =1;  
}

void i2c1Stop(void){
	// Change the mode to start
	i2c1State = i2c1State == CONFIG_DONE? CONFIG_STOP : READ_STOP;
	// Stop the bus
	I2C1CONbits.PEN =1;  
}
void i2c1Write(unsigned char byte2write){
	// Send the data
	I2C1TRN = byte2write;
}



void __attribute__((__interrupt__, no_auto_psv)) _MI2C1Interrupt(void){
	//printToUart2("==== Stat: %d\n\r",i2c1State);
	//printToUart2("at:%d rb:%d \n\r",I2C1STATbits.ACKSTAT, I2C1STATbits.RBF);
	//printToUart2("br:%d wr:%d \n\r",byteRead, wordRead);
		
	switch (i2c1State) {
		case CONFIG_START:
			if (!I2C1CONbits.SEN){
				// change the state
				i2c1State = CONFIG_IDTX;
				// Send the address to write
				i2c1Write(0x3C);
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
				if (reg2Config==0){
					// send the actual configuration for 50Hz
					i2c1Write(0x18);
				} else {
					// send the configuration for continuous sampling
					i2c1Write(0x00);
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
				if (reg2Config!=0x02){
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
				i2c1Write(0x3D);
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
				//printToUart2("br:%d wr:%d dc:%d\n\r",byteRead, wordRead,debugCount);
				debugCount++;
				// read the received Data
				if (debugCount < 7) {
					currentMag.chData[byteRead] = (unsigned char)I2C1RCV;
					//printToUart2("byte:%d\n\r", I2C1RCV);
				} else {
					wordRead= (unsigned char)I2C1RCV;
					byteRead = 1;
					printToUart2("ignored:%d\n\r", I2C1RCV);
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
				if (debugCount >= 7 ){
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
				if (debugCount < 7){
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

	IFS1bits.MI2C1IF = 0;			// Clear the master interrupt
	I2C1STATbits.IWCOL = 0;			// Clear the collision flag just in case		
}

void printToUart2 (const char *fmt, ...){
	va_list ap;
	char buf [300];
	
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end (ap);
	putsUART2((unsigned int*)buf);
}

/*
		case READ_START:
			if (!I2C1CONbits.SEN){
				// change the state
				i2c1State = READ_IDTX;
				// Send the address to write
				i2c1Write(0x3D);
			}		
		break;
		case READ_IDTX:
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = READ_RESTART;
				// Generate a Restart Event
				I2C1CONbits.RSEN = 1;
			}		
		break;
		case READ_RESTART:
			if (!I2C1CONbits.RSEN){
				// change the state
				i2c1State = READ_REGADD;
				// Write the Register address
				i2c1Write(0x03);
			}		
		break;	
		case READ_REGADD:
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = READ_DATA;
				// Enable reading
				I2C1CONbits.RCEN = 1;
			}		
		break;	
		case READ_DATA:
			if (!I2C1STATbits.RBF){
				// read the received Data
				currentMag.chData[byteRead] = (unsigned char)I2C1RCV;
				// if we just read a word (i.e. byteRead == 1)
				if(byteRead == 1)
				{
					readMag(wordRead,currentMag.usData);
					wordRead++;
				}
				
				// flip the byte
				byteRead = !byteRead;
				
				if (wordRead >= 3){
					// change the state
					i2c1State = READ_DONE;
					i2c1Stop();					
				} else {
					// Enable reading
					I2C1CONbits.RCEN = 1;					
				}
				
			}		
		break;	
		case READ_STOP:
			if (!I2C1CONbits.PEN){
				// Ready to read next magnetometer data
				i2c1State = READ_IDLE;				
			}
		break;	
*/


/*
		case READ_START:
			if (!I2C1CONbits.SEN){
				// change the state
				i2c1State = READ_IDTX;
				// Send the address to write
				i2c1Write(0x3D);
			}		
		break;
		case READ_IDTX:
			//if (!I2C1CONbits.RSEN){
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = READ_REGADD;
				// Write the Register address
				i2c1Write(0x02);
			}		
		break;	
		case READ_REGADD:
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = READ_RESTART;
				// Enable reading
				I2C1CONbits.SEN =1;
			}		
		break;	
		case READ_RESTART:
			if (!I2C1CONbits.SEN){
				// change the state
				i2c1State = READ_IDADD2;
				// Send the address to write
				i2c1Write(0x3D);
			}
		break;
		case READ_IDADD2:
			if (!I2C1STATbits.ACKSTAT){
				// change the state
				i2c1State = READ_DATA;
				// Enable reading
				I2C1CONbits.RCEN = 1;
			}		
		break;	
		case READ_DATA:
			if (I2C1STATbits.RBF){
				debugCount++;
				// read the received Data
				if (debugCount < 7) {
					currentMag.chData[byteRead] = (unsigned char)I2C1RCV;
					printToUart2("byte:%d", I2C1RCV);
				} else {
					wordRead= (unsigned char)I2C1RCV;
					byteRead = 1;
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
				
				if (wordRead >= 3){
				//if (debugCount < 7 ){
					// Done Generate a NACK 
					I2C1CONbits.ACKDT = 1;
		            I2C1CONbits.ACKEN = 1;
				} else {
					// Generate the AKN
					I2C1CONbits.ACKDT = 0;
            		I2C1CONbits.ACKEN = 1;
				}
			} else if (!I2C1STATbits.ACKSTAT){
				if (wordRead < 3){
				//if (debugCount < 7){
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

*/


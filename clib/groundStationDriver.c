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

#include "groundStationDriver.h"

struct CircBuffer com1BufferIn;
CBRef uartBufferIn;

struct CircBuffer com1BufferOut;
CBRef uartBufferOut;

struct CircBuffer gsParseBuffer;
CBRef gsBuffer;

unsigned int BufferB[MAXSEND] __attribute__((space(dma))) = {0};

// UART, DMA and Buffer initialization
void uart1Init (void){
	// initialize the circular buffers
	uartBufferIn = (struct CircBuffer* )&com1BufferIn;
	newCircBuffer(uartBufferIn);

	uartBufferOut = (struct CircBuffer* )&com1BufferOut;
	newCircBuffer(uartBufferOut);
	
	gsBuffer = (struct CircBuffer* )&gsParseBuffer;
	newCircBuffer(gsBuffer);
	
	// DMA1REQ Register
	// ================
	DMA1REQ = 0x001F;
	
	// DMA1PAD Register
	// ================
	DMA1PAD = (volatile unsigned int) &U2TXREG;
	
	// DMA1CON Register
	// ================
	DMA1CONbits.AMODE   = 0;        // Register Indirect with post-increment
	DMA1CONbits.MODE    = 1;        // One-shot, No Ping-Pong Mode	
	DMA1CONbits.DIR     = 1;        // Read from RAM and send to Periphereal
	DMA1CONbits.SIZE    = 0;        // Word Data Transfer

	// DMA1CNT Register
	// ==============
	DMA1CNT = LOGSEND-1;

	// DMA1STA Register
	// ================
	DMA1STA= __builtin_dmaoffset(BufferB);

	// Enable DMA1 TX interrupts
	IFS0bits.DMA1IF  = 0;			// Clear DMA Interrupt Flag
	IPC3bits.DMA1IP  = 6;			// interrupt priority to 6
	IEC0bits.DMA1IE  = 1;			// Enable DMA interrupt
	
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
	U2STAbits.URXISEL	= 0;		// RX interrupt when a char is in
	U2STAbits.OERR		= 0;		// clear overun error
	
	// U1BRG Register
	// ==============
	U2BRG = LOG_UBRG;				// Set the baud rate for 115,200
	
	// Initialize the Interrupt  
  	// ========================
	IPC7bits.U2RXIP   = 6;    		// Interrupt priority 6  
  	IFS1bits.U2RXIF   = 0;    		// Clear the interrupt flag
  	IEC1bits.U2RXIE   = 1;    		// Enable interrupts

	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
	
	IEC4bits.U2EIE 		= 0;
	
}

void controlMCUInit(void){
	unsigned char eepInitMsg = 0;
	
	// Initialize the SPI Port for IPC
	spiSlaveInit();
	
	// initialize the Protocol Parser and Decoder
	protParserInit();
	
	// Initialize the UART1 port for Telemetry
	uart1Init();
	
	// Initialize EEPROM emulator
	EEPInit();
	
	// Load Data from EEPROM if the initialization worked
	if (aknControlData.pidCal==0){
	   loadEEPData();
	}
	
	// Control MCU boot procedures
	#ifdef _IN_PC_
		//
	#else
		aknControlData.reboot = 1;		
	#endif
	
}

void EEPInit(void){
	unsigned char eepInitMsg = 0;
	
	// Initialize the EEPROM emulation and read the PID Data
	eepInitMsg = DataEEInit();
	
	if (eepInitMsg == 1){
		aknControlData.pidCal = PIDEEP_PAGE_EXP; // Page Expired
	} else if (eepInitMsg == 6){
		aknControlData.pidCal = PIDEEP_MEMORY_CORR; // Memory Corrupted
	}
}

void loadEEPData(void){
	unsigned char i;
	
	for(  i = 0; i < 10; i++ )
	{
		// PID Gains
		pidControlData.P[i].shData[0]= DataEERead(PID_OFFSET+i*6);
		pidControlData.P[i].shData[1]= DataEERead(PID_OFFSET+i*6+1);
		pidControlData.I[i].shData[0]= DataEERead(PID_OFFSET+i*6+2);
		pidControlData.I[i].shData[1]= DataEERead(PID_OFFSET+i*6+3);
		pidControlData.D[i].shData[0]= DataEERead(PID_OFFSET+i*6+4);
		pidControlData.D[i].shData[1]= DataEERead(PID_OFFSET+i*6+5);
		
		// Way Points
		wpsControlData.lat[i].shData[0]= DataEERead(WPS_OFFSET+i*8);   
		wpsControlData.lat[i].shData[1]= DataEERead(WPS_OFFSET+i*8+1);      
		wpsControlData.lon[i].shData[0]= DataEERead(WPS_OFFSET+i*8+2);      
		wpsControlData.lon[i].shData[1]= DataEERead(WPS_OFFSET+i*8+3);      
		wpsControlData.hei[i].shData[0]= DataEERead(WPS_OFFSET+i*8+4);      
		wpsControlData.hei[i].shData[1]= DataEERead(WPS_OFFSET+i*8+5);      
		wpsControlData.typ[i]		  = (unsigned char)DataEERead(WPS_OFFSET+i*8+6);
		wpsControlData.val[i].shData   = DataEERead(WPS_OFFSET+i*8+7);         	
	}
	// load WP 11 that contains the GS location
	i = 10;
	wpsControlData.lat[i].shData[0]= DataEERead(WPS_OFFSET+i*8);   
	wpsControlData.lat[i].shData[1]= DataEERead(WPS_OFFSET+i*8+1);      
	wpsControlData.lon[i].shData[0]= DataEERead(WPS_OFFSET+i*8+2);      
	wpsControlData.lon[i].shData[1]= DataEERead(WPS_OFFSET+i*8+3);      
	wpsControlData.hei[i].shData[0]= DataEERead(WPS_OFFSET+i*8+4);      
	wpsControlData.hei[i].shData[1]= DataEERead(WPS_OFFSET+i*8+5);      
	wpsControlData.typ[i]		  = (unsigned char)DataEERead(WPS_OFFSET+i*8+6);
	wpsControlData.val[i].shData   = DataEERead(WPS_OFFSET+i*8+7);         	

	// Compute the waypoint count
	i = 0;
	while ((int)(wpsControlData.lat[i].flData) != 0 && i < 9 ) i++;{
		wpsControlData.wpCount = i;
	}
}

void gsRead(unsigned char* gsChunk){
	// fix the data length so if the interrupt adds data
	// during execution of this block, it will be read
	// until the next gsRead
	unsigned int tmpLen = getLength(uartBufferIn), i=0;
	
	// if the buffer has more data than the max size, set it to max,
	// otherwise set it to the length
	gsChunk[0] =  (tmpLen > MAXSEND -1)? MAXSEND -1: tmpLen;
	
	// read the data 
	for(i = 1; i <= gsChunk[0]; i += 1 )
	{
		gsChunk[i] = readFront(uartBufferIn);
	}
}


// VERY IMPORTANT NOTE
// ===================
// THIS PROCEDURE ALSO EXISTS IN THE SENSOR MCU IN A
// DIFFERENT FILE (LOGDATA.C ) THEY ARE DUPLICATED 
// HERE TO KEEP SENSOR MCU AND CONTROL MCU FILES COMPLETELY
// INDEPENDENT
//
// IT WILL BE REPLICATED TO A STANDARD LIBRARY TIME PERMITTING
void protParseDecodeGS(unsigned char* fromSPI){
	// Static variables CAREFUL
	static unsigned char prevBufferGS[2*MAXLOGLEN];
	static unsigned char previousCompleteGS =1;
	static unsigned char indexLastGS = 0;
	
	// local variables 
	unsigned char i;
	unsigned char tmpChksum = 0, headerFound=0, noMoreBytes = 1;
	unsigned char trailerFound = 0;

	//unsigned char logSize = 0;
	
	// Add the received bytes to the protocol parsing circular buffer
    for(i = 1; i <= fromSPI[0]; i += 1 )
    //for(i = 0; i <= 95; i += 1 )
	{
		writeBack(gsBuffer, fromSPI[i]);
	}
	
	// update the noMoreBytes flag accordingly
   noMoreBytes = (fromSPI[0]>0)?0:1;
   // noMoreBytes = 0;
	
	while (!noMoreBytes){
		// if the previous message was complete then read from the circular buffer
		// and make sure that you are into the begining of a message
		if(previousCompleteGS){
			while (!headerFound && !noMoreBytes) {
				// move along until you find a dollar sign or run out of bytes
				while (getLength(gsBuffer)>1 && peak(gsBuffer)!=DOLLAR){
					readFront(gsBuffer);
				}			
				// if you found a dollar then make sure the next one is an AT
				if(getLength(gsBuffer)>1 && peak(gsBuffer) == DOLLAR){
					// read it
					prevBufferGS[indexLastGS++] = readFront(gsBuffer);
                    // if next is a at sign
					if (peak(gsBuffer) == AT){
						// read it
						prevBufferGS[indexLastGS++] = readFront(gsBuffer);
						// and signal you found a header
						headerFound = 1;
                         // and set as  incomplete the sentece
                         previousCompleteGS = 0;
					}
				} else {
					noMoreBytes = 1;
				} // else no dollar				
			} // while we found header && no more bytes
		}// if previous complete
		
		// At this point either you found a header from a previous complete
		// or you are reading from a message that was incomplete the last time
		// in any of those two cases, keep reading until you run out of bytes
		// or find a STAR and an AT
		while (!trailerFound && !noMoreBytes){
			while (getLength(gsBuffer)>2 && peak(gsBuffer)!=STAR){
				prevBufferGS[indexLastGS++] = readFront(gsBuffer);
			}
			// if you found a STAR (42) and stil have bytes
			if (getLength(gsBuffer)>2 && peak(gsBuffer)==STAR){
				// read it
				prevBufferGS[indexLastGS++] = readFront(gsBuffer);
				// if you still have 2 bytes
				if (getLength(gsBuffer)>1){
					// and the next byte is an AT sign
					if (peak(gsBuffer)==AT){
						// then you found a trailer
						trailerFound =1;
					}
				} else {
					noMoreBytes =1;
				}
			} else {
				// no more bytes
				noMoreBytes =1;
			} 
		}
		
		// if you found a trailer, then the message is done
		if(trailerFound){
			// read the AT and the checksum
			prevBufferGS[indexLastGS++] = readFront(gsBuffer);
			prevBufferGS[indexLastGS] = readFront(gsBuffer);

			// Compute the checksum
			tmpChksum= getChecksum(prevBufferGS, indexLastGS-1);
	
			// if the checksum is valid
			if (tmpChksum ==prevBufferGS[indexLastGS]){
				// update the states depending on the message
				updateStates(&prevBufferGS[0]);
				// Copy the data to the out buffer for logging purposes
				// increment the log size
				//logSize += (indexLastGS+1);
			}
            else{
             indexLastGS = 1; // just to stop debugger
            }
            // get everything ready to start all-over
			previousCompleteGS =1;
			indexLastGS = 0;
            headerFound = 0;
            trailerFound = 0;
            memset(prevBufferGS, 0, sizeof(prevBufferGS));

		}else { // you ran out of bytes
			// No More Bytes
			noMoreBytes = 1;
		}// else no star	
	} // big outer while (no more bytes)
}

/*
	TODO: This function needs to be merged with logData
	in dataLogger.c and moved to something like
	apUtils.c
	
*/



void prepareTelemetry( unsigned char* dataOut){
	unsigned char rawSentence[35];
	
	// sampleTelemetry variable is the one that cycles from 1 to 10 to decide which 
	// message's turn is to be sent
	static unsigned char sampleTelemetry = 1;
	
	static unsigned char scheduleBiases = 1;
	
	static unsigned char telemetryBuf [37];
	
	
	// temp var to store the assembled message
	unsigned char i;
	
	// this variable sets the lenght of the telemetry to be sent
	unsigned char len2Telemetry=0;
	
	
	unsigned char bufLen = 0;
	
	//TODO: Remove 
	tFloatToChar val1, val2, val3;
	
	memset(telemetryBuf, 0, sizeof(telemetryBuf));
		
	switch (sampleTelemetry){
		case 1: // GPS				
			rawSentence[0] =  gpsControlData.year	;			
			rawSentence[1] =  gpsControlData.month	;		
			rawSentence[2] =  gpsControlData.day	;			
			rawSentence[3] =  gpsControlData.hour	;			
			rawSentence[4] =  gpsControlData.min	;			
			rawSentence[5] =  gpsControlData.sec	;			
			rawSentence[6] = gpsControlData.lat.chData[0];	
			rawSentence[7] = gpsControlData.lat.chData[1];	
			rawSentence[8] = gpsControlData.lat.chData[2];				
			rawSentence[9] = gpsControlData.lat.chData[3];			
			rawSentence[10] = gpsControlData.lon.chData[0];	
			rawSentence[11] = gpsControlData.lon.chData[1];	
			rawSentence[12] = gpsControlData.lon.chData[2];	
			rawSentence[13] = gpsControlData.lon.chData[3];	
			rawSentence[14] = gpsControlData.height.chData[0];		
			rawSentence[15] = gpsControlData.height.chData[1];	
			rawSentence[16] = gpsControlData.height.chData[2];		
			rawSentence[17] = gpsControlData.height.chData[3];	
			rawSentence[18] = gpsControlData.cog.chData[0];	
			rawSentence[19] = gpsControlData.cog.chData[1];	
			rawSentence[20] = gpsControlData.sog.chData[0];	
			rawSentence[21] = gpsControlData.sog.chData[1];	
			rawSentence[22] = gpsControlData.hdop.chData[0];	
			rawSentence[23] = gpsControlData.hdop.chData[1];	
			rawSentence[24] = gpsControlData.fix			;	
			rawSentence[25] = gpsControlData.sats			;	
			rawSentence[26] = gpsControlData.newValue		;	
					
			// assemble the GPS data for protocol sending
			assembleMsg(&rawSentence[0], GPSMSG_LEN, GPSMSG_ID, telemetryBuf);

			// add it to the out Array
			for( i = 0; i < GPSMSG_LEN+7; i += 1 ){
				dataOut[i+1] = telemetryBuf[i];
			}					

			// set the total data out for log
			len2Telemetry = GPSMSG_LEN+7; 

			break;

		case 2: // LOAD and PWM
			
			rawSentence[0] = statusControlData.load		 	;
			rawSentence[1] = statusControlData.vdetect	 	;
			rawSentence[2] = statusControlData.bVolt.chData[0] ;
			rawSentence[3] = statusControlData.bVolt.chData[1] ;
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], LOADMSG_LEN, LOADMSG_ID, telemetryBuf);

			// add it to the out Array
			for( i = 0; i < LOADMSG_LEN+7; i += 1 ){
				dataOut[i+1] = telemetryBuf[i];
			}					

			// set the total data out for log
			len2Telemetry = LOADMSG_LEN+7; 
			
			// if the HIL is on, pwmControlData will be sent every cycle
			// so dont send it here
			if (!apsControlData.hilStatus){
				// clear the buffer for next sentence
				memset(telemetryBuf, 0, sizeof(telemetryBuf));
			
				rawSentence[0]	=	pwmControlData.dt_c.chData[0]	;	
				rawSentence[1]	=	pwmControlData.dt_c.chData[1]	; 	
				rawSentence[2]	=	pwmControlData.dla_c.chData[0]	;		 	
				rawSentence[3]	=	pwmControlData.dla_c.chData[1]	; 
				rawSentence[4]	=	pwmControlData.dra_c.chData[0]	;	 
				rawSentence[5]	=	pwmControlData.dra_c.chData[1]	;	 
				rawSentence[6]	=	pwmControlData.dr_c.chData[0]	;	 
				rawSentence[7]	=	pwmControlData.dr_c.chData[1]	;	   
				rawSentence[8]	=	pwmControlData.dle_c.chData[0]	;	  
				rawSentence[9]	=	pwmControlData.dle_c.chData[1]	;	  
				rawSentence[10]	=	pwmControlData.dre_c.chData[0]	;	  
				rawSentence[11]	=	pwmControlData.dre_c.chData[1]	;	  
				rawSentence[12]	=	pwmControlData.dlf_c.chData[0]	;	  
				rawSentence[13]	=	pwmControlData.dlf_c.chData[1]	;	  
				rawSentence[14]	=	pwmControlData.drf_c.chData[0]	;	  
				rawSentence[15]	=	pwmControlData.drf_c.chData[1]	;	  
				rawSentence[16]	=	pwmControlData.da1_c.chData[0]	;	  
				rawSentence[17]	=	pwmControlData.da1_c.chData[1]	;	  
				rawSentence[18]	=	pwmControlData.da2_c.chData[0]	;	  
				rawSentence[19]	=	pwmControlData.da2_c.chData[1]	;	  
			
				// assemble the Diag data for protocol sending
				assembleMsg(&rawSentence[0], PWMMSG_LEN, PWMMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < PWMMSG_LEN+7; i += 1 ){
					dataOut[i+1+len2Telemetry] = telemetryBuf[i];
				}					

				// set the total data out for log
				len2Telemetry += PWMMSG_LEN+7; 
			}		
		break;

		case 3: // Raw, XYZ, or diagnostic depending on logging config
			#if defined(LOGRAW100) || defined (DIAG100) 	// If log raw or diag at 100 Hz, then send XYZ here
				rawSentence[0] = xyzControlData.Xcoord.chData[0];
				rawSentence[1] = xyzControlData.Xcoord.chData[1];
				rawSentence[2] = xyzControlData.Xcoord.chData[2];
				rawSentence[3] = xyzControlData.Xcoord.chData[3];
				rawSentence[4] = xyzControlData.Ycoord.chData[0];	
				rawSentence[5] = xyzControlData.Ycoord.chData[1];	
				rawSentence[6] = xyzControlData.Ycoord.chData[2];	
				rawSentence[7] = xyzControlData.Ycoord.chData[3];	
				rawSentence[8] = xyzControlData.Zcoord.chData[0];
				rawSentence[9] = xyzControlData.Zcoord.chData[1];
				rawSentence[10]= xyzControlData.Zcoord.chData[2];
				rawSentence[11]= xyzControlData.Zcoord.chData[3];
				rawSentence[12]= xyzControlData.VX.chData[0]	;	
				rawSentence[13]= xyzControlData.VX.chData[1]	;	
				rawSentence[14]= xyzControlData.VX.chData[2]	;	
				rawSentence[15]= xyzControlData.VX.chData[3]	;	
				rawSentence[16]= xyzControlData.VY.chData[0]	;	
				rawSentence[17]= xyzControlData.VY.chData[1]	;	
				rawSentence[18]= xyzControlData.VY.chData[2]	;	
				rawSentence[19]= xyzControlData.VY.chData[3]	;	
				rawSentence[20]= xyzControlData.VZ.chData[0]	;	
				rawSentence[21]= xyzControlData.VZ.chData[1]	;	
				rawSentence[22]= xyzControlData.VZ.chData[2]	;	
				rawSentence[23]= xyzControlData.VZ.chData[3]	;	
						
				// assemble the XYZ data for protocol sending
				assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}					

				// set the total data out for log
				len2Telemetry = XYZMSG_LEN+7; 		

			#else // if XYZ is sent at 100Hz then send raw here at 10 hz
	
				rawSentence[0] 	=	rawControlData.gyroX.chData[0];	
				rawSentence[1]  =	rawControlData.gyroX.chData[1];	
				rawSentence[2] 	=	rawControlData.gyroY.chData[0];		 	
				rawSentence[3]  =	rawControlData.gyroY.chData[1];	
				rawSentence[4] 	=	rawControlData.gyroZ.chData[0];	 
				rawSentence[5] 	=	rawControlData.gyroZ.chData[1];	 
				rawSentence[6] =	rawControlData.accelX.chData[0];	 
				rawSentence[7] =	rawControlData.accelX.chData[1];	   
				rawSentence[8] =	rawControlData.accelY.chData[0];	  
				rawSentence[9] =	rawControlData.accelY.chData[1];	  
				rawSentence[10] =	rawControlData.accelZ.chData[0];	  
				rawSentence[11] =	rawControlData.accelZ.chData[1];	  
				rawSentence[12] =	rawControlData.magX.chData[0];	  
				rawSentence[13] =	rawControlData.magX.chData[1];	  
				rawSentence[14] =	rawControlData.magY.chData[0];	  
				rawSentence[15] =	rawControlData.magY.chData[1];	  
				rawSentence[16] =	rawControlData.magZ.chData[0];	  
				rawSentence[17] =	rawControlData.magZ.chData[1];	
				// included in SLUGS MKII
				rawSentence[18] =	rawControlData.baro.chData[0];	  
				rawSentence[19] =	rawControlData.baro.chData[1];	
				rawSentence[20] =	rawControlData.pito.chData[0];	  
				rawSentence[21] =	rawControlData.pito.chData[1];	
				rawSentence[22] =	rawControlData.powr.chData[0];	  
				rawSentence[23] =	rawControlData.powr.chData[1];
				rawSentence[24] =	rawControlData.ther.chData[0];	  
				rawSentence[25] =	rawControlData.ther.chData[1];

				// assemble the Attitude data for protocol sending
				assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, telemetryBuf);
	
				// add it to the circular buffer and SPI queue
				for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}					
	
				// set the total data out for SPI			
				len2Telemetry= RAWMSG_LEN+7; 

			#endif	

		break;
			
		case 4: // Dynamic and pilot Console	
		
			rawSentence[0] = dynTempControlData.dynamic.chData[0];
			rawSentence[1] = dynTempControlData.dynamic.chData[1];
			rawSentence[2] = dynTempControlData.dynamic.chData[2];
			rawSentence[3] = dynTempControlData.dynamic.chData[3];
			rawSentence[4] = dynTempControlData.stat.chData[0]	;	
			rawSentence[5] = dynTempControlData.stat.chData[1]	;	
			rawSentence[6] = dynTempControlData.stat.chData[2]	;	
			rawSentence[7] = dynTempControlData.stat.chData[3]	;	
			rawSentence[8] = dynTempControlData.temp.chData[0]	;
			rawSentence[9] = dynTempControlData.temp.chData[1]	;
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], DYNMSG_LEN, DYNMSG_ID, telemetryBuf);

			// add it to the out Array
			for( i = 0; i < DYNMSG_LEN+7; i += 1 ){
				dataOut[i+1] = telemetryBuf[i];
			}					

			// set the total data out for SPI
			len2Telemetry = DYNMSG_LEN+7; 

			// clear the buffer for next sentence
			memset(telemetryBuf, 0, sizeof(telemetryBuf));
			
			rawSentence[0] = pilControlData.dt.chData[0]	;
			rawSentence[1] = pilControlData.dt.chData[1]	;
			rawSentence[2] = pilControlData.dla.chData[0];
			rawSentence[3] = pilControlData.dla.chData[1];
			rawSentence[4] = pilControlData.dra.chData[0];
			rawSentence[5] = pilControlData.dra.chData[1];
			rawSentence[6] = pilControlData.dr.chData[0]	;
			rawSentence[7] = pilControlData.dr.chData[1]	;
			rawSentence[8] = pilControlData.de.chData[0]	;
			rawSentence[9] = pilControlData.de.chData[1]	;
			
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], PILMSG_LEN, PILMSG_ID, telemetryBuf);

			// add it to the out Array
			for( i = 0; i < PILMSG_LEN+7; i += 1 ){
				dataOut[i+1+len2Telemetry] = telemetryBuf[i];
			}					

			// set the total data out for log
			len2Telemetry += PILMSG_LEN+7; 

		break;
		
		case 5: // Bias		
			if (1 == scheduleBiases){
				rawSentence[0] = biasControlData.axb.chData[0] ;
				rawSentence[1] = biasControlData.axb.chData[1] ;
				rawSentence[2] = biasControlData.axb.chData[2] ;
				rawSentence[3] = biasControlData.axb.chData[3] ;
				rawSentence[4] = biasControlData.ayb.chData[0] ;	
				rawSentence[5] = biasControlData.ayb.chData[1] ;	
				rawSentence[6] = biasControlData.ayb.chData[2] ;	
				rawSentence[7] = biasControlData.ayb.chData[3] ;	
				rawSentence[8] = biasControlData.azb.chData[0] ;
				rawSentence[9] = biasControlData.azb.chData[1] ;
				rawSentence[10]= biasControlData.azb.chData[2];
				rawSentence[11]= biasControlData.azb.chData[3];
				rawSentence[12]= biasControlData.gxb.chData[0];	
				rawSentence[13]= biasControlData.gxb.chData[1];	
				rawSentence[14]= biasControlData.gxb.chData[2];	
				rawSentence[15]= biasControlData.gxb.chData[3];	
				rawSentence[16]= biasControlData.gyb.chData[0];	
				rawSentence[17]= biasControlData.gyb.chData[1];	
				rawSentence[18]= biasControlData.gyb.chData[2];	
				rawSentence[19]= biasControlData.gyb.chData[3];	
				rawSentence[20]= biasControlData.gzb.chData[0];	
				rawSentence[21]= biasControlData.gzb.chData[1];	
				rawSentence[22]= biasControlData.gzb.chData[2];	
				rawSentence[23]= biasControlData.gzb.chData[3];	
						
				// assemble the Diag data for protocol sending
				assembleMsg(&rawSentence[0], BIAMSG_LEN, BIAMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < BIAMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}
				
				// set the total data out for log
				len2Telemetry = BIAMSG_LEN+7; 
			}	else {
				rawSentence[0] = logControlData.fl1.chData[0] ;
				rawSentence[1] = logControlData.fl1.chData[1] ;
				rawSentence[2] = logControlData.fl1.chData[2] ;
				rawSentence[3] = logControlData.fl1.chData[3] ;
				rawSentence[4] = logControlData.fl2.chData[0] ;	
				rawSentence[5] = logControlData.fl2.chData[1] ;	
				rawSentence[6] = logControlData.fl2.chData[2] ;	
				rawSentence[7] = logControlData.fl2.chData[3] ;	
				rawSentence[8] = logControlData.fl3.chData[0] ;
				rawSentence[9] = logControlData.fl3.chData[1] ;
				rawSentence[10]= logControlData.fl3.chData[2];
				rawSentence[11]= logControlData.fl3.chData[3];
				rawSentence[12]= logControlData.fl4.chData[0];	
				rawSentence[13]= logControlData.fl4.chData[1];	
				rawSentence[14]= logControlData.fl4.chData[2];	
				rawSentence[15]= logControlData.fl4.chData[3];	
				rawSentence[16]= logControlData.fl5.chData[0];	
				rawSentence[17]= logControlData.fl5.chData[1];	
				rawSentence[18]= logControlData.fl5.chData[2];	
				rawSentence[19]= logControlData.fl5.chData[3];	
				rawSentence[20]= logControlData.fl6.chData[0];	
				rawSentence[21]= logControlData.fl6.chData[1];	
				rawSentence[22]= logControlData.fl6.chData[2];	
				rawSentence[23]= logControlData.fl6.chData[3];	
						
				// assemble the Diag data for protocol sending
				assembleMsg(&rawSentence[0], LOGMSG_LEN, LOGMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < LOGMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];					
				}
				
				// set the total data out for log
				len2Telemetry = LOGMSG_LEN+7; 
			}
			scheduleBiases= (scheduleBiases>9)? 1 : scheduleBiases+1;
		
		break;

		case 6: // Diagnostic/Raw and Aknowledge
			#if defined(DIAG100)
				rawSentence[0] 	=	rawControlData.gyroX.chData[0];	
				rawSentence[1]  =	rawControlData.gyroX.chData[1];	
				rawSentence[2] 	=	rawControlData.gyroY.chData[0];		 	
				rawSentence[3]  =	rawControlData.gyroY.chData[1];	
				rawSentence[4] 	=	rawControlData.gyroZ.chData[0];	 
				rawSentence[5] 	=	rawControlData.gyroZ.chData[1];	 
				rawSentence[6] =	rawControlData.accelX.chData[0];	 
				rawSentence[7] =	rawControlData.accelX.chData[1];	   
				rawSentence[8] =	rawControlData.accelY.chData[0];	  
				rawSentence[9] =	rawControlData.accelY.chData[1];	  
				rawSentence[10] =	rawControlData.accelZ.chData[0];	  
				rawSentence[11] =	rawControlData.accelZ.chData[1];	  
				rawSentence[12] =	rawControlData.magX.chData[0];	  
				rawSentence[13] =	rawControlData.magX.chData[1];	  
				rawSentence[14] =	rawControlData.magY.chData[0];	  
				rawSentence[15] =	rawControlData.magY.chData[1];	  
				rawSentence[16] =	rawControlData.magZ.chData[0];	  
				rawSentence[17] =	rawControlData.magZ.chData[1];	
				// included in SLUGS MKII
				rawSentence[18] =	rawControlData.baro.chData[0];	  
				rawSentence[19] =	rawControlData.baro.chData[1];	
				rawSentence[20] =	rawControlData.pito.chData[0];	  
				rawSentence[21] =	rawControlData.pito.chData[1];	
				rawSentence[22] =	rawControlData.powr.chData[0];	  
				rawSentence[23] =	rawControlData.powr.chData[1];
				rawSentence[24] =	rawControlData.ther.chData[0];	  
				rawSentence[25] =	rawControlData.ther.chData[1];

				// assemble the Attitude data for protocol sending
				assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, telemetryBuf);
	
				// add it to the circular buffer and SPI queue
				for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}					
	
				// set the total data out for SPI			
				len2Telemetry= RAWMSG_LEN+7; 
			 	
			#else
				rawSentence[0]	=	diagControlData.fl1.chData[0];	
				rawSentence[1]	=	diagControlData.fl1.chData[1];	
				rawSentence[2]	=	diagControlData.fl1.chData[2];	
				rawSentence[3]	=	diagControlData.fl1.chData[3];	
				rawSentence[4]	=	diagControlData.fl2.chData[0];	
				rawSentence[5]	=	diagControlData.fl2.chData[1];	
				rawSentence[6]	=	diagControlData.fl2.chData[2];	
				rawSentence[7]	=	diagControlData.fl2.chData[3];	
				rawSentence[8]	=	diagControlData.fl3.chData[0];	
				rawSentence[9]	=	diagControlData.fl3.chData[1];	
				rawSentence[10]=	diagControlData.fl3.chData[2];	
				rawSentence[11]=	diagControlData.fl3.chData[3];	
				rawSentence[12]=	diagControlData.sh1.chData[0];	
				rawSentence[13]=	diagControlData.sh1.chData[1];	
				rawSentence[14]=	diagControlData.sh2.chData[0];	
				rawSentence[15]=	diagControlData.sh2.chData[1];	
				rawSentence[16]=	diagControlData.sh3.chData[0];	
				rawSentence[17]=	diagControlData.sh3.chData[1];
					 	
						
				// assemble the Diag data for protocol sending
				assembleMsg(&rawSentence[0], DIAMSG_LEN, DIAMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}					

				// set the total data out for log
				len2Telemetry = DIAMSG_LEN+7; 			
				
			#endif
				
			// if one of the aknowledge flags are turned on
			// then the AKN message needs to be sent
			if ((aknControlData.WP>0) || (aknControlData.commands>0) || (aknControlData.pidCal > 0)
				 || (aknControlData.sensorReboot>0) || aknControlData.filOnOff
				 || aknControlData.reboot){
				// clear the buffer for next sentence
				memset(telemetryBuf, 0, sizeof(telemetryBuf));
			
				// set the correct flags
				rawSentence[0] = aknControlData.WP;
				rawSentence[1] = aknControlData.commands;
				rawSentence[2] = aknControlData.pidCal;
				rawSentence[3] = aknControlData.sensorReboot;
				rawSentence[4] = aknControlData.filOnOff;
				rawSentence[5] = aknControlData.reboot;
			
				// assemble the protocol message
				assembleMsg(&rawSentence[0],AKNMSG_LEN, AKNMSG_ID, telemetryBuf);
			
				// add it to the out Array
				for( i = 0; i < AKNMSG_LEN+7; i += 1 ){
					dataOut[i+1+len2Telemetry] = telemetryBuf[i];
				}
			
				// set the length of the message
				len2Telemetry += AKNMSG_LEN+7;
					 							
				// clear the flags
				memset(&aknControlData, 0, sizeof(tAknData));

			} 

			
		break;
		
		case 7: // Pending aknowledge requests OR Sensor Data. If there is a pending request
						// Sensor data will NOT be sent in this sample
			if (queControlData.pendingRequest){
				
				assembleRawSentence (queControlData.idReq, queControlData.indxReq, &rawSentence[0]);

				// assemble the protocol message
				assembleMsg(&rawSentence[0],CALMSG_LEN, CALMSG_ID, telemetryBuf);
				
				// add it to the out Array
				for( i = 0; i < CALMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}
				
				// set the length of the message
				len2Telemetry = CALMSG_LEN+7;
				
				// clear the pending request
				queControlData.pendingRequest = 0;
			} else {
				rawSentence[0] = senControlData.Ax.chData[0] ;
				rawSentence[1] = senControlData.Ax.chData[1] ;
				rawSentence[2] = senControlData.Ax.chData[2] ;
				rawSentence[3] = senControlData.Ax.chData[3] ;
				rawSentence[4] = senControlData.Ay.chData[0] ;	
				rawSentence[5] = senControlData.Ay.chData[1] ;	
				rawSentence[6] = senControlData.Ay.chData[2] ;	
				rawSentence[7] = senControlData.Ay.chData[3] ;	
				rawSentence[8] = senControlData.Az.chData[0] ;
				rawSentence[9] = senControlData.Az.chData[1] ;
				rawSentence[10]= senControlData.Az.chData[2];
				rawSentence[11]= senControlData.Az.chData[3];
				rawSentence[12]= senControlData.Mx.chData[0];	
				rawSentence[13]= senControlData.Mx.chData[1];	
				rawSentence[14]= senControlData.Mx.chData[2];	
				rawSentence[15]= senControlData.Mx.chData[3];	
				rawSentence[16]= senControlData.My.chData[0];	
				rawSentence[17]= senControlData.My.chData[1];	
				rawSentence[18]= senControlData.My.chData[2];	
				rawSentence[19]= senControlData.My.chData[3];	
				rawSentence[20]= senControlData.Mz.chData[0];	
				rawSentence[21]= senControlData.Mz.chData[1];	
				rawSentence[22]= senControlData.Mz.chData[2];	
				rawSentence[23]= senControlData.Mz.chData[3];	
						
				// assemble the data for protocol sending
				assembleMsg(&rawSentence[0], SENMSG_LEN, SENMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < SENMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}					

				// set the total data out for log
				len2Telemetry = SENMSG_LEN+7; 
			}
		break;
		case 8: // AP Status
			rawSentence[0] =  apsControlData.controlType;			
			rawSentence[1] =  apsControlData.beaconStatus;		
			rawSentence[2] =  apsControlData.hilStatus;			
					
			// assemble the GPS data for protocol sending
			assembleMsg(&rawSentence[0], APSMSG_LEN, APSMSG_ID, telemetryBuf);

			// add it to the out Array
			for( i = 0; i < APSMSG_LEN+7; i += 1 ){
				dataOut[i+1] = telemetryBuf[i];
			}					

			// set the total data out for log
			len2Telemetry = APSMSG_LEN+7; 		
		break;
		
		case 9: // This only works when HIL is on
			if (apsControlData.hilStatus){
			#if defined(LOGRAW100) 	// If we need to log raw at 100 Hz
				rawSentence[0] 	=	rawControlData.gyroX.chData[0];	
				rawSentence[1]  =	rawControlData.gyroX.chData[1];	
				rawSentence[2] 	=	rawControlData.gyroY.chData[0];		 	
				rawSentence[3]  =	rawControlData.gyroY.chData[1];	
				rawSentence[4] 	=	rawControlData.gyroZ.chData[0];	 
				rawSentence[5] 	=	rawControlData.gyroZ.chData[1];	 
				rawSentence[6] =	rawControlData.accelX.chData[0];	 
				rawSentence[7] =	rawControlData.accelX.chData[1];	   
				rawSentence[8] =	rawControlData.accelY.chData[0];	  
				rawSentence[9] =	rawControlData.accelY.chData[1];	  
				rawSentence[10] =	rawControlData.accelZ.chData[0];	  
				rawSentence[11] =	rawControlData.accelZ.chData[1];	  
				rawSentence[12] =	rawControlData.magX.chData[0];	  
				rawSentence[13] =	rawControlData.magX.chData[1];	  
				rawSentence[14] =	rawControlData.magY.chData[0];	  
				rawSentence[15] =	rawControlData.magY.chData[1];	  
				rawSentence[16] =	rawControlData.magZ.chData[0];	  
				rawSentence[17] =	rawControlData.magZ.chData[1];	
				// included in SLUGS MKII
				rawSentence[18] =	rawControlData.baro.chData[0];	  
				rawSentence[19] =	rawControlData.baro.chData[1];	
				rawSentence[20] =	rawControlData.pito.chData[0];	  
				rawSentence[21] =	rawControlData.pito.chData[1];	
				rawSentence[22] =	rawControlData.powr.chData[0];	  
				rawSentence[23] =	rawControlData.powr.chData[1];
				rawSentence[24] =	rawControlData.ther.chData[0];	  
				rawSentence[25] =	rawControlData.ther.chData[1];		
	
				// assemble the Attitude data for protocol sending
				assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, telemetryBuf);
	
				// add it to the circular buffer and SPI queue
				for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
					dataOut[i+1+len2Telemetry] = telemetryBuf[i];
				}					
	
				// set the total data out for SPI			
				len2Telemetry+= RAWMSG_LEN+7; 			
  			
			#elif  defined(DIAG100) //if we want diagnostics at 100
				rawSentence[0]	=	diagControlData.fl1.chData[0];	
				rawSentence[1]	=	diagControlData.fl1.chData[1];	
				rawSentence[2]	=	diagControlData.fl1.chData[2];	
				rawSentence[3]	=	diagControlData.fl1.chData[3];	
				rawSentence[4]	=	diagControlData.fl2.chData[0];	
				rawSentence[5]	=	diagControlData.fl2.chData[1];	
				rawSentence[6]	=	diagControlData.fl2.chData[2];	
				rawSentence[7]	=	diagControlData.fl2.chData[3];	
				rawSentence[8]	=	diagControlData.fl3.chData[0];	
				rawSentence[9]	=	diagControlData.fl3.chData[1];	
				rawSentence[10]=	diagControlData.fl3.chData[2];	
				rawSentence[11]=	diagControlData.fl3.chData[3];	
				rawSentence[12]=	diagControlData.sh1.chData[0];	
				rawSentence[13]=	diagControlData.sh1.chData[1];	
				rawSentence[14]=	diagControlData.sh2.chData[0];	
				rawSentence[15]=	diagControlData.sh2.chData[1];	
				rawSentence[16]=	diagControlData.sh3.chData[0];	
				rawSentence[17]=	diagControlData.sh3.chData[1];
					 	
						
				// assemble the Diag data for protocol sending
				assembleMsg(&rawSentence[0], DIAMSG_LEN, DIAMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
					dataOut[i+1] = telemetryBuf[i];
				}					

				// set the total data out for log
				len2Telemetry = DIAMSG_LEN+7; 		
						
			#else
				rawSentence[0] = xyzControlData.Xcoord.chData[0];
				rawSentence[1] = xyzControlData.Xcoord.chData[1];
				rawSentence[2] = xyzControlData.Xcoord.chData[2];
				rawSentence[3] = xyzControlData.Xcoord.chData[3];
				rawSentence[4] = xyzControlData.Ycoord.chData[0];	
				rawSentence[5] = xyzControlData.Ycoord.chData[1];	
				rawSentence[6] = xyzControlData.Ycoord.chData[2];	
				rawSentence[7] = xyzControlData.Ycoord.chData[3];	
				rawSentence[8] = xyzControlData.Zcoord.chData[0];
				rawSentence[9] = xyzControlData.Zcoord.chData[1];
				rawSentence[10]= xyzControlData.Zcoord.chData[2];
				rawSentence[11]= xyzControlData.Zcoord.chData[3];
				rawSentence[12]= xyzControlData.VX.chData[0]	;	
				rawSentence[13]= xyzControlData.VX.chData[1]	;	
				rawSentence[14]= xyzControlData.VX.chData[2]	;	
				rawSentence[15]= xyzControlData.VX.chData[3]	;	
				rawSentence[16]= xyzControlData.VY.chData[0]	;	
				rawSentence[17]= xyzControlData.VY.chData[1]	;	
				rawSentence[18]= xyzControlData.VY.chData[2]	;	
				rawSentence[19]= xyzControlData.VY.chData[3]	;	
				rawSentence[20]= xyzControlData.VZ.chData[0]	;	
				rawSentence[21]= xyzControlData.VZ.chData[1]	;	
				rawSentence[22]= xyzControlData.VZ.chData[2]	;	
				rawSentence[23]= xyzControlData.VZ.chData[3]	;	
						
				// assemble the Diag data for protocol sending
				assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, telemetryBuf);

				// add it to the out Array
				for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
					dataOut[i+1+ len2Telemetry] = telemetryBuf[i];
				}					

				// set the total data out for log
				len2Telemetry += XYZMSG_LEN+7; 
			#endif
			}
			
		break;
		
		case 10: // Nav Sentence 
			rawSentence[0] = navControlData.uMeasured.chData[0];
			rawSentence[1] = navControlData.uMeasured.chData[1];
			rawSentence[2] = navControlData.uMeasured.chData[2];
			rawSentence[3] = navControlData.uMeasured.chData[3];
			rawSentence[4] = navControlData.thetaCommanded.chData[0];	
			rawSentence[5] = navControlData.thetaCommanded.chData[1];	
			rawSentence[6] = navControlData.thetaCommanded.chData[2];	
			rawSentence[7] = navControlData.thetaCommanded.chData[3];	
			rawSentence[8] = navControlData.psiDotCommanded.chData[0];
			rawSentence[9] = navControlData.psiDotCommanded.chData[1];
			rawSentence[10]= navControlData.psiDotCommanded.chData[2];
			rawSentence[11]= navControlData.psiDotCommanded.chData[3];
			rawSentence[12]= navControlData.phiCommanded.chData[0];		
			rawSentence[13]= navControlData.phiCommanded.chData[1];		
			rawSentence[14]= navControlData.phiCommanded.chData[2];		
			rawSentence[15]= navControlData.phiCommanded.chData[3];		
			rawSentence[16]= navControlData.rHighPass.chData[0]; 
			rawSentence[17]= navControlData.rHighPass.chData[1]; 
			rawSentence[18]= navControlData.rHighPass.chData[2]; 
			rawSentence[19]= navControlData.rHighPass.chData[3]; 
			rawSentence[20]= navControlData.totRun.chData[0];
			rawSentence[21]= navControlData.totRun.chData[1];
			rawSentence[22]= navControlData.totRun.chData[2];
			rawSentence[23]= navControlData.totRun.chData[3];
			rawSentence[24]= navControlData.distance2Go.chData[0];		
			rawSentence[25]= navControlData.distance2Go.chData[1]; 
			rawSentence[26]= navControlData.distance2Go.chData[2]; 
			rawSentence[27]= navControlData.distance2Go.chData[3]; 
			rawSentence[28]= navControlData.fromWp; 
			rawSentence[29]= navControlData.toWp; 

			// assemble the XYZ data for protocol sending
			assembleMsg(&rawSentence[0], NAVMSG_LEN, NAVMSG_ID, telemetryBuf);

			// add it to the out Array
			for( i = 0; i < NAVMSG_LEN+7; i += 1 ){
				dataOut[i+1] = telemetryBuf[i];
			}					

				// set the total data out for log
				len2Telemetry = NAVMSG_LEN+7; 			
		break;
		
		default:
			dataOut[0] = 0;
			break;
	}
	
	memset(telemetryBuf, 0, sizeof(telemetryBuf));
	
	// Raw/XYZ and Attitude data. Gets included every sample time
	// ==============================================
	
	// Raw, DIAG or XYZ data is sent down to GS at 100Hz only in real flight (or in the ground)
	// if HIL is on then control commands are sent at 100Hz instead of either raw
	
	if (!apsControlData.hilStatus){
	#if defined(LOGRAW100) 	// If we need to log raw at 100 Hz
		rawSentence[0] 	=	rawControlData.gyroX.chData[0];	
		rawSentence[1]  =	rawControlData.gyroX.chData[1];	
		rawSentence[2] 	=	rawControlData.gyroY.chData[0];		 	
		rawSentence[3]  =	rawControlData.gyroY.chData[1];	
		rawSentence[4] 	=	rawControlData.gyroZ.chData[0];	 
		rawSentence[5] 	=	rawControlData.gyroZ.chData[1];	 
		rawSentence[6] =	rawControlData.accelX.chData[0];	 
		rawSentence[7] =	rawControlData.accelX.chData[1];	   
		rawSentence[8] =	rawControlData.accelY.chData[0];	  
		rawSentence[9] =	rawControlData.accelY.chData[1];	  
		rawSentence[10] =	rawControlData.accelZ.chData[0];	  
		rawSentence[11] =	rawControlData.accelZ.chData[1];	  
		rawSentence[12] =	rawControlData.magX.chData[0];	  
		rawSentence[13] =	rawControlData.magX.chData[1];	  
		rawSentence[14] =	rawControlData.magY.chData[0];	  
		rawSentence[15] =	rawControlData.magY.chData[1];	  
		rawSentence[16] =	rawControlData.magZ.chData[0];	  
		rawSentence[17] =	rawControlData.magZ.chData[1];	
		// included in SLUGS MKII
		rawSentence[18] =	rawControlData.baro.chData[0];	  
		rawSentence[19] =	rawControlData.baro.chData[1];	
		rawSentence[20] =	rawControlData.pito.chData[0];	  
		rawSentence[21] =	rawControlData.pito.chData[1];	
		rawSentence[22] =	rawControlData.powr.chData[0];	  
		rawSentence[23] =	rawControlData.powr.chData[1];
		rawSentence[24] =	rawControlData.ther.chData[0];	  
		rawSentence[25] =	rawControlData.ther.chData[1];		
	
		// assemble the Attitude data for protocol sending
		assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, telemetryBuf);
	
		// add it to the circular buffer and SPI queue
		for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
			dataOut[i+1+len2Telemetry] = telemetryBuf[i];
		}					
	
		// set the total data out for SPI			
		len2Telemetry+= RAWMSG_LEN+7; 			
  	
	#elif  defined(DIAG100) //if we want diagnostics at 100 
		rawSentence[0]	=	diagControlData.fl1.chData[0];	
		rawSentence[1]	=	diagControlData.fl1.chData[1];	
		rawSentence[2]	=	diagControlData.fl1.chData[2];	
		rawSentence[3]	=	diagControlData.fl1.chData[3];	
		rawSentence[4]	=	diagControlData.fl2.chData[0];	
		rawSentence[5]	=	diagControlData.fl2.chData[1];	
		rawSentence[6]	=	diagControlData.fl2.chData[2];	
		rawSentence[7]	=	diagControlData.fl2.chData[3];	
		rawSentence[8]	=	diagControlData.fl3.chData[0];	
		rawSentence[9]	=	diagControlData.fl3.chData[1];	
		rawSentence[10]=	diagControlData.fl3.chData[2];	
		rawSentence[11]=	diagControlData.fl3.chData[3];	
		rawSentence[12]=	diagControlData.sh1.chData[0];	
		rawSentence[13]=	diagControlData.sh1.chData[1];	
		rawSentence[14]=	diagControlData.sh2.chData[0];	
		rawSentence[15]=	diagControlData.sh2.chData[1];	
		rawSentence[16]=	diagControlData.sh3.chData[0];	
		rawSentence[17]=	diagControlData.sh3.chData[1];
			 	
				
		// assemble the Diag data for protocol sending
		assembleMsg(&rawSentence[0], DIAMSG_LEN, DIAMSG_ID, telemetryBuf);

		// add it to the out Array
		for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
			dataOut[i+1+len2Telemetry] = telemetryBuf[i];
		}					

		// set the total data out for log
		len2Telemetry += DIAMSG_LEN+7; 		
				
	#else
		rawSentence[0] = xyzControlData.Xcoord.chData[0];
		rawSentence[1] = xyzControlData.Xcoord.chData[1];
		rawSentence[2] = xyzControlData.Xcoord.chData[2];
		rawSentence[3] = xyzControlData.Xcoord.chData[3];
		rawSentence[4] = xyzControlData.Ycoord.chData[0];	
		rawSentence[5] = xyzControlData.Ycoord.chData[1];	
		rawSentence[6] = xyzControlData.Ycoord.chData[2];	
		rawSentence[7] = xyzControlData.Ycoord.chData[3];	
		rawSentence[8] = xyzControlData.Zcoord.chData[0];
		rawSentence[9] = xyzControlData.Zcoord.chData[1];
		rawSentence[10]= xyzControlData.Zcoord.chData[2];
		rawSentence[11]= xyzControlData.Zcoord.chData[3];
		rawSentence[12]= xyzControlData.VX.chData[0]	;	
		rawSentence[13]= xyzControlData.VX.chData[1]	;	
		rawSentence[14]= xyzControlData.VX.chData[2]	;	
		rawSentence[15]= xyzControlData.VX.chData[3]	;	
		rawSentence[16]= xyzControlData.VY.chData[0]	;	
		rawSentence[17]= xyzControlData.VY.chData[1]	;	
		rawSentence[18]= xyzControlData.VY.chData[2]	;	
		rawSentence[19]= xyzControlData.VY.chData[3]	;	
		rawSentence[20]= xyzControlData.VZ.chData[0]	;	
		rawSentence[21]= xyzControlData.VZ.chData[1]	;	
		rawSentence[22]= xyzControlData.VZ.chData[2]	;	
		rawSentence[23]= xyzControlData.VZ.chData[3]	;	
				
		// assemble the Diag data for protocol sending
		assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, telemetryBuf);

		// add it to the out Array
		for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
			dataOut[i+1+ len2Telemetry] = telemetryBuf[i];
		}					

		// set the total data out for log
		len2Telemetry += XYZMSG_LEN+7; 
	#endif

	} else {
		// clear the buffer for next sentence
		memset(telemetryBuf, 0, sizeof(telemetryBuf));
		
		rawSentence[0]	=	pwmControlData.dt_c.chData[0]	;	
		rawSentence[1]	=	pwmControlData.dt_c.chData[1]	; 	
		rawSentence[2]	=	pwmControlData.dla_c.chData[0]	;		 	
		rawSentence[3]	=	pwmControlData.dla_c.chData[1]	; 
		rawSentence[4]	=	pwmControlData.dra_c.chData[0]	;	 
		rawSentence[5]	=	pwmControlData.dra_c.chData[1]	;	 
		rawSentence[6]	=	pwmControlData.dr_c.chData[0]	;	 
		rawSentence[7]	=	pwmControlData.dr_c.chData[1]	;	   
		rawSentence[8]	=	pwmControlData.dle_c.chData[0]	;	  
		rawSentence[9]	=	pwmControlData.dle_c.chData[1]	;	  
		rawSentence[10]	=	pwmControlData.dre_c.chData[0]	;	  
		rawSentence[11]	=	pwmControlData.dre_c.chData[1]	;	  
		rawSentence[12]	=	pwmControlData.dlf_c.chData[0]	;	  
		rawSentence[13]	=	pwmControlData.dlf_c.chData[1]	;	  
		rawSentence[14]	=	pwmControlData.drf_c.chData[0]	;	  
		rawSentence[15]	=	pwmControlData.drf_c.chData[1]	;	  
		rawSentence[16]	=	pwmControlData.da1_c.chData[0]	;	  
		rawSentence[17]	=	pwmControlData.da1_c.chData[1]	;	  
		rawSentence[18]	=	pwmControlData.da2_c.chData[0]	;	  
		rawSentence[19]	=	pwmControlData.da2_c.chData[1]	;	  
		
		// assemble the Diag data for protocol sending
		assembleMsg(&rawSentence[0], PWMMSG_LEN, PWMMSG_ID, telemetryBuf);

		// add it to the out Array
		for( i = 0; i < PWMMSG_LEN+7; i += 1 ){
			dataOut[i+1+len2Telemetry] = telemetryBuf[i];
		}					

		// set the total data out for log
		len2Telemetry += PWMMSG_LEN+7; 
					
	} // if hil	
	
	rawSentence[0] = attitudeRotatedControlData.roll.chData[0]		;
	rawSentence[1] = attitudeRotatedControlData.roll.chData[1]		;
	rawSentence[2] = attitudeRotatedControlData.roll.chData[2]		;
	rawSentence[3] = attitudeRotatedControlData.roll.chData[3]		;
	rawSentence[4] = attitudeRotatedControlData.pitch.chData[0]	;	
	rawSentence[5] = attitudeRotatedControlData.pitch.chData[1]	;	
	rawSentence[6] = attitudeRotatedControlData.pitch.chData[2]	;	
	rawSentence[7] = attitudeRotatedControlData.pitch.chData[3]	;	
	rawSentence[8] = attitudeRotatedControlData.yaw.chData[0]		;
	rawSentence[9] = attitudeRotatedControlData.yaw.chData[1]		;
	rawSentence[10] =attitudeRotatedControlData.yaw.chData[2]		;
	rawSentence[11] =attitudeRotatedControlData.yaw.chData[3]		;
	rawSentence[12] =attitudeRotatedControlData.p.chData[0]		;	
	rawSentence[13] =attitudeRotatedControlData.p.chData[1]		;	
	rawSentence[14] =attitudeRotatedControlData.p.chData[2]		;	
	rawSentence[15] =attitudeRotatedControlData.p.chData[3]		;	
	rawSentence[16] =attitudeRotatedControlData.q.chData[0]		;	
	rawSentence[17] =attitudeRotatedControlData.q.chData[1]		;	
	rawSentence[18] =attitudeRotatedControlData.q.chData[2]		;	
	rawSentence[19] =attitudeRotatedControlData.q.chData[3]		;	
	rawSentence[20] =attitudeRotatedControlData.r.chData[0]		;	
	rawSentence[21] =attitudeRotatedControlData.r.chData[1]		;	
	rawSentence[22] =attitudeRotatedControlData.r.chData[2]		;	
	rawSentence[23] =attitudeRotatedControlData.r.chData[3]		;	
	rawSentence[24] =attitudeRotatedControlData.timeStamp.chData[0];	
	rawSentence[25] =attitudeRotatedControlData.timeStamp.chData[1];					 	
			
	// assemble the Diag data for protocol sending
	assembleMsg(&rawSentence[0], ATTMSG_LEN, ATTMSG_ID, telemetryBuf);

	// add it to the out Array
	for( i = 0; i < ATTMSG_LEN+7; i += 1 ){
		dataOut[i+1+len2Telemetry] = telemetryBuf[i];
	}					

	// set the total data out for SPI			
	dataOut[0] =  len2Telemetry+ ATTMSG_LEN+7; 			

	// increment/overflow the samplePeriod counter
	// configured for 16 Hz in non vital messages
	sampleTelemetry = (sampleTelemetry >= 10)? 1: sampleTelemetry + 1;

}


void updatePWM(unsigned short * PWMData){
	pwmControlData.dt_c.usData 	= PWMData[0];
	pwmControlData.dla_c.usData = PWMData[1];
	pwmControlData.dra_c.usData = PWMData[2];
	pwmControlData.dr_c.usData 	= PWMData[3];
	pwmControlData.dle_c.usData = PWMData[4];	
}

void updatePWM2(unsigned short PWMData, unsigned char channel ){
	switch (channel){
		case 0:
			pwmControlData.dre_c.usData = PWMData;
		break; 
		case 1:
			pwmControlData.dlf_c.usData = PWMData;
		break; 
		case 2:
			pwmControlData.drf_c.usData = PWMData;
		break; 
		case 3:
			pwmControlData.da1_c.usData = PWMData;
		break; 
		case 4:
			pwmControlData.da2_c.usData = PWMData;
		break; 
								
	}
}

void updateLoad (unsigned char mcuLoad){
	statusControlData.vdetect =  mcuLoad;
}

void updateEuler(float* newEuler){
	attitudeRotatedControlData.roll.flData = newEuler[0];
	attitudeRotatedControlData.pitch.flData = newEuler[1];
	attitudeRotatedControlData.yaw.flData = newEuler[2];
	attitudeRotatedControlData.timeStamp.usData = attitudeControlData.timeStamp.usData;
}


void updatePQR(float* newPQR){
	attitudeRotatedControlData.p.flData = newPQR[0];
	attitudeRotatedControlData.q.flData = newPQR[1];
	attitudeRotatedControlData.r.flData = newPQR[2];
}

void pilotCommands (unsigned short*  pilCom){
	pilCom[0] = pilControlData.dt.usData;
	pilCom[1] = pilControlData.dla.usData;
	pilCom[2] = pilControlData.dra.usData;
	pilCom[3] = pilControlData.dr.usData;
	pilCom[4] = pilControlData.de.usData;
}

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
    // Clear the DMA1 Interrupt Flag;
    IFS0bits.DMA1IF  = 0;		
}

void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void){
 
	// Read the buffer while it has data
	// and add it to the circular buffer
	while(U2STAbits.URXDA == 1){
		writeBack(uartBufferIn, (unsigned char)U2RXREG);
	}
	
	// If there was an overun error clear it and continue
	if (U2STAbits.OERR == 1){
		U2STAbits.OERR = 0;
	}
	
	// clear the interrupt
	IFS1bits.U2RXIF = 0;
}


void __attribute__ ((interrupt, no_auto_psv)) _U1ErrInterrupt(void)
{
	IFS4bits.U2EIF = 0; // Clear the UART2 Error Interrupt Flag
}


void copyBufferToDMA1 (unsigned char size){
	unsigned char i;
	for(  i = 0; i < size; i += 1 )
	{
		BufferB[i] = (unsigned int) readFront(uartBufferOut);
	}
}

void send2GS(unsigned char* protData){
	unsigned int bufLen,i;
		
	// add the data to the circular buffer
	for(i = 1; i <= protData[0]; i += 1 )
	{
		writeBack(uartBufferOut, protData[i] );
	}
	
	// get the Length of the logBuffer
	bufLen = getLength(uartBufferOut);
	

	// if the interrupt catched up with the circularBuffer
	// and new data was added then turn on the DMA 
	if(!(DMA1CONbits.CHEN) && (bufLen>0)){
		// Configure the bytes to send
		DMA1CNT =  bufLen<= (MAXSEND-1)? bufLen-1: MAXSEND-1;	
		// copy the buffer to the DMA channel outgoing buffer
		copyBufferToDMA1((unsigned char) DMA1CNT+1);
		// Enable the DMA
		DMA1CONbits.CHEN = 1;
		// Init the transmission
		DMA1REQbits.FORCE = 1;
	}
	
}




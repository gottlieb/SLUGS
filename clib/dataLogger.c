// ==============================================================
// dataLogger.c
// This is code implements a fully DMA driven UART writer to
// be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures UART 2
// at a predefined baud rate, then initializes a circular buffer,
// configures the DMA and starts the service. 
// The main function logData writes data to UART2 in the predefined
// comm protocol and returns data in the comm protocol to be sent
// via SPI to the second MCU. 
// 
// This file also contains Sensor MCU support functions
//
// Code by: Mariano I. Lizarraga
// First Revision: Aug 26 2008 @ 21:15
// =========================================================

#include "dataLogger.h"


struct CircBuffer com2Buffer;
CBRef logBuffer;

struct CircBuffer com2BufferIn;
CBRef uartBufferIn;

unsigned int BufferA[MAXSEND] __attribute__((space(dma))) = {0};

void loggerInit (void){
	// initialize the circular buffers
	logBuffer = (struct CircBuffer* )&com2Buffer;
	newCircBuffer(logBuffer);

	uartBufferIn = (struct CircBuffer* )&com2BufferIn;
	newCircBuffer(uartBufferIn);
	
	// DMA0REQ Register
	// ================
	DMA0REQ = 0x001F;
	
	// DMA0PAD Register
	// ================
	DMA0PAD = (volatile unsigned int) &U2TXREG;

	// DMA0CON Register
	// ================
	DMA0CONbits.AMODE   = 0;        // Register Indirect with post-increment
	DMA0CONbits.MODE    = 1;        // One-shot, No Ping-Pong Mode	
	DMA0CONbits.DIR     = 1;        // Read from RAM and send to Periphereal
	DMA0CONbits.SIZE    = 0;        // Word Data Transfer

	// DMA0CNT Register
	// ==============
	DMA0CNT = LOGSEND-1;

	// DMA0STA Register
	// ================
	DMA0STA= __builtin_dmaoffset(BufferA);

	// Enable DMA0 TX interrupts
	IFS0bits.DMA0IF  = 0;			// Clear DMA Interrupt Flag
	IEC0bits.DMA0IE  = 1;			// Enable DMA interrupt
	
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
	IPC7bits.U2RXIP   = 5;    		// Interrupt priority 5  
  	IFS1bits.U2RXIF   = 0;    		// Clear the interrupt flag
  	IEC1bits.U2RXIE   = 1;    		// Enable interrupts
  		
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
		
	IEC4bits.U2EIE 		= 0;	
}

void copyBufferToDMA (unsigned char size){
	unsigned char i;
	for(  i = 0; i < size; i += 1 )
	{
		BufferA[i] = (unsigned int) readFront(logBuffer);
	}
}

/*
	logData is the implementation of the outgoing Comunications 		
	protocol it is geared to prepare the data for logging and
	for the SPI inter processor communication. It uses a 
	static variable to monitor at which samples the outgoing messages 
	are queued in the circular buffer for DMA transmision.
*/
	
/*
	TODO: This function needs to be merged with prepareTelemetry
	in groundStationDriver.c and moved to something like
	apUtils.c
	
*/

void logData (unsigned char hilOn, unsigned char* data4SPI){
	unsigned char rawSentence[35];
	
	// sample period variable
	static unsigned char samplePeriod = 1;
	static unsigned char tmpBuf [37];
	
	// temp var to store the assembled message
	unsigned char i;
	unsigned char len2SPI=0;
	unsigned char bufLen = 0;
	unsigned char aknSentence[6];

	memset(tmpBuf, 0, sizeof(tmpBuf));
		
	switch (samplePeriod){
		case 1: //GPS
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
			assembleMsg(&rawSentence[0], GPSMSG_LEN, GPSMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < GPSMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}					

			// set the total data out for SPI
			len2SPI = GPSMSG_LEN+7; 

		break;
		case 2: // LOAD 
			rawSentence[0] = statusControlData.load		 	;
			rawSentence[1] = statusControlData.vdetect	 	;
			rawSentence[2] = statusControlData.bVolt.chData[0] ;
			rawSentence[3] = statusControlData.bVolt.chData[1] ;

			// assemble the CPU load data for protocol sending	
			assembleMsg(&rawSentence[0], LOADMSG_LEN, LOADMSG_ID, tmpBuf);
			// add it to the circular buffer and SPI queue
			for( i = 0; i < LOADMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI = LOADMSG_LEN+7; 	
			
		break;
		case 3:	// RAW or XYZ depending if we are logging raw @ 100		
			#ifdef LOGRAW100 	// If we need to log raw at 100 Hz
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
				assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, tmpBuf);
				// add it to the circular buffer and SPI queue
				for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
					writeBack(logBuffer,tmpBuf[i]);
					data4SPI[i+1+len2SPI] = tmpBuf[i];
				}
			
		    	// set the total data out for SPI
				len2SPI = XYZMSG_LEN+7;
			
			#else
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
				
		    	// assemble the Raw Sensor data for protocol sending	
				assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, tmpBuf);

				// add it to the circular buffer and SPI queue
				for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
					writeBack(logBuffer,tmpBuf[i]);
					data4SPI[i+1] = tmpBuf[i];
				}		

				// set the total data out for SPI			
				len2SPI = RAWMSG_LEN+7; 			
			#endif
				
		break;
		case 4:	// Dynamic and Reboot (if required)		
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


			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(&rawSentence[0], DYNMSG_LEN, DYNMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < DYNMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}		
			// set the total data out for SPI			
			len2SPI = DYNMSG_LEN+7; 			
			
			// it there has been a reboot
			if(aknControlData.sensorReboot >0){
				// clear tmpBuf
				memset(tmpBuf, 0, sizeof(tmpBuf));
				
				// configure the akn sentence
				memset(aknSentence,0, 6);
				aknSentence[3] = aknControlData.sensorReboot;
				
				// assemble the message
				assembleMsg(&aknSentence[0], AKNMSG_LEN, AKNMSG_ID, tmpBuf);
				
				// add it to the SPI QUEUE
				for( i = 0; i < AKNMSG_LEN+7; i += 1 ){

					data4SPI[i+1+len2SPI] = tmpBuf[i];
				}		
				
				// clear the flag
				aknControlData.sensorReboot = 0;
				// set the total data out for SPI			
				len2SPI += AKNMSG_LEN+7; 	
			}
		break;

		case 5:	// Bias		

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
		
			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(&rawSentence[0], BIAMSG_LEN, BIAMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < BIAMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}		
			// set the total data out for SPI			
			len2SPI = BIAMSG_LEN+7; 			
			
		break;
		case 6: // Diagnostic
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
		
		    // assemble the Diagnostic data for protocol sending	
			assembleMsg(&rawSentence[0], DIAMSG_LEN, DIAMSG_ID, tmpBuf);
			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI = (DIAMSG_LEN+7); 			
		break;
		
		case 7: // Pilot Console Data
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
		
		    // assemble the Pilot Console data for protocol sending	
			assembleMsg(&rawSentence[0], PILMSG_LEN, PILMSG_ID, tmpBuf);
			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < PILMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI = (PILMSG_LEN+7); 			
		break;
		
		case 8: // Sensor Data in meaningful units
			rawSentence[0] = senControlData.Ax.chData[0];
			rawSentence[1] = senControlData.Ax.chData[1];
			rawSentence[2] = senControlData.Ax.chData[2];
			rawSentence[3] = senControlData.Ax.chData[3];
			rawSentence[4] = senControlData.Ay.chData[0];
			rawSentence[5] = senControlData.Ay.chData[1];
			rawSentence[6] = senControlData.Ay.chData[2];
			rawSentence[7] = senControlData.Ay.chData[3];
			rawSentence[8] = senControlData.Az.chData[0];
			rawSentence[9] = senControlData.Az.chData[1];
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
			
		    // assemble the Pilot Console data for protocol sending	
			assembleMsg(&rawSentence[0], SENMSG_LEN, SENMSG_ID, tmpBuf);
			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < SENMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI = (SENMSG_LEN+7); 			
		break;
		default:
			data4SPI[0] = 0;
		break;
	}
	
	memset(tmpBuf, 0,  sizeof(tmpBuf));
	
	// Attitude data. Gets included every sample time
	// ==============================================
	rawSentence[0] = attitudeControlData.roll.chData[0]		;
	rawSentence[1] = attitudeControlData.roll.chData[1]		;
	rawSentence[2] = attitudeControlData.roll.chData[2]		;
	rawSentence[3] = attitudeControlData.roll.chData[3]		;
	rawSentence[4] = attitudeControlData.pitch.chData[0]	;	
	rawSentence[5] = attitudeControlData.pitch.chData[1]	;	
	rawSentence[6] = attitudeControlData.pitch.chData[2]	;	
	rawSentence[7] = attitudeControlData.pitch.chData[3]	;	
	rawSentence[8] = attitudeControlData.yaw.chData[0]		;
	rawSentence[9] = attitudeControlData.yaw.chData[1]		;
	rawSentence[10] =attitudeControlData.yaw.chData[2]		;
	rawSentence[11] =attitudeControlData.yaw.chData[3]		;
	rawSentence[12] =attitudeControlData.p.chData[0]		;	
	rawSentence[13] =attitudeControlData.p.chData[1]		;	
	rawSentence[14] =attitudeControlData.p.chData[2]		;	
	rawSentence[15] =attitudeControlData.p.chData[3]		;	
	rawSentence[16] =attitudeControlData.q.chData[0]		;	
	rawSentence[17] =attitudeControlData.q.chData[1]		;	
	rawSentence[18] =attitudeControlData.q.chData[2]		;	
	rawSentence[19] =attitudeControlData.q.chData[3]		;	
	rawSentence[20] =attitudeControlData.r.chData[0]		;	
	rawSentence[21] =attitudeControlData.r.chData[1]		;	
	rawSentence[22] =attitudeControlData.r.chData[2]		;	
	rawSentence[23] =attitudeControlData.r.chData[3]		;	
	rawSentence[24] =attitudeControlData.timeStamp.chData[0];	
	rawSentence[25] =attitudeControlData.timeStamp.chData[1];					 	
	
	// assemble the Attitude data for protocol sending
	assembleMsg(&rawSentence[0], ATTMSG_LEN, ATTMSG_ID, tmpBuf);
	
	// add it to the circular buffer and SPI queue
	for( i = 0; i < ATTMSG_LEN+7; i += 1 ){
		writeBack(logBuffer,tmpBuf[i]);
		data4SPI[i+1+len2SPI] = tmpBuf[i];
	}					
	
	// increment the data counter for SPI
	len2SPI += ATTMSG_LEN+7; 
	
	memset(tmpBuf, 0, sizeof(tmpBuf));
	
	// XYZ data. Gets included every sample time
	// ==============================================
	
	#ifdef LOGRAW100
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

		// assemble the Raw Sensor data for protocol sending	
		assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, tmpBuf);

		// add it to the circular buffer and SPI queue
		for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
			writeBack(logBuffer,tmpBuf[i]);
			data4SPI[i+1+len2SPI] = tmpBuf[i];
		}		

		// set the total data out for SPI			
		data4SPI[0] = len2SPI + RAWMSG_LEN+7; 	
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
	
		// assemble the XYZ data for protocol sending
		assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, tmpBuf);
		// add it to the circular buffer and SPI queue
		for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
			writeBack(logBuffer,tmpBuf[i]);
			data4SPI[i+1+len2SPI] = tmpBuf[i];
		}
	
    	// set the total data out for SPI
		data4SPI[0] = len2SPI + XYZMSG_LEN+7; 
	
	#endif
		
	// increment/overflow the samplePeriod counter
	// configured for 10 Hz in non vital messages
	samplePeriod = (samplePeriod >= 8)? 1: samplePeriod + 1;
	
	// get the Length of the logBuffer
	bufLen = getLength(logBuffer);
	
	// if HIL is ON do not transmit diagnostic data in the diagnostic port
	// let the circular buffer overwrite itself
	hilOn =1;
	if (hilOn!= 1){		
		// if the interrupt catched up with the circularBuffer
		//  then turn on the DMA
		if(!(DMA0CONbits.CHEN) && bufLen> 0){
			// Configure the bytes to send
			DMA0CNT =  bufLen<= (MAXSEND-1)? bufLen-1: MAXSEND-1;		
			// copy the buffer to the DMA channel outgoing buffer	
			copyBufferToDMA((unsigned char) DMA0CNT+1);
			// Enable the DMA
			DMA0CONbits.CHEN = 1;
			// Init the transmission
			DMA0REQbits.FORCE = 1;
		}
	}

}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	
    // Clear the DMA0 Interrupt Flag;
    IFS0bits.DMA0IF  = 0;		

}

// Interrupt service routine for U2 HIL protocol port
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

void __attribute__ ((interrupt, no_auto_psv)) _U2ErrInterrupt(void)
{
	IFS4bits.U2EIF = 0; // Clear the UART2 Error Interrupt Flag
}

// =====================================
//         Sensor MCU Support Functions
// =====================================


void hilRead(unsigned char* hilChunk){
	// fix the data length so if the interrupt adds data
	// during execution of this block, it will be read
	// until the next hilRead
	unsigned char tmpLen = getLength(uartBufferIn), i=0;
	
	// if the buffer has more data than the max size, set it to max,
	// otherwise set it to the length
	hilChunk[0] =  (tmpLen > MAXSEND -1)? MAXSEND -1: tmpLen;
	
	// read the data 
	for(i = 1; i <= hilChunk[0]; i += 1 )
	{
		hilChunk[i] = readFront(uartBufferIn);
	}
}

void updateRawADCData (short * adcData) {
	rawControlData.baro.shData = adcData[0];
	rawControlData.pito.shData = adcData[1];
	rawControlData.powr.shData = adcData[2];
	rawControlData.ther.shData = adcData[3];
}

void updateAirData (float* airData) {
	dynTempControlData.dynamic.flData 	= airData[0];
	dynTempControlData.stat.flData 		= airData[1];
	dynTempControlData.temp.shData 		= (short) airData[2];
}

void updateLoadData (unsigned char load, unsigned short mvPower) {
	statusControlData.load = load;
	statusControlData.bVolt.usData = mvPower;
}

void updateAttitude (float * attitudeData) {
	attitudeControlData.roll.flData 	= attitudeData[0];
	attitudeControlData.pitch.flData 	= attitudeData[1];
	attitudeControlData.yaw.flData 		= attitudeData[2];
	attitudeControlData.p.flData 		= attitudeData[3];
	attitudeControlData.q.flData 		= attitudeData[4];
	attitudeControlData.r.flData 		= attitudeData[5];
}

void updateTimeStamp (unsigned short timeSt) {
	attitudeControlData.timeStamp.usData = timeSt;
}

void updatePosition (float * posData) {
	xyzControlData.Xcoord.flData		= posData[0];
	xyzControlData.Ycoord.flData		= posData[1];
	xyzControlData.Zcoord.flData		= posData[2];
	xyzControlData.VX.flData			= posData[3];
	xyzControlData.VY.flData			= posData[4];
	xyzControlData.VZ.flData			= posData[5];
}

void updatePilotConsole (unsigned short * pilData) {
	pilControlData.dt.usData			= pilData[0];
	pilControlData.dla.usData			= pilData[1];
	pilControlData.dra.usData			= pilData[2];
	pilControlData.dr.usData			= pilData[3];
	pilControlData.de.usData			= pilData[4];
}

void updateDiagnosticFl (float* diagFl) {
	diagControlData.fl1.flData =	diagFl[0];
	diagControlData.fl2.flData =	diagFl[1];
	diagControlData.fl3.flData =	diagFl[2];
}

void updateDiagnosticSh (short* diagSh) {
	diagControlData.sh1.shData =	diagSh[0];
	diagControlData.sh2.shData =	diagSh[1];
	diagControlData.sh3.shData =	diagSh[2];
}

void updateBias (float * biasData) {
	biasControlData.gxb.flData		= biasData[0];
	biasControlData.gyb.flData		= biasData[1];
	biasControlData.gzb.flData		= biasData[2];
	biasControlData.axb.flData		= biasData[3];
	biasControlData.ayb.flData		= biasData[4];
	biasControlData.azb.flData		= biasData[5];
}

void updateSensorData (float* sens){
	senControlData.Ax.flData			= sens[0];
	senControlData.Ay.flData			= sens[1];
	senControlData.Az.flData			= sens[2];
	senControlData.Mx.flData			= sens[3];
	senControlData.My.flData			= sens[4];
	senControlData.Mz.flData			= sens[5];
}

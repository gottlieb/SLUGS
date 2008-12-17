// ==============================================================
// dataLogger.c
// This is code implements a fully DMA driven UART writer to
// be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures UART 2
// at a predefined baud rate, then initializes a circular buffer,
// configures the DMA and starts the service. 
// The main function logData writes data to UART2 in the predefined
// comm protocol. 
// 
// Code by: Mariano I. Lizarraga
// First Revision: Sep 1st 2008 @ 13:21
// =========================================================

#include "sendProtocol.h"

struct CircBuffer com2Buffer;
CBRef commProtBuffer;
unsigned int BufferA[MAXSEND] __attribute__((space(dma))) = {0};

tGpsData 		gpsLogData;
tRawData 		rawLogData;
tSensStatus		statusLogData;
tAttitudeData	attitudeLogData;
tDynTempData	dynTempLogData;
tBiasData		biasLogData;
tDiagData		diagLogData;
tXYZData		xyzLogData;
unsigned char   filterLogData;
tAknData		aknLogData;

void commProtInit (void){
	// initialize the circular buffer
	commProtBuffer = (struct CircBuffer* )&com2Buffer;
	newCircBuffer(commProtBuffer);
	
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
	
	// U1BRG Register
	// ==============
	U2BRG = LOGOMAT_UBRG;				// Set the baud rate for data logger


	// U1STA Register
	// ==============
	U2STAbits.UTXISEL0	= 0;		// generate interrupt on every char
	U2STAbits.UTXISEL1	= 0;		// for the DMA
	U2STAbits.URXISEL	= 0;		// RX interrupt irrelevant
	U2STAbits.OERR		= 0;		// clear overun error
	
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
		
	IEC4bits.U2EIE 		= 0;	
}

void copyBufferToDMA (unsigned char size){
	unsigned char i;
	for(  i = 0; i < size; i += 1 )
	{
		BufferA[i] = (unsigned int) readFront(commProtBuffer);
	}
}

void prepareLog( unsigned char* dataOut){
	unsigned char rawSentence[35];
	
	// sample period variable
	static unsigned char sampleLog = 1;
	static unsigned char tmpBuf [MAXLOGSEND];
	
	// temp var to store the assembled message
	unsigned char i;
	unsigned char len2log=0;
	unsigned char bufLen = 0;

	memset(tmpBuf, 0, sizeof(tmpBuf));
		
	switch (sampleLog){
		case 1: // GPS		
			gpsLogData = getGpsStruct();
			
			rawSentence[0] =  gpsLogData.year	;			
			rawSentence[1] =  gpsLogData.month	;		
			rawSentence[2] =  gpsLogData.day	;			
			rawSentence[3] =  gpsLogData.hour	;			
			rawSentence[4] =  gpsLogData.min	;			
			rawSentence[5] =  gpsLogData.sec	;			
			rawSentence[6] = gpsLogData.lat.chData[0];	
			rawSentence[7] = gpsLogData.lat.chData[1];	
			rawSentence[8] = gpsLogData.lat.chData[2];				
			rawSentence[9] = gpsLogData.lat.chData[3];			
			rawSentence[10] = gpsLogData.lon.chData[0];	
			rawSentence[11] = gpsLogData.lon.chData[1];	
			rawSentence[12] = gpsLogData.lon.chData[2];	
			rawSentence[13] = gpsLogData.lon.chData[3];	
			rawSentence[14] = gpsLogData.height.chData[0];		
			rawSentence[15] = gpsLogData.height.chData[1];	
			rawSentence[16] = gpsLogData.height.chData[2];		
			rawSentence[17] = gpsLogData.height.chData[3];	
			rawSentence[18] = gpsLogData.cog.chData[0];	
			rawSentence[19] = gpsLogData.cog.chData[1];	
			rawSentence[20] = gpsLogData.sog.chData[0];	
			rawSentence[21] = gpsLogData.sog.chData[1];	
			rawSentence[22] = gpsLogData.hdop.chData[0];	
			rawSentence[23] = gpsLogData.hdop.chData[1];	
			rawSentence[24] = gpsLogData.fix			;	
			rawSentence[25] = gpsLogData.sats			;	
			rawSentence[26] = gpsLogData.newValue		;	
					
			// assemble the GPS data for protocol sending
			assembleMsg(&rawSentence[0], GPSMSG_LEN, GPSMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < GPSMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = GPSMSG_LEN+7; 

			break;

		case 2: // Diag		
			diagLogData = getDiagStruct();
			
			rawSentence[0]	=	diagLogData.fl1.chData[0];	
			rawSentence[1]	=	diagLogData.fl1.chData[1];	
			rawSentence[2]	=	diagLogData.fl1.chData[2];	
			rawSentence[3]	=	diagLogData.fl1.chData[3];	
			rawSentence[4]	=	diagLogData.fl2.chData[0];	
			rawSentence[5]	=	diagLogData.fl2.chData[1];	
			rawSentence[6]	=	diagLogData.fl2.chData[2];	
			rawSentence[7]	=	diagLogData.fl2.chData[3];	
			rawSentence[8]	=	diagLogData.fl3.chData[0];	
			rawSentence[9]	=	diagLogData.fl3.chData[1];	
			rawSentence[10]=	diagLogData.fl3.chData[2];	
			rawSentence[11]=	diagLogData.fl3.chData[3];	
			rawSentence[12]=	diagLogData.sh1.chData[0];	
			rawSentence[13]=	diagLogData.sh1.chData[1];	
			rawSentence[14]=	diagLogData.sh2.chData[0];	
			rawSentence[15]=	diagLogData.sh2.chData[1];	
			rawSentence[16]=	diagLogData.sh3.chData[0];	
			rawSentence[17]=	diagLogData.sh3.chData[1];
				 	
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], DIAMSG_LEN, DIAMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = DIAMSG_LEN+7; 

		break;
		case 3: // Attitude		
			attitudeLogData = getAttStruct();
			
			rawSentence[0] = attitudeLogData.roll.chData[0]		;
			rawSentence[1] = attitudeLogData.roll.chData[1]		;
			rawSentence[2] = attitudeLogData.roll.chData[2]		;
			rawSentence[3] = attitudeLogData.roll.chData[3]		;
			rawSentence[4] = attitudeLogData.pitch.chData[0]	;	
			rawSentence[5] = attitudeLogData.pitch.chData[1]	;	
			rawSentence[6] = attitudeLogData.pitch.chData[2]	;	
			rawSentence[7] = attitudeLogData.pitch.chData[3]	;	
			rawSentence[8] = attitudeLogData.yaw.chData[0]		;
			rawSentence[9] = attitudeLogData.yaw.chData[1]		;
			rawSentence[10] =attitudeLogData.yaw.chData[2]		;
			rawSentence[11] =attitudeLogData.yaw.chData[3]		;
			rawSentence[12] =attitudeLogData.p.chData[0]		;	
			rawSentence[13] =attitudeLogData.p.chData[1]		;	
			rawSentence[14] =attitudeLogData.p.chData[2]		;	
			rawSentence[15] =attitudeLogData.p.chData[3]		;	
			rawSentence[16] =attitudeLogData.q.chData[0]		;	
			rawSentence[17] =attitudeLogData.q.chData[1]		;	
			rawSentence[18] =attitudeLogData.q.chData[2]		;	
			rawSentence[19] =attitudeLogData.q.chData[3]		;	
			rawSentence[20] =attitudeLogData.r.chData[0]		;	
			rawSentence[21] =attitudeLogData.r.chData[1]		;	
			rawSentence[22] =attitudeLogData.r.chData[2]		;	
			rawSentence[23] =attitudeLogData.r.chData[3]		;	
			rawSentence[24] =attitudeLogData.timeStamp.chData[0];	
			rawSentence[25] =attitudeLogData.timeStamp.chData[1];					 	
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], ATTMSG_LEN, ATTMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < ATTMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = ATTMSG_LEN+7; 

		break;
			
		case 4: // Bias		
			biasLogData = getBiasStruct();
			
			rawSentence[0] = biasLogData.axb.chData[0] ;
			rawSentence[1] = biasLogData.axb.chData[1] ;
			rawSentence[2] = biasLogData.axb.chData[2] ;
			rawSentence[3] = biasLogData.axb.chData[3] ;
			rawSentence[4] = biasLogData.ayb.chData[0] ;	
			rawSentence[5] = biasLogData.ayb.chData[1] ;	
			rawSentence[6] = biasLogData.ayb.chData[2] ;	
			rawSentence[7] = biasLogData.ayb.chData[3] ;	
			rawSentence[8] = biasLogData.azb.chData[0] ;
			rawSentence[9] = biasLogData.azb.chData[1] ;
			rawSentence[10]= biasLogData.azb.chData[2];
			rawSentence[11]= biasLogData.azb.chData[3];
			rawSentence[12]= biasLogData.gxb.chData[0];	
			rawSentence[13]= biasLogData.gxb.chData[1];	
			rawSentence[14]= biasLogData.gxb.chData[2];	
			rawSentence[15]= biasLogData.gxb.chData[3];	
			rawSentence[16]= biasLogData.gyb.chData[0];	
			rawSentence[17]= biasLogData.gyb.chData[1];	
			rawSentence[18]= biasLogData.gyb.chData[2];	
			rawSentence[19]= biasLogData.gyb.chData[3];	
			rawSentence[20]= biasLogData.gzb.chData[0];	
			rawSentence[21]= biasLogData.gzb.chData[1];	
			rawSentence[22]= biasLogData.gzb.chData[2];	
			rawSentence[23]= biasLogData.gzb.chData[3];	
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], BIAMSG_LEN, BIAMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < BIAMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = BIAMSG_LEN+7; 

		break;
		
		case 5: // XYZ		
			xyzLogData = getXYZStruct();
			
			rawSentence[0] = xyzLogData.Xcoord.chData[0];
			rawSentence[1] = xyzLogData.Xcoord.chData[1];
			rawSentence[2] = xyzLogData.Xcoord.chData[2];
			rawSentence[3] = xyzLogData.Xcoord.chData[3];
			rawSentence[4] = xyzLogData.Ycoord.chData[0];	
			rawSentence[5] = xyzLogData.Ycoord.chData[1];	
			rawSentence[6] = xyzLogData.Ycoord.chData[2];	
			rawSentence[7] = xyzLogData.Ycoord.chData[3];	
			rawSentence[8] = xyzLogData.Zcoord.chData[0];
			rawSentence[9] = xyzLogData.Zcoord.chData[1];
			rawSentence[10]= xyzLogData.Zcoord.chData[2];
			rawSentence[11]= xyzLogData.Zcoord.chData[3];
			rawSentence[12]= xyzLogData.VX.chData[0]	;	
			rawSentence[13]= xyzLogData.VX.chData[1]	;	
			rawSentence[14]= xyzLogData.VX.chData[2]	;	
			rawSentence[15]= xyzLogData.VX.chData[3]	;	
			rawSentence[16]= xyzLogData.VY.chData[0]	;	
			rawSentence[17]= xyzLogData.VY.chData[1]	;	
			rawSentence[18]= xyzLogData.VY.chData[2]	;	
			rawSentence[19]= xyzLogData.VY.chData[3]	;	
			rawSentence[20]= xyzLogData.VZ.chData[0]	;	
			rawSentence[21]= xyzLogData.VZ.chData[1]	;	
			rawSentence[22]= xyzLogData.VZ.chData[2]	;	
			rawSentence[23]= xyzLogData.VZ.chData[3]	;	
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = XYZMSG_LEN+7; 

		break;

		case 6: // Load and Dynamic	
		
			 // dynamic first
			dynTempLogData = getDynStruct();
			
			rawSentence[0] = dynTempLogData.dynamic.chData[0];
			rawSentence[1] = dynTempLogData.dynamic.chData[1];
			rawSentence[2] = dynTempLogData.dynamic.chData[2];
			rawSentence[3] = dynTempLogData.dynamic.chData[3];
			rawSentence[4] = dynTempLogData.stat.chData[0]	;	
			rawSentence[5] = dynTempLogData.stat.chData[1]	;	
			rawSentence[6] = dynTempLogData.stat.chData[2]	;	
			rawSentence[7] = dynTempLogData.stat.chData[3]	;	
			rawSentence[8] = dynTempLogData.temp.chData[0]	;
			rawSentence[9] = dynTempLogData.temp.chData[1]	;
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], DYNMSG_LEN, DYNMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < DYNMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for SPI
			len2log = DYNMSG_LEN+7; 
			
			memset(tmpBuf, 0, sizeof(tmpBuf));
			
			// then load
			statusLogData = getSensStruct();
			
			rawSentence[0] = statusLogData.load		 	;
			rawSentence[1] = statusLogData.vdetect	 	;
			rawSentence[2] = statusLogData.bVolt.chData[0] ;
			rawSentence[3] = statusLogData.bVolt.chData[1] ;
					
			// assemble the Diag data for protocol sending
			assembleMsg(&rawSentence[0], LOADMSG_LEN, LOADMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < LOADMSG_LEN+7; i += 1 ){
				dataOut[i+1+len2log] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = len2log+ LOADMSG_LEN+7; 
			
		break;
		
		default:
			dataOut[0] = 0;
			break;
	}
	
	memset(tmpBuf, 0, sizeof(tmpBuf));
	
	// Raw data. Gets included every sample time
	// ==============================================
	
	rawLogData = getRawStruct();
	
	rawSentence[0] 	=	rawLogData.gyroX.chData[0];	
	rawSentence[1]  =	rawLogData.gyroX.chData[1];	
	rawSentence[2] 	=	rawLogData.gyroY.chData[0];		 	
	rawSentence[3]  =	rawLogData.gyroY.chData[1];	
	rawSentence[4] 	=	rawLogData.gyroZ.chData[0];	 
	rawSentence[5] 	=	rawLogData.gyroZ.chData[1];	 
	rawSentence[6] =	rawLogData.accelX.chData[0];	 
	rawSentence[7] =	rawLogData.accelX.chData[1];	   
	rawSentence[8] =	rawLogData.accelY.chData[0];	  
	rawSentence[9] =	rawLogData.accelY.chData[1];	  
	rawSentence[10] =	rawLogData.accelZ.chData[0];	  
	rawSentence[11] =	rawLogData.accelZ.chData[1];	  
	rawSentence[12] =	rawLogData.magX.chData[0];	  
	rawSentence[13] =	rawLogData.magX.chData[1];	  
	rawSentence[14] =	rawLogData.magY.chData[0];	  
	rawSentence[15] =	rawLogData.magY.chData[1];	  
	rawSentence[16] =	rawLogData.magZ.chData[0];	  
	rawSentence[17] =	rawLogData.magZ.chData[1];	
	
	// assemble the Attitude data for protocol sending
	assembleMsg(&rawSentence[0], RAWMSG_LEN, RAWMSG_ID, tmpBuf);
	
	// add it to the circular buffer and SPI queue
	for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
		dataOut[i+1+len2log] = tmpBuf[i];
	}					
	
	// set the total data out for SPI			
	dataOut[0] = len2log + RAWMSG_LEN+7; 			

	// increment/overflow the samplePeriod counter
	// configured for 16 Hz in non vital messages
	sampleLog = (sampleLog >= 6)? 1: sampleLog + 1;

}

void txProtocol(unsigned char* protData){
	unsigned char bufLen,i;
		
	// add the data to the circular buffer
	for(i = 1; i <= protData[0]; i += 1 )
	{
		writeBack(commProtBuffer, protData[i] );
	}
	
	// get the Length of the logBuffer
	bufLen = getLength(commProtBuffer);

	// if the interrupt catched up with the circularBuffer
	// and new data was added then turn on the DMA 
	if(!(DMA0CONbits.CHEN) && (bufLen>0)){
		// Configure the bytes to send
		DMA0CNT =  bufLen<= (MAXLOGSEND-1)? bufLen-1: MAXSEND-1;	
		// copy the buffer to the DMA channel outgoing buffer
		copyBufferToDMA((unsigned char) DMA0CNT+1);
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}
	
}



void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    // Clear the DMA0 Interrupt Flag;
    IFS0bits.DMA0IF  = 0;		
	
	// if there are more bytes to send
	/*if(getLength(commProtBuffer)>= LOGSEND)
	{
		copyBufferToDMA();
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}
    */
}

void __attribute__ ((interrupt, no_auto_psv)) _U2ErrInterrupt(void)
{
	IFS4bits.U2EIF = 0; // Clear the UART2 Error Interrupt Flag
}

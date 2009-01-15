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

			// add it to the out Array
			for( i = 0; i < GPSMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = GPSMSG_LEN+7; 

			break;

		case 2: // Diag		
			
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
			assembleMsg(&rawSentence[0], DIAMSG_LEN, DIAMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = DIAMSG_LEN+7; 

		break;
		case 3: // Attitude		
			
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
			assembleMsg(&rawSentence[0], BIAMSG_LEN, BIAMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < BIAMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = BIAMSG_LEN+7; 

		break;
		
		case 5: // XYZ		
			
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
			assembleMsg(&rawSentence[0], XYZMSG_LEN, XYZMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for log
			len2log = XYZMSG_LEN+7; 

		break;

		case 6: // Load and Dynamic	
		
			
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
			assembleMsg(&rawSentence[0], DYNMSG_LEN, DYNMSG_ID, tmpBuf);

			// add it to the out Array
			for( i = 0; i < DYNMSG_LEN+7; i += 1 ){
				dataOut[i+1] = tmpBuf[i];
			}					

			// set the total data out for SPI
			len2log = DYNMSG_LEN+7; 
			
			// clear the buffer for next sentence
			memset(tmpBuf, 0, sizeof(tmpBuf));
			
			// assemble next sentence			
			rawSentence[0] = statusControlData.load		 	;
			rawSentence[1] = statusControlData.vdetect	 	;
			rawSentence[2] = statusControlData.bVolt.chData[0] ;
			rawSentence[3] = statusControlData.bVolt.chData[1] ;
					
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

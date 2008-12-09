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
	IPC7bits.U2RXIP   = 5;    		// Interrupt priority 6  
  	IFS1bits.U2RXIF   = 0;    		// Clear the interrupt flag
  	IEC1bits.U2RXIE   = 1;    		// Enable interrupts
  		
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
		
	IEC4bits.U2EIE 		= 0;	
}

void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg ){
	unsigned char i;
	// start the header
	*(protMsg+0) = DOLLAR;
	*(protMsg+1) = AT;
	*(protMsg+2) = type;
	*(protMsg+3) = size;
	for( i = 0; i < size; i += 1 )
	{
		*(protMsg+i+4) = *(rawData +i);
	}
	*(protMsg+size+4) = STAR;
	*(protMsg+size+5) = AT;
	*(protMsg+size+6) = getChecksum(protMsg, (size+5));	
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
	protocol it is geared to prepare the data either for the data 
	logger or the communications device (radio modem). It uses a 
	static variable to monitor at which samples the outgoing messages 
	are queued in the circular buffer for DMA transmision.
*/
void logData (unsigned char* rawData, unsigned char* data4SPI){
	// sample period variable
	static unsigned char samplePeriod = 1;
	static unsigned char tmpBuf [MAXLOGLEN];
	
	// temp var to store the assembled message
	unsigned char i;
	unsigned char len2SPI=0;
	unsigned char bufLen = 0;

	memset(tmpBuf, 0, sizeof(tmpBuf));
		
	switch (samplePeriod){
		case 1:
			// assemble the GPS data for protocol sending
			assembleMsg(&rawData[GPS_START], GPSMSG_LEN, GPSMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < GPSMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}					

			// set the total data out for SPI
			len2SPI = GPSMSG_LEN+7; 

			break;
		case 2:
			// assemble the CPU load data for protocol sending	
			assembleMsg(&rawData[LOAD_START], LOADMSG_LEN, LOADMSG_ID, tmpBuf);
			// add it to the circular buffer and SPI queue
			for( i = 0; i < LOADMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI = LOADMSG_LEN+7; 	
			
			/*// clear the buffer
			memset(tmpBuf, 0, sizeof(tmpBuf));		
			
			// assemble the Diagnostic data for protocol sending	
			assembleMsg(&rawData[DIA_START], DIAMSG_LEN, DIAMSG_ID, tmpBuf);
			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1+len2SPI] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI += (DIAMSG_LEN+7); 			*/
			break;
		case 3:			
			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(&rawData[RAW_START], RAWMSG_LEN, RAWMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}		

			// set the total data out for SPI			
			len2SPI = RAWMSG_LEN+7; 			

			break;
		case 4:			
			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(&rawData[DYN_START], DYNMSG_LEN, DYNMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < DYNMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}		
			// set the total data out for SPI			
			len2SPI = DYNMSG_LEN+7; 			

			break;

		case 5:			
			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(&rawData[BIA_START], BIAMSG_LEN, BIAMSG_ID, tmpBuf);

			// add it to the circular buffer and SPI queue
			for( i = 0; i < BIAMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}		
			// set the total data out for SPI			
			len2SPI = BIAMSG_LEN+7; 			


			break;
		case 6:
		    // assemble the Diagnostic data for protocol sending	
			assembleMsg(&rawData[DIA_START], DIAMSG_LEN, DIAMSG_ID, tmpBuf);
			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < DIAMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			// set the total data out for SPI
			len2SPI = (DIAMSG_LEN+7); 			
		break;

		default:
			data4SPI[0] = 0;
			break;
	}
	
	memset(tmpBuf, 0, sizeof(tmpBuf));
	
	// Attitude data. Gets included every sample time
	// ==============================================
	
	// assemble the Attitude data for protocol sending
	assembleMsg(&rawData[ATT_START], ATTMSG_LEN, ATTMSG_ID, tmpBuf);
	
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
	
	// assemble the XYZ data for protocol sending
	assembleMsg(&rawData[XYZ_START], XYZMSG_LEN, XYZMSG_ID, tmpBuf);
	// add it to the circular buffer and SPI queue
	for( i = 0; i < XYZMSG_LEN+7; i += 1 ){
		writeBack(logBuffer,tmpBuf[i]);
		data4SPI[i+1+len2SPI] = tmpBuf[i];
	}
	
    // set the total data out for SPI
	data4SPI[0] = len2SPI + XYZMSG_LEN+7; 
	
	// increment/overflow the samplePeriod counter
	// configured for 10 Hz in non vital messages
	samplePeriod = (samplePeriod >= 10)? 1: samplePeriod + 1;
	
	// get the Length of the logBuffer
	bufLen = getLength(logBuffer);
	
	// if HIL is do not transmit diagnostic data in the diagnostic port
	if (rawData[HIL_START]!= 1){		
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

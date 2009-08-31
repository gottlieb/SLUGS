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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "protDecoder.h"
#include "apDefinitions.h"
#include "gpsSplit.h"
#include "circBuffer.h"

	unsigned char msg1 [] = {0x24, 0x40, 0x01, 0x1b, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a,
    0x40, 0x5a};

    unsigned char msg2[] = {0x24, 0x40, 0x02, 0x04, 0x00, 0x01, 0x02, 0x03,
    0x2a, 0x40, 0x46};

    unsigned char msg3[] = {0x24, 0x40, 0x03, 0x12, 0x44, 0x07, 0xf2, 0x07,
    0xf6, 0x07, 0xdb, 0x07, 0xdd, 0x07, 0x5f, 0x09, 0xf9, 0x0f, 0xf9, 0x0f,
    0xf9, 0x0f, 0x2a, 0x40, 0xb0};

    unsigned char msg4[] = {0x24, 0x40, 0x04, 0x18, 0x24, 0x60, 0xc5, 0x3d,
    0x6d, 0x95, 0x83, 0x3d, 0x6d, 0x95, 0x03, 0x3e, 0x24, 0x60, 0xc5, 0x3d,
    0x6d, 0x95, 0x83, 0x3d, 0x6d, 0x95, 0x03, 0x3e, 0x2a, 0x40, 0x5c};

    unsigned char msg11[]= {0x24, 0x40, 0x0b, 0x0c, 0x24, 0x60, 0xc5, 0x3d,
    0x6d, 0x95, 0x83, 0x3d, 0x6d, 0x95, 0x03, 0x3e, 0x2a, 0x40, 0x3d};


    unsigned char retV[16];

    struct CircBuffer com2Buffer;
    CBRef logBuffer;

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

void logData (unsigned char* rawData, unsigned char* data4SPI){
	// sample period variable
	static unsigned char samplePeriod = 0;
	unsigned char tmpBuf [MAXLOGLEN];

	// temp var to store the assembled message
	unsigned char i;
	unsigned char len2SPI=0;
	unsigned char bufLen = 0;

	memset(tmpBuf, 0, sizeof(tmpBuf));
    	
	switch (samplePeriod){
		case 2:
			// assemble the CPU load data for protocol sending	
			assembleMsg(&rawData[LOAD_START], LOADMSG_LEN, LOADMSG_ID, tmpBuf);
			// set the total data out for SPI
			len2SPI = LOADMSG_LEN+7; 			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < LOADMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}

			break;
		case 3:			
			// assemble the Raw Sensor data for protocol sending	
			assembleMsg(&rawData[RAW_START], RAWMSG_LEN, RAWMSG_ID, tmpBuf);
			// set the total data out for SPI			
			len2SPI = RAWMSG_LEN+7; 			
			// add it to the circular buffer and SPI queue
			for( i = 0; i < RAWMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}
		
			break;
		case 1:
			// assemble the GPS data for protocol sending
			assembleMsg(&rawData[GPS_START], GPSMSG_LEN, GPSMSG_ID, tmpBuf);
			// set the total data out for SPI
			len2SPI = GPSMSG_LEN+7; 
			// add it to the circular buffer and SPI queue
			for( i = 0; i < GPSMSG_LEN+7; i += 1 ){
				writeBack(logBuffer,tmpBuf[i]);
				data4SPI[i+1] = tmpBuf[i];
			}					
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
	samplePeriod = (samplePeriod >= 4)? 0: samplePeriod + 1;
	
	// get the Length of the logBuffer
	bufLen = getLength(logBuffer);
	
   /*	// if the interrupt catched up with the circularBuffer
	//  then turn on the DMA
	if(!(DMA0CONbits.CHEN) && bufLen> 0){
		// Configure the bytes to send
		DMA0CNT =  bufLen<= (MAXSEND-1)? bufLen-1: MAXSEND-1;
		// copy the buffer to the DMA channel outgoing buffer
		copyBufferToDMA((unsigned char) DMA0CNT);
		// Enable the DMA
		DMA0CONbits.CHEN = 1;
		// Init the transmission
		DMA0REQbits.FORCE = 1;
	}

    */
}



int main (int argc, char const* argv[])
{
    FILE *file;
	unsigned char *buffer;
	unsigned long fileLen;
    unsigned long i;

    unsigned char mychk;
    unsigned char myRawData[97];
    unsigned char myData4SPI[97];
    unsigned char myToLog[97];

    logBuffer = (struct CircBuffer* )&com2Buffer;
	newCircBuffer(logBuffer);

    memset(myRawData,0,sizeof(myRawData));
    memset(myData4SPI,0,sizeof(myData4SPI));

    // create the raw stream
    //====================
    for(i=0; i< GPSMSG_LEN; i+=1){
        myRawData[i] = msg1[4+i];
    }

    for(i=GPSMSG_LEN; i< (GPSMSG_LEN + LOADMSG_LEN); i+=1){
        myRawData[i] = msg2[4+i-GPSMSG_LEN];
    }

    for(i=(GPSMSG_LEN + LOADMSG_LEN); i< (GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN); i+=1){
        myRawData[i] = msg3[4+i - (GPSMSG_LEN + LOADMSG_LEN)];
    }

    for(i=(GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN); i< (GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN+ATTMSG_LEN); i+=1){
        myRawData[i] = msg4[4+i-(GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN)];
    }


    for(i=(GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN+ATTMSG_LEN); i< (GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN+ATTMSG_LEN + XYZMSG_LEN); i+=1){
        myRawData[i] = msg11[4+i-(GPSMSG_LEN + LOADMSG_LEN + RAWMSG_LEN+ATTMSG_LEN)];
    }

    //====================

    /*for (i=0;i<10 ;i+=1)
    {
      logData(myRawData,myData4SPI);
      myData4SPI;
      memset(myData4SPI,0,sizeof(myData4SPI));
    }*/

    
	//Open file
	file = fopen("prot.bin", "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file");
		return 0;
	}
	
	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	//Allocate memory
	buffer=(unsigned char *)malloc(fileLen+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                                fclose(file);
		return 0;
	}

        protParserInit();

	//Read file contents into buffer
        i = 0;
        while (i<fileLen-96){
	        fread(buffer, 96, 1, file);
            i+=96;
            protParseDecode(buffer, myToLog);
        }
        fclose(file);
	//Do what ever with buffer

	free(buffer);



	return 0;
}
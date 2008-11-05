// ==========================================================
// protDecoder.c
// This is code implements the communications protocol decoder.
// It adds the bytes as they come in from the SPI to a circular
// buffer which is then read to parse sentences and updates the 
// data structures accordingly if the checksum tallies.
//
// 
// Code by: Mariano I. Lizarraga
// First Revision: Sep 2 2008 @ 15:03
// ==========================================================

#include "protDecoder.h"


// These are the global data structures that hold the state
// there are accessor methods to read data off them
// use with care
tGpsData 		gpsControlData;
tRawData 		rawControlData;
tSensStatus		statusControlData;
tAttitudeData	attitudeControlData;
tDynTempData	dynTempControlData;
tXYZData		xyzControlData;
unsigned char   filterControlData;
tAknData		aknControlData;

struct CircBuffer protParseBuffer;
CBRef ppBuffer;


void protParserInit(void){
	// initialize the circular buffer
	ppBuffer = (struct CircBuffer* )&protParseBuffer;
	newCircBuffer(ppBuffer);
	
	// Initialize all global data structures
	memset(&gpsControlData, 0, sizeof(tGpsData));
	memset(&rawControlData, 0, sizeof(tRawData));
	memset(&statusControlData, 0, sizeof(tSensStatus));
	memset(&attitudeControlData, 0, sizeof(tAttitudeData));
	memset(&dynTempControlData, 0, sizeof(tDynTempData));
	memset(&xyzControlData, 0, sizeof(tXYZData));
	memset(&aknControlData, 0, sizeof(tAknData));
	filterControlData = 0;
}

void updateStates(unsigned char * completeSentence){
	switch (completeSentence[2]){
		// Sensor MCU sentences
		// ====================
		case 1:		// GPS Sentence
			gpsControlData.year				= completeSentence[4];	
			gpsControlData.month			= completeSentence[5];	
			gpsControlData.day				= completeSentence[6];	
			gpsControlData.hour				= completeSentence[7];	
			gpsControlData.min				= completeSentence[8];	
			gpsControlData.sec				= completeSentence[9];	
			gpsControlData.lat.chData[0]	= completeSentence[10];	
			gpsControlData.lat.chData[1]	= completeSentence[11];	
			gpsControlData.lat.chData[2]	= completeSentence[12];				
			gpsControlData.lat.chData[3]	= completeSentence[13];			
			gpsControlData.lon.chData[0]	= completeSentence[14];	
			gpsControlData.lon.chData[1]	= completeSentence[15];	
			gpsControlData.lon.chData[2]	= completeSentence[16];	
			gpsControlData.lon.chData[3]	= completeSentence[17];	
			gpsControlData.height.chData[0]	= completeSentence[18];		
			gpsControlData.height.chData[1]	= completeSentence[19];	
			gpsControlData.height.chData[2]	= completeSentence[20];		
			gpsControlData.height.chData[3]	= completeSentence[21];	
			gpsControlData.cog.chData[0]	= completeSentence[22];	
			gpsControlData.cog.chData[1]	= completeSentence[23];	
			gpsControlData.sog.chData[0]	= completeSentence[24];	
			gpsControlData.sog.chData[1]	= completeSentence[25];	
			gpsControlData.hdop.chData[0]	= completeSentence[26];	
			gpsControlData.hdop.chData[1]	= completeSentence[27];	
			gpsControlData.fix				= completeSentence[28];	
			gpsControlData.sats				= completeSentence[29];	
			gpsControlData.newValue		 	= completeSentence[30];	
		break;
		case 2:
			statusControlData.load		 	= completeSentence[4];
			statusControlData.vdetect	 	= completeSentence[5];
			statusControlData.bVolt.chData[0] 	= completeSentence[6];
			statusControlData.bVolt.chData[1] 	= completeSentence[7];
		break;
		case 3: // Sensor Raw data, this one is done for demo. I will not fly
			rawControlData.gyroX.chData[0]	= completeSentence[4];	
			rawControlData.gyroX.chData[1]	= completeSentence[5]; 	
			rawControlData.gyroY.chData[0]	= completeSentence[6];		 	
			rawControlData.gyroY.chData[1]	= completeSentence[7]; 
			rawControlData.gyroZ.chData[0]	= completeSentence[8];	 
			rawControlData.gyroZ.chData[1]	= completeSentence[9];	 
			rawControlData.accelX.chData[0]	= completeSentence[10];	 
			rawControlData.accelX.chData[1]	= completeSentence[11];	   
			rawControlData.accelY.chData[0]	= completeSentence[12];	  
			rawControlData.accelY.chData[1]	= completeSentence[13];	  
			rawControlData.accelZ.chData[0]	= completeSentence[14];	  
			rawControlData.accelZ.chData[1]	= completeSentence[15];	  
			rawControlData.magX.chData[0]	= completeSentence[16];	  
			rawControlData.magX.chData[1]	= completeSentence[17];	  
			rawControlData.magY.chData[0]	= completeSentence[18];	  
			rawControlData.magY.chData[1]	= completeSentence[19];	  
			rawControlData.magZ.chData[0]	= completeSentence[20];	  
			rawControlData.magZ.chData[1]	= completeSentence[21];	  
		break;
		case 4:
			attitudeControlData.roll.chData[0]	= completeSentence[4];
			attitudeControlData.roll.chData[1]	= completeSentence[5];
			attitudeControlData.roll.chData[2]	= completeSentence[6];
			attitudeControlData.roll.chData[3]	= completeSentence[7];
			attitudeControlData.pitch.chData[0]	= completeSentence[8];
			attitudeControlData.pitch.chData[1]	= completeSentence[9];
			attitudeControlData.pitch.chData[2]	= completeSentence[10];
			attitudeControlData.pitch.chData[3]	= completeSentence[11];
			attitudeControlData.yaw.chData[0]	= completeSentence[12];
			attitudeControlData.yaw.chData[1]	= completeSentence[13];
			attitudeControlData.yaw.chData[2]	= completeSentence[14];
			attitudeControlData.yaw.chData[3]	= completeSentence[15];
			attitudeControlData.p.chData[0]	= completeSentence[16];
			attitudeControlData.p.chData[1]	= completeSentence[17];
			attitudeControlData.p.chData[2]	= completeSentence[18];
			attitudeControlData.p.chData[3]	= completeSentence[19];
			attitudeControlData.q.chData[0]	= completeSentence[20];
			attitudeControlData.q.chData[1]	= completeSentence[21];
			attitudeControlData.q.chData[2]	= completeSentence[22];
			attitudeControlData.q.chData[3]	= completeSentence[23];
			attitudeControlData.r.chData[0]	= completeSentence[24];
			attitudeControlData.r.chData[1]	= completeSentence[25];
			attitudeControlData.r.chData[2]	= completeSentence[26];
			attitudeControlData.r.chData[3]	= completeSentence[27];			
		break;
        case 5:
			dynTempControlData.dynamic.chData[0]	= completeSentence[4];
			dynTempControlData.dynamic.chData[1]	= completeSentence[5];
			dynTempControlData.dynamic.chData[2]	= completeSentence[6];
			dynTempControlData.dynamic.chData[3]	= completeSentence[7];
			dynTempControlData.stat.chData[0]	= completeSentence[8];
			dynTempControlData.stat.chData[1]	= completeSentence[9];
			dynTempControlData.stat.chData[2]	= completeSentence[10];
			dynTempControlData.stat.chData[3]	= completeSentence[11];
			dynTempControlData.temp.chData[1]	= completeSentence[12];	  
			dynTempControlData.temp.chData[0]	= completeSentence[13];	  
		break;
		case 11:
			xyzControlData.Xcoord.chData[0]	= completeSentence[4];
			xyzControlData.Xcoord.chData[1]	= completeSentence[5];
			xyzControlData.Xcoord.chData[2]	= completeSentence[6];
			xyzControlData.Xcoord.chData[3]	= completeSentence[7];
			xyzControlData.Ycoord.chData[0]	= completeSentence[8];
			xyzControlData.Ycoord.chData[1]	= completeSentence[9];
			xyzControlData.Ycoord.chData[2]	= completeSentence[10];
			xyzControlData.Ycoord.chData[3]	= completeSentence[11];
			xyzControlData.Zcoord.chData[0]	= completeSentence[12];
			xyzControlData.Zcoord.chData[1]	= completeSentence[13];
			xyzControlData.Zcoord.chData[2]	= completeSentence[14];
			xyzControlData.Zcoord.chData[3]	= completeSentence[15];
			xyzControlData.VX.chData[0]	= completeSentence[16];
			xyzControlData.VX.chData[1]	= completeSentence[17];
			xyzControlData.VX.chData[2]	= completeSentence[18];
			xyzControlData.VX.chData[3]	= completeSentence[19];
			xyzControlData.VY.chData[0]	= completeSentence[20];
			xyzControlData.VY.chData[1]	= completeSentence[21];
			xyzControlData.VY.chData[2]	= completeSentence[22];
			xyzControlData.VY.chData[3]	= completeSentence[23];
			xyzControlData.VZ.chData[0]	= completeSentence[24];
			xyzControlData.VZ.chData[1]	= completeSentence[25];
			xyzControlData.VZ.chData[2]	= completeSentence[26];
			xyzControlData.VZ.chData[3]	= completeSentence[27];
		break;	
		case 205:
			// turn the filter on
			filterControlData = completeSentence[4];
			
			// turn on the required Aknowledge flag
			aknControlData.filOnOff = 1;
			
		break;	
		default:
		break;
	}
}

#ifdef _IN_PC_
void protParseDecode (unsigned char* fromSPI, unsigned char* toLog, FILE* outFile){
#else
void protParseDecode (unsigned char* fromSPI, unsigned char* toLog){
#endif
	// Static variables CAREFUL
	static unsigned char prevBuffer[2*MAXLOGLEN];
	static unsigned char previousComplete =1;
	static unsigned char indexLast = 0;

	// local variables
	unsigned char i;
	unsigned char tmpChksum = 0, headerFound=0, noMoreBytes = 1;
	unsigned char trailerFound = 0;

	unsigned char logSize = 0;

	// Add the received bytes to the protocol parsing circular buffer
    for(i = 1; i <= fromSPI[0]; i += 1 )
    //for(i = 0; i <= 95; i += 1 )
	{
		writeBack(ppBuffer, fromSPI[i]);
	}

	// update the noMoreBytes flag accordingly
   noMoreBytes = (fromSPI[0]>0)?0:1;
   // noMoreBytes = 0;

	while (!noMoreBytes){
		// if the previous message was complete then read from the circular buffer
		// and make sure that you are into the begining of a message
		if(previousComplete){
			while (!headerFound && !noMoreBytes) {
				// move along until you find a dollar sign or run out of bytes
				while (getLength(ppBuffer)>1 && peak(ppBuffer)!=DOLLAR){
					readFront(ppBuffer);
				}
				// if you found a dollar then make sure the next one is an AT
				if(getLength(ppBuffer)>1 && peak(ppBuffer) == DOLLAR){
					// read it
					prevBuffer[indexLast++] = readFront(ppBuffer);
                    // if next is a at sign
					if (peak(ppBuffer) == AT){
						// read it
						prevBuffer[indexLast++] = readFront(ppBuffer);
						// and signal you found a header
						headerFound = 1;
                         // and set as  incomplete the sentece
                         previousComplete = 0;
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
			while (getLength(ppBuffer)>2 && peak(ppBuffer)!=STAR){
				prevBuffer[indexLast++] = readFront(ppBuffer);
			}
			// if you found a STAR (42) and stil have bytes
			if (getLength(ppBuffer)>2 && peak(ppBuffer)==STAR){
				// read it
				prevBuffer[indexLast++] = readFront(ppBuffer);
				// if you still have 2 bytes
				if (getLength(ppBuffer)>1){
					// and the next byte is an AT sign
					if (peak(ppBuffer)==AT){
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
			prevBuffer[indexLast++] = readFront(ppBuffer);
			prevBuffer[indexLast] = readFront(ppBuffer);

			// Compute the checksum
			tmpChksum= getChecksum(prevBuffer, indexLast-1);

			// if the checksum is valid
			if (tmpChksum ==prevBuffer[indexLast]){
				// update the states depending on the message
				updateStates(&prevBuffer[0]);
                #ifdef _IN_PC_
                   if (outFile != NULL) printState(outFile);
                #endif
				// Copy the data to the out buffer for logging purposes
				memcpy(&toLog[logSize+1],&prevBuffer[0], indexLast+1);
				// increment the log size
				logSize += (indexLast+1);
			}
            else{
             indexLast = 1; // just to stop debugger
            }
            // get everything ready to start all-over
			previousComplete =1;
			indexLast = 0;
            headerFound = 0;
            trailerFound = 0;
            memset(prevBuffer, 0, sizeof(prevBuffer));

		}else { // you ran out of bytes
			// No More Bytes
			noMoreBytes = 1;
		}// else no star	
	} // big outer while (no more bytes)
	toLog[0] = logSize;
}


#ifdef _IN_PC_
void printState (FILE* outFile){
/*
tGpsData 		gpsControlData;
tRawData 		rawControlData;
tSensStatus		statusControlData;
tAttitudeData	attitudeControlData;
tDynTempData	dynTempControlData;
tXYZData		xyzControlData;
unsigned char   filterControlData;
tAknData		aknControlData;
*/
    fprintf(outFile, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
         attitudeControlData.roll.flData,
         attitudeControlData.pitch.flData,
         attitudeControlData.yaw.flData,
         attitudeControlData.p.flData,
         attitudeControlData.q.flData,
         attitudeControlData.r.flData,
         xyzControlData.Xcoord.flData,
         xyzControlData.Ycoord.flData,
         xyzControlData.Zcoord.flData,
         xyzControlData.VX.flData,
         xyzControlData.VY.flData,
         xyzControlData.VZ.flData);
}
#endif


// ===============================================
// Accesor Methods for the Global Data Structures
// ===============================================
tGpsData getGpsStruct(void){
 return gpsControlData;
}

tRawData getRawStruct(void){
 return rawControlData;
}

tXYZData getXYZStruct(void){
 return xyzControlData;
}

tAttitudeData getAttStruct(void){
 return attitudeControlData;
}

tAknData getAknStruct(void){
 return aknControlData;
}

void setAknFilter (unsigned char value){
	aknControlData.filOnOff = value;
}

void getTime (unsigned char * values){
	values[0] = gpsControlData.hour;
	values[1] = gpsControlData.min;
	values[2] = gpsControlData.sec;		
}

unsigned char getFilterOnOff (void){
	return filterControlData;
}



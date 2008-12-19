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
tBiasData		biasControlData;
tDiagData		diagControlData;
tXYZData		xyzControlData;
unsigned char   filterControlData;
tAknData		aknControlData;
tPilotData		pilControlData;

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
	memset(&biasControlData, 0, sizeof(tBiasData));
	memset(&diagControlData, 0, sizeof(tDiagData));
	memset(&xyzControlData, 0, sizeof(tXYZData));
	memset(&aknControlData, 0, sizeof(tAknData));
	memset(&pilControlData, 0, sizeof(tPilotData));
	filterControlData = 0;
}

void updateStates(unsigned char * completeSentence){
	switch (completeSentence[2]){
		// Sensor MCU sentences
		// ====================
		case GPSMSG_ID:		// GPS Sentence
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
		case LOADMSG_ID:
			statusControlData.load		 		= completeSentence[4];
			statusControlData.vdetect	 		= completeSentence[5];
			statusControlData.bVolt.chData[0] 	= completeSentence[6];
			statusControlData.bVolt.chData[1] 	= completeSentence[7];
		break;
		case RAWMSG_ID: // Sensor Raw data
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
		case ATTMSG_ID:
			attitudeControlData.roll.chData[0]		= completeSentence[4];
			attitudeControlData.roll.chData[1]		= completeSentence[5];
			attitudeControlData.roll.chData[2]		= completeSentence[6];
			attitudeControlData.roll.chData[3]		= completeSentence[7];
			attitudeControlData.pitch.chData[0]		= completeSentence[8];
			attitudeControlData.pitch.chData[1]		= completeSentence[9];
			attitudeControlData.pitch.chData[2]		= completeSentence[10];
			attitudeControlData.pitch.chData[3]		= completeSentence[11];
			attitudeControlData.yaw.chData[0]		= completeSentence[12];
			attitudeControlData.yaw.chData[1]		= completeSentence[13];
			attitudeControlData.yaw.chData[2]		= completeSentence[14];
			attitudeControlData.yaw.chData[3]		= completeSentence[15];
			attitudeControlData.p.chData[0]			= completeSentence[16];
			attitudeControlData.p.chData[1]			= completeSentence[17];
			attitudeControlData.p.chData[2]			= completeSentence[18];
			attitudeControlData.p.chData[3]			= completeSentence[19];
			attitudeControlData.q.chData[0]			= completeSentence[20];
			attitudeControlData.q.chData[1]			= completeSentence[21];
			attitudeControlData.q.chData[2]			= completeSentence[22];
			attitudeControlData.q.chData[3]			= completeSentence[23];
			attitudeControlData.r.chData[0]			= completeSentence[24];
			attitudeControlData.r.chData[1]			= completeSentence[25];
			attitudeControlData.r.chData[2]			= completeSentence[26];
			attitudeControlData.r.chData[3]			= completeSentence[27];			
			attitudeControlData.timeStamp.chData[0]	= completeSentence[28];			
			attitudeControlData.timeStamp.chData[1]	= completeSentence[29];			
		break;
        case DYNMSG_ID:
			dynTempControlData.dynamic.chData[0]	= completeSentence[4];
			dynTempControlData.dynamic.chData[1]	= completeSentence[5];
			dynTempControlData.dynamic.chData[2]	= completeSentence[6];
			dynTempControlData.dynamic.chData[3]	= completeSentence[7];
			dynTempControlData.stat.chData[0]	= completeSentence[8];
			dynTempControlData.stat.chData[1]	= completeSentence[9];
			dynTempControlData.stat.chData[2]	= completeSentence[10];
			dynTempControlData.stat.chData[3]	= completeSentence[11];
			dynTempControlData.temp.chData[0]	= completeSentence[12];	  
			dynTempControlData.temp.chData[1]	= completeSentence[13];	  
		break;
		case BIAMSG_ID:
			biasControlData.axb.chData[0]	= completeSentence[4];
			biasControlData.axb.chData[1]	= completeSentence[5];
			biasControlData.axb.chData[2]	= completeSentence[6];
			biasControlData.axb.chData[3]	= completeSentence[7];
			biasControlData.ayb.chData[0]	= completeSentence[8];
			biasControlData.ayb.chData[1]	= completeSentence[9];
			biasControlData.ayb.chData[2]	= completeSentence[10];
			biasControlData.ayb.chData[3]	= completeSentence[11];
			biasControlData.azb.chData[0]	= completeSentence[12];
			biasControlData.azb.chData[1]	= completeSentence[13];
			biasControlData.azb.chData[2]	= completeSentence[14];
			biasControlData.azb.chData[3]	= completeSentence[15];
			biasControlData.gxb.chData[0]	= completeSentence[16];
			biasControlData.gxb.chData[1]	= completeSentence[17];
			biasControlData.gxb.chData[2]	= completeSentence[18];
			biasControlData.gxb.chData[3]	= completeSentence[19];
			biasControlData.gyb.chData[0]	= completeSentence[20];
			biasControlData.gyb.chData[1]	= completeSentence[21];
			biasControlData.gyb.chData[2]	= completeSentence[22];
			biasControlData.gyb.chData[3]	= completeSentence[23];
			biasControlData.gzb.chData[0]	= completeSentence[24];
			biasControlData.gzb.chData[1]	= completeSentence[25];
			biasControlData.gzb.chData[2]	= completeSentence[26];
			biasControlData.gzb.chData[3]	= completeSentence[27];			
		break;		
		case DIAMSG_ID:
			diagControlData.fl1.chData[0]	= completeSentence[4];
			diagControlData.fl1.chData[1]	= completeSentence[5];
			diagControlData.fl1.chData[2]	= completeSentence[6];
			diagControlData.fl1.chData[3]	= completeSentence[7];
			diagControlData.fl2.chData[0]	= completeSentence[8];
			diagControlData.fl2.chData[1]	= completeSentence[9];
			diagControlData.fl2.chData[2]	= completeSentence[10];
			diagControlData.fl2.chData[3]	= completeSentence[11];
			diagControlData.fl3.chData[0]	= completeSentence[12];
			diagControlData.fl3.chData[1]	= completeSentence[13];
			diagControlData.fl3.chData[2]	= completeSentence[14];
			diagControlData.fl3.chData[3]	= completeSentence[15];
			diagControlData.sh1.chData[0]	= completeSentence[16];
			diagControlData.sh1.chData[1]	= completeSentence[17];
			diagControlData.sh2.chData[0]	= completeSentence[18];
			diagControlData.sh2.chData[1]	= completeSentence[19];
			diagControlData.sh3.chData[0]	= completeSentence[20];
			diagControlData.sh3.chData[1]	= completeSentence[21];		
		break;
		case XYZMSG_ID:
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
			xyzControlData.VX.chData[0]		= completeSentence[16];
			xyzControlData.VX.chData[1]		= completeSentence[17];
			xyzControlData.VX.chData[2]		= completeSentence[18];
			xyzControlData.VX.chData[3]		= completeSentence[19];
			xyzControlData.VY.chData[0]		= completeSentence[20];
			xyzControlData.VY.chData[1]		= completeSentence[21];
			xyzControlData.VY.chData[2]		= completeSentence[22];
			xyzControlData.VY.chData[3]		= completeSentence[23];
			xyzControlData.VZ.chData[0]		= completeSentence[24];
			xyzControlData.VZ.chData[1]		= completeSentence[25];
			xyzControlData.VZ.chData[2]		= completeSentence[26];
			xyzControlData.VZ.chData[3]		= completeSentence[27];
		break;	
		case FILMSG_ID:
			// turn the filter on
			filterControlData = completeSentence[4];
			
			// turn on the required Aknowledge flag
			aknControlData.filOnOff = 1;
			
		break;	
		case PILMSG_ID: // Pilot Console Commands data
			pilControlData.dt.chData[0]		= completeSentence[4];	
			pilControlData.dt.chData[1]		= completeSentence[5]; 	
			pilControlData.dla.chData[0]	= completeSentence[6];		 	
			pilControlData.dla.chData[1]	= completeSentence[7]; 
			pilControlData.dra.chData[0]	= completeSentence[8];	 
			pilControlData.dra.chData[1]	= completeSentence[9];	 
			pilControlData.dr.chData[0]		= completeSentence[10];	 
			pilControlData.dr.chData[1]		= completeSentence[11];	   
			pilControlData.de.chData[0]		= completeSentence[12];	  
			pilControlData.de.chData[1]		= completeSentence[13];	  
		break;
		
		
		default:
		break;   
	}
}

#ifdef _IN_PC_
float protParseDecode (unsigned char* fromSPI,  FILE* outFile){
#else
void protParseDecode (unsigned char* fromSPI){
#endif
	// Static variables CAREFUL
	static unsigned char prevBuffer[2*MAXLOGLEN];
	static unsigned char previousComplete =1;
	static unsigned char indexLast = 0;
    #ifdef _IN_PC_
         static long long checkSumFail = 0;
         static long long totalPackets = 0;
         static float test = 0.0;
         float alpha = 0.3;
    #endif


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
            #ifdef _IN_PC_
               totalPackets++;
            #endif

			// if the checksum is valid
			if (tmpChksum ==prevBuffer[indexLast]){
				// update the states depending on the message
				updateStates(&prevBuffer[0]);
				// increment the log size
				logSize += (indexLast+1);
                #ifdef _IN_PC_
                    if ((outFile != NULL)){
                       printState(outFile);
                    }
                    //test = alpha*test;
                #endif
			}
            else{
                 #ifdef _IN_PC_
                    checkSumFail++;
                    //test = (1.0-alpha) + alpha*test;
                 #endif
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
    #ifdef _IN_PC_
       if (totalPackets>0){
          //test =  ((float)checkSumFail/(float)totalPackets);
          test = (float)checkSumFail;

       } else {
          test = 0.0;
       }
       return test;
    #endif
}


#ifdef _IN_PC_
void printState (FILE* outFile){
static tGpsData 		cpgpsControlData;
static tRawData 		cprawControlData;
static tSensStatus		cpstatusControlData;
static tAttitudeData	cpattitudeControlData;
static tDynTempData	    cpdynTempControlData;
static tBiasData		cpbiasControlData;
static tDiagData		cpdiagControlData;
static tXYZData		    cpxyzControlData;
static unsigned char    cpfilterControlData;
static tAknData		    cpaknControlData;
static tPilotData		cppilControlData;  

	if (cpattitudeControlData.timeStamp.usData != attitudeControlData.timeStamp.usData) {
		// the time changed, so print the known state in the last sample time
	    // Print Attitude and Position
	    fprintf(outFile, "%hu,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,",
	         cpattitudeControlData.timeStamp.usData,
	         cpattitudeControlData.roll.flData,
	         cpattitudeControlData.pitch.flData,
	         cpattitudeControlData.yaw.flData,
	         cpattitudeControlData.p.flData,
	         cpattitudeControlData.q.flData,
	         cpattitudeControlData.r.flData,
	         cpxyzControlData.Xcoord.flData,
	         cpxyzControlData.Ycoord.flData,
	         cpxyzControlData.Zcoord.flData,
	         cpxyzControlData.VX.flData,
	         cpxyzControlData.VY.flData,
	         cpxyzControlData.VZ.flData);

	    // Print GPS
	    fprintf(outFile, "%d,%d,%d,%d,%d,%d,%f,%f,%f,%d,%d,%d,%d,%d,%d,",
	         cpgpsControlData.year,
	         cpgpsControlData.month,
	         cpgpsControlData.day,
	         cpgpsControlData.hour,
	         cpgpsControlData.min,
	         cpgpsControlData.sec,
	         cpgpsControlData.lat.flData,
	         cpgpsControlData.lon.flData,
	         cpgpsControlData.height.flData,
	         cpgpsControlData.cog.usData,
	         cpgpsControlData.sog.usData,
	         cpgpsControlData.hdop.usData,
	         cpgpsControlData.fix,
	         cpgpsControlData.sats,
	         cpgpsControlData.newValue);

	    // Print Raw Data
	    fprintf(outFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,",
	         cprawControlData.gyroX.usData,
	         cprawControlData.gyroY.usData,
	         cprawControlData.gyroZ.usData,
	         cprawControlData.accelX.usData,
	         cprawControlData.accelY.usData,
	         cprawControlData.accelZ.usData,
	         cprawControlData.magX.usData,
	         cprawControlData.magY.usData,
	         cprawControlData.magZ.usData);


    // Print Bias Data
	    fprintf(outFile, "%f,%f,%f,%f,%f,%f,",
	         cpbiasControlData.axb.flData,
	         cpbiasControlData.ayb.flData,
	         cpbiasControlData.azb.flData,
	         cpbiasControlData.gxb.flData,
	         cpbiasControlData.gyb.flData,
	         cpbiasControlData.gzb.flData);

	    // Print Air Data
	    fprintf(outFile, "%f,%f,%d,",
	         cpdynTempControlData.dynamic.flData,
	         cpdynTempControlData.stat.flData,
	         cpdynTempControlData.temp.shData);

	    // Print Diagnostic Data
    fprintf(outFile, "%f,%f,%f,%d,%d,%d,",
	         cpdiagControlData.fl1.flData,
	         cpdiagControlData.fl2.flData,
	         cpdiagControlData.fl3.flData,
	         cpdiagControlData.sh1.shData,
	         cpdiagControlData.sh2.shData,
	         cpdiagControlData.sh3.shData);

        // Print Sensor MCU Load
       fprintf(outFile, "%d,%d,%d,",
	         cpstatusControlData.load,
	         cpstatusControlData.vdetect,
	         cpstatusControlData.bVolt.usData);

   	// Print Pilot Console Data
    fprintf(outFile, "%d,%d,%d,%d,%d,",
	         cppilControlData.dt.usData,
	         cppilControlData.dla.usData,
	         cppilControlData.dra.usData,
	         cppilControlData.dr.usData,
	         cppilControlData.de.usData);

	    // Add new line
	    fprintf(outFile, "\n");

	}// if

    cpgpsControlData 		= gpsControlData;
	cprawControlData 		= rawControlData;
	cpstatusControlData 	= statusControlData;
	cpattitudeControlData	= attitudeControlData;
	cpdynTempControlData 	= dynTempControlData;
	cpbiasControlData		= biasControlData;
	cpdiagControlData		= diagControlData;
	cpxyzControlData		= xyzControlData;
	cpfilterControlData		= filterControlData;
	cpaknControlData		= aknControlData;
    cppilControlData        = pilControlData;


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

tBiasData getBiasStruct(void){
 return biasControlData;
}

tDiagData getDiagStruct (void){
 return diagControlData;
}

tDynTempData getDynStruct (void){
 return dynTempControlData;
}

tSensStatus getSensStruct (void){
 return statusControlData;
}

tAknData getAknStruct(void){
 return aknControlData;
}

void setAknFilter (unsigned char value){
	aknControlData.filOnOff = value;
}

tPilotData getPilotStruct(void){
	return pilControlData;
}

void getTime (unsigned char * values){
	values[0] = gpsControlData.hour;
	values[1] = gpsControlData.min;
	values[2] = gpsControlData.sec;
}

unsigned char getFilterOnOff (void){
	return filterControlData;
}

// ================================
//  hardware in the loop methods
// ================================

void hil_getRawRead(unsigned short * rawData){
	// data for the bus is as follows:
	// Accel Y
	// Accel Z
	// Gyro X
	// IDG Ref
	// Gyro Y
	// Accel X
	// Gyro Z
	// ADX Ref
	// Mag23
	// Mag01
	// Mag Z
	// Baro
	// Pitot
	// Thermistor
	// Power
/*
	
	*/
	rawData[0] =  	rawControlData.accelY.usData;
	rawData[1] =  	rawControlData.accelZ.usData;
	rawData[2] =  	rawControlData.gyroX.usData;
	rawData[3] = 	0;
	rawData[4] = 	rawControlData.gyroY.usData;
	rawData[5] = 	rawControlData.accelX.usData;
	rawData[6] = 	rawControlData.gyroZ.usData;
	rawData[7] = 	0;
	rawData[8] = 	rawControlData.magY.usData;
	rawData[9] = 	rawControlData.magX.usData;
	rawData[10] = 	rawControlData.magZ.usData;
	rawData[11] = 	(unsigned short)dynTempControlData.dynamic.flData;
	rawData[12] = 	(unsigned short)dynTempControlData.stat.flData;;
	rawData[13] = 	(unsigned short)dynTempControlData.temp.shData;
	rawData[14] = 	770;
	
}

void hil_getGPSRead (unsigned char * gpsMsg){
		// write the output data;
		gpsMsg[0]  = gpsControlData.year;					
		gpsMsg[1]  = gpsControlData.month;					
		gpsMsg[2]  = gpsControlData.day;	
		gpsMsg[3]  = gpsControlData.hour;
		gpsMsg[4]  = gpsControlData.min;
		gpsMsg[5]  = gpsControlData.sec;
		gpsMsg[6]  = gpsControlData.lat.chData[0];
		gpsMsg[7]  = gpsControlData.lat.chData[1];
		gpsMsg[8]  = gpsControlData.lat.chData[2];					
		gpsMsg[9]  = gpsControlData.lat.chData[3];
		gpsMsg[10] = gpsControlData.lon.chData[0];
		gpsMsg[11] = gpsControlData.lon.chData[1];
		gpsMsg[12] = gpsControlData.lon.chData[2];					
		gpsMsg[13] = gpsControlData.lon.chData[3];					
		gpsMsg[14] = gpsControlData.height.chData[0];
		gpsMsg[15] = gpsControlData.height.chData[1];
		gpsMsg[16] = gpsControlData.height.chData[2];					
		gpsMsg[17] = gpsControlData.height.chData[3];					
		gpsMsg[18] = gpsControlData.cog.chData[0];					
		gpsMsg[19] = gpsControlData.cog.chData[1];									
		gpsMsg[20] = gpsControlData.sog.chData[0];					
		gpsMsg[21] = gpsControlData.sog.chData[1];
		gpsMsg[22] = gpsControlData.hdop.chData[0];					
		gpsMsg[23] = gpsControlData.hdop.chData[1];
		gpsMsg[24] = gpsControlData.fix;
		gpsMsg[25] = gpsControlData.sats;									
		gpsMsg[26] = gpsControlData.newValue;								
}

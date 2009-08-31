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

#ifndef _PROTDECODER_H_
#define _PROTDECODER_H_

#include "apDefinitions.h"
#ifdef __BORLANDC__ 
       #include "gsDefinitions.h"
#endif
#include <stdio.h>
#include <string.h>
#include "circBuffer.h"
#include "apUtils.h"


#ifdef __cplusplus
       extern "C"{
#endif

// These are the global data structures that hold the state
// use with care
extern tGpsData 		gpsControlData;
extern tRawData 		rawControlData;
extern tSensStatus		statusControlData;
extern tAttitudeData	attitudeControlData;
extern tAttitudeData	attitudeRotatedControlData;
extern tDynTempData		dynTempControlData;
extern tBiasData		biasControlData;
extern tDiagData		diagControlData;
extern tXYZData			xyzControlData;
extern unsigned char   	filterControlData;
extern tAknData			aknControlData;
extern tPilotData		pilControlData;
extern tPIDData			pidControlData;
extern tPWMData			pwmControlData;
extern tQueryData		queControlData;
extern tWPData			wpsControlData;
extern tAPStatusData	apsControlData;
extern tCommandsData	comControlData;
extern tNavData			navControlData;
extern tSensData senControlData;
extern tLogFloats  logControlData;

void protParserInit (void);

#ifdef _IN_PC_
    float protParseDecode (unsigned char* fromSPI,  FILE* outFile, unsigned char prevException);
    void printState (FILE* outFile, unsigned char prevException);
    void getTime (unsigned char * values);
    tGpsData getGpsStruct (void);
    tRawData getRawStruct (void);
    tXYZData getXYZStruct (void);
    tAttitudeData getAttStruct (void);
    unsigned short getAttTimeStamp(void);
    tAknData getAknStruct (void);
    tBiasData getBiasStruct (void);
    tDynTempData getDynStruct (void);
    tDiagData getDiagStruct (void);
    tSensStatus getSensStruct (void);
    tPilotData getPilotStruct (void);
    tNavData getNavStruct (void);
    tSensData getSensorStruct (void);
    void setAknFilter (unsigned char value);
    void setAknPidCal (unsigned char value);
    void setAknReboot (unsigned char value);
    void setAknSensorReboot (unsigned char value);
    void setAknWpCal (unsigned char value);
    void setAknComCal (unsigned char value);
    tPWMData getPWMStruct (void);
    tPIDData getPidStruct (void);
    tWPData  getWPStruct (void);
	tAPStatusData getAPSStruct (void);   
	tCommandsData getComStruct (void); 
	tLogFloats getLogStruct (void);
    
#else
     void protParseDecode (unsigned char* fromSPI);
     void protParserInit (void);
#endif

void hil_getRawRead (short * rawData);
void hil_getGPSRead (unsigned char * gpsMsg);
void hil_getVned (float* vned);
void hil_getXYZ (float* xyz);
void hil_getEuler (float* euler);
void hil_getRates (float* pqr);
unsigned short hil_getTs (void);

#ifdef __cplusplus
       }
#endif


#endif /* _PROTDECODER_H_ */

#ifndef _APUTILS_H_
#define _APUTILS_H_

#ifdef __cplusplus
       extern "C"{
#endif
#ifdef __BORLANDC__ 
       #include "gsDefinitions.h"
#else
       #include "DEE.h"
#endif

#include <math.h>
#include <string.h>
#include "apDefinitions.h"
#include "protDecoder.h"

// Uncomment if you want to use sensor
// mcu diagnostic  data. Note that you can only
// use diagnostic data from 1 MCU at a time
// 
//#define USE_SENSOR_MCU_DIAG		0

	
unsigned char getChecksum(unsigned char* sentence, unsigned char size);
void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg );
void updateStates(unsigned char * completeSentence);
void assembleRawSentence (unsigned char id, unsigned char indx, unsigned char * data);
void decodeCalSentence (unsigned char id, unsigned char indx, unsigned char * data, unsigned char inBoard);
void decodeCmdsSentence (unsigned char id,unsigned char* data);      	

// Trig and Math Functions
float myAtan2 (float num, float denom);
float myPow (float x, float toTheN);
float mySqrt (float x);
float myAbs (float x);
float myAtan (float x);
float myAsin (float x);
float mySin (float x);
float myCos (float x);
float myTan (float x);
float myAcos (float x);
#ifdef __cplusplus
      }
#endif


#endif /* _APUTILS_H_ */

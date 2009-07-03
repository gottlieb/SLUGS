#ifndef _GPS_H_
#define _GPS_H_


#ifdef __cplusplus
       extern "C"{
#endif
       	
#include "circBuffer.h"
#include "apDefinitions.h"
#ifdef __IN_DSPIC__
	#include <p33fxxxx.h>
	#include <uart.h>
	#include "protDecoder.h"
	#include "apUtils.h"
#endif
#include <stdlib.h>
#include <string.h>


#if DEBUG
	#include <stdio.h>
#endif

#define TOKEN_SIZE	15

#ifdef __IN_DSPIC__       	
	void uartInit (void);
	void gpsSentenceConfig (void);
	void gpsFreqConfig (void);
#else
	extern tGpsData gpsControlData;
	extern CBRef uartBuffer;
#endif

unsigned char hex2char (unsigned char halfhex);
// void gpsRead (unsigned char* gpsChunk);
void gpsInit(void);
unsigned char gpsSeparate(unsigned char* outStream);
void gpsParse (void);
void getGpsMainData (float* data);
float degMinToDeg(unsigned char degrees, float minutes);
char gpSmbl(char symbl);
void parseRMC(unsigned char* stream);
void parseGGA(unsigned char* stream);

#ifdef __cplusplus
       }
#endif
       
#endif /* _GPS_H_ */

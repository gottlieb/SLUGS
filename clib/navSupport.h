#ifndef _NAVSUPPORT_H_
#define _NAVSUPPORT_H_

#ifdef __cplusplus
       extern "C"{
#endif
       	
#include "apDefinitions.h"
#include "protDecoder.h"
       	       	
void getMidLevelCommands (float* commands);
unsigned char apStatus (void);
void getPidIdx (unsigned char idx, float* PID);
float getDynamic (void);
void getAttitude (float* attitude);
void getXYZ (float* xyz);
       	
#ifdef __cplusplus
       }
#endif

#endif /* _NAVSUPPORT_H_ */

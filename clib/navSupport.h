#ifndef _NAVSUPPORT_H_
#define _NAVSUPPORT_H_

#ifdef __cplusplus
       extern "C"{
#endif
       	
#include "apDefinitions.h"
#include "protDecoder.h"
       	       	
void getMidLevelCommands (float* commands);
unsigned char isApManual (void);
void getPidIdx (unsigned char idx, float* PID);
float getDynamic (void);
void getAttitude ( float* attitude);
void getXYZ (float* xyz);
unsigned char getMaxWp (void);
unsigned char isWpFly (void);
void setDiagnosticFloat (float * flValues);
void setDiagnosticShort (short* shValues);
void getWP (unsigned char idx, float* WPpos);
void setDiagnosticAb (float * flValues);
void setDiagnosticGb (float * flValues);
unsigned char getApControlType (void);
unsigned char getPassValues (unsigned char * pasVals);
void setCurrentCommands (float airSpeed);
unsigned char quickSort (unsigned short *arr, char elements);
// void bufferICValues (unsigned short latest, unsigned short* history);
unsigned short meanFilter5 (unsigned short * values);
void setNavLong (float* values);
void setNavLat (float* values);
void setNavNav (float* values);
void setLogFloat1 (float * flValues);
void setLogFloat2 (float * flValues);
void getVned (float* xyz) ;
#ifdef __cplusplus
       }
#endif

#endif /* _NAVSUPPORT_H_ */

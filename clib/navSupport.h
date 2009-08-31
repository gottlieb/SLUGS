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

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

#ifndef _GROUNDSTATIONDRIVER_H_
#define _GROUNDSTATIONDRIVER_H_

#ifdef __cplusplus
       extern "C"{
#endif

#include "circBuffer.h"
#include "apDefinitions.h"
#include "protDecoder.h"
#include "apUtils.h"
#include <p33fxxxx.h>
#include <string.h>
#include <uart.h>
#include "DEE.h"
#include "interProcCommSlave.h"
       	
void uart1Init (void);
void gsRead (unsigned char* gsChunk);       	
void prepareTelemetry ( unsigned char* dataOut);
void updatePWM (unsigned short * PWMData);
void updatePWM2 (unsigned short PWMData, unsigned char channel );
void updateLoad (unsigned char mcuLoad);
void controlMCUInit (void);
void EEPInit (void);
void loadEEPData (void);
void pilotCommands (unsigned short* pilCom);
void updateEuler (float* newEuler);
void updatePQR (float* newPQR);
#ifdef __cplusplus
      }
#endif


#endif /* _GROUNDSTATIONDRIVER_H_ */

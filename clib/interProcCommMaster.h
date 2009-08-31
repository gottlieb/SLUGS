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

#ifndef _INTERPROCCOMMMASTER_H_
#define _INTERPROCCOMMMASTER_H_

#ifdef __cplusplus
       extern "C"{
#endif
       	
#include "apDefinitions.h"
#include "circBuffer.h"
#include <p33fxxxx.h>
#include <spi.h>
// #include "gpsSplit.h"
// #include "bufferedUART.h" //
#include "gps.h"
#include "dataLogger.h"
#include "protDecoder.h"   
#include "magneto.h"
#include "adisCube.h"

void spiMasterInit (void);
void spiSend (unsigned char * data2Send);
void sensorMCUInit (void);       	

#ifdef __cplusplus
       }
#endif
       	

#endif /* _INTERPROCCOMMMASTER_H_ */

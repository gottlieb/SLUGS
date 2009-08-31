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

#ifndef _MAGNETO_H_
#define _MAGNETO_H_
#ifdef __cplusplus
       extern "C"{
#endif

#include <p33fxxxx.h>
#include <i2c.h>
#include "apDefinitions.h"
#include "protDecoder.h"
#include "apUtils.h"
#include <uart.h>


// Magnetomertometer Data
#define MAG_READ		0x3D
#define	MAG_WRITE		0x3C
#define REGISTER_A		0x00
#define REGISTER_B		0x01
#define MODE_REGISTER	0x02

// Configuration Settings
#define	MODE_50_HZ		0x18		
#define MODE_CONTINUOS	0x00

//  I2C State Machine Defines

// Configuration State Machine
#define CONFIG_IDLE		0
#define CONFIG_START	1
#define CONFIG_IDTX		2
#define CONFIG_REG_TX	3
#define CONFIG_VAL_TX	4
#define CONFIG_DONE		5
#define CONFIG_STOP		6

// Reading State Machine
#define	READ_IDLE		10
#define READ_START		11
#define READ_IDTX		12
#define READ_RESTART	13
#define READ_REGADD		14
#define READ_IDADD2		15
#define	READ_DATA		16
#define READ_DONE		17
#define	READ_STOP		17

void magnetoInit (void);
void startMagRead (void);   
void i2c1Start (void);    	
void i2c1Stop (void);
void i2c1Write (unsigned char byte2write);
void dummyDelay (void);

#ifdef __cplusplus
       }
#endif

#endif /* _MAGNETO_H_ */

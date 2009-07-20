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

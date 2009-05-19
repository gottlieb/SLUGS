#ifndef _ADISCUBE_H_
#define _ADISCUBE_H_
#ifdef __cplusplus
    extern "C"{
#endif
#include <p33fxxxx.h>
#include <spi.h>
#include "apDefinitions.h"
#include "protDecoder.h"
#include "magneto.h"

#define selectCube()		LATGbits.LATG9 = 0
#define deselectCube()		LATGbits.LATG9 = 1
#define cubeDataReady()		PORTCbits.RC3

#define BITMASK_14		(unsigned short)0x3FFF
#define BITMASK_12		(unsigned short)0x0FFF

#define BITTEST_14		(unsigned short)0x2000
#define BITTEST_12		(unsigned short)0x0800

#define BITEXTEND_14	(unsigned short)0xC000
#define BITEXTEND_12	(unsigned short)0xF000


// Register Addresses
// ==================
// Note that FOR READING register addresses are in the MSB, assigning dont cares
// to the LSB
#define R_ADISPWR   	(unsigned short)0x0300		// ADIS Power Supply 
#define R_GYROX     	(unsigned short)0x0500		// X-CHANNEL GYRO 
#define R_GYROY     	(unsigned short)0x0700		// Y-CHANNEL GYRO 
#define R_GYROZ     	(unsigned short)0x0900		// Z-CHANNEL GYRO 
#define R_ACCELX    	(unsigned short)0X0B00		// X-CHANNEL ACCEL
#define R_ACCELY    	(unsigned short)0x0C00		// Y-CHANNEL ACCEL 
#define R_ACCELZ    	(unsigned short)0x0F00		// Z-CHANNEL ACCEL
#define R_TEMPX     	(unsigned short)0x1100		// X-CHANNEL TEMP
#define R_TEMPY     	(unsigned short)0x1300		// Y-CHANNEL TEMP
#define R_TEMPZ     	(unsigned short)0x1500		// Z-CHANNEL TEMP
#define R_STATUS    	(unsigned short)0x3D00		// STATUS REGISTER

// Note that FOR WRITING register addresses are in the MSB and the actual data
// to write is in the LSB

// Startup Config Values
// =====================
/*
Calibration
We will use the precission bias null calibration. That requires the unit to be static for 30 seconds.
Address = 0x3E
Value   = 0x10
bits [6:7] of Address must be [1 0] since this will be a write
=> [1 0 1 1][1 1 1 0][0 0 0 1][0 0 0 0]
=> 0xBE10

we will also use the acceleration bias compensation and use the
DIO pin in the cube to let us know when data is ready

Address = 0x34
Value   = 0x86
bits [6:7] of Address must be [1 0] since this will be a write
=> [1 0 1 1][1 1 1 0][1 0 0 0] [0 1 1 0]
=> 0xB486

*/

#define W_COMMAND_FULLCAL	(unsigned short)0xBE10		//Start full calibration
#define W_COMMAND_QUICKCAL	(unsigned short)0xBE01		//Start Quick calibration
#define W_MSC_CTRL			(unsigned short)0xB486		// Set DIO1 as data ready pin

/*
Definition of the Internal Sample Rate

Ts = Tb(Ns+1) , where
	 Ts is Sample Time (1/Fs)
	 Tb is time base, it is either 0.61035e-3 S or 18.921e-3 S
	 Ns is the multiplier, which is configured in register SMPL_PRD
	 
So desired Ts = 0.0025 (400Hz) then
	 0.0025 = 0.61035e-3 * (3.096 + 1)
	 => Choose multiplier as 3 => Ts = 2.4e-3 S => Fs= 409.601 Hz

So the register configuration is as follows:
Address = 0x36
Value   = 0x03
bits [6:7] of Address must be [1 0] since this will be a write
=> [1 0 1 1][0 1 1 0][0 0 0 0][0 1 1 1]
=> 0xB603
*/
#define W_SMPL_PRD  	(unsigned short)0xB603		// INTERNAL SAMPLE RATE

/*
Digital Filtering and Dynamic Range

The dynamic range will be set to 300 deg/s and the taps at the minimum 4.
Since this configuration spans two registers it will be done in two steps,
by the data sheet recomendation, sensitivity first, then taps.

Address	= 0x39
Value	= 0x04
bits [6:7] of Address must be [1 0] since this will be a write
=> [1 0 1 1][1 0 0 1][0 0 0 0][0 1 0 0]
=> 0xB904

The taps will be set at the minimum of 4  (therefore the value is 2 since
they are powers of 2)
Address	= 0x38
Value	= 0x04
bits [6:7] of Address must be [1 0] since this will be a write
=> [1 0 1 1][1 0 0 0][0 0 0 0][0 1 0 0]
=> 0xB804

*/
#define W_SENS_AVG_H  	(unsigned short)0xB904		// DYNAMIC RANGE
#define W_SENS_AVG_L  	(unsigned short)0xB804		// DIGITAL FILTERING

#define W_MSC_CTRL_SELFTEST (unsigned short)0xB504
/*
Sleeping
*/

#define W_SLP_CNT		(unsigned short)0xBA00		// DONT SLEEP

unsigned short write2Cube (unsigned short data2Send);
void getCubeData (short * cubeData);
void startCubeRead (void);
void initDevBoard (void);
short convert12BitToShort (short wordData);
short convert14BitToShort (short wordData);
	
#ifdef __cplusplus
    }
#endif
#endif /* _ADISCUBE_H_ */

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
#include <stdlib.h>
#include <stdarg.h>
#include "mavlink.h"

// Uncomment if you want to use sensor
// mcu diagnostic  data. Note that you can only
// use diagnostic data from 1 MCU at a time
// 
//#define USE_SENSOR_MCU_DIAG		1

extern mavlink_gps_raw_t	mlGpsData;
extern mavlink_cpu_load_t	mlCpuLoadData;
extern mavlink_air_data_t	mlAirData;
extern mavlink_sensor_bias_t	mlSensorBiasData;
extern mavlink_diagnostic_t	mlDiagnosticData;
extern mavlink_pilot_console_t mlPilotConsoleData;
extern mavlink_pwm_commands_t mlPwmCommandsData;
extern mavlink_raw_imu_t mlRawImuData;
extern mavlink_raw_pressure_t mlRawPressureData;
extern mavlink_attitude_t mlAttitudeData;
extern mavlink_local_position_t mlLocalPositionData;




	
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
float myExp (float x);

#ifndef _IN_PC_
void printToUart2 (const char *fmt, ...);
#endif

#ifdef __cplusplus
      }
#endif


#endif /* _APUTILS_H_ */

// ==============================================================
// dataLogger.c
// This is code implements a fully DMA driven UART writer to
// be used in the UCSC Autopilot project. It makes use of the 
// circular buffer data structure circBuffer.c. It has been 
// written to be implemented in Simulink. It configures UART 2
// at a predefined baud rate, then initializes a circular buffer,
// configures the DMA and starts the service. 
// The main function logData writes data to UART2 in the predefined
// comm protocol and returns data in the comm protocol to be sent
// via SPI to the second MCU. 
// 
// Code by: Mariano I. Lizarraga
// First Revision: Aug 26 2008 @ 21:15
// =========================================================

#ifndef _DATALOGGER_H_
#define _DATALOGGER_H_

#include "apDefinitions.h"
#include "circBuffer.h"
#include "apUtils.h"
#include <string.h>
#include <p33fxxxx.h>
#include <uart.h>

void assembleMsg (unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg );
void copyBufferToDMA (unsigned char size);
void logData (unsigned char hilOn, unsigned char* data4SPI);
void hilRead (unsigned char* hilChunk);
void loggerInit (void);
void updateRawADCData (short * adcData);
void updateAirData (float* airData);
void updateLoadData (unsigned char load, unsigned short mvPower);
void updateAttitude (float * attitudeData);
void updatePosition (float * posData);
void updateTimeStamp (unsigned short timeSt);
void updatePilotConsole (unsigned short * pilData);
void updateDiagnosticFl (float* diagFl);
void updateDiagnosticSh (short* diagSh);
void updateBias (float * biasData); 

#endif /* _DATALOGGER_H_ */


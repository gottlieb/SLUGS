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

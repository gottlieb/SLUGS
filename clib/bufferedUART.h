#ifndef _BUFFEREDUART_H_
#define _BUFFEREDUART_H_


#ifdef __cplusplus
       extern "C"{
#endif
       	
#include "circBuffer.h"
#include "apDefinitions.h"
#include <p33fxxxx.h>
#include <uart.h>
       	
void gpsSentenceConfig (void);
void gpsFreqConfig (void);
void uartInit (void);
void gpsRead (unsigned char* gpsChunk);

#ifdef __cplusplus
       }
#endif
       
#endif /* _BUFFEREDUART_H_ */

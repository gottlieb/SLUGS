#ifndef _APUTILS_H_
#define _APUTILS_H_

#ifdef __cplusplus
       extern "C"{
#endif
#ifdef __BORLANDC__ 
       #include "gsDefinitions.h"
#endif

#include <math.h>
#include "apDefinitions.h"
#include "protDecoder.h"



float myAtan2(float num, float denom);
unsigned char getChecksum(unsigned char* sentence, unsigned char size);
void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg );
void updateStates(unsigned char * completeSentence);
       	
#ifdef __cplusplus
      }
#endif


#endif /* _APUTILS_H_ */

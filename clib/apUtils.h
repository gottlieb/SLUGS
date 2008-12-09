#ifndef _APUTILS_H_
#define _APUTILS_H_

#ifdef __cplusplus
       extern "C"{
#endif
#include <math.h>       	

float myAtan2(float num, float denom);       	
unsigned char getChecksum(unsigned char* sentence, unsigned char size);
void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg );
       	
#ifdef __cplusplus
      }
#endif


#endif /* _APUTILS_H_ */

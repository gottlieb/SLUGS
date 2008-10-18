#ifndef _CONVERSIONS_H_
#define _CONVERSIONS_H_

#ifdef __cplusplus
       extern "C"{
#endif
       	
float bytesToFloat (unsigned char* inBytes);
void floatToBytes (float inFloat, unsigned char* inBytes);
unsigned short bytesToUShort (unsigned char* inBytes);


#ifdef __cplusplus
       }
#endif
       
#endif /* _CONVERSIONS_H_ */

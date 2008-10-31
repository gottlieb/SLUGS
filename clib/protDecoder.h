#ifndef _PROTDECODER_H_
#define _PROTDECODER_H_

#include "apDefinitions.h"


#ifdef __cplusplus
       extern "C"{
#endif

void protParserInit (void);
void protParseDecode (unsigned char* fromSPI, unsigned char* toLog);
void getTime (unsigned char * values);
tGpsData getGpsStruct (void);
tRawData getRawStruct (void);
tXYZData getXYZStruct (void);
tAttitudeData getAttStruct (void);
tAknData getAknStruct (void);
void setAknFilter (unsigned char value);

#ifdef __cplusplus
       }
#endif


#endif /* _PROTDECODER_H_ */

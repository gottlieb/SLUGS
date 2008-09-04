#ifndef _PROTDECODER_H_
#define _PROTDECODER_H_

void protParserInit (void);
void protParseDecode (unsigned char* fromSPI);
void getTime (unsigned char * values);

#endif /* _PROTDECODER_H_ */

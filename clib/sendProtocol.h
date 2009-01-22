#ifndef _SENDPROTOCOL_H_
#define _SENDPROTOCOL_H_

#include "apDefinitions.h"
#include "circBuffer.h"
#include "protDecoder.h"
#include "apUtils.h"
#include <p33fxxxx.h>
#include <uart.h>
#include <string.h>


#ifdef __cplusplus
       extern "C"{
#endif
	void commProtInit (void);
	void txProtocol (unsigned char* protData);       	
	void prepareLog (unsigned char* dataOut);

#ifdef __cplusplus
       }
#endif

#endif /* _SENDPROTOCOL_H_ */

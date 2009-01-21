#ifndef _INTERPROCCOMMSLAVE_
#define _INTERPROCCOMMSLAVE_

#include "apDefinitions.h"
#include "circBuffer.h"
#include <p33fxxxx.h>
#include <spi.h>
#include <stdlib.h>
#include <stdarg.h>


void spiSlaveInit (void);
void printToUart2 (const char *fmt, ...);
void readIpc (unsigned char* bufferedData);


#endif /* _INTERPROCCOMMSLAVE_ */

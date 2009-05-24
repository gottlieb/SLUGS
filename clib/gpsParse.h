#ifndef _GPSPARSE_H_
#define _GPSPARSE_H_

/* ==============================================================
This file implements the GPS parsing of 2 sentences, GGA & RMC 
it receives an incomming stream of data already splitted and
verified, as well as an indication of a message type and if
the checksum worked. It splits the data into meaningful messages
and are assembled accordingly.

  This code was written specifically to work in Simulink so
inStream and outStream are of fixed length (n & m respectively)

 Code by: Mariano I. Lizarraga
 First Revision: Aug 18 2008 @ 17:50
 ==============================================================


Parameters
in_stream  [1...n-1]	... Incomming GPS Sentence
in_stream [0] 			...	GPS Sentence Type
in_stream[n]			... IsValid flag
*/
#include "apDefinitions.h"
#include <string.h>
#include <stdlib.h>
#include "protDecoder.h"

#if DEBUG
	#include <stdio.h>
#endif

#ifdef __cplusplus
       extern "C"{
#endif
       	
void gpsParse (unsigned char* inStream);
void getGpsMainData (float* data);
#ifdef __cplusplus
       }
#endif
       
#endif /* _GPSPARSE_H_ */

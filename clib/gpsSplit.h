/* ==============================================================
This file header file implements the GPS splitting of sentences, it receives
the incomming stream of data into a circular buffer, it then
splits it in sentences, verifies the checksum, clasifies them
accordingly and sends them to the next Simulink block for
parsing.

  This code was written specifically to work in Simulink so
inStream and outStream are of fixed length (n & m respectively)

 Code by: Mariano I. Lizarraga
 First Revision: Aug 18 2008 @ 17:42
 ==============================================================


Parameters
in_stream  [1...n]	... Raw incomming byte stream as it is read from the serial port
in_stream [0] 		...	Byte containing the amount of new bytes
out_stream [1...m] 	... Output sentece containing exactly one message
out_stream [0]		... Byte containing the Message type
out_stream [m+1]	...	Byte indicating wether there is a valid message
*/

#ifndef _GPSSPLIT_H_
#define _GPSSPLIT_H_

#ifdef __cplusplus
       extern "C"{
#endif

void gpsInit(void);
void gpsSeparate(unsigned char* inStream, unsigned char* outStream);
unsigned char getChecksum(unsigned char* sentence, unsigned char size);

#ifdef __cplusplus
       }
#endif

#endif /* _GPSSPLIT_H_ */


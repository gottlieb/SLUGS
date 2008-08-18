/* ==============================================================
The following function receives a raw input stream and
produces an output stream with split sentences ready to
parse. The checksum is validated. The function, which
will be a simulink C function call.

  This code was written specifically to work in Simulink so
inStream and outStream are of fixed length (n & m respectively)

// Code by: Mariano I. Lizarraga
// First Revision: Aug 16 2008 @ 00:36
// ==============================================================


Parameters
in_stream  [1...n]	... Raw incomming byte stream as it is read from the serial port
in_stream [0] 		...	Byte containing the amount of new bytes
out_stream [1...m] 	... Output sentece containing exactly one message
out_stream [0]		... Byte containing the Message type
out_stream [m+1]	...	Byte indicating wether there is a valid message
*/


#include "circBuffer.h"
#include <stdlib.h>

#ifdef DEBUG
	#include <stdio.h>
#endif

// GPS Checksum Messages
#define GGACS	86
#define RMCCS	75

// Circular Buffer and Out Message size
#define BSIZE	127
#define MSIZE	127

// Standard characters to parse the message
#define DOLLAR	36
#define STAR	42
#define CR		13
#define LF		10

// Global Circular buffer
CBRef serBuffer;

// call this from Simulink to initialize the circular buffer
void gpsInit(void){
	serBuffer = newCircBuffer(BSIZE);
}

// GPS checksum code based on 
// http://www.codeproject.com/KB/mobile/WritingGPSApplications2.aspx
// original code in C# written by Jon Person, author of "GPS.NET" (www.gpsdotnet.com)
unsigned char getChecksum(unsigned char* sentence, unsigned char size){

    // Loop through all chars to get a checksum
    unsigned char checkSum = 0;
	unsigned char i;
	for (i = 0; i< size; i++)
    {
      if (sentence[i] == DOLLAR)
      {
        // Ignore the dollar sign
      }
      else if (sentence[i] == STAR)
      {
        // Stop processing before the asterisk
        break;
      }
      else
      {
        // Is this the first value for the checksum?
        if (i == 0)
        {
          // Yes. Set the checksum to the value
          checkSum = sentence[i];
        }
        else
        {
          // No. XOR the checksum with this character's value
	       /*#ifdef DEBUG
	       	printf("%d XOR %d = %d\n", checkSum, sentence[i], checkSum ^ sentence[i]);
	       #endif*/
	       checkSum ^= sentence[i];
        }
      }
    }
    // Return the checksum 
    return checkSum;
}

// this function converts one hex ascii character to decimal
// used for the checksum comparison
unsigned char hex2char (unsigned char halfhex){
	if ((halfhex - 48) < 9) {
		return (halfhex -48);
	}
	return (halfhex - 55);
}


// this function reads the serial stream as it comes in
// then assembles full messages, verifies the checksum and
// if valid sends it out to the parser
void gpsSeparate(unsigned char* inStream, unsigned char* outStream)
{
	// Static variables CAREFUL
	static unsigned char outBuf [MSIZE] ={0};
	static unsigned char previousComplete = 1;
	static unsigned char indexLast = 0;
	
	// local variables
	unsigned char i;
	unsigned char tmpChksum = 0;
	unsigned char chsmStr_0, chsmStr_1;
	unsigned char isValid =0;
	unsigned char chksumHeader = 0;
	unsigned char tmpIndex = 0;

	// read the new values to the buffer
	for (i=1; i<=inStream[0]; i++){
		writeBack(serBuffer, inStream[i]);
	}
	#ifdef DEBUG
		printf("Data Received\n");
		printCircBuf(serBuffer);
	#endif
	
	
	// If the previous message was complete, then
	// go over the buffer and advance until you find a dollar sign
	if (previousComplete){
		while (getLength(serBuffer)>0 && peak(serBuffer)!= DOLLAR){
			readFront(serBuffer);
		}
	} 
	#ifdef DEBUG
		printf("Data Read up to dollar sign\n");
		printCircBuf(serBuffer);
	#endif
	
	// read until you find a CR or run out of bytes to read
	while (getLength(serBuffer)>0 && peak(serBuffer)!= CR){
		outBuf[indexLast] = readFront(serBuffer);
		indexLast++;
	}
	#ifdef DEBUG
		printf("Read until CR or out of bytes\n");
		printCircBuf(serBuffer);
	#endif

	// if we found a carriage return, then the message is complete
	if (peak(serBuffer)== CR){
		#ifdef DEBUG
			printf("%d\n", peak(serBuffer));
		#endif
		// validate the checksum
		chsmStr_0 = hex2char(outBuf[indexLast - 2]);
		chsmStr_1 = hex2char(outBuf[indexLast - 1]);
		// convert the hex checksum to decimal
		tmpChksum = (unsigned char)(chsmStr_0 * 16 + chsmStr_1);
		// verify the validity
		isValid = (tmpChksum == getChecksum(outBuf,indexLast));
		#ifdef DEBUG
			printf("%c%c %d\n", chsmStr_0,chsmStr_1,getChecksum(outBuf,indexLast));
			printf("%d \n", tmpChksum);
		#endif
		
		// turn on the flag of complete stream
		previousComplete = 1;
		
		// set the outStream valid flag
		outStream[MSIZE-1] = isValid;
		
		// save the index value for copying purposes
		tmpIndex = indexLast;
		
		// reset the array index
		indexLast = 0;			
	} else { // if we did not find a CR, i.e. we ran out of bytes
		// turn off the previousComplete flag
		previousComplete = 0;
	}
	
	// If we found a complete sentence and it is valid
	if(previousComplete && isValid)
	{
		// copy the data to the outstream
		for(i = 1; i <= tmpIndex; ++i)
		{
			outStream[i] = outBuf[i-1];
		}

		// finally compute the type of message
		chksumHeader = getChecksum(outBuf,6);
		#ifdef DEBUG
			printf("Header Checksum: %d \n", chksumHeader);
		#endif
		
		// based on the obtained header checksum set the type
		switch (chksumHeader){
			case GGACS: 
				outStream[0] = 1;
				break;
			case RMCCS:
				outStream[0] = 2;
				break;
			default:
				outStream[0] = 254;
				break;
		}
	}
}


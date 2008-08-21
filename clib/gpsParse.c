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

// global structure to hold the GPS data
tGpsData gpsData;

char gpSmbl(char symbl)
{	
	switch (symbl)
	{	case 'N': return 1; /*North*/
		case 'E': return 1; /*East*/
		case 'S': return -1;/*South*/
		case 'W': return -1;/*West*/
		case 'A': return 4; /*Valid or Autonomous*/
		case 'D': return 5; /*Differential*/
		case 'V': return 6; /*Non-Valid*/
		case 'M': return 7; /*Meters*/
		default:  return 6; /*Non-Valid*/
	}
}

void parseRMC(unsigned char* stream){
	// declare the local vars
	char * token;
	char tmp [4] ={0}, tokLen = 0;
	
	// initialize tokenizer, let go first token which holds the msg type
	token = strtok(stream, ",");
	
	// 1.- hhmmss.ssss
	token = strtok(NULL, ",");
	//tokLen = strlen(token);
	tmp[0] = token[0]; tmp[1] = token[1];
	gpsData.hour = (unsigned char) atoi(tmp);
	tmp[0] = token[2]; tmp[1] = token[3];
	gpsData.min = (unsigned char) atoi(tmp);
	tmp[0] = token[4]; tmp[1] = token[5];
	gpsData.sec = (unsigned char) atoi(tmp);
}

void gpsParse(unsigned char* inStream, unsigned char * parsedData){

	// if the sentence is valid
	if(inStream[MSIZE-1]==1)
	{
		// parse the data according to the header
		switch (inStream[0]){
			case RMCID:
				parseRMC(inStream);
				break;
			case GGAID:
				//parseGGA(inStream);
				break;
			default:
				break;
		}
		// write the output data;
		parsedData[0] = gpsData.hour;
		parsedData[1] = gpsData.min;
		parsedData[2] = gpsData.sec;		
	}
}


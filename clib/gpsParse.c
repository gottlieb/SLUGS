/* ==============================================================
This file implements the GPS parsing of 2 sentences, GGA & RMC 
it receives an incomming stream of data already splitted and
verified, as well as an indication of a message type and if
the checksum worked. It splits the data into meaningful messages
and are assembled accordingly.

  This code was written specifically to work in Simulink so
inStream and outStream are of fixed length (n & m respectively)

 Code by: Mariano I. Lizarraga
 First Revision: Aug 21 2008 @ 17:50
 ==============================================================


Parameters
in_stream  [1...n-1]	... Incomming GPS Sentence
in_stream [0] 			...	GPS Sentence Type
in_stream[n]			... IsValid flag
*/

#include "apDefinitions.h"
#include <string.h>
#include <stdlib.h>
#if DEBUG
	#include <stdio.h>
#endif

// global structure to hold the GPS data
tGpsData gpsData;

char gpSmbl(char symbl)
{	
	switch (symbl)
	{	case 'N': return 1; /*North*/
		case 'E': return 1; /*East*/
		case 'S': return -1;/*South*/
		case 'W': return -1;/*West*/
		case 'A': return 1; /*Valid or Autonomous*/
		case 'D': return 1; /*Differential*/
		case 'V': return 0; /*Non-Valid*/
		case 'M': return 100; /*Meters*/
		default:  return 0; /*Non-Valid*/
	}
}

float degMinToDeg(unsigned char degrees, float minutes){
	return ((float)degrees + minutes/60.0);
}

void parseRMC(unsigned char* stream){
	// declare the local vars
	char * token;
	char tmp [3] ={0,0,'\0'}, tmp3[4]={0,0,0,'\0'};
	unsigned char chTmp = 0;
	
	// initialize tokenizer, let go first token which holds the msg type
	token = strtok(stream, ",");
	
	// 1.- hhmmss.ssss
	token = strtok(NULL, ",");
	if (strlen(token)>5){
		tmp[0] = token[0]; tmp[1] = token[1];
		gpsData.hour = (unsigned char) atoi(tmp);
		tmp[0] = token[2]; tmp[1] = token[3];
		gpsData.min = (unsigned char) atoi(tmp);
		tmp[0] = token[4]; tmp[1] = token[5];
		gpsData.sec = (unsigned char) atoi(tmp);		
	}
	
	// 2.- Status of position Fix
	token = strtok(NULL, ",");
	if (strlen(token)== 1){
		gpsData.fix = gpSmbl((char)token[0]);
	}
	
	// 3.- Latitude
	// ddmm.mmmmmm
	token = strtok(NULL, ",");
	if (strlen(token)>0){
		// get the first two values
		tmp[0] = token[0]; tmp[1] = token[1];
		// get the degrees
		chTmp = (unsigned char)atoi(tmp);
		// make the degrees zero for minutes conversion
		token[0]='0'; token[1]='0';
		// get the float
		gpsData.lat.flData =  degMinToDeg(chTmp,atof(token));
		
		// 4.- Latitude Sector
		token = strtok(NULL, ",");
		#if DEBUG
			printf("\nToken :%d\n", token[0]);
			printf("\nToken Len:%d\n", strlen(token));
		#endif
		if (strlen(token)==1){
			// set the sign of the float value
			gpsData.lat.flData *= gpSmbl((char)token[0]);
		}
	}
	
	// 5.- Longitude
	// ddmm.mmmmmm
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		// get the first two values
		tmp3[0] = token[0]; tmp3[1] = token[1]; tmp3[2] = token[2];
		// get the degrees
		chTmp = (unsigned char)atoi(tmp3);
		// make the degrees zero for minutes conversion
		token[0]='0'; token[1]='0'; token [2] = '0';
		// get the float
		gpsData.lon.flData =  degMinToDeg(chTmp,atof(token));
		
		// 6.- Longitude Sector
		token = strtok(NULL, ",");
		#if DEBUG
			printf("\nToken :%d\n", token[0]);
			printf("\nToken Len:%d\n", strlen(token));
		#endif
		if (strlen(token)==1){
			// set the sign of the float value
			gpsData.lon.flData *= gpSmbl((char)token[0]);
		}
	}
	
	// 7.- SOG in knots but gets stored in cm/s CAUTION
	// xx.xx
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		gpsData.sog.usData = (unsigned short) (atof(token)*KTS2MPS*100.0);	
	}
	
	// 8.- COG in degrees
	// xxx.xxx
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		gpsData.cog.usData = (unsigned short) atof(token);	
	}
	
	// 9.- UTC Date
	// ddmmyy
	token = strtok(NULL, ",");	
	if (strlen(token)>5){
		// get day
		tmp[0]= token[0]; tmp[1]=token[1];
		gpsData.day = (unsigned char) atoi(tmp);	
		// get month
		tmp[0]= token[2]; tmp[1]=token[3];
		gpsData.month = (unsigned char) atoi(tmp);	
		// get year
		tmp[0]= token[4]; tmp[1]=token[5];
		gpsData.year = (unsigned char) atoi(tmp);	
	}
	
	// turn the flag on of new data
	gpsData.newValue = 1;
}

void parseGGA(unsigned char* stream){
	// declare the local vars
	char * token;
	char tmp [3] ={0,0,'\0'}, tmp3[4]={0,0,0,'\0'};
	unsigned char chTmp = 0;
	
	// initialize tokenizer, let go first token which holds the msg type
	token = strtok(stream, ",");
	
	// 1.- hhmmss.ssss
	token = strtok(NULL, ",");
	if (strlen(token)>5){
		tmp[0] = token[0]; tmp[1] = token[1];
		gpsData.hour = (unsigned char) atoi(tmp);
		tmp[0] = token[2]; tmp[1] = token[3];
		gpsData.min = (unsigned char) atoi(tmp);
		tmp[0] = token[4]; tmp[1] = token[5];
		gpsData.sec = (unsigned char) atoi(tmp);		
	}	
	// 2.- Latitude
	// ddmm.mmmmmm
	token = strtok(NULL, ",");
	if (strlen(token)>0){
		// get the first two values
		tmp[0] = token[0]; tmp[1] = token[1];
		// get the degrees
		chTmp = (unsigned char)atoi(tmp);
		// make the degrees zero for minutes conversion
		token[0]='0'; token[1]='0';
		// get the float
		gpsData.lat.flData =  degMinToDeg(chTmp,atof(token));		
		// 3.- Latitude Sector
		token = strtok(NULL, ",");
		#if DEBUG
			printf("\nToken :%d\n", token[0]);
			printf("\nToken Len:%d\n", strlen(token));
		#endif
		if (strlen(token)==1){
			// set the sign of the float value
			gpsData.lat.flData *= gpSmbl((char)token[0]);
		}
	}
	
	// 4.- Longitude
	// ddmm.mmmmmm
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		// get the first two values
		tmp3[0] = token[0]; tmp3[1] = token[1]; tmp3[2] = token[2];
		// get the degrees
		chTmp = (unsigned char)atoi(tmp3);
		// make the degrees zero for minutes conversion
		token[0]='0'; token[1]='0'; token [2] = '0';
		// get the float
		gpsData.lon.flData =  degMinToDeg(chTmp,atof(token));
		
		// 5.- Longitude Sector
		token = strtok(NULL, ",");
		#if DEBUG
			printf("\nToken :%d\n", token[0]);
			printf("\nToken Len:%d\n", strlen(token));
		#endif
		if (strlen(token)>0){
			// set the sign of the float value
			gpsData.lon.flData *= gpSmbl((char)token[0]);
		}
	}
	
	// 6.- Quality Indicator
	token = strtok(NULL, ",");
	if (strlen(token)== 1){
		gpsData.fix = (char)atoi(token);
	}

	// 7.- Sats used in solution
	// xx
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		gpsData.sats = (unsigned char) atoi(token);	
	}
	
	// 8.- HDOP given from 0 to 99.99 but stored from 0 - 990 
	//in integers, i.e HDOP = HDOP_stored/100 CAUTION
	// xx.xx
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		gpsData.hdop.usData = (unsigned short) (atof(token)*10.0);	
	}
	
	// 9.- Altitude above mean sea level given in meters
	// xxx.xxx
	token = strtok(NULL, ",");	
	if (strlen(token)>0){
		gpsData.height.flData =  atof(token);	
	}
	
	// turn the flag on of new data
	gpsData.newValue = 1;
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
	}else{
		// turn the flag on of new data
		gpsData.newValue = 0;
	}
		// write the output data;
		parsedData[0]  = gpsData.year;					
		parsedData[1]  = gpsData.month;					
		parsedData[2]  = gpsData.day;	
		parsedData[3]  = gpsData.hour;
		parsedData[4]  = gpsData.min;
		parsedData[5]  = gpsData.sec;
		parsedData[6]  = gpsData.lat.chData[0];
		parsedData[7]  = gpsData.lat.chData[1];
		parsedData[8]  = gpsData.lat.chData[2];					
		parsedData[9]  = gpsData.lat.chData[3];					
		parsedData[10] = gpsData.lon.chData[0];
		parsedData[11] = gpsData.lon.chData[1];
		parsedData[12] = gpsData.lon.chData[2];					
		parsedData[13] = gpsData.lon.chData[3];					
		parsedData[14] = gpsData.height.chData[0];
		parsedData[15] = gpsData.height.chData[1];
		parsedData[16] = gpsData.height.chData[2];					
		parsedData[17] = gpsData.height.chData[3];					
		parsedData[18] = gpsData.cog.chData[0];					
		parsedData[19] = gpsData.cog.chData[1];									
		parsedData[20] = gpsData.sog.chData[0];					
		parsedData[21] = gpsData.sog.chData[1];
		parsedData[22] = gpsData.hdop.chData[0];					
		parsedData[23] = gpsData.hdop.chData[1];
		parsedData[24]  = gpsData.fix;
		parsedData[25]  = gpsData.sats;									
		parsedData[26]  = gpsData.newValue;									
}


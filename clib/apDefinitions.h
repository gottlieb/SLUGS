/* ==================================================
This is the definition file for the the UCSC AP code
it creates all the common defines, unions, enumerations
and data types.

 Code by: Mariano I. Lizarraga
 First Revision: Aug 18 2008 @ 17:42
 ====================================================*/
#ifndef _APDEFINITIONS_H_
#define _APDEFINITIONS_H_

// =========== Global Definitions ==========
// GPS Checksum Messages
#define GGACS	86
#define RMCCS	75

// GPS Header IDs
#define GGAID	1
#define RMCID	2
#define UNKID	254

// GPS Circular Buffer and Out Message size
#define BSIZE	127
#define MSIZE	127

// Standard characters to parse the GPS message
#define DOLLAR	36
#define STAR	42
#define CR		13
#define LF		10

// Standard Units
#define KTS2MPS 0.514444444

// Periphereal Configurations
#define UCSCAP_UBRG 5

// ifdef switches for debugging and conditional inclusion
#define __IN_DSPIC__ 1 // switch for use in PC

#if __IN_DSPIC__
	#ifdef DEBUG
		#undef DEBUG
	#endif	
#else
	#define DEBUG 1
#endif


// ============= Unions Used for Data Transmission ====
//Type definitions for standard unions used in sending
// and receiving data
typedef union{
	unsigned char    chData[2];
	unsigned short   usData;
} tUnsignedShortToChar; 

typedef union{
	unsigned char    chData[2];
 	short   		 shData;
} tShortToChar; 

typedef union{
	unsigned char   chData[4];
 	unsigned int   	uiData;
} tUnsignedIntToChar; 

typedef union{
	unsigned char   chData[4];
 	int   			inData;
} tIntToChar; 

typedef union{
	unsigned char   chData[4];
 	float   		flData;
} tFloatToChar; 


// ============== Enumerations for Data Order ========
// Enumeration Definitions for sentences 
enum gpsOutSentence {
	gpsYear,
	gpsMonth,
	gpsDay,
	gpsHour,
	gpsMin,
	gpsSec,
	gpsLat,
	gpsLong,
	gpsHeight,
	gpsCOG,
	gpsSOG,
	gpsFix	
};

// ============= Structures used for data ============
typedef struct tGpsData{
	unsigned char	 		year;
	unsigned char			month;
	unsigned char			day;
	unsigned char			hour;
	unsigned char			min;
	unsigned char			sec;	 
	tFloatToChar 			lat;
	tFloatToChar 			lon;
	tFloatToChar 			height;
	tIntToChar				cog;
	tIntToChar				sog;
	tIntToChar				hdop;	
	unsigned char			fix;
	unsigned char 			sats;	
}tGpsData;

#endif /* _APDEFINITIONS_H_ */

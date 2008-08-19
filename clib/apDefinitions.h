/* ==================================================
This is the definition file for the the UCSC AP code
it creates all the common defines, unions, enumerations
and data types.

 Code by: Mariano I. Lizarraga
 First Revision: Aug 18 2008 @ 17:42
 ====================================================*/


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


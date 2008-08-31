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

// Circular Buffer Size
// ===================
#define BSIZE			200

// GPS Checksum Messages
// =====================
#define GGACS			86
#define RMCCS			75

// GPS Header IDs
// ==============
#define GGAID			1
#define RMCID			2
#define UNKID			254

// GPS Circular Buffers
// ====================
#define MSIZE			127
#define CSIZE			26 //[newBytes payload remaingBytes]  (comms buffer out of readGPS)

// Data Logger Values
// ================
#define LOGSEND			8
#define MAXLOGLEN		33

#define GPS_START 		0
#define LOAD_START		28
#define RAW_START 		29

// Message Protocol Lengths and IDs
// ================================
#define GPSMSG_ID		1
#define GPSMSG_LEN		27
#define LOADMSG_ID		2
#define LOADMSG_LEN		1
#define RAWMSG_ID		3
#define RAWMSG_LEN		18

// Standard characters used in the parsing of messages
// ===================================================
#define DOLLAR			36
#define STAR			42
#define CR				13
#define LF				10
#define AT				64

// Interprocessor Communication
// ============================
#define BEGINSPI		0xFFFF
#define ENDSPI			0xBEEF
#define SPIBUFSIZE		46

// Standard Units
// ==============
#define KTS2MPS 		0.514444444

// Periphereal Configurations
// ==========================
#define APFCY			40000000

#define GPSBAUDF		19200
#define GPSBAUDI		4800
#define UCSCAP_UBRGF 	129
#define UCSCAP_UBRGI 	520

#define LOGBAUD			57600
#define LOG_UBRG		42

// ifdef switches for debugging and conditional inclusion
// ======================================================
#define __IN_DSPIC__ 	1 // switch for use in PC

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
	gpsLat0,
	gpsLat1,
	gpsLat2,
	gpsLat3,
	gpsLong0,
	gpsLong1,
	gpsLong2,
	gpsLong3,
	gpsHeight0,
	gpsHeight1,
	gpsHeight2,
	gpsHeight3,
	gpsCOG0,
	gpsCOG1,
	gpsSOG0,
	gpsSOG1,
	gpsHDOP0,
	gpsHDOP1,
	gpsFix,
	gpsSats,
	gpsNew		
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
	unsigned char			new;
}tGpsData;

typedef struct tRawData{
	tUnsignedIntToChar 		gyroX;
	tUnsignedIntToChar 		gyroY;
	tUnsignedIntToChar 		gyroZ;
	tUnsignedIntToChar 		accelX;
	tUnsignedIntToChar 		accelY;
	tUnsignedIntToChar 		accelZ;
	tUnsignedIntToChar 		baro;
	tUnsignedIntToChar 		pitot;
	tUnsignedIntToChar 		temp;
}tRawData;


#endif /* _APDEFINITIONS_H_ */

/* ==================================================
This is the definition file for the the UCSC AP code
it creates all the common defines, unions, enumerations
and data types.

 Code by: Mariano I. Lizarraga
 First Revision: Aug 18 2008 @ 17:42
 ====================================================*/
#ifndef _APDEFINITIONS_H_
#define _APDEFINITIONS_H_

#ifdef __cplusplus
       extern "C"{
#endif

// =========== Global Definitions ==========

// Circular Buffer Size
// ===================
#ifdef __cplusplus
       #define BSIZE			1024
#else
       #define BSIZE			250
#endif

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
#define LOGSEND					8
#define MAXSEND					103

#ifdef __cplusplus
       #define MAXLOGLEN		500
#else
       #define MAXLOGLEN		103
#endif



#define GPS_START 		0
#define LOAD_START		27
#define RAW_START 		31
#define ATT_START		49
#define XYZ_START		73

// Message Protocol Lengths and IDs
// ================================
// SENSOR MCU
#define GPSMSG_ID		1
#define GPSMSG_LEN		27 
#define LOADMSG_ID		2
#define LOADMSG_LEN		4
#define RAWMSG_ID		3
#define RAWMSG_LEN		18
#define ATTMSG_ID		4
#define ATTMSG_LEN		24
#define XYZMSG_ID		11
#define XYZMSG_LEN		24
// CONTROL MCU
#define FILMSG_ID		205
#define FILMSG_LEN		5	

// Communication Protocol Merging Offsets
// ======================================
#define GSMSG_IDX		97
#define AKMSG_IDX		200


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
#define EARTHRADIUS     6378.135 // km
#define PI              3.141592653589793
#define DEG2RAD			0.017453292519943
#define RAD2DEG			57.29577951308232

// Periphereal Configurations
// ==========================
#define APFCY			40000000

	
#define GPSBAUDF		19200
#define GPSBAUDI		4800
#define UCSCAP_UBRGF 	129
#define UCSCAP_UBRGI 	520

#define LOGBAUD			115200
#define LOG_UBRG		21

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
	tUnsignedShortToChar	cog;
	tUnsignedShortToChar	sog;
	tUnsignedShortToChar	hdop;	
	unsigned char			fix;
	unsigned char 			sats;	
	unsigned char			newValue;
}tGpsData;

typedef struct tRawData{
	tUnsignedShortToChar 	gyroX;
	tUnsignedShortToChar 	gyroY;
	tUnsignedShortToChar 	gyroZ;
	tUnsignedShortToChar 	accelX;
	tUnsignedShortToChar 	accelY;
	tUnsignedShortToChar 	accelZ;
	tUnsignedShortToChar 	magX;
	tUnsignedShortToChar 	magY;
	tUnsignedShortToChar 	magZ;
}tRawData;

typedef struct tAttitudeData{
	tFloatToChar			roll;
	tFloatToChar			pitch;
	tFloatToChar			yaw;
	tFloatToChar			p;
	tFloatToChar			q;
	tFloatToChar			r;
}tAttitudeData;

typedef struct tSensStatus{
	char					load;
	char					vdetect;
	tUnsignedShortToChar	bVolt;
}tSensStatus;

typedef struct tDynTempData{
	tFloatToChar	dynamic;
	tFloatToChar	stat;
	tShortToChar	temp;
}tDynTempData;

typedef struct tXYZData{
	tFloatToChar	Xcoord;
	tFloatToChar	Ycoord;
	tFloatToChar	Zcoord;	
	tFloatToChar	VX;
	tFloatToChar	VY;
	tFloatToChar	VZ;	
}tXYZData;

typedef struct tAknData{
	unsigned char 	WP;
	unsigned char 	csCal;
	unsigned char 	pidCal;
	unsigned char 	csLimits;
	unsigned char 	filOnOff;	
}tAknData;


#ifdef __cplusplus
      }
#endif

#endif /* _APDEFINITIONS_H_ */

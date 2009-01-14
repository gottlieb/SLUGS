#include "apUtils.h"



float myAtan2(float num, float denom){
     #ifdef _IN_PC_
        return atan2(num,denom);
     #else
	return atan2f(num,denom);
     #endif
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
	       checkSum ^= sentence[i];
        }
      }
    }
    // Return the checksum 
    return checkSum;
}

void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg ){
	unsigned char i;
	// start the header
	*(protMsg+0) = DOLLAR;
	*(protMsg+1) = AT;
	*(protMsg+2) = type;
	*(protMsg+3) = size;
	for( i = 0; i < size; i += 1 )
	{
		*(protMsg+i+4) = *(rawData +i);
	}
	*(protMsg+size+4) = STAR;
	*(protMsg+size+5) = AT;
	*(protMsg+size+6) = getChecksum(protMsg, (size+5));	
}

void updateStates(unsigned char * completeSentence){
	switch (completeSentence[2]){
		// Sensor MCU sentences
		// ====================
		case GPSMSG_ID:		// GPS Sentence
			gpsControlData.year				= completeSentence[4];	
			gpsControlData.month			= completeSentence[5];	
			gpsControlData.day				= completeSentence[6];	
			gpsControlData.hour				= completeSentence[7];	
			gpsControlData.min				= completeSentence[8];	
			gpsControlData.sec				= completeSentence[9];	
			gpsControlData.lat.chData[0]	= completeSentence[10];	
			gpsControlData.lat.chData[1]	= completeSentence[11];	
			gpsControlData.lat.chData[2]	= completeSentence[12];				
			gpsControlData.lat.chData[3]	= completeSentence[13];			
			gpsControlData.lon.chData[0]	= completeSentence[14];	
			gpsControlData.lon.chData[1]	= completeSentence[15];	
			gpsControlData.lon.chData[2]	= completeSentence[16];	
			gpsControlData.lon.chData[3]	= completeSentence[17];	
			gpsControlData.height.chData[0]	= completeSentence[18];		
			gpsControlData.height.chData[1]	= completeSentence[19];	
			gpsControlData.height.chData[2]	= completeSentence[20];		
			gpsControlData.height.chData[3]	= completeSentence[21];	
			gpsControlData.cog.chData[0]	= completeSentence[22];	
			gpsControlData.cog.chData[1]	= completeSentence[23];	
			gpsControlData.sog.chData[0]	= completeSentence[24];	
			gpsControlData.sog.chData[1]	= completeSentence[25];	
			gpsControlData.hdop.chData[0]	= completeSentence[26];	
			gpsControlData.hdop.chData[1]	= completeSentence[27];	
			gpsControlData.fix				= completeSentence[28];	
			gpsControlData.sats				= completeSentence[29];	
			gpsControlData.newValue		 	= completeSentence[30];	
		break;
		case LOADMSG_ID:
			statusControlData.load		 		= completeSentence[4];
			statusControlData.vdetect	 		= completeSentence[5];
			statusControlData.bVolt.chData[0] 	= completeSentence[6];
			statusControlData.bVolt.chData[1] 	= completeSentence[7];
		break;
		case RAWMSG_ID: // Sensor Raw data
			rawControlData.gyroX.chData[0]	= completeSentence[4];	
			rawControlData.gyroX.chData[1]	= completeSentence[5]; 	
			rawControlData.gyroY.chData[0]	= completeSentence[6];		 	
			rawControlData.gyroY.chData[1]	= completeSentence[7]; 
			rawControlData.gyroZ.chData[0]	= completeSentence[8];	 
			rawControlData.gyroZ.chData[1]	= completeSentence[9];	 
			rawControlData.accelX.chData[0]	= completeSentence[10];	 
			rawControlData.accelX.chData[1]	= completeSentence[11];	   
			rawControlData.accelY.chData[0]	= completeSentence[12];	  
			rawControlData.accelY.chData[1]	= completeSentence[13];	  
			rawControlData.accelZ.chData[0]	= completeSentence[14];	  
			rawControlData.accelZ.chData[1]	= completeSentence[15];	  
			rawControlData.magX.chData[0]	= completeSentence[16];	  
			rawControlData.magX.chData[1]	= completeSentence[17];	  
			rawControlData.magY.chData[0]	= completeSentence[18];	  
			rawControlData.magY.chData[1]	= completeSentence[19];	  
			rawControlData.magZ.chData[0]	= completeSentence[20];	  
			rawControlData.magZ.chData[1]	= completeSentence[21];	  
		break;
		case ATTMSG_ID:
			attitudeControlData.roll.chData[0]		= completeSentence[4];
			attitudeControlData.roll.chData[1]		= completeSentence[5];
			attitudeControlData.roll.chData[2]		= completeSentence[6];
			attitudeControlData.roll.chData[3]		= completeSentence[7];
			attitudeControlData.pitch.chData[0]		= completeSentence[8];
			attitudeControlData.pitch.chData[1]		= completeSentence[9];
			attitudeControlData.pitch.chData[2]		= completeSentence[10];
			attitudeControlData.pitch.chData[3]		= completeSentence[11];
			attitudeControlData.yaw.chData[0]		= completeSentence[12];
			attitudeControlData.yaw.chData[1]		= completeSentence[13];
			attitudeControlData.yaw.chData[2]		= completeSentence[14];
			attitudeControlData.yaw.chData[3]		= completeSentence[15];
			attitudeControlData.p.chData[0]			= completeSentence[16];
			attitudeControlData.p.chData[1]			= completeSentence[17];
			attitudeControlData.p.chData[2]			= completeSentence[18];
			attitudeControlData.p.chData[3]			= completeSentence[19];
			attitudeControlData.q.chData[0]			= completeSentence[20];
			attitudeControlData.q.chData[1]			= completeSentence[21];
			attitudeControlData.q.chData[2]			= completeSentence[22];
			attitudeControlData.q.chData[3]			= completeSentence[23];
			attitudeControlData.r.chData[0]			= completeSentence[24];
			attitudeControlData.r.chData[1]			= completeSentence[25];
			attitudeControlData.r.chData[2]			= completeSentence[26];
			attitudeControlData.r.chData[3]			= completeSentence[27];			
			attitudeControlData.timeStamp.chData[0]	= completeSentence[28];			
			attitudeControlData.timeStamp.chData[1]	= completeSentence[29];			
		break;
        case DYNMSG_ID:
			dynTempControlData.dynamic.chData[0]	= completeSentence[4];
			dynTempControlData.dynamic.chData[1]	= completeSentence[5];
			dynTempControlData.dynamic.chData[2]	= completeSentence[6];
			dynTempControlData.dynamic.chData[3]	= completeSentence[7];
			dynTempControlData.stat.chData[0]	= completeSentence[8];
			dynTempControlData.stat.chData[1]	= completeSentence[9];
			dynTempControlData.stat.chData[2]	= completeSentence[10];
			dynTempControlData.stat.chData[3]	= completeSentence[11];
			dynTempControlData.temp.chData[0]	= completeSentence[12];	  
			dynTempControlData.temp.chData[1]	= completeSentence[13];	  
		break;
		case BIAMSG_ID:
			biasControlData.axb.chData[0]	= completeSentence[4];
			biasControlData.axb.chData[1]	= completeSentence[5];
			biasControlData.axb.chData[2]	= completeSentence[6];
			biasControlData.axb.chData[3]	= completeSentence[7];
			biasControlData.ayb.chData[0]	= completeSentence[8];
			biasControlData.ayb.chData[1]	= completeSentence[9];
			biasControlData.ayb.chData[2]	= completeSentence[10];
			biasControlData.ayb.chData[3]	= completeSentence[11];
			biasControlData.azb.chData[0]	= completeSentence[12];
			biasControlData.azb.chData[1]	= completeSentence[13];
			biasControlData.azb.chData[2]	= completeSentence[14];
			biasControlData.azb.chData[3]	= completeSentence[15];
			biasControlData.gxb.chData[0]	= completeSentence[16];
			biasControlData.gxb.chData[1]	= completeSentence[17];
			biasControlData.gxb.chData[2]	= completeSentence[18];
			biasControlData.gxb.chData[3]	= completeSentence[19];
			biasControlData.gyb.chData[0]	= completeSentence[20];
			biasControlData.gyb.chData[1]	= completeSentence[21];
			biasControlData.gyb.chData[2]	= completeSentence[22];
			biasControlData.gyb.chData[3]	= completeSentence[23];
			biasControlData.gzb.chData[0]	= completeSentence[24];
			biasControlData.gzb.chData[1]	= completeSentence[25];
			biasControlData.gzb.chData[2]	= completeSentence[26];
			biasControlData.gzb.chData[3]	= completeSentence[27];			
		break;		
		case DIAMSG_ID:
			diagControlData.fl1.chData[0]	= completeSentence[4];
			diagControlData.fl1.chData[1]	= completeSentence[5];
			diagControlData.fl1.chData[2]	= completeSentence[6];
			diagControlData.fl1.chData[3]	= completeSentence[7];
			diagControlData.fl2.chData[0]	= completeSentence[8];
			diagControlData.fl2.chData[1]	= completeSentence[9];
			diagControlData.fl2.chData[2]	= completeSentence[10];
			diagControlData.fl2.chData[3]	= completeSentence[11];
			diagControlData.fl3.chData[0]	= completeSentence[12];
			diagControlData.fl3.chData[1]	= completeSentence[13];
			diagControlData.fl3.chData[2]	= completeSentence[14];
			diagControlData.fl3.chData[3]	= completeSentence[15];
			diagControlData.sh1.chData[0]	= completeSentence[16];
			diagControlData.sh1.chData[1]	= completeSentence[17];
			diagControlData.sh2.chData[0]	= completeSentence[18];
			diagControlData.sh2.chData[1]	= completeSentence[19];
			diagControlData.sh3.chData[0]	= completeSentence[20];
			diagControlData.sh3.chData[1]	= completeSentence[21];		
		break;
		case XYZMSG_ID:
			xyzControlData.Xcoord.chData[0]	= completeSentence[4];
			xyzControlData.Xcoord.chData[1]	= completeSentence[5];
			xyzControlData.Xcoord.chData[2]	= completeSentence[6];
			xyzControlData.Xcoord.chData[3]	= completeSentence[7];
			xyzControlData.Ycoord.chData[0]	= completeSentence[8];
			xyzControlData.Ycoord.chData[1]	= completeSentence[9];
			xyzControlData.Ycoord.chData[2]	= completeSentence[10];
			xyzControlData.Ycoord.chData[3]	= completeSentence[11];
			xyzControlData.Zcoord.chData[0]	= completeSentence[12];
			xyzControlData.Zcoord.chData[1]	= completeSentence[13];
			xyzControlData.Zcoord.chData[2]	= completeSentence[14];
			xyzControlData.Zcoord.chData[3]	= completeSentence[15];
			xyzControlData.VX.chData[0]		= completeSentence[16];
			xyzControlData.VX.chData[1]		= completeSentence[17];
			xyzControlData.VX.chData[2]		= completeSentence[18];
			xyzControlData.VX.chData[3]		= completeSentence[19];
			xyzControlData.VY.chData[0]		= completeSentence[20];
			xyzControlData.VY.chData[1]		= completeSentence[21];
			xyzControlData.VY.chData[2]		= completeSentence[22];
			xyzControlData.VY.chData[3]		= completeSentence[23];
			xyzControlData.VZ.chData[0]		= completeSentence[24];
			xyzControlData.VZ.chData[1]		= completeSentence[25];
			xyzControlData.VZ.chData[2]		= completeSentence[26];
			xyzControlData.VZ.chData[3]		= completeSentence[27];
		break;	
		case FILMSG_ID:
			// turn the HIL on
			filterControlData = completeSentence[4];
			
			// turn on the required Aknowledge flag
			aknControlData.filOnOff = 1;
			
		break;	
		case PILMSG_ID: // Pilot Console Commands data
			pilControlData.dt.chData[0]		= completeSentence[4];	
			pilControlData.dt.chData[1]		= completeSentence[5]; 	
			pilControlData.dla.chData[0]	= completeSentence[6];		 	
			pilControlData.dla.chData[1]	= completeSentence[7]; 
			pilControlData.dra.chData[0]	= completeSentence[8];	 
			pilControlData.dra.chData[1]	= completeSentence[9];	 
			pilControlData.dr.chData[0]		= completeSentence[10];	 
			pilControlData.dr.chData[1]		= completeSentence[11];	   
			pilControlData.de.chData[0]		= completeSentence[12];	  
			pilControlData.de.chData[1]		= completeSentence[13];	  
		break;
		
		case PWMMSG_ID: // PWM Control Surface Commands data
			pwmControlData.dt_c.chData[0]		= completeSentence[4] ;	
			pwmControlData.dt_c.chData[1]		= completeSentence[5] ; 	
			pwmControlData.dla_c.chData[0]		= completeSentence[6] ;		 	
			pwmControlData.dla_c.chData[1]		= completeSentence[7] ; 
			pwmControlData.dra_c.chData[0]		= completeSentence[8] ;	 
			pwmControlData.dra_c.chData[1]		= completeSentence[9] ;	 
			pwmControlData.dr_c.chData[0]		= completeSentence[10];	 
			pwmControlData.dr_c.chData[1]		= completeSentence[11];	   
			pwmControlData.dle_c.chData[0]		= completeSentence[12];	  
			pwmControlData.dle_c.chData[1]		= completeSentence[13];	  
			pwmControlData.dre_c.chData[0]		= completeSentence[14];	  
			pwmControlData.dre_c.chData[1]		= completeSentence[15];	  
			pwmControlData.dlf_c.chData[0]		= completeSentence[16];	  
			pwmControlData.dlf_c.chData[1]		= completeSentence[17];	  
			pwmControlData.drf_c.chData[0]		= completeSentence[18];	  
			pwmControlData.drf_c.chData[1]		= completeSentence[19];	  
			pwmControlData.da1_c.chData[0]		= completeSentence[20];	  
			pwmControlData.da1_c.chData[1]		= completeSentence[21];	  
			pwmControlData.da2_c.chData[0]		= completeSentence[22];	  
			pwmControlData.da2_c.chData[1]		= completeSentence[23];	  
		break;
		
		default:
		break;   
	}
}


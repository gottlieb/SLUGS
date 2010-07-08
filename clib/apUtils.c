/*
The MIT License

Copyright (c) 2009 UCSC Autonomous Systems Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "apUtils.h"

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
	/*for( i = 0; i < size; i += 1 )
	{
		*(protMsg+i+4) = *(rawData +i);
	} */
    memcpy(protMsg+4,rawData,size);
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
			
			// Mavlink
			// =======
			
			mlGpsData.fix_type = gpsControlData.fix;
			mlGpsData.lat = gpsControlData.lat.flData;
			mlGpsData.lon = gpsControlData.lon.flData;
			mlGpsData.alt = gpsControlData.height.flData;
			mlGpsData.eph = gpsControlData.hdop.usData;
			mlGpsData.epv = 0.0;
			mlGpsData.v = ((float)gpsControlData.sog.usData/100.0);
			mlGpsData.hdg = gpsControlData.cog.usData;
			
			
		break;
		case LOADMSG_ID:
			statusControlData.load		 		= completeSentence[4];
			statusControlData.vdetect	 		= completeSentence[5];
			statusControlData.bVolt.chData[0] 	= completeSentence[6];
			statusControlData.bVolt.chData[1] 	= completeSentence[7];
			
			// Mavlink
			// =======
			
			mlCpuLoadData.target = SLUGS_SYSTEMID;
			mlCpuLoadData.sensLoad = statusControlData.load;
			mlCpuLoadData.ctrlLoad = statusControlData.vdetect;
			mlCpuLoadData.batVolt  = statusControlData.bVolt.usData;
			
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
			// included in SLUGS MKII
			rawControlData.baro.chData[0]	= completeSentence[22];	  
			rawControlData.baro.chData[1]	= completeSentence[23];	 
			rawControlData.pito.chData[0]	= completeSentence[24];	  
			rawControlData.pito.chData[1]	= completeSentence[25];	 
			rawControlData.powr.chData[0]	= completeSentence[26];	  
			rawControlData.powr.chData[1]	= completeSentence[27];
			rawControlData.ther.chData[0]	= completeSentence[28];	  
			rawControlData.ther.chData[1]	= completeSentence[29];	
			
			// Mavlink
			// =======
			
			mlRawImuData.xacc = rawControlData.gyroX.shData;
			mlRawImuData.yacc = rawControlData.gyroY.shData;
			mlRawImuData.zacc = rawControlData.gyroZ.shData;
			mlRawImuData.xgyro = rawControlData.accelX.shData;
			mlRawImuData.ygyro = rawControlData.accelY.shData;
			mlRawImuData.zgyro = rawControlData.accelZ.shData;
			mlRawImuData.xmag = rawControlData.magX.shData;
			mlRawImuData.ymag = rawControlData.magY.shData;
			mlRawImuData.zmag = rawControlData.magZ.shData;

			mlRawPressureData.press_abs = rawControlData.baro.shData;
			mlRawPressureData.press_diff1 = rawControlData.pito.shData;
			mlRawPressureData.press_diff2 = rawControlData.powr.shData;
			 
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
			
			// Mavlink
			// =======
			
			mlAttitudeData.roll = attitudeControlData.roll.flData;
			mlAttitudeData.pitch = attitudeControlData.pitch.flData;
			mlAttitudeData.yaw = attitudeControlData.yaw.flData;
			mlAttitudeData.rollspeed = attitudeControlData.p.flData;
			mlAttitudeData.pitchspeed = attitudeControlData.q.flData;
			mlAttitudeData.yawspeed = attitudeControlData.r.flData;
			
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
			
			// Mavlink
			// =======
			
			mlAirData.target = SLUGS_SYSTEMID;
			mlAirData.dynamicPressure = dynTempControlData.dynamic.flData;
			mlAirData.staticPressure  = dynTempControlData.stat.flData;
			mlAirData.temperature     = (float)dynTempControlData.temp.shData;

		break;
		case BIAMSG_ID:
			// Note that as an additional tool the bias messages can be used as 
			// diagnostic messages providing an additional 6 floating point values
			// for diagnostics
		
			//#if defined(_IN_PC_) || defined(USE_SENSOR_MCU_DIAG)
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
			//#endif
				
			// Mavlink
			// =======
			
			mlSensorBiasData.target = SLUGS_SYSTEMID;
			mlSensorBiasData.axBias = biasControlData.axb.flData;
			mlSensorBiasData.ayBias = biasControlData.ayb.flData;
			mlSensorBiasData.azBias = biasControlData.azb.flData;
			mlSensorBiasData.gxBias = biasControlData.gxb.flData;
			mlSensorBiasData.gyBias = biasControlData.gyb.flData;
			mlSensorBiasData.gzBias = biasControlData.gzb.flData;

		break;		
		case DIAMSG_ID:
			//change comment on USE_SENSOR_MCU_DIAG (in apUtils.h) if you want to use diagnostic data
			// from the sensor MCU
			#if defined(_IN_PC_) || defined(USE_SENSOR_MCU_DIAG)
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
			#endif		
				
			// Mavlink
			// =======
			
			mlDiagnosticData.target = SLUGS_SYSTEMID;
			mlDiagnosticData.diagFl1 = diagControlData.fl1.flData;
			mlDiagnosticData.diagFl2 = diagControlData.fl2.flData;
			mlDiagnosticData.diagFl3 = diagControlData.fl3.flData;
			mlDiagnosticData.diagSh1 = diagControlData.sh1.shData;
			mlDiagnosticData.diagSh2 = diagControlData.sh2.shData;
			mlDiagnosticData.diagSh3 = diagControlData.sh3.shData;
			
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
			
			// Mavlink
			// =======
			
			mlLocalPositionData.x = xyzControlData.Xcoord.flData;
			mlLocalPositionData.y = xyzControlData.Ycoord.flData;
			mlLocalPositionData.z = xyzControlData.Zcoord.flData;
			mlLocalPositionData.vx= xyzControlData.VX.flData;
			mlLocalPositionData.vy= xyzControlData.VY.flData;
			mlLocalPositionData.vz= xyzControlData.VZ.flData;
			
		break;	
		case FILMSG_ID:
			// turn the HIL on
			// TODO: the variable filterControlData is here for legacy purposes
			// 		 do not use it for anything else, instead use the flag in
			//		 the apsControlStatus struct called hilStatus.
			filterControlData = completeSentence[4];
			apsControlData.hilStatus = completeSentence[4];
			
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
			
			// Change the mode to manual automatically when received 
			// the pilot console message
			#ifndef __BORLANDC__   // Make sure we are not in the GS
				if(pilControlData.de.usData > PIL_FAILSAFE) {
					apsControlData.controlType = CTRL_TYPE_MANUAL;
				} else if (apsControlData.controlType == CTRL_TYPE_MANUAL) {
					apsControlData.controlType = CTRL_TYPE_AP_COMM;
				}
				
			#endif 
				
			// Mavlink
			// =======
			
			mlPilotConsoleData.target = SLUGS_SYSTEMID;
			mlPilotConsoleData.dt = pilControlData.dt.usData;
			mlPilotConsoleData.dla = pilControlData.dla.usData;
			mlPilotConsoleData.dra = pilControlData.dra.usData;
			mlPilotConsoleData.dr = pilControlData.dr.usData;
			mlPilotConsoleData.de = pilControlData.de.usData;

		break;
		
		case AKNMSG_ID: // Aknowledge Messages
			aknControlData.WP 			= completeSentence[4];
			aknControlData.commands 	= completeSentence[5];
			aknControlData.pidCal 		= completeSentence[6];
			aknControlData.sensorReboot = completeSentence[7];
			aknControlData.filOnOff 	= completeSentence[8];
			aknControlData.reboot	 	= completeSentence[9];
			
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
	   		
	   	// Mavlink
			// =======
			
			mlPwmCommandsData.target = SLUGS_SYSTEMID;
			mlPwmCommandsData.dt_c =  pwmControlData.dt_c.usData;
			mlPwmCommandsData.dla_c = pwmControlData.dla_c.usData;
			mlPwmCommandsData.dra_c = pwmControlData.dra_c.usData;
			mlPwmCommandsData.dr_c =  pwmControlData.dr_c.usData;
			mlPwmCommandsData.dle_c = pwmControlData.dle_c.usData;
			mlPwmCommandsData.dre_c = pwmControlData.dre_c.usData;
			mlPwmCommandsData.dlf_c = pwmControlData.dlf_c.usData;
			mlPwmCommandsData.drf_c = pwmControlData.drf_c.usData;
			mlPwmCommandsData.aux1 =  pwmControlData.da1_c.usData;
			mlPwmCommandsData.aux2 =  pwmControlData.da2_c.usData;
			
		break;
		
		case APSMSG_ID: // AP Status Report
	   		apsControlData.controlType		= completeSentence[4] ;	
	   		apsControlData.beaconStatus		= completeSentence[5] ; 	
	   		apsControlData.hilStatus		= completeSentence[6] ;		 	
	   	break;
		
		case CALMSG_ID: // report from AP to GS regarding Calib Values
			decodeCalSentence (completeSentence[4], completeSentence[5], &completeSentence[6],0);
		break;
		
		case PIDMSG_ID: // PID Configuration values
			decodeCalSentence(PIDTYPE_ID,completeSentence[4], &completeSentence[5],1);
		break;
		
		case WPSMSG_ID:
			decodeCalSentence(WPSTYPE_ID,completeSentence[4], &completeSentence[5],1);
		break;
		
		case QUEMSG_ID: // Query the Status of a particular configuration value
			queControlData.pendingRequest 	= 1;
			queControlData.idReq 			= completeSentence[4];
			queControlData.indxReq 			= completeSentence[5];
		break;
		
		case COMMSG_ID:
			decodeCmdsSentence(completeSentence[4],&completeSentence[5]); 
		break;
		
		case CHSMSG_ID:
			apsControlData.controlType 	= 	completeSentence[4] ;
			apsControlData.dt_pass		= 	completeSentence[5] ;	
			apsControlData.dla_pass		=	completeSentence[6] ;	
			apsControlData.dra_pass		=	completeSentence[7] ;	
			apsControlData.dr_pass		=	completeSentence[8] ;	
			apsControlData.dle_pass		=	completeSentence[9] ;	
			apsControlData.dre_pass		=	completeSentence[10];	
			apsControlData.dlf_pass		=	completeSentence[11];	
			apsControlData.drf_pass		=	completeSentence[12];						
		break;
		
		case NAVMSG_ID:
			navControlData.uMeasured.chData[0]	= completeSentence[4];
			navControlData.uMeasured.chData[1]	= completeSentence[5];
			navControlData.uMeasured.chData[2]	= completeSentence[6];
			navControlData.uMeasured.chData[3]	= completeSentence[7];
			navControlData.thetaCommanded.chData[0]	= completeSentence[8];
			navControlData.thetaCommanded.chData[1]	= completeSentence[9];
			navControlData.thetaCommanded.chData[2]	= completeSentence[10];
			navControlData.thetaCommanded.chData[3]	= completeSentence[11];
			navControlData.psiDotCommanded.chData[0]	= completeSentence[12];
			navControlData.psiDotCommanded.chData[1]	= completeSentence[13];
			navControlData.psiDotCommanded.chData[2]	= completeSentence[14];
			navControlData.psiDotCommanded.chData[3]	= completeSentence[15];
			navControlData.phiCommanded.chData[0]		= completeSentence[16];
			navControlData.phiCommanded.chData[1]		= completeSentence[17];
			navControlData.phiCommanded.chData[2]		= completeSentence[18];
			navControlData.phiCommanded.chData[3]		= completeSentence[19];
			navControlData.rHighPass.chData[0]		= completeSentence[20];
			navControlData.rHighPass.chData[1]		= completeSentence[21];
			navControlData.rHighPass.chData[2]		= completeSentence[22];
			navControlData.rHighPass.chData[3]		= completeSentence[23];
			navControlData.totRun.chData[0]		= completeSentence[24];
			navControlData.totRun.chData[1]		= completeSentence[25];
			navControlData.totRun.chData[2]		= completeSentence[26];
			navControlData.totRun.chData[3]		= completeSentence[27];		
			navControlData.distance2Go.chData[0]		= completeSentence[28];
			navControlData.distance2Go.chData[1]		= completeSentence[29];
			navControlData.distance2Go.chData[2]		= completeSentence[30];
			navControlData.distance2Go.chData[3]		= completeSentence[31];		
			navControlData.fromWp			= completeSentence[32];
			navControlData.toWp			  = completeSentence[33];
		break;
		
		case SENMSG_ID:
			senControlData.Ax.chData[0]	= completeSentence[4];
			senControlData.Ax.chData[1]	= completeSentence[5];
			senControlData.Ax.chData[2]	= completeSentence[6];
			senControlData.Ax.chData[3]	= completeSentence[7];
			senControlData.Ay.chData[0]	= completeSentence[8];
			senControlData.Ay.chData[1]	= completeSentence[9];
			senControlData.Ay.chData[2]	= completeSentence[10];
			senControlData.Ay.chData[3]	= completeSentence[11];
			senControlData.Az.chData[0]	= completeSentence[12];
			senControlData.Az.chData[1]	= completeSentence[13];
			senControlData.Az.chData[2]	= completeSentence[14];
			senControlData.Az.chData[3]	= completeSentence[15];
			senControlData.Mx.chData[0]	= completeSentence[16];
			senControlData.Mx.chData[1]	= completeSentence[17];
			senControlData.Mx.chData[2]	= completeSentence[18];
			senControlData.Mx.chData[3]	= completeSentence[19];
			senControlData.My.chData[0]	= completeSentence[20];
			senControlData.My.chData[1]	= completeSentence[21];
			senControlData.My.chData[2]	= completeSentence[22];
			senControlData.My.chData[3]	= completeSentence[23];
			senControlData.Mz.chData[0]	= completeSentence[24];
			senControlData.Mz.chData[1]	= completeSentence[25];
			senControlData.Mz.chData[2]	= completeSentence[26];
			senControlData.Mz.chData[3]	= completeSentence[27];			
		break;	
		case LOGMSG_ID:
			logControlData.fl1.chData[0]	= completeSentence[4];
			logControlData.fl1.chData[1]	= completeSentence[5];
			logControlData.fl1.chData[2]	= completeSentence[6];
			logControlData.fl1.chData[3]	= completeSentence[7];
			logControlData.fl2.chData[0]	= completeSentence[8];
			logControlData.fl2.chData[1]	= completeSentence[9];
			logControlData.fl2.chData[2]	= completeSentence[10];
			logControlData.fl2.chData[3]	= completeSentence[11];
			logControlData.fl3.chData[0]	= completeSentence[12];
			logControlData.fl3.chData[1]	= completeSentence[13];
			logControlData.fl3.chData[2]	= completeSentence[14];
			logControlData.fl3.chData[3]	= completeSentence[15];
			logControlData.fl4.chData[0]	= completeSentence[16];
			logControlData.fl4.chData[1]	= completeSentence[17];
			logControlData.fl4.chData[2]	= completeSentence[18];
			logControlData.fl4.chData[3]	= completeSentence[19];
			logControlData.fl5.chData[0]	= completeSentence[20];
			logControlData.fl5.chData[1]	= completeSentence[21];
			logControlData.fl5.chData[2]	= completeSentence[22];
			logControlData.fl5.chData[3]	= completeSentence[23];
			logControlData.fl6.chData[0]	= completeSentence[24];
			logControlData.fl6.chData[1]	= completeSentence[25];
			logControlData.fl6.chData[2]	= completeSentence[26];
			logControlData.fl6.chData[3]	= completeSentence[27];			
		break;	
						
		default:
		break;   
	}
}

// Called to respond to a query
void assembleRawSentence (unsigned char id, unsigned char indx, unsigned char * data){
	switch (id) {
		case PIDTYPE_ID: //PID Values
			data[0]	 = id;
			data[1]	 = indx;
			data[2]	 = pidControlData.P[indx].chData[0];
			data[3]	 = pidControlData.P[indx].chData[1];
			data[4]	 = pidControlData.P[indx].chData[2];
			data[5]	 = pidControlData.P[indx].chData[3];
			data[6]	 = pidControlData.I[indx].chData[0];
			data[7]	 = pidControlData.I[indx].chData[1];
			data[8]	 = pidControlData.I[indx].chData[2];
			data[9]	 = pidControlData.I[indx].chData[3];
			data[10] = pidControlData.D[indx].chData[0];
			data[11] = pidControlData.D[indx].chData[1];
			data[12] = pidControlData.D[indx].chData[2];
			data[13] = pidControlData.D[indx].chData[3];
			data[14] = 0;
			data[15] = 0;
			data[16] = 0;
		break;
		
		case WPSTYPE_ID: //WayPoint Values
			data[0]	 = id;
			data[1]	 = indx;
			data[2]	 = wpsControlData.lat[indx].chData[0];
			data[3]	 = wpsControlData.lat[indx].chData[1];
			data[4]	 = wpsControlData.lat[indx].chData[2];
			data[5]	 = wpsControlData.lat[indx].chData[3];
			data[6]	 = wpsControlData.lon[indx].chData[0];
			data[7]	 = wpsControlData.lon[indx].chData[1];
			data[8]	 = wpsControlData.lon[indx].chData[2];
			data[9]	 = wpsControlData.lon[indx].chData[3];
			data[10] = wpsControlData.hei[indx].chData[0];
			data[11] = wpsControlData.hei[indx].chData[1];
			data[12] = wpsControlData.hei[indx].chData[2];
			data[13] = wpsControlData.hei[indx].chData[3];
			data[14] = wpsControlData.typ[indx];
			data[15] = wpsControlData.val[indx].chData[0];
			data[16] = wpsControlData.val[indx].chData[1];
		break;
		
		case PASTYPE_ID:
			data[0]	 = id;
			data[1]	 = apsControlData.dt_pass;
			data[2]	 = apsControlData.dla_pass;
			data[3]	 = apsControlData.dra_pass;
			data[4]	 = apsControlData.dr_pass;
			data[5]	 = apsControlData.dle_pass;
			data[6]	 = apsControlData.dre_pass;
			data[7]	 = apsControlData.dlf_pass;
			data[8]	 = apsControlData.drf_pass;			
		break;
		
		case COMTYPE_ID:
			data[0] = id;
			data[1]	 = indx;
			
			switch (indx){
				case COMM_TYPE_HEIGHT:
					data[2]	 = comControlData.hCommand.chData[0];
					data[3]	 = comControlData.hCommand.chData[1];
					data[4]	 = comControlData.hCommand.chData[2];
					data[5]	 = comControlData.hCommand.chData[3];
				break;

				case COMM_TYPE_AIRSPEED:
					data[2]	 = comControlData.airspeedCommand.chData[0];
					data[3]	 = comControlData.airspeedCommand.chData[1];
					data[4]	 = comControlData.airspeedCommand.chData[2];
					data[5]	 = comControlData.airspeedCommand.chData[3];
				break;

				case COMM_TYPE_TURNRATE:
					data[2]	 = comControlData.rCommand.chData[0];
					data[3]	 = comControlData.rCommand.chData[1];
					data[4]	 = comControlData.rCommand.chData[2];
					data[5]	 = comControlData.rCommand.chData[3];
				break;

				case COMM_TYPE_GOTO_WP:
					data[2]	 = comControlData.currWPCommand;
				break;				
			}
			
		break;
		
		// TODO: Include report for Limits and Calibration
		
		default:
		break;
	}
}

void decodeCalSentence (unsigned char id, unsigned char indx, unsigned char * data, unsigned char inBoard){
	int indexOffset = 0;
	unsigned char writeSuccess = 0;
	unsigned char wpMaxCount = 0;
	
	switch (id) {
		case PIDTYPE_ID: //PID Values
			pidControlData.P[indx].chData[0]=	data[0]	;
			pidControlData.P[indx].chData[1]=	data[1]	;
			pidControlData.P[indx].chData[2]=	data[2]	;
			pidControlData.P[indx].chData[3]=	data[3]	;
			pidControlData.I[indx].chData[0]=	data[4]	;
			pidControlData.I[indx].chData[1]=	data[5]	;
			pidControlData.I[indx].chData[2]=	data[6]	;
			pidControlData.I[indx].chData[3]=	data[7]	;
			pidControlData.D[indx].chData[0]=	data[8];
			pidControlData.D[indx].chData[1]=	data[9];
			pidControlData.D[indx].chData[2]=	data[10];
			pidControlData.D[indx].chData[3]=	data[11];
			
			if (inBoard){
				
                #ifndef __BORLANDC__
				// Compute the adecuate index offset
				indexOffset = indx*6;
				
				// Save the data to the EEPROM
				writeSuccess += DataEEWrite(pidControlData.P[indx].shData[0], PID_OFFSET+indexOffset);
				writeSuccess += DataEEWrite(pidControlData.P[indx].shData[1], PID_OFFSET+indexOffset+1);
				writeSuccess += DataEEWrite(pidControlData.I[indx].shData[0], PID_OFFSET+indexOffset+2);
				writeSuccess += DataEEWrite(pidControlData.I[indx].shData[1], PID_OFFSET+indexOffset+3);
				writeSuccess += DataEEWrite(pidControlData.D[indx].shData[0], PID_OFFSET+indexOffset+4);
				writeSuccess += DataEEWrite(pidControlData.D[indx].shData[1], PID_OFFSET+indexOffset+5);
				
				// Set the flag of Aknowledge for the AKN Message
				// if the write was successful
				if (writeSuccess==0){
					aknControlData.pidCal = indx+1;	
				} else{
					aknControlData.pidCal = PIDEEP_WRITE_FAIL;	
				}

				#endif

			}
		break;

		case WPSTYPE_ID: //WP Values
			wpsControlData.lat[indx].chData[0]=	data[0]	;
			wpsControlData.lat[indx].chData[1]=	data[1]	;
			wpsControlData.lat[indx].chData[2]=	data[2]	;
			wpsControlData.lat[indx].chData[3]=	data[3]	;
			wpsControlData.lon[indx].chData[0]=	data[4]	;
			wpsControlData.lon[indx].chData[1]=	data[5]	;
			wpsControlData.lon[indx].chData[2]=	data[6]	;
			wpsControlData.lon[indx].chData[3]=	data[7]	;
			wpsControlData.hei[indx].chData[0]=	data[8];
			wpsControlData.hei[indx].chData[1]=	data[9];
			wpsControlData.hei[indx].chData[2]=	data[10];
			wpsControlData.hei[indx].chData[3]=	data[11];
			wpsControlData.typ[indx] 		  = data[12];
			wpsControlData.val[indx].chData[0]= data[13];
			wpsControlData.val[indx].chData[1]= data[14];
			
			if (inBoard){
				
                #ifndef __BORLANDC__
				// Compute the adecuate index offset
				indexOffset = indx*8;
				
				// Save the data to the EEPROM
				writeSuccess += DataEEWrite(wpsControlData.lat[indx].shData[0], WPS_OFFSET+indexOffset);   
				writeSuccess += DataEEWrite(wpsControlData.lat[indx].shData[1], WPS_OFFSET+indexOffset+1);      
				writeSuccess += DataEEWrite(wpsControlData.lon[indx].shData[0], WPS_OFFSET+indexOffset+2);      
				writeSuccess += DataEEWrite(wpsControlData.lon[indx].shData[1], WPS_OFFSET+indexOffset+3);       
				writeSuccess += DataEEWrite(wpsControlData.hei[indx].shData[0], WPS_OFFSET+indexOffset+4);      
				writeSuccess += DataEEWrite(wpsControlData.hei[indx].shData[1], WPS_OFFSET+indexOffset+5);      
				writeSuccess += DataEEWrite((unsigned short)wpsControlData.typ[indx], WPS_OFFSET+indexOffset+6);
				writeSuccess += DataEEWrite(wpsControlData.val[indx].shData, WPS_OFFSET+indexOffset+7);          
				
				// Set the flag of Aknowledge for the AKN Message
				// if the write was successful
				if (writeSuccess==0){
					aknControlData.WP = indx+1;	
				} else{
					aknControlData.WP = WPSEEP_WRITE_FAIL;	
				}
				
				// Update the waypoint count
				while ((int)(wpsControlData.lat[wpMaxCount].flData) != 0 && wpMaxCount < 9 ) wpMaxCount++;
				wpsControlData.wpCount = wpMaxCount;
				
				#endif

			}
		break;
		
		case PASTYPE_ID: //WP Values
			apsControlData.dt_pass	= 	indx;
			apsControlData.dla_pass	=	data[0]	;
			apsControlData.dra_pass	=	data[1]	;
			apsControlData.dr_pass	=	data[2]	;
			apsControlData.dle_pass	=	data[3]	;
			apsControlData.dre_pass	=	data[4]	;
			apsControlData.dlf_pass	=	data[5]	;
			apsControlData.drf_pass	=	data[6]	;
		break;
			
		case COMTYPE_ID:			
			switch (indx){
				case COMM_TYPE_HEIGHT:
					comControlData.hCommand.chData[0]	=	data[0];
					comControlData.hCommand.chData[1]	=	data[1];
					comControlData.hCommand.chData[2]	=	data[2];
					comControlData.hCommand.chData[3]	=	data[3];
				break;

				case COMM_TYPE_AIRSPEED:
					comControlData.airspeedCommand.chData[0]	=	data[0];
					comControlData.airspeedCommand.chData[1]	=	data[1];
					comControlData.airspeedCommand.chData[2]	=	data[2];
					comControlData.airspeedCommand.chData[3]	=	data[3];
				break;

				case COMM_TYPE_TURNRATE:
					comControlData.rCommand.chData[0]	=	data[0];
					comControlData.rCommand.chData[1]	=	data[1];
					comControlData.rCommand.chData[2]	=	data[2];
					comControlData.rCommand.chData[3]	=	data[3];
				break;

				case COMM_TYPE_GOTO_WP:
					comControlData.currWPCommand 		= data[0];
				break;				
			}		
		break;
				
		// TODO: Include report for Limits and Calibration
		default:
		break;
	}
}

void decodeCmdsSentence(unsigned char id,unsigned char* data){
	switch (id){
		case COMM_TYPE_HEIGHT:
			comControlData.hCommand.chData[0] = data[0];
			comControlData.hCommand.chData[1] = data[1];
			comControlData.hCommand.chData[2] = data[2];
			comControlData.hCommand.chData[3] = data[3];
		break;
		
		case COMM_TYPE_TURNRATE:
			comControlData.rCommand.chData[0] = data[0];
			comControlData.rCommand.chData[1] = data[1];
			comControlData.rCommand.chData[2] = data[2];
			comControlData.rCommand.chData[3] = data[3];	
		break;
		
		case COMM_TYPE_AIRSPEED:
			comControlData.airspeedCommand.chData[0] = data[0];
			comControlData.airspeedCommand.chData[1] = data[1];
			comControlData.airspeedCommand.chData[2] = data[2];
			comControlData.airspeedCommand.chData[3] = data[3];
		break;
		
		case COMM_TYPE_GOTO_WP:
			comControlData.currWPCommand = data[0];
		break;
	}
	aknControlData.commands = id;
}

/*
				diagControlData.sh1.shData= (short) rawSentence[0];
				diagControlData.sh2.shData= (short) rawSentence[1];
				
				val1.chData[0] = rawSentence[2];
				val1.chData[1] = rawSentence[3];
				val1.chData[2] = rawSentence[4];
				val1.chData[3] = rawSentence[5];
				diagControlData.fl1.flData= val1.flData;
				
				val2.chData[0] = rawSentence[6];
				val2.chData[1] = rawSentence[7];
				val2.chData[2] = rawSentence[8];
				val2.chData[3] = rawSentence[9];
				diagControlData.fl2.flData= val2.flData;

				val3.chData[0] = rawSentence[10];
				val3.chData[1] = rawSentence[11];
				val3.chData[2] = rawSentence[12];
				val3.chData[3] = rawSentence[13];
				diagControlData.fl3.flData= val3.flData;

*/

/*
// =====================================
//			Trig and Math Functions
// =====================================
*/

float myAtan2(float num, float denom){
     #ifdef _IN_PC_
        return atan2(num,denom);
     #else
		return atan2f(num,denom);
     #endif
}


float myPow(float x, float toTheN){
     #ifdef _IN_PC_
        return pow(x,toTheN);
     #else
		return powf(x,toTheN);
     #endif
}

float mySqrt(float x){
     #ifdef _IN_PC_
        return sqrt(x);
     #else
		return sqrtf(x);
     #endif
}

float myAbs(float x){
     #ifdef _IN_PC_
        return fabs(x);
     #else
		return fabsf(x);
     #endif
}


float myAtan(float x){
     #ifdef _IN_PC_
        return atan(x);
     #else
		return atanf(x);
     #endif
}

float myAsin(float x){
     #ifdef _IN_PC_
        return asin(x);
     #else
		return asinf(x);
     #endif
}

float mySin(float x){
     #ifdef _IN_PC_
        return sin(x);
     #else
		return sinf(x);
     #endif
}

float myCos(float x){
     #ifdef _IN_PC_
        return cos(x);
     #else
		return cosf(x);
     #endif
}

float myTan(float x){
     #ifdef _IN_PC_
        return tan(x);
     #else
		return tanf(x);
     #endif
}

float myAcos(float x){
     #ifdef _IN_PC_
        return acos(x);
     #else
		return acosf(x);
     #endif
	
}

float myExp(float x){
     #ifdef _IN_PC_
        return exp(x);
     #else
		return expf(x);
     #endif
}

// ================================
//    Debug Functions
// ================================
#ifndef _IN_PC_
void printToUart2 (const char *fmt, ...){
	va_list ap;
	char buf [300];
	
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end (ap);
	putsUART2((unsigned int*)buf);
}
#endif
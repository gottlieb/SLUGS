#include "mavlinkSlugs.h"

void prepareTelemetryPixHawk( unsigned char* dataOut){
 
	// Generic message container used to pack the messages
	mavlink_message_t msg;
	
	// Generic buffer used to hold data to be streamed via serial port
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	
	// Cycles from 1 to 10 to decide which 
	// message's turn is to be sent
	static uint8_t sampleTelemetry = 1;
	
	// Contains the total bytes to send via the serial port
	uint8_t bytes2Send = 0;
	
	memset(&msg,0,sizeof(mavlink_message_t));
	
	switch (sampleTelemetry){
		case 1: // GPS and Heartbeat
			// Pack the Heartbeat message
			mavlink_msg_heartbeat_pack(SLUGS_SYSTEMID, 
																 SLUGS_COMPID, 
																 &msg, 
																 MAV_FIXED_WING, 
																 MAV_AUTOPILOT_SLUGS);
			// Copy the message to the send buffer
			bytes2Send += mavlink_msg_to_send_buffer((dataOut+1+bytes2Send), &msg);
			
			memset(&msg,0,sizeof(mavlink_message_t));
			
			// Pack the GPS message
			mavlink_msg_gps_raw_pack(SLUGS_SYSTEMID, 
																 SLUGS_COMPID, 
																 &msg, 
																 attitudeRotatedControlData.timeStamp.usData, 
																 mlGpsData.fix_type, 
																 mlGpsData.lat, 
																 mlGpsData.lon, 
																 mlGpsData.alt, 
																 mlGpsData.eph, 
																 0.0, 
																 mlGpsData.v, 
																 mlGpsData.hdg);
																 
			// Copy the message to the send buffer
			bytes2Send += mavlink_msg_to_send_buffer((dataOut+1+bytes2Send), &msg);
		break;
		case 2: // LOAD and PWM
			mavlink_msg_cpu_load_pack( SLUGS_SYSTEMID, 
																 SLUGS_COMPID, 
																 &msg, 
																 mlCpuLoadData.target, 
																 mlCpuLoadData.sensLoad, 
																 mlCpuLoadData.ctrlLoad, 
																 mlCpuLoadData.batVolt);
		  
			// Copy the message to the send buffer
			bytes2Send += mavlink_msg_to_send_buffer((dataOut+1+bytes2Send), &msg);

			
			mavlink_msg_pwm_commands_pack( SLUGS_SYSTEMID, 
																 		 SLUGS_COMPID, 
																 		 &msg, 
																 		 mlPwmCommandsData.dt_c, 
																 		 mlPwmCommandsData.dla_c, 
																 		 mlPwmCommandsData.dra_c, 
																 		 mlPwmCommandsData.dr_c, 
																 		 mlPwmCommandsData.dle_c, 
																 		 mlPwmCommandsData.dre_c, 
																 		 mlPwmCommandsData.dlf_c, 
																 		 mlPwmCommandsData.drf_c, 
																 		 mlPwmCommandsData.aux1, 
																 		 mlPwmCommandsData.aux2);

			// Copy the message to the send buffer
			bytes2Send += mavlink_msg_to_send_buffer((dataOut+1+bytes2Send), &msg);

		break;
	}
	 
	// Put the length of the message in the first byte of the outgoing array
	*dataOut = bytes2Send;
	
	// increment/overflow the samplePeriod counter
	// configured for 10 Hz in non vital messages
	sampleTelemetry = (sampleTelemetry >= 10)? 1: sampleTelemetry + 1;

}
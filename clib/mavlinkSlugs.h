#ifndef _MAVLINKSLUGS_H_
#define _MAVLINKSLUGS_H_

#ifdef __cplusplus
       extern "C"{
#endif
       	
  #include "mavlink.h"
  #include "apDefinitions.h"
  #include "protDecoder.h"
  
       	
  extern mavlink_gps_raw_t	mlGpsData;
  extern mavlink_cpu_load_t mlCpuLoadData;
  extern mavlink_air_data_t mlAirData;
  extern mavlink_sensor_bias_t mlSensorBiasData;
  extern mavlink_diagnostic_t mlDiagnosticData;
  extern mavlink_pilot_console_t mlPilotConsoleData;
  extern mavlink_pwm_commands_t mlPwmCommandsData;
  extern mavlink_raw_imu_t mlRawImuData;
	extern mavlink_raw_pressure_t mlRawPressureData;
	extern mavlink_attitude_t mlAttitudeData;
  extern mavlink_local_position_t mlLocalPositionData;

  void prepareTelemetryPixHawk (unsigned char* dataOut);     	
       	
#ifdef __cplusplus
       }
#endif

#endif /* _MAVLINKSLUGS_H_ */

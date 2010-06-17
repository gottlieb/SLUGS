#ifndef _MAVLINKSLUGS_H_
#define _MAVLINKSLUGS_H_

#ifdef __cplusplus
       extern "C"{
#endif
       	
  #include "mavlink.h"
  #include "apDefinitions.h"
  #include "protDecoder.h"
  
       	
  extern mavlink_gps_raw_t	mlGpsData;
  
  void prepareTelemetryPixHawk (unsigned char* dataOut);     	
       	
#ifdef __cplusplus
       }
#endif

#endif /* _MAVLINKSLUGS_H_ */

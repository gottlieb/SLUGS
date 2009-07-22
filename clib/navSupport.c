#include "navSupport.h"

void getMidLevelCommands(float* commands) {
	commands[0] = comControlData.airspeedCommand.flData;
	commands[1] = comControlData.hCommand.flData;
	commands[2] = comControlData.rCommand.flData;
}

unsigned char isApManual (void) {
	return apsControlData.controlType == CTRL_TYPE_MANUAL;
}

void getPidIdx(unsigned char idx, float* PID){
	PID[0] = pidControlData.P[idx].flData;
	PID[1] = pidControlData.I[idx].flData;
	PID[2] = pidControlData.D[idx].flData; 
}

float getDynamic (void) {
	return dynTempControlData.dynamic.flData;
} 

void getAttitude (float* correction, float* attitude){	
	float tmp_att[3];
		
	// Return the values to the control algorithm
	attitude[0] = attitudeControlData.roll.flData;
	attitude[1] = attitudeControlData.pitch.flData;
	attitude[2] = attitudeControlData.yaw.flData;
	attitude[3] = attitudeControlData.p.flData;
	attitude[4] = attitudeControlData.q.flData;
	attitude[5] = attitudeControlData.r.flData;	
	
}

void getXYZ (float* xyz) {
	xyz[0] =  xyzControlData.Xcoord.flData;
	xyz[1] =  xyzControlData.Ycoord.flData;
	xyz[2] =  xyzControlData.Zcoord.flData;
	xyz[3] =  xyzControlData.VX.flData;
	xyz[4] =  xyzControlData.VY.flData;
	xyz[5] =  xyzControlData.VZ.flData;
}

unsigned char getMaxWp (void){
	return wpsControlData.wpCount;
}

unsigned char isWpFly (void){
	return apsControlData.controlType == CTRL_TYPE_AP_WP; 
}

void setDiagnosticFloat(float * flValues){
	diagControlData.fl1.flData = flValues[0];
	diagControlData.fl2.flData = flValues[1];
	diagControlData.fl3.flData = flValues[2];	
}

void setDiagnosticShort(short* shValues){
	diagControlData.sh1.shData = shValues[0];
	diagControlData.sh2.shData = shValues[1];
	diagControlData.sh3.shData = shValues[2];	
}

void getWP (unsigned char idx, float* WPpos){
	WPpos[0] = wpsControlData.lat[idx-1].flData;
	WPpos[1] = wpsControlData.lon[idx-1].flData;
	WPpos[2] = wpsControlData.hei[idx-1].flData;
}

void setDiagnosticAb(float * flValues){
	biasControlData.axb.flData = flValues[0];
	biasControlData.ayb.flData = flValues[1];
	biasControlData.azb.flData = flValues[2];	
}

void setDiagnosticGb(float * flValues){
	biasControlData.gxb.flData = flValues[0];
	biasControlData.gyb.flData = flValues[1];
	biasControlData.gzb.flData = flValues[2];	
}

unsigned char getApControlType (void) {
	return apsControlData.controlType;
}

unsigned char getPassValues (unsigned char * pasVals){
	pasVals[0] = apsControlData.dt_pass;
	pasVals[1] = apsControlData.dla_pass;
	pasVals[2] = apsControlData.dr_pass;
	pasVals[3] = apsControlData.dle_pass;
}

void setCurrentCommands (float airSpeed){
	comControlData.hCommand.flData = xyzControlData.Zcoord.flData;
	comControlData.airspeedCommand.flData = airSpeed; 
	comControlData.rCommand.flData = 0.0;
}
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

void getAttitude ( float* attitude){	
		
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


void setNavLong (float* values) {
	navControlData.uMeasured.flData = values[0];
	navControlData.thetaCommanded.flData = values[1];
}

void setNavLat (float* values) {
	navControlData.psiDotCommanded.flData = values[0];
	navControlData.phiCommanded.flData = values[1];
	navControlData.rHighPass.flData = values[2];
}

void setNavNav (float* values) {
	navControlData.totRun.flData = values[0];
	navControlData.distance2Go.flData = values[1];
	navControlData.fromWp = (unsigned char) values[2];
	navControlData.toWp = (unsigned char) values[3];
}

void getAccels (float * accels){
	accels[0] = senControlData.Ax.flData;
	accels[1] = senControlData.Ay.flData;
	accels[2] = senControlData.Az.flData;
}

void getAccBias (float * bias){
	bias[0] = biasControlData.axb.flData;
	bias[1] = biasControlData.ayb.flData;
	bias[2] = biasControlData.azb.flData;
}

// void bufferICValues(unsigned short latest, unsigned short* history){
// 	static unsigned short * oldValues[] = {0, 0, 0, 0, 0, 0, 0};
// 	unsigned char i;
// 	for (i=6; i>0; i--){
// 		oldValues[i] = oldValues[i-1];
// 		history[i] = oldValues[i];
// 	}
// 	
// 	oldValues[0] = latest;
// 	history[0] = latest;
// }

unsigned short meanFilter5(unsigned short * values){
	quickSort(values, 7);
	return values[3];
}

//  quickSort
//
//  This public-domain C implementation by Darel Rex Finley.
//
//  * Returns YES if sort was successful, or NO if the nested
//    pivots went too deep, in which case your array will have
//    been re-ordered, but probably not sorted correctly.
//
//  * This function assumes it is called with valid parameters.
//
//  * Example calls:
//    quickSort(&myArray[0],5); // sorts elements 0, 1, 2, 3, and 4
//    quickSort(&myArray[3],5); // sorts elements 3, 4, 5, 6, and 7
//
// 	source: http://alienryderflex.com/quicksort/

 
unsigned char quickSort(unsigned short *arr, char elements) {

  #define  MAX_LEVELS  8

	short i=0, L, R ;
	unsigned short  piv, beg[MAX_LEVELS], end[MAX_LEVELS];

  beg[0]=0; end[0]=elements;
  while (i>=0) {
    L=beg[i]; R=end[i]-1;
    if (L<R) {
      piv=arr[L]; if (i==MAX_LEVELS-1) return 0;
      while (L<R) {
        while (arr[R]>=piv && L<R) {
        	R--; 
        }
        if (L<R){ 
        	arr[L++]=arr[R];
        }
        while (arr[L]<=piv && L<R) {
        	L++;
        } 
        if (L<R) {
        	arr[R--]=arr[L];
      	}   
      }
      arr[L]=piv; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L; 
    } else {
      i--;     
    }
  }
  return 1; 
}
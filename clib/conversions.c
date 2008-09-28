#include "conversions.h"
#include "apDefinitions.h"

float bytesToFloat (unsigned char* inBytes){
	tFloatToChar convert;
	convert.chData[0] = inBytes[0];
	convert.chData[1] = inBytes[1];
	convert.chData[2] = inBytes[2];
	convert.chData[3] = inBytes[3];
	return convert.flData;
}

void floatToBytes (float inFloat, unsigned char* inBytes){
	tFloatToChar convert;
	convert.flData = inFloat;
	
	inBytes[0] = convert.chData[0];
	inBytes[1] = convert.chData[1];
	inBytes[2] = convert.chData[2];
	inBytes[3] = convert.chData[3];	
}
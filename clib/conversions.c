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

unsigned short bytesToUShort (unsigned char* inBytes){
	tUnsignedShortToChar convert;
	convert.chData[0] = inBytes[0];
	convert.chData[1] = inBytes[1];
	return convert.usData;
}

void uShortToBytes (unsigned short inUShort, unsigned char* inBytes){
	tUnsignedShortToChar convert;
	convert.usData = inUShort;
	
	inBytes[0] = convert.chData[0];
	inBytes[1] = convert.chData[1];
}

short bytesToShort (unsigned char* inBytes){
	tShortToChar convert;
	convert.chData[0] = inBytes[0];
	convert.chData[1] = inBytes[1];
	return convert.shData;
}

void shortToBytes (short inShort, unsigned char* inBytes){
	tShortToChar convert;
	convert.shData = inShort;
	
	inBytes[0] = convert.chData[0];
	inBytes[1] = convert.chData[1];
}

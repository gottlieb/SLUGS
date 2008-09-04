#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "protDecoder.h"

	unsigned char msg1 [] = {38,42,21,14,15,42,79,36,64,02,01,12,42,79,36,64,3,
							 18,12,45,12,12,15,14,18,14,16,03,14,18,17,78,
							 79,75,45,45,42,57};


int main (int argc, char const* argv[])
{
	protParserInit();
	protParseDecode(&msg1);
	return 0;
}
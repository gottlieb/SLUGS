#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "protDecoder.h"

	unsigned char msg1 [] = {38,42,21,14,15,42,79,36,64,02,01,12,42,79,36,64,3,
							 18,12,45,12,12,15,14,18,14,16,03,14,18,17,78,
							 79,75,45,45,42,57};
        unsigned char retV[16];


int main (int argc, char const* argv[])
{
        FILE *file;
	char *buffer;
	unsigned long fileLen;
        unsigned long i;

	//Open file
	file = fopen("prot.bin", "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file");
		return 0;
	}
	
	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	//Allocate memory
	buffer=(char *)malloc(fileLen+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                                fclose(file);
		return 0;
	}

        protParserInit();

	//Read file contents into buffer
        i = 0;
        while (i<fileLen-35){
	        fread(buffer, 35, 1, file);
                i+=35;
                protParseDecode(buffer, retV);
        }
        fclose(file);
	//Do what ever with buffer

	free(buffer);



	return 0;
}
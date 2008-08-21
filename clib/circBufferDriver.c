#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "circBuffer.h"
#include "gpsSplit.h"
#include "apDefinitions.h"
#include "gpsParse.h"

int main(int argc, char* argv[])
{
   char i;
/*   CBRef A = newCircBuffer(10);
   CBRef B = newCircBuffer(20);

   for(i=0; i<=12; i++)
   {
      writeBack(A, i);
      writeBack(B, 15-i);
   }
   printCircBuf(A);
   printCircBuf(B);
   printf("\n");
   printf("\n");

   for(i=0; i<=6; i++)
   {
	printf("Read byte: %d\n", readFront(A));
	//printCircBuf(A);
   }

	makeEmpty(A);
	printCircBuf(A);

	freeCircBuffer(&A);
	freeCircBuffer(&B);*/
	
	unsigned char msg1 [] = "B$GPRMC,213922.000,A,4221.1129,N,07102.9146,W,0.00,,010207,,,A*6F\r\n";
	unsigned char msg2 [] = "G$GPRMC,184050.84,A,3907.3839,N,12102.4772,W,00.0,000.0,080301,15,E*54\r\n";
	unsigned char msg3 [] = "&$GPGGA,213922.000,4221.1129,N,07102.91";
	unsigned char msg4 [] = "(46,W,1,04,3.9,129.7,M,-33.7,M,,0000*6E\r\n";
	
	unsigned char outBuffer [128] ={0}, parsedData[128]={0};
	
	gpsInit();
	
	printf("Message 1\n");
	gpsSeparate(msg1, outBuffer);	
		printf("\n");
		printf(outBuffer);
		printf("\nValid: %d Type:%d", outBuffer[MSIZE-1], outBuffer[0]);
		printf("\n");
		printf(msg1);
	
	gpsParse(outBuffer, parsedData);
	
	for(i=0;i<10;i++){
		printf("%d ", parsedData[i]);
	}
	printf("\n");
	
	/*printf("Message 2\n");
	gpsSeparate(msg2, outBuffer);	
		printf("\n");
		printf(outBuffer);
		printf("\nValid: %d Type:%d", outBuffer[MSIZE-1], outBuffer[0]);
		printf("\n");
		printf(msg2);
	


	printf("First Call to GPS Separate\n");
	gpsSeparate(msg3, outBuffer);	
	printf("============================\n");
	
	printf("Second Call to GPS Separate\n");	
	gpsSeparate(msg4, outBuffer);	
	printf("============================\n");
	
	printf(outBuffer);
	printf("\nValid: %d Type:%d", outBuffer[MSIZE-1], outBuffer[0]);
	printf("\n");
	printf(msg3);
	printf(msg4);

	printf("============================\n");
	printf("============================\n");
	printf("============================\n");
	printf("============================\n");
	printf("Char: %d, Short: %d, Int: %d, Float: %d, Long:%d", sizeof(char), sizeof(short), sizeof(int), sizeof(float), sizeof(long));
	printf("\n");	
	*/
   return(0);
}

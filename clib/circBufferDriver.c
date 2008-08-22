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
   /*
	//CBRef A = newCircBuffer(10);
   //CBRef B = newCircBuffer(20);
   struct CircBuffer Anp;
   struct CircBuffer Bnp;
   
	CBRef A = &Anp;
	CBRef B = &Bnp; 
	
	newCircBuffer(A);
	newCircBuffer(B);
	
   for(i=0; i<=12; i++)
   {
      writeBack(B, i);
      writeBack(A, 15-i);
   }
   //printCircBuf(A);
   //printCircBuf(B);
   printf("\n");
   printf("\n");

   for(i=0; i<=12; i++)
   {
	printf("Read byte A: %d\n", readFront(A));
	printf("Read byte B: %d\n", readFront(B));
	//printCircBuf(A);
   }

	makeEmpty(A);
	//printCircBuf(A);

	freeCircBuffer(&A);
	freeCircBuffer(&B);
	
	*/
	
	unsigned char msg1 [] = "@$GPRMC,040302.663,A,3939.7,N,10506.6,W,5.27,358.86,200804,,*1A\r\n";
	unsigned char msg2 [] = "N$GPGGA,213924.000,4221.1129,N,07102.9146,W,1,04,3.9,129.7,M,-33.7,M,,0000*68\r\n";
	unsigned char msg3 [] = "&$GPGGA,213922.000,4221.1129,N,07102.91";
	unsigned char msg4 [] = "(46,W,1,04,3.9,129.7,M,-33.7,M,,0000*6E\r\n";
	
	unsigned char outBuffer [128] ={0}, parsedData[128]={0};
	
	gpsInit();
	
	printf("Message 1\n");
	gpsSeparate(msg2, outBuffer);	
		printf("\n");
		printf(outBuffer);
		printf("\nValid: %d Type:%d", outBuffer[MSIZE-1], outBuffer[0]);
		printf("\n");
		printf(msg2);
	
	gpsParse(outBuffer, parsedData);
	
	for(i=0;i<6;i++){
		printf("%d ", parsedData[i]);
	}
	
	tFloatToChar flCh;
	tIntToChar inCh;
	
	flCh.chData[0] = parsedData[6];
	flCh.chData[1] = parsedData[7];
	flCh.chData[2] = parsedData[8];
	flCh.chData[3] = parsedData[9];
	printf("%f ", flCh.flData);
	
	flCh.chData[0] = parsedData[10];
	flCh.chData[1] = parsedData[11];
	flCh.chData[2] = parsedData[12];
	flCh.chData[3] = parsedData[13];
	printf("%f ", flCh.flData);

	flCh.chData[0] = parsedData[14];
	flCh.chData[1] = parsedData[15];
	flCh.chData[2] = parsedData[16];
	flCh.chData[3] = parsedData[17];
	printf("%f ", flCh.flData);
	
	inCh.chData[0] = parsedData[18];
	inCh.chData[1] = parsedData[19];
	printf("%d ", inCh.inData);

	inCh.chData[0] = parsedData[20];
	inCh.chData[1] = parsedData[21];
	printf("%d ", inCh.inData);
	
	inCh.chData[0] = parsedData[22];
	inCh.chData[1] = parsedData[23];
	printf("%d ", inCh.inData);
	
	for(i=24;i<26;i++){
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

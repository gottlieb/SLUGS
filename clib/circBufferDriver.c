#include <stdio.h>
#include <stdarg.h>
#include"circBuffer.h"

int main(int argc, char* argv[])
{
   char i;
   CBRef A = newCircBuffer(10);
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
	printCircBuf(A);
   }

	makeEmpty(A);
	printCircBuf(A);

	freeCircBuffer(&A);
	freeCircBuffer(&B);


   return(0);
}

# Makefile for Queue ADT
#
# make             makes circBufferDriver
# make clean       removes object files
#

circBufferDriver : circBufferDriver.o circBuffer.o
	gcc -o circBufferDriver circBufferDriver.o circBuffer.o 

circBufferDriver.o : circBuffer.h circBufferDriver.c
	gcc -c  -Wall circBufferDriver.c

circBuffer.o : circBuffer.h circBuffer.c
	gcc -c  -Wall circBuffer.c


clean :
	rm -f circBufferDriver circBufferDriver.o circBuffer.o
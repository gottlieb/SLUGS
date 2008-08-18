# Makefile for Queue ADT
#
# make             makes circBufferDriver
# make clean       removes object files
#

circBufferDriver : circBufferDriver.o circBuffer.o gpsSplit.o
	gcc -o circBufferDriver circBufferDriver.o circBuffer.o gpsSplit.o

circBufferDriver.o : circBuffer.h circBufferDriver.c
	gcc -c  -Wall circBufferDriver.c

circBuffer.o : circBuffer.h circBuffer.c
	gcc -c  -Wall circBuffer.c
	
gpsSplit.o : gpsSplit.c gpsSplit.h
	gcc -c -Wall gpsSplit.c

clean :
	rm -f circBufferDriver circBufferDriver.o circBuffer.o gpsSplit.o
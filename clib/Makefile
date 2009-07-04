# Makefile for Queue ADT
#
# make             makes circBufferDriver
# make clean       removes object files
#

circBufferDriver: circBufferDriver.o circBuffer.o gps.o
	gcc -o circBufferDriver circBufferDriver.o circBuffer.o gps.o 

circBufferDriver.o: circBuffer.h circBufferDriver.c
	gcc -c  -Wall circBufferDriver.c

gps.o: gps.h gps.c apDefinitions.h
	gcc -c  -Wall gps.c

circBuffer.o: circBuffer.h circBuffer.c
	gcc -c  -Wall circBuffer.c
# 	
# gpsSplit.o: gpsSplit.c gpsSplit.h apDefinitions.h
# 	gcc -c -Wall gpsSplit.c
# 
# gpsParse.o: gpsParse.c gpsParse.h apDefinitions.h
# 	gcc -c -Wall gpsParse.c
# 	
# protDecoDriver: circBuffer.o gpsSplit.o protDecoder.o protDecoDriver.o
# 	gcc -o protDecoDriver protDecoDriver.o circBuffer.o gpsSplit.o
# 
# protDecoDriver.o: protDecoDriver.c 
# 	gcc -c -Wall protDecoDriver.c
# 
# protDecoder.o: protDecoder.c apDefinitions.h circBuffer.h gpsSplit.h
# 	gcc -c -Wall protDecoder.c

clean:
	rm -f circBufferDriver circBufferDriver.o 
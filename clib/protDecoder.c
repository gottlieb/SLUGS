// ==========================================================
// protDecoder.c
// This is code implements the communications protocol decoder.
// It adds the bytes as they come in from the SPI to a circular
// buffer which is then read to parse sentences and updates the 
// data structures accordingly if the checksum tallies.
//
// 
// Code by: Mariano I. Lizarraga
// First Revision: Sep 2 2008 @ 15:03
// ==========================================================

#include "apDefinitions.h"
#include "circBuffer.h"
#include "gpsSplit.h"

struct CircBuffer protParseBuffer;
CBRef ppBuffer;

void protParserInit(void){
	// initialize the circular buffer
	ppBuffer = (struct CircBuffer* )&protParseBuffer;
	newCircBuffer(ppBuffer);
}

void protParseDecode(unsigned char* fromSPI, unsigned char* stateVector){
	
}
// ==============================================================
// circBuffer.h
// This is the header file for the circular buffer. This library
// implements a circular buffer to be used in the serial readers
// for the GPS, IPC and telemetry decoders of the UCSC AutoPilot. 
//
// Comment the DEBUG define prior to compile for dsPIC
//
// Code by: Mariano I. Lizarraga
// First Revision: Aug 16 2008 @ 00:36
// ==============================================================
#ifndef _CIRCBUFFER_H_
#define _CIRCBUFFER_H_

#include "apDefinitions.h"

#ifdef __cplusplus
       extern "C"{
#endif

# if __IN_DSPIC__
	typedef struct CircBuffer{
		unsigned char buffer[BSIZE];
		unsigned int length;
		unsigned int head;
		unsigned int tail;
		unsigned int size;
	}CircBuffer;
#else
	typedef struct CircBuffer{
		unsigned char* buffer;
		unsigned int length;
		unsigned int head;
		unsigned int tail;
		unsigned int size;
	}CircBuffer;
#endif

// Exported Types
// ==============
typedef struct CircBuffer* CBRef;

// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new Circular Buffer of size pm_size 

#if __IN_DSPIC__
	void newCircBuffer (CBRef cB);
#else
	CBRef newCircBuffer (int pm_size);
#endif

// this function frees the Circular Buffer CB Ref
void freeCircBuffer (CBRef* cB);


// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer
unsigned int getLength (CBRef cB);

// returns the actual index of the head
unsigned char readHead (CBRef cB);

// returns the actual index of the tail
unsigned char readTail (CBRef cB);

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to peak will
// always return the same value
unsigned char peak(CBRef cB);


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read
unsigned char readFront (CBRef cB);

// writes one byte at the end of the circular buffer, returns 1 if overflow occured
unsigned char writeBack (CBRef cB, unsigned char data);

// empties the circular buffer. It does not change the size. use with caution!!
void makeEmpty (CBRef cB);


#if DEBUG
	// Other Functions
	// ===============
	// prints the circular buffer, used for debug
	void printCircBuf(CBRef cB);
#endif /* DEBUG */

#ifdef __cplusplus
       }
#endif

#endif /* _CIRCBUFFER_H_ */


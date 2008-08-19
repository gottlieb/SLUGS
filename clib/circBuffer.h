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

#ifndef C30
	#define DEBUG 1
#endif

// Exported Types
// ==============
typedef struct CircBuffer* CBRef;

// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new Circular Buffer of size pm_size 
CBRef newCircBuffer (int pm_size);

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
unsigned char writeBack(CBRef cB, char data);

// empties the circular buffer. It does not change the size. use with caution!!
void makeEmpty(CBRef cB);


#ifdef DEBUG
	// Other Functions
	// ===============
	// prints the circular buffer, used for debug
	void printCircBuf(CBRef cB);
#endif /* DEBUG */

#endif /* _CIRCBUFFER_H_ */


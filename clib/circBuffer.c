// ==============================================================
// circBuffer.c
// This is the implementation file for the circular buffer. This library
// implements a circular buffer to be used in the serial readers
// for the GPS, IPC and telemetry decoders of the UCSC AutoPilot. 
//
// Comment the DEBUG define int the header prior to compile for dsPIC
//
// Code by: Mariano I. Lizarraga
// First Revision: Aug 16 2008 @ 00:36
// ==============================================================

#include <stdlib.h>
#include "circBuffer.h"

#if DEBUG
	#include <stdio.h>
#endif



// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new Circular Buffer of size pm_size 

#if __IN_DSPIC__
	void newCircBuffer (CBRef cB){
		
		// initialize to zero
		int i;
		for (i=0; i<BSIZE; i++){
			cB->buffer[i] = 0;
		}
				
		// initialize the data members
		cB->length = 0;
		cB->head = 0;
		cB->tail = 0;
		cB->size = BSIZE;

	}

// this function frees the Circular Buffer CB Ref
	void freeCircBuffer (CBRef* cB){
		// if it is already null, nothing to free
		if (cB == NULL || *cB == NULL) {return;}
				
		// free and nil the pointer
		//free(*cB);
		*cB = NULL;
	}


#else
	CBRef newCircBuffer (int pm_size){
		// create the circular buffer pointer
		CBRef cB;
		
		// allocate memory for it
		cB = (CBRef) malloc(sizeof(CircBuffer));
		
		// allocate memory for the buffer
		cB->buffer = (unsigned char *)calloc(pm_size, sizeof(unsigned char));
		
		// initialize the data members
		cB->length = 0;
		cB->head = 0;
		cB->tail = 0;
		cB->size = pm_size;
		
		// return the buffer pointer
		return (cB);
		
		printf("No Jala");
	}

	// this function frees the Circular Buffer CB Ref
	void freeCircBuffer (CBRef* cB){
		// if it is already null, nothing to free
		if (cB == NULL || *cB == NULL) {return;}
		
		// free the buffer
		free((*cB)->buffer);
		
		// free and nil the pointer
		free(*cB);
		*cB = NULL;
	}

#endif
	


// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer
unsigned int getLength (CBRef cB){
	
	// if the circular buffer is not null
	if (cB != NULL){
		return (cB->length);
	}
	else{
		return -1;
	}
	
}

// returns the actual index of the head
unsigned char readHead (CBRef cB){
	// if the circular buffer is not null
	if (cB != NULL){
		return (cB->head);
	}
	else{
		return -1;
	}

}

// returns the actual index of the tail
unsigned char readTail (CBRef cB){
	// if the circular buffer is not null
	if (cB != NULL){
		return (cB->tail);
	}
	else{
		return -1;
	}

}

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to peak will
// always return the same value
unsigned char peak(CBRef cB){
	// if the circular buffer is not null
	if (cB != NULL)
	{	
		// if there are bytes in the buffer
		if (cB->length > 0){
			return cB->buffer[cB->head];
		}
	}
	return 0;	
}


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read
unsigned char readFront (CBRef cB){
	// if the circular buffer is not null
	if (cB != NULL)
	{	
		char retVal;
		// if there are bytes in the buffer
		if (cB->length > 0){
			retVal = cB->buffer[cB->head];
			// increase the head and wrap around if needed
			cB->head = cB->head < (cB->size -1)? cB->head+1: 0;
			// // decrease the amount of data available
			cB->length--;
			return retVal;
		}
	}
	return 0;
}

// writes one byte at the end of the circular buffer, returns 1 if overflow occured
unsigned char writeBack (CBRef cB, unsigned char data){
	// if the circular buffer is not null
	if (cB != NULL){
		cB->buffer[cB->tail] = data;
		cB->tail = cB->tail < (cB->size -1)? cB->tail+1: 0;
		cB->length = cB->length<cB->size? cB->length+1: cB->size;
		return (cB->head == cB->tail && cB->length>0);
	}
	else{
		return 2;
	}
}

// empties the circular buffer. It does not change the size. use with caution!!
void makeEmpty(CBRef cB){
	if (cB != NULL){
		int i;
		for(i = 0; i < cB->size; ++i)
		{
			cB->buffer[i]= 0;
		}
		cB->length = 0;
		cB->head = 0;
		cB->tail = 0;
	}
}

#if DEBUG
// Other Functions
// ===============
// prints the circular buffer, used for debug
void printCircBuf(CBRef cB){
	// if the circular buffer is not null
	if (cB != NULL){
		printf("[");
		int i;
		for(i = 0; i < cB->size; ++i)
		{
			printf("%d ", cB->buffer[i]);
		}
		printf("]\n");
		printf("Size of: %d\n", cB->size );
		printf("Len. of: %d\n", cB->length );
		printf("Head at: %d\n", cB->head );
		printf("Tail at: %d\n\n", cB->tail );

	}
	else{
		printf("Calling Print on an empty Circular Buffer");
	}
}
#endif

#include "apUtils.h"



float myAtan2(float num, float denom){
     #ifdef _IN_PC_
        return atan2(num,denom);
     #else
	return atan2f(num,denom);
     #endif
}

// GPS checksum code based on 
// http://www.codeproject.com/KB/mobile/WritingGPSApplications2.aspx
// original code in C# written by Jon Person, author of "GPS.NET" (www.gpsdotnet.com)
unsigned char getChecksum(unsigned char* sentence, unsigned char size){

    // Loop through all chars to get a checksum
    unsigned char checkSum = 0;
	unsigned char i;
	for (i = 0; i< size; i++)
    {
      if (sentence[i] == DOLLAR)
      {
        // Ignore the dollar sign
      }
      else if (sentence[i] == STAR)
      {
        // Stop processing before the asterisk
        break;
      }
      else
      {
        // Is this the first value for the checksum?
        if (i == 0)
        {
          // Yes. Set the checksum to the value
          checkSum = sentence[i];
        }
        else
        {
          // No. XOR the checksum with this character's value
	       checkSum ^= sentence[i];
        }
      }
    }
    // Return the checksum 
    return checkSum;
}

void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg ){
	unsigned char i;
	// start the header
	*(protMsg+0) = DOLLAR;
	*(protMsg+1) = AT;
	*(protMsg+2) = type;
	*(protMsg+3) = size;
	for( i = 0; i < size; i += 1 )
	{
		*(protMsg+i+4) = *(rawData +i);
	}
	*(protMsg+size+4) = STAR;
	*(protMsg+size+5) = AT;
	*(protMsg+size+6) = getChecksum(protMsg, (size+5));	
}


/*
The following function receives a raw input stream and
produces an output stream with split sentences ready to
parse. This is done specifically to work in Simulink so
inStream and outStream are fixed length, n & m respectively

Parameters
in_stream  [1...n]	... Raw incomming byte stream as it is read from the serial port
in_stream [0] 		...	Byte containing the amount of new bytes
out_stream [1...m] 	... Output sentece containing exactly one message
out_stream [0]		... Byte containing the Message type
out_stream [m+1]	...	Byte indicating wether there is a valid message
*/

void gpsInit(void);
void gpsSeparate(unsigned char* inStream, unsigned char* outStream);

// checksum code based on 
// http://www.codeproject.com/KB/mobile/WritingGPSApplications2.aspx
// original code in C# written by Jon Person, author of "GPS.NET" (www.gpsdotnet.com)
char getChecksum(unsigned char* sentence, unsigned char size);

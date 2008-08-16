/*
The following function receives a raw input stream and
produces an output stream with split sentences ready to
parse.

Parameters
in_stream  			... Raw incomming byte stream as it is read from the serial port
out_stream [1...n] 	... Output sentece containing exactly one message
out_stream [0]		... Byte containing the Message type
*/

#define GGA		358
#define RMC		377
#define 

void gpsSeparate(char* in_stream, char* out_streams)
{
    int width   = (int)mxGetPr(OUT_WIDTH_ARG)[0];	//specify output port width =WIDTH_ARG that is the max length of GPS sentence  */
    
    unsigned char tmp;							  /* temp char holder */	
    unsigned char *buf = (unsigned char *)ssGetDWork(S, 0);	/* uchar buffer to contain bytes from serial port*/
    int	*current   = ssGetIWork(S);				  /* current = addr of current position pointer in buf */
    int	*recLength = ssGetIWork(S) + 1;			  /* recLength = addr of receieved data length */
	int	*bufCount = ssGetIWork(S)+ 2;			  /* count number of useful bytes in buf. */
    int  serbufCount;							  /* count number of useful bytes collected in Serial buf*/
	int  HeaderFound, i, j, bufStop, chksum=0, nextbytetoprocess=0, lastHeaderPos=0, EOB;
	int  GGA=358,RMC=377;// checksum of 'GPGGA','GPRMC' sentences's header
	int  bl_header;// boolean values for GGA=1 and RMC=2 sentences, 0=nothing found
	int  headwidth=5;// length of GPS header except '$'
	int  ggalng=87,rmclng=73, enough_bytes =1;// initialize length of GGA (87) and RMC(73) sentences without header
	int_T temp[1024]={0};
	int *head_ptr = &bl_header;

    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);

	// Get the number of bytes available from the port
	serbufCount = (int)mxGetPr(IN_WIDTH_ARG)[0];    

	for (i=0; i<serbufCount; i++){temp[i] = ( int_T)(*uPtrs[i]);}

	*bufCount = serbufCount + *current;
	// place new chunk of data at the end of previously unprocessed data
	// 'buf' also keeps the remains of previous step ending at the *(buf+current),
	// where 'current' is the position of last byte
	for (i=*current;i<*bufCount;i++)
	{
		 *(buf+i)=(unsigned char)temp[i-*current];
	}
	
	i=0;

	
	/*Initialize logical flags*/
	HeaderFound = 0;
	i = 0;
	EOB = 0;//end of buffer
	
	//if (*bufCount<width) return;		// Not enough bytes to decode, output old value
	
	// while no header has been found
	while ((HeaderFound==0) && (EOB !=1) && (enough_bytes ==1))
	{			/* find Header byte = '$'=36 */

		    chksum =0;
			//printf("\n%d %d %d" , *bufCount,i, EOB);
            // while no header has been found
			while ((*(buf+i) != HEADER) && (EOB != 1))
		    {	
				//if (*(buf+i) == HEADER)
				//{
				//	printf("%d %d %d", i, *(buf+i), HEADER);
				//}
				// if you have enough bytes
				if (i < *bufCount)
				{
					// increment position indx
					i++;
				}
				// if you ran out of bytes
				else
				{
					// turn on the flag
					EOB = 1; 
				}
			} 
			
			//printf("\n%d %d %d" , *bufCount,i, EOB);
			// if the remaining amount of data read from the port is less
			// then the amount of data I want to write to the output
			if (*bufCount - i < width-1)
			{
				// turn the flag
				enough_bytes = 0;
			}

			// if I did not reach the End Of Buffer and have enough bytes
			// to write
			if ((EOB!=1) && (enough_bytes == 1) )
			{	
				//printf("\n Header Found i = %d" , i);
				// initialize the chechsum
				chksum = 0;				 

				// grab GPXXX
				for (j=1;j<headwidth+1;j++)
				{
					chksum = chksum + *(buf+i+j);
				}

				//printf("\n Checksum = %d" , chksum);						
			    if  (chksum == GGA)
				{      
					// turn on the flag
					HeaderFound = 1;
					
					// turn on the boolean flag
					bl_header=1;

					// intialize the length of the GGA message
					ggalng=0;

					// while we do not find a 13 (CR)
					//"0D"=13(ASCII), 
					while(*(buf+i+headwidth+1+ggalng) != 13) 
					{
						// increment the counter
						ggalng++;
					}
					
					// once we found the CR
					// copy to the outputport ggalng bytes
					memcpy(ssGetOutputPortSignal(S,1),buf+i+headwidth+1,ggalng);// ? chek to be ","=44

					// increment the position index to reflect all the bytes read
					i = i + ggalng;
				} // if checksum tally
				else
				{
					if (chksum == RMC)
					{        
						HeaderFound = 1; 
						bl_header=2;
						rmclng = 0;
						while(*(buf+i+headwidth+1+rmclng) != 13) 
						{
							rmclng++;//"0D"=13(ASCII), 
						}
						//					printf("rmc length = %d", rmclng);
						memcpy(ssGetOutputPortSignal(S,1),buf+i+headwidth+1,rmclng);// ? chek to be ","=44
						i = i + rmclng;
					} // if checksum tally
					else
					{ 
						// checksum doesn't tally
						i=i+5;
						bl_header=0;
					}// end of checksum searching
				}
				
				memcpy(ssGetOutputPortSignal(S,2),head_ptr,1);// ? chek to be ","=44

			}// if not EOB and there is enough bytes

	 } /* while HeaderFound = 0*/ 
	 
	 
        
	// if I did not reach the EOB looking for a header but I ran out of bytes to send
	// then copy the remains to the beginning of buffer
	if ((EOB != 1) || (enough_bytes == 0))
	{
		*bufCount=*bufCount-i;	//number of remain bytes
		// buf[j]=buf[i]
		for (j=0;j<*bufCount; j++) 
		{
			*(buf+j)=*(buf+i);
			i++;
		}//  end of for 
		*current=*bufCount;
	}
        
	ssCallSystemWithTid(S, 0, 0);	/* issue done pulse to outport 0 */
    return;
    
//#endif
}
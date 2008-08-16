#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME gpsrcv_v2

#include <stddef.h>
#include <stdlib.h>

#include "tmwtypes.h"
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include <string.h>
#include "time_xpcimport.h"
#endif

/* Input Arguments */
#define NUMBER_OF_ARGS          (2)
#define IN_WIDTH_ARG               ssGetSFcnParam(S,0) // Get the width of the input
#define OUT_WIDTH_ARG              ssGetSFcnParam(S,1) // Get the width of the input


#define NO_I_WORKS              (3)     /* current pos pointer in buf, rec length, bufCount */
#define NO_R_WORKS              (0)
#define NO_P_WORKS              (0)
#define NO_D_WORKS              (1)		/* for buf array */

#define HEADER					(36) // $- sign

static char_T msg[256];


static void mdlInitializeSizes(SimStruct *S)
{


    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n"
                "%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }


    /* Set-up size information */
    ssSetNumContStates( S, 0);
    ssSetNumDiscStates( S, 0);
    
	ssSetNumOutputPorts(S, 3);          // function-call, actual data and header indicator 
    ssSetNumInputPorts( S, 1);          // data from serial port

	// Configure the output
    ssSetOutputPortWidth(S, 0, 1);		/* Function-call */

    ssSetOutputPortWidth(S, 1, (int)mxGetPr(OUT_WIDTH_ARG)[0]);/* Data */
    ssSetOutputPortDataType(S, 1, SS_UINT8);

    ssSetOutputPortWidth(S, 2, 1);		/* Header index */
    ssSetOutputPortDataType(S, 2, SS_UINT8);

	// Configure the Input
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortWidth(S, 0, (int)mxGetPr(IN_WIDTH_ARG)[0]);
    ssSetInputPortDataType(S, 0, SS_UINT8);

   

    // Set Size of working vectors

    ssSetNumSampleTimes(S,1);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);
    ssSetNumDWork(S, NO_D_WORKS);

    ssSetDWorkDataType(S, 0, SS_UINT8);
	ssSetDWorkWidth(   S, 0, 2048);


    ssSetNumModes(         S, 0);
    ssSetNumNonsampledZCs( S, 0);

    ssSetSFcnParamNotTunable(S,0);
    ssSetSFcnParamNotTunable(S,1);
    
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

/* Function to initialize sample times */
static void mdlInitializeSampleTimes(SimStruct *S)
{
   // Inherit the sample time from the model
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetCallSystemOutput(S, 0);
}

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    ssGetIWork(S)[0] = 0;	/* set current buf pointer = 0 */
	ssGetIWork(S)[2] = 0;	/* set bufCount = 0 */

#endif
}
#endif


/* Function to compute outputs */
static void mdlOutputs(SimStruct *S, int_T tid)
{
//#ifndef MATLAB_MEX_FILE
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

/* Function to perform housekeeping at execution termination */
static void mdlTerminate(SimStruct *S)
{
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
 

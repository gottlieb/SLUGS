#include "adisCube.h"

void cubeInit (void){
	unsigned short recvdData = 0;
	printToUart2("Starting %s\n\r","Cube Init");
    // SPI1CON1 Register Settings
    SPI2CON1bits.DISSCK = 0;    //Internal Serial Clock is Enabled.
    SPI2CON1bits.DISSDO = 0;    //SDOx pin is controlled by the module.
    SPI2CON1bits.MODE16 = 1;    //Communication is word-wide (16 bits).
    SPI2CON1bits.SMP    = 0;    //Sample at the middle .
    SPI2CON1bits.CKE    = 0;    //Serial output data changes on transition from
                                //Idle clock state to active clock state
    SPI2CON1bits.CKP    = 0;    //Idle state for clock is a low level;
                                //active state is a high level
    SPI2CON1bits.SSEN   = 0;    // SS not Used ( Master mode)    
    SPI2CON1bits.MSTEN  = 1;    //Master Mode Enabled
    
    // Configure the clock for 2 MHz
    SPI2CON1bits.SPRE   = 3;    //Secondary prescaler to 5:1
    SPI2CON1bits.PPRE   = 1;    //Primary prescaler 4:1
    
    
    // Enable the module 
    SPI2STATbits.SPIROV  = 0;   //Clear overflow bit
    SPI2STATbits.SPIEN   = 1;   //Enable SPI Module
    
    printToUart2("Starting %s\n\r","SPI Enabled");
    // AN18 is used for data reading
    
    // Configure the Analog pins C3 as digital.
    // C3 is used to determine if data is ready on the 
    // CUBE
    AD1PCFGHbits.PCFG18 = 1;
	TRISCbits.TRISC3 	= 1;
	
	// Configure RG9 as output pin to use as chip-select
	TRISGbits.TRISG9	= 0;
	
	printToUart2("Starting %s\n\r","Cube Config");
	// Start the Configuration Process
	// ===============================
	// Drive SS
	selectCube();
	Nop(); Nop(); Nop();
		
	// Set the DIO pin and Gyro accel compensation
	write2Cube(W_MSC_CTRL);
	printToUart2("Starting %s\n\r","Gyro Comp");
	
	// Set the internal sample rate
	write2Cube(W_SMPL_PRD);
	printToUart2("Starting %s\n\r","Sample Rate");
	// Set the sensitivity
	write2Cube(W_SENS_AVG_H);
	printToUart2("Starting %s\n\r","sensitivity");
	// Set the digital filtering
	write2Cube(W_SENS_AVG_L);
	printToUart2("Starting %s\n\r","Filtering");
	// Dont Sleep
	write2Cube(W_SLP_CNT);
	printToUart2("Starting %s\n\r","No Sleep");
	// Start a full calibration
	write2Cube(W_COMMAND_FULLCAL);
	printToUart2("Starting %s\n\r","Full Cal");
	// Drive SS
	deselectCube();
}

void startCubeRead (void) {
	// Drive SS
	selectCube();
	Nop(); Nop(); Nop();
	
	// dummy read 
	write2Cube(R_GYROX);
	
	rawControlData.gyroX.shData = write2Cube(R_GYROY);
	printToUart2("GYRO X %X\n\r",rawControlData.gyroX.shData);
	rawControlData.gyroY.shData = write2Cube(R_GYROZ);
	rawControlData.gyroZ.shData = write2Cube(R_ACCELX);
	
	rawControlData.accelX.shData = write2Cube(R_ACCELY);
	rawControlData.accelY.shData = write2Cube(R_ACCELZ);
	rawControlData.accelZ.shData = write2Cube(R_STATUS); // dummy write

	// Drive SS
	deselectCube();
	
}

void getCubeData (short * cubeData) {
	if (cubeDataReady()){
		startCubeRead();
	}
	
	cubeData[0] = rawControlData.gyroX.shData;
	cubeData[1] = rawControlData.gyroY.shData;
	cubeData[2] = rawControlData.gyroZ.shData;
	cubeData[3] = rawControlData.accelX.shData;
	cubeData[4] = rawControlData.accelY.shData;
	cubeData[5] = rawControlData.accelZ.shData;
}

// SPI Primitives
// ==============
unsigned short write2Cube (unsigned short data2Send) {
	unsigned short temp = 3;
	// Write the data to the SPI buffer
	WriteSPI2(data2Send);
	
	// Wait for the TX buffer to empty
	while(SPI2STATbits.SPITBF);
	
	// Wait for the RX buffer to be full
	while(!SPI2STATbits.SPIRBF);
	
	// Read the receive buffer
	temp =  ReadSPI2();
	return temp;
	
	// Clear the overflow for safekeeping
	// If overflow occurs and the flag is not cleared the module will freeze
	SPI2STATbits.SPIROV  = 0;   
}


void initDevBoard (void){
	magnetoInit();
	cubeInit();
}

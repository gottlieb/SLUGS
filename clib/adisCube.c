#include "adisCube.h"

void cubeInit (void){
	long i = 0;
	printToUart2("Starting %s\n\r","Cube Init");
    // SPI1CON1 Register Settings
    SPI2CON1bits.DISSCK = 0;    //Internal Serial Clock is Enabled.
    SPI2CON1bits.DISSDO = 0;    //SDOx pin is controlled by the module.
    SPI2CON1bits.MODE16 = 1;    //Communication is word-wide (16 bits).
    SPI2CON1bits.SMP    = 0;    //Sample at the middle.
    SPI2CON1bits.CKE    = 0;    //Serial output data changes on transition from
                                //Idle clock state to active clock state
    SPI2CON1bits.CKP    = 1;    //Idle state for clock is a high level;
                                //active state is a low level
    SPI2CON1bits.SSEN   = 0;    // SS not Used ( Master mode)    
    SPI2CON1bits.MSTEN  = 1;    //Master Mode Enabled
    
    // Configure the clock for 2 MHz
    SPI2CON1bits.SPRE   = 3;    //Secondary prescaler to 5:1
    SPI2CON1bits.PPRE   = 2;    //Primary prescaler 4:1
    
    
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
	
	printToUart2("Starting %s\n\r","Self Test");
	write2Cube(W_MSC_CTRL_SELFTEST);
	
	for(i = 0; i < 1500000; i += 1 )
	{
		Nop();
	}
	
	//Send a status register message
	write2Cube(R_STATUS);
	
	printToUart2("Status %X\n\r",write2Cube(R_ADISPWR));
		
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
	
	while(!cubeDataReady());
	printToUart2("Starting %s\n\r","Done Cal");
	
	
	printToUart2("Starting %s\n\r","Self Test Again");
	write2Cube(W_MSC_CTRL_SELFTEST);
	
	for(i = 0; i < 1500000; i += 1 )
	{
		Nop();
	}
	
	//Send a status register message
	write2Cube(R_STATUS);
	
	printToUart2(" === Status %X\n\r",write2Cube(R_ADISPWR));
	
	deselectCube();
}

void startCubeRead (void) {
	// Drive SS
	LATAbits.LATA0 = 1;
	
	selectCube();
	Nop(); Nop(); Nop();
	
	// dummy read 
	//printToUart2("Config %X\n\r",write2Cube(R_GYROX));
	write2Cube(R_GYROX);
	
	rawControlData.gyroX.shData = convert14BitToShort(write2Cube(R_GYROY));
	printToUart2("GYRO X %d\n\r",rawControlData.gyroX.shData);
	rawControlData.gyroY.shData = convert14BitToShort(write2Cube(R_GYROZ));
	//printToUart2("GYRO Y %X\n\r",rawControlData.gyroY.shData);
	rawControlData.gyroZ.shData = convert14BitToShort(write2Cube(R_ACCELX));
	
	rawControlData.accelX.shData =convert14BitToShort(write2Cube(R_ACCELY));
	rawControlData.accelY.shData =convert14BitToShort(write2Cube(R_ACCELZ));
	rawControlData.accelZ.shData =convert14BitToShort(write2Cube(R_STATUS)); // dummy write

	// Drive SS
	deselectCube();
	
	LATAbits.LATA0 = 0;
}

void getCubeData (short * cubeData) {
	LATAbits.LATA15 = PORTCbits.RC3;
	if (cubeDataReady()){
		startCubeRead();
	}
	
	cubeData[0] = rawControlData.gyroX.shData;
	cubeData[1] = rawControlData.gyroY.shData;
	cubeData[2] = rawControlData.gyroZ.shData;
	cubeData[3] = rawControlData.accelX.shData;
	cubeData[4] = rawControlData.accelY.shData;
	cubeData[5] = rawControlData.accelZ.shData;
	LATAbits.LATA15 = PORTCbits.RC3;
}

// SPI Primitives
// ==============
unsigned short write2Cube (unsigned short data2Send) {
	
	unsigned short temp = 3, i;
	
	// Write the data to the SPI buffer
	WriteSPI2(data2Send);
	
	// Wait for the TX buffer to empty
	while(SPI2STATbits.SPITBF);
	
	// Wait for the RX buffer to be full
	while(!SPI2STATbits.SPIRBF);
	
	// Read the receive buffer
	temp =  ReadSPI2();
	
	for(i = 0; i < 700; i += 1 )
	{
		Nop();
	}
	return temp;
	
	// Clear the overflow for safekeeping
	// If overflow occurs and the flag is not cleared the module will freeze
	SPI2STATbits.SPIROV  = 0;   
}

short convert14BitToShort (short wordData) {
return (wordData & BITTEST_14)? (wordData | BITEXTEND_14) : (wordData & BITMASK_14);
}


short convert12BitToShort (short wordData) {

	
	return (wordData & BITTEST_12)? (wordData | BITEXTEND_12) : (wordData & BITMASK_12);
}

void initDevBoard (void){
	magnetoInit();
	cubeInit();
}

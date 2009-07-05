%% Read the data from the workspace. 
% It assumes the telemtery is stored in a workspace variable named data

% GPS
% ===
gpsYrIdx        = 14;
gpsMoIdx        = 15;
gpsDyIdx        = 16;
gpsHrIdx        = 17;
gpsMnIdx        = 18;
gpsScIdx        = 19;
gpsLatIdx       = 20;
gpsLonIdx       = 21;
gpsHeiIdx       = 22;
gpsCogIdx       = 23;
gpsSogIdx       = 24;
gpsHdoIdx       = 25;
gpsFixIdx       = 26;
gpsSatIdx       = 27;
gpsNewIdx       = 28;

% Raw Data
% ========
rawGxIdx        = 29;
rawGyIdx        = 30 ;
rawGzIdx        = 31 ;
rawAxIdx        = 32 ;
rawAyIdx        = 33 ;
rawAzIdx        = 34 ;
rawMxIdx        = 35 ;
rawMyIdx        = 36 ;
rawMzIdx        = 37 ;
rawBarIdx       = 38 ;
rawPitIdx       = 39 ;
rawPwrIdx       = 40 ;
rawTheIdx       = 41 ;

% Air data and Diagnostics
airDynIdx       = 48;
airStaIdx       = 49;
airTemIdx       = 50;
diaFl1Idx       = 51;
diaFl2Idx       = 52;
diaFl3Idx       = 53;
diaSh1Idx       = 54;
diaSh2Idx       = 55;
diaSh3Idx       = 56;

M = data;

% Produce the Time vector
time = transpose( 0:0.01:(size(M(:,1))*.01 - 0.01));

% load the calibration and temp compensation data
run ../mcuInit.m

% generate each meaningful data 
PQR_hil = data(:, rawGxIdx : rawGzIdx)* cubeGyroGain;
ACC_hil = data(:, rawAxIdx : rawAzIdx)* cubeAccelGain;
MAG_hil = data(:, rawMxIdx : rawMzIdx);

GPS_hil =  data(:, gpsLatIdx:gpsSogIdx);

% GS Location. East field location
GS_location = [0 36.9898376464844 -122.051963806152];

% Returning raw data mapped to speed in the future this should come from
% the computed in the airData message
DYN_hil = data(:,rawPitIdx);

baseHeight = GPS_hil(1,3);

STA_hil = data(:,rawBarIdx);

TEM_hil = data(:,airTemIdx);

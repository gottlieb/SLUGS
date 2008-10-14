%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%							                    %
%%%	  PICCOLO SIMULINK MODEL INITIALIZATION   %%%
%                                               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%clear all;
%clc;

% Sample time
APtsamp = 0.05;

% Sensors
SizeSensors = 26;
IdxSensorsReserved0 = 1;
IdxSensorsGPSNew = 2;
IdxSensorsLat = 3;
IdxSensorsLon = 4;
IdxSensorsAlt = 5;
IdxSensorsVNorth = 6;
IdxSensorsVEast = 7;
IdxSensorsVDown = 8;
IdxSensorsAccX = 9;
IdxSensorsAccY = 10;
IdxSensorsAccZ = 11;
IdxSensorsRollRate = 12;
IdxSensorsPitchRate = 13;
IdxSensorsYawRate = 14;
IdxSensorsPstat = 15;
IdxSensorsPdyn = 16;
IdxSensorsOAT = 17;
IdxSensorsMagX = 18;
IdxSensorsMagY = 19;
IdxSensorsMagZ = 20;
IdxSensorsReserved1 = 21;
IdxSensorsReserved2 = 22;
IdxSensorsReserved3 = 23;
IdxSensorsReserved4 = 24;
IdxSensorsReserved5 = 25;
IdxSensorsReserved6 = 26;

% Estimates
SizeEstim = 16;
IdxEstimReserved0 = 1;
IdxEstimWNorth = 2;
IdxEstimWEast = 3;
IdxEstimReserved1 = 4;
IdxEstimRollAngle = 5;
IdxEstimPitchAngle = 6;
IdxEstimHeading = 7;
IdxEstimBaroAlt = 8;
IdxEstimDensity = 9;
IdxEstimTAS = 10;
IdxEstimReserved5 = 11;
IdxEstimReserved6 = 12;
IdxEstimReserved7 = 13;
IdxEstimReserved8 = 14;
IdxEstimReserved9 = 15;
IdxEstimReserved10 = 16;

% Settings
SizeSet = 12;
IdxSetReserved0 = 1;
IdxSetPSL = 2;
IdxSetReserved1 = 3;
IdxSetAileronTrim = 4;
IdxSetReserved2 = 5;
IdxSetElevatorTrim = 6;
IdxSetReserved3 = 7;
IdxSetRudderTrim = 8;
IdxSetReserved4 = 9;
IdxSetThrottleTrim = 10;
IdxSetLandingFlap = 11;
IdxSetReserved6 = 12;

% Commands
SizeCmd = 18;
IdxCmdPdynShift = 1;
IdxCmdPdyn = 2;
IdxCmdPitchAngle = 3;
IdxCmdSlopeAngle = 4;
IdxCmdTouchDownLat = 5;
IdxCmdTouchDownLon = 6;
IdxCmdAlt = 7;
IdxCmdFlap = 8;
IdxCmdTurnRateShift = 9;
IdxCmdTurnRate = 10;
IdxCmdWp1Lat = 11;
IdxCmdWp1Lon = 12;
IdxCmdWp1Alt = 13;
IdxCmdWp2Lat = 14;
IdxCmdWp2Lon = 15;
IdxCmdWp2Alt = 16;
IdxCmdOrbitRadius = 17;
IdxCmdOrbitSense = 18;

% States
SizeStates = 16;
IdxStatesReserved0 = 1;
IdxStatesGlobal = 2;
IdxStatesPdyn = 3;
IdxStatesPitch = 4;
IdxStatesAlt = 5;
IdxStatesSlope = 6;
IdxStatesTurnRate = 7;
IdxStatesRoll = 8;
IdxStatesYaw = 9;
IdxStatesTurnComp = 10;
IdxStatesAltToElev = 11;
IdxStatesTracker = 12;
IdxStatesAltToPdyn = 13;
IdxStatesFlap = 14;
IdxStatesMode = 15;
IdxStatesManual = 16;

% Gains
SizeGains = 27;
IdxGainsReserved0 = 1;
IdxGainsPdynP = 2;
IdxGainsPdynI = 3;
IdxGainsPdynD = 4;
IdxGainsPitchP = 5;
IdxGainsPitchI = 6;
IdxGainsPitchD = 7;
IdxGainsAltP = 8;
IdxGainsAltI = 9;
IdxGainsAltD = 10;
IdxGainsSlopeConv = 11;
IdxGainsTurnP = 12;
IdxGainsTurnI = 13;
IdxGainsTurnD = 14;
IdxGainsRollP = 15;
IdxGainsRollI = 16;
IdxGainsRollD = 17;
IdxGainsYawP = 18;
IdxGainsYawI = 19;
IdxGainsYawD = 20;
IdxGainsTrackP = 21;
IdxGainsTrackI = 22;
IdxGainsTrackD = 23;
IdxGainsTrackConv = 24;
IdxGainsSlopeElevatorD = 25;
IdxGainsSlopeElevatorP = 26;
IdxGainsReserved3 = 27;

% Limits
SizeLimits = 21;
IdxLimitsReserved0 = 1;
IdxLimitsPdynMin = 2;
IdxLimitsPdynMax = 3;
IdxLimitsSlopeMin = 4;
IdxLimitsSlopeMax = 5;
IdxLimitsAltMin = 6;
IdxLimitsAltMax = 7;
IdxLimitsBankMin = 8;
IdxLimitsBankMax = 9;
IdxLimitsAileronMin = 10;
IdxLimitsAileronMax = 11;
IdxLimitsElevatorMin = 12;
IdxLimitsElevatorMax = 13;
IdxLimitsRudderMin = 14;
IdxLimitsRudderMax = 15;
IdxLimitsThrottleMin = 16;
IdxLimitsThrottleMax = 17;
IdxLimitsFlapMin = 18;
IdxLimitsFlapMax = 19;
IdxLimitsReserved1 = 20;
IdxLimitsReserved2 = 21;

% Actuators
SizeAct = 12;
IdxActReserved0 = 1;
IdxActAileron = 2;
IdxActReserved1 = 3;
IdxActElevator = 4;
IdxActReserved2 = 5;
IdxActRudder = 6;
IdxActReserved3 = 7;
IdxActThrottle = 8;
IdxActReserved4 = 9;
IdxActFlap = 10;
IdxActReserved5 = 11;
IdxActReserved6 = 12;

% Derived
SizeDrv = 30;
IdxDrvBaroAlt = 1;
IdxDrvDensity = 2;
IdxDrvTAS = 3;
IdxDrvGainScaler = 4;
IdxDrvBankAngleCmd = 5;
IdxDrvYawRateCmd = 6;
IdxDrvTASCmdNom = 8;        %modified by E.Xargay: See block Ptch Control Vector Inputs
IdxDrvTASCmd = 7;           %modified by E.Xargay: See block Ptch Control Vector Inputs
%IdxDrvTASCmdNom = 7;
%IdxDrvTASCmd = 8;
IdxDrvPitchRateCmd = 9;
IdxDrvTurnRateCmd = 10;
IdxDrvTurnRateMin = 11;
IdxDrvTurnRateMax = 12;
IdxDrvWp2Dist = 13;
IdxDrvXtrack = 14;
IdxDrvYtrack = 15;
IdxDrvVxtrack = 16;
IdxDrvVytrack = 17;
IdxDrvTrackLength = 18;
IdxDrvXECEF = 19;
IdxDrvYECEF = 20;
IdxDrvZECEF = 21;
IdxDrvVxECEF = 22;
IdxDrvVyECEF = 23;
IdxDrvVzECEF = 24;
IdxDrvAltCmd = 25;
IdxDrvSlopeAlt = 26;
IdxDrvTouchDownDist = 27;
IdxDrvVerticalVel = 28;
IdxDrvSlopeElevator = 29;
IdxDrvAltError = 30;

% NPS AUTOPILOT SETTINGS

% Commands
SizeNPSCmd = 6;
IdxNPSCmdTAS = 1;
IdxNPSCmdPitchRate = 2;
IdxNPSCmdYawRate = 3;
IdxNPSCmdReserved0 = 4;
IdxNPSCmdReserved1 = 5;
IdxNPSCmdReserved2 = 6;

% States
SizeNPSStates = 6;
IdxNPSStatesGlobal = 1;
IdxNPSStatesElev = 2;
IdxNPSStatesAil = 3;
IdxNPSStatesRudd = 4;
IdxNPSStatesThr = 5;
IdxNPSStatesReserved0 = 6;

% Limits
SizeNPSLimits = 18;
IdxNPSLimitsElevMin = 1;
IdxNPSLimitsElevMax = 2;
IdxNPSLimitsAilMin = 3;
IdxNPSLimitsAilMax = 4;
IdxNPSLimitsRuddMin = 5;
IdxNPSLimitsRuddMax = 6;
IdxNPSLimitsThrMin = 7;
IdxNPSLimitsThrMax = 8;
IdxNPSLimitsTrimElevMin = 9;
IdxNPSLimitsTrimElevMax = 10;
IdxNPSLimitsTrimAilMin = 11;
IdxNPSLimitsTrimAilMax = 12;
IdxNPSLimitsTrimRuddMin = 13;
IdxNPSLimitsTrimRuddMax = 14;
IdxNPSLimitsReserved0 = 15;
IdxNPSLimitsReserved1 = 16;
IdxNPSLimitsReserved2 = 17;
IdxNPSLimitsReserved3 = 18;

% Gains
SizeNPSGains = 8;
IdxNPSGainsElev = 1;
IdxNPSGainsAil = 2;
IdxNPSGainsRudd = 3;
IdxNPSGainsThr = 4;
IdxNPSGainsReserved0 = 5;
IdxNPSGainsReserved1 = 6;
IdxNPSGainsReserved2 = 7;
IdxNPSGainsReserved3 = 8;


% Actuators
deg2rad=pi/180;
damin=-25*deg2rad;
damax=25*deg2rad;
demin=-15*deg2rad;
demax=15*deg2rad;
drmin=-25*deg2rad;
drmax=25*deg2rad;
dtmin=0;
dtmax=1;
dfmin=0*deg2rad;
dfmax=30*deg2rad;

% trim
datrim=0*deg2rad;
detrim=-0.75*deg2rad;
drtrim=0*deg2rad;
dttrim=0.35;

% landing
dfland=30*deg2rad;

%% General values
% Global Sample Time
T = 0.01;

%% Gains and Biases

% Straight Gains
% ==============
cubeGyroGain = .07326*pi/180;
cubeAccelGain = (2.522e-3)*9.815;


% Temp Coefficients
% =================

% No gyro, accels temp compensation needed

% Mags
magTempK = [.0057 -.0423 .0426];
magMeanTemp = [162.42 162.42 162.42];

barTGain1 = -0.0102663;
barTGain2 = 0.0207608;
barTMean1 = -161.3;
barTMean2 = 347.23;
barAdjust = -6;
baroCutTemp = -50.0;

pitTGain1 = -0.0552923;
pitTGain2 = -0.0950433;
pitTMean1 = -202.93;
pitTMean2 = 293.053;
pitAdjust = -41;
pitCutTemp = -130.0;

axTGain1 = -0.0332796;
axTGain2 = 0.0543519;
axTMean1 = 68.41;
axTMean2 = 500.7;
accelXCutTemp = 350.0;


% Scale/Offset sets
% =================

% Baro
% From data sheet assuming linear mapping from 5 to 3.3 
% into the micro ADC
% 0.25*3.3/5  ->  15000
% 4.75*3.3/5  -> 115000
raw = 1.2412*[250*3300/5000 4750*3300/5000];
pre = [15000 115000];
P =  polyfit(raw,pre,1);
baroScale  = P(1);
baroOffset = P(2);

magScale  = 0.3418;
magOffset = 0;

% Pito
% ====

% pitotScale  = 0.9258;
% pitotOffset = -830.6641;
pitotScale  = 1.213292590242;
pitotOffset = -1083.881038056753;


% Temp
% 14.8  -> 1160
% 17.9  -> 1180
% 24.3  -> 1230
% 32.0  -> 1265
% 33.5  -> 1280
% 35.1  -> 1301

temp = [148 179 243 32 335 351];
raw  = [1160 1180 1230 1265 1280 1301];
P =  polyfit(raw,temp,1);
tempScale  = P(1);
tempOffset = P(2);

% Power
%  7.0 -> 1921
%  7.5 -> 2075
%  8.0 -> 2225
%  8.5 -> 2383
%  9.0 -> 2536
%  9.5 -> 2712
% 10.0 -> 2874
% 10.5 -> 3026
% 11.0 -> 3173
% 11.5 -> 3341
% 12.0 -> 3493
% 12.5 -> 3632
% 13.0 -> 3806
% 13.5 -> 3966
powr = [7000 7500 8000 8500 9000 9500 10000 10500 11000 11500 12000 12500 13000 13500];
raw  = [1921 2075 2225 2383 2536 2712 2874 3026 3173 3341 3493 3632 3806 3966];

P =  polyfit(raw,powr,1);
powerScale  = P(1);
powerOffset = P(2);

% Baro Altitude Computation
% =========================
basePressure = 98192.64;
baseTemp = 288.215;
lapseRate = -0.00198122;
baseH = 225;
       
% Ellipse Compensation for Magnetometers
% =========================
param_mag.xo = 52.298979126589039;
param_mag.yo = 57.602648678399504;
param_mag.zo = 52.984329390038532;
param_mag.a =   240.2003709561940;
param_mag.c =   230.2578675792432;
param_mag.b =   244.9911695537955;
param_mag.phi= -7.433915262037260;
param_mag.rho = -4.077131534516775;
param_mag.lambda = 4.050279490811578;
param_mag.R = 1;
param_mag.one_over_a = 1/param_mag.a;
param_mag.one_over_b = 1/param_mag.b;
param_mag.one_over_c = 1/param_mag.c;

  % Ellipse Compensation for Accelerometers
% =========================
param_acc.xo =  0.570077407545699;
param_acc.yo =  -0.037320719350785;
param_acc.zo = -0.155871603576177;
param_acc.a =   1.021447629870704;
param_acc.c =   0.965852814030698;
param_acc.b =   1.012956660540617;
param_acc.phi= -0.587227044344071;
param_acc.rho = 0.768452775068802;
param_acc.lambda = 0.179663683262263;
param_acc.R = 9.810000000000001;
param_acc.one_over_a = 1/param_acc.a;
param_acc.one_over_b = 1/param_acc.b;
param_acc.one_over_c = 1/param_acc.c;  % Ellipse Compensation for Accelerometers
% =========================
param_acc.xo =  0.570077407545699;
param_acc.yo =  -0.037320719350785;
param_acc.zo = -0.155871603576177;
param_acc.a =   1.021447629870704;
param_acc.c =   0.965852814030698;
param_acc.b =   1.012956660540617;
param_acc.phi= -0.587227044344071;
param_acc.rho = 0.768452775068802;
param_acc.lambda = 0.179663683262263;
param_acc.R = 9.810000000000001;
param_acc.one_over_a = 1/param_acc.a;
param_acc.one_over_b = 1/param_acc.b;
param_acc.one_over_c = 1/param_acc.c;


%% Run the HIL init
run ./HILSim/hilInit.m

%% Curve fitting for IC from Pilot Console. 
% Conversion from IC output to Radians

% Rudder
mICdr = mPWMdr/2;
bICdr = bPWMdr;

% Aileron
mICda = mPWMda/2;
bICda = bPWMda;

% Elevator
mICde = mPWMde/2;
bICde = bPWMde;


%Throttle
mICdt = mPWMdt/2;
bICdt = bPWMdt;

%% Sensor Lowpass filter cutoff filters and other limits
mainSensorCutoff = 10;

pressureSensorCutoff = 5;

lowRateSensorCutoff = 0.02;

maxDynPressure = 3000;

%% Data for Ren's Complementary Filters
% Position Comp Filters
xCutoff = 10;
yCutoff = 10;
zCutoff = 0.2;
baroCutoff = 0.2/(2*pi);

%Velocity Comp filters
vzCutoff = 1;

% Accelerometer bias rate limiter
accBiasRateLimit = 2*(.014844)/300*apSampleTime;

% Gyro bias rate limiter
gyroBiasRateLimit = 2*(.006393)/500*apSampleTime;

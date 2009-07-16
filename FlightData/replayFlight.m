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

% Attitude
% ========
timeStampIdx    = 1;
attRollIdx      = 2;
attPitchIdx     = 3;
attYawIdx       = 4;
attPIdx         = 5;
attQIdx         = 6;
attRIdx         = 7;

% Position
% ========
posXIdx         = 8;
posYIdx         = 9;
posZIdx         = 10;
posVxIdx        = 11;
posVyIdx        = 12;
posVzIdx        = 13;

% Bias
% ====
biaAxIdx        = 42;
biaAyIdx        = 43;
biaAzIdx        = 44;
biaGxIdx        = 45;
biaGyIdx        = 46;
biaGzIdx        = 47;

M = data;

% Produce the Time vector
time = transpose( 0:0.01:(size(M(:,1))*.01 - 0.01));
%% MCU INIT BEGIN
% ===============
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

baroTempK = 0.7085;
baroMeanTemp = 205.64;

pitTempK = -0.0333;
pitMeanTemp = 205.64;


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
pitotScale  = 0.9909;
pitotOffset = -940.1001;


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
param_mag.xo =  62.582994105307556;
param_mag.yo =  59.395539601652828;
param_mag.zo = -66.523069120295460;
param_mag.a =   2.447039991696393e+002;
param_mag.one_over_a = 1/param_mag.a;
param_mag.c =   2.357258726014612e+002;
param_mag.one_over_c = 1/param_mag.c;
param_mag.b =   2.529708146776011e+002;
param_mag.one_over_b = 1/param_mag.b;
param_mag.phi= -7.564558089048317;
param_mag.rho = 4.431438455319272;
param_mag.lambda = -3.931339025635420;
param_mag.R = 1;

% Ellipse Compensation for Accelerometers
% =========================
param_acc.xo =  -0.870652332890343;
param_acc.yo =  0.392105017623336;
param_acc.zo = 0.058285827021149;
param_acc.a =   1.028348124236639;
param_acc.one_over_a = 1/param_acc.a;
param_acc.c =   0.989537431181334;
param_acc.one_over_c = 1/param_acc.c;
param_acc.b =   1.051705796999721;
param_acc.one_over_b = 1/param_acc.b;
param_acc.phi= -2.270537506584771;
param_acc.rho = 0.056163200653814;
param_acc.lambda = 0.268027255513422;
param_acc.R = 9.810000000000001;


%% HIL INIT BEGIN
% =========
%% Set up the values for the HIL Simulation
HIL_K = 3;


%% RASCAL VAR INIT BEGIN
% ======================
%% Sig RASCAL 110 data
clc;
SampleT=0.005;
r_lim=200*pi/180;

% Standartd Atmosphere
    ISA_lapse = .0065;          % Lapse rate            (degC/m)
    ISA_hmax  = 2000;           % Altitude limit        (m)
    ISA_R     = 287;            % Gas Constant          (degK*m*m/s/s)
    ISA_g     = 9.815;          % Gravity               (m/s/s)
    ISA_rho0  = 1.225;          % Density at sea level  (kg/m/m/m)
    ISA_P0    = 101325;         % Sea-level Pressure    (N/m/m)
    ISA_T0    = 289;            % Sea-level Temperature (degK)

% Set the initial conditions based on the Piccolo Doublets File
%  Initial Conditions in ENU (all vector data is represented as a column
%  vectors)
Pos_0   = [-200; 0 ;150]';     % Initial position vector (m)
Euler_0 = [0; 0; 160*pi/180]';     % Initial Euler angles    (rad)
Omega_0 = [0; 0; 0]';                              % Initial Omega           (rad/s)
PQR_0   = [0;0;0]';      % Initial Omega           (rad/s)
Vb_0    = [ 25; 0;0]';                     % Initial body-velocity vector (m/s)

% Mass and Geometric Parameters recomputation
S     = 0.982;       % surface area of wing  (m2)
span  = 2.795;       % wingspan              (m)
chord = S/span;      % chord                 (m)
elarm  =  1.21;      % elevator arm vr CG    (m)
mass =  0.45359237*18;        % gross weight          (kg)


 Ixx   = 4.12;    % main moment of inertia around axis Ox (kg*sq.m)
 Iyy   = 9.58;%5.43789;    % main moment of inertia around axis Oy (kg*sq.m)
 Izz   = 9.85;    % main moment of inertia around axis Oz (kg*sq.m)

 % Aerodynamic Derivatives (all per radian)
 CL0     = 0.38;      % lift coefficient at a = 0 = 0.0003;
 CLa     = 18.5;       % lift curve slope
 CLa_dot = 2.64;       % lift due to angle of attack rate
 CLq     = 7.4;       % lift due to pitch rate
 CLDe    = 0.24;       % lift due to elevator
 CLDf    = 0.4;       % delta lift due to flaps

 CD0     = 0.022;     % drag coefficient at a = 0
 A1      = 0.007;
 Apolar  = 0.057;       % drag curve slope (A2)

 CYb     = -1.098;      % side force due to sideslip
 CYDr    = 0.143;        % sideforce due to rudder

 Clb     = -0.296;      % roll moment due to beta::dihedral effect =-0.0132
 Clp     = -1.96;      % roll damping
 Clr     = 0.103;      % roll due to yaw rate
 ClDa    = 0.1695;    % roll control power
 ClDr    = 0.106;      % roll due to rudder

Cm0     = 0.3;%-0.05;      % pitch moment at a = 0
Cma     = -1.239;%-0.5;       % pitch moment due to angle of attack
Cma_dot = -7.00;      % pitch moment due to angle of attack rate    {Not included in model}
Cmq     = -2.4;        % pitch moment due to pitch rate             
CmDe    = -3.2;        %  pitch control power

 Cnb     = 0.277;%0.12;       % weathercock stability = 0.075
 Cnp     = -0.0889;    % adverse yaw
 Cnr     = -0.19997;      % yaw damping
 CnDa    = -0.023;      % aileron adverse yaw
% Piccolo user Guide:>The sign convention on the surface deflection has the following rules:
% flaps, ailerons, and elevators are all positive down. Rudders are positive right. 
% For ruddervators the sign convention follows the elevator rule, i.e. positive down.
 CnDr    = -0.1997;       % yaw control power (Sign convention : Positive for TER rudder deflection and Negative for TEL rudder deflection)

 CmDf    = -.021;

 % Engine Constants
 MinThK    = 0.077;
 ThK       = 2.17;
 TFact     = 0.4;%1.0;
 
% Wind Configuration
windBase = 3.5;
windDirTurb = 180;
windDirHor = 180;

% Baro Altitude Computation
% =========================
baseHeight =225;
baseTemp = 288.215;
lapseRate = -0.00198122;

% GS Location. East field location
GS_location = [0 36.9898376464844 -122.051963806152];

%  Initial Conditions in ENU (all vector data is represented as a column
%  vectors) for the quaternion
Euler_quat = [0; 0;  -160*pi/180]';     % Initial Euler angles    (rad)

% initial quaternion
cph = cos(Euler_quat(1)/2); sph = sin(Euler_quat(1)/2);
cth = cos(Euler_quat(2)/2); sth = sin(Euler_quat(2)/2);
cps = cos(Euler_quat(3)/2); sps = sin(Euler_quat(3)/2);
q_quat(1) = cph*cth*cps + sph*sth*sps;
q_quat(2) = sph*cth*cps - cph*sth*sps;
q_quat(3) = cph*sth*cps + sph*cth*sps;
q_quat(4) = cph*cth*sps - sph*sth*cps;
%% RASCAL VAR INIT END
% =====================

%% INNER OUTER INIT BEGIN
% =======================
%% General Values
derivativesConstant = 5;
apSampleTime = 0.01;

%% Control Surface Limits
deLimit = single(15*pi/180);
daLimit = single(35*pi/180);
dtLimit = single(1);
drLimit = single(10*pi/180);

%% Integrator Limits
uHoldLimit = single(0.85*dtLimit);          % Controls throttle
heightErrorLimit = single(15*pi/180);       % this loop generates theta_command
pitchErrorLimit = single(0.9*deLimit);      % controls elevator
yawDamperLimit = single(0.9*drLimit);       % controls rudder
rollControlLimit = single(0.95*daLimit);     % controls aileron

%% Command Limits
pitchCommandLimit = single(15*pi/180);
bankCommandLimit = single(45*pi/180);

%% Nav Values

L2_base = single(5);
U_comm = single(20);
R = single((U_comm)^2/(ISA_g*tan(bankCommandLimit)));

%% Curve fitting for PWM . Conversion from Radians to PWM
% Rudder
% The Values are as follows:
% -20 -> 2700
% -10 -> 3250
% -5  -> 3475
% 0   -> 3750
% +5  -> 3950
% +10 -> 4200
% +20 -> 4725

rad = [-20 -10 -5 0 5 10 20]*pi/180;
pwm = [2700 3250 3475 3750 3950 4200 4725];
P =  polyfit(rad, pwm,1);
mdr = P(1);
bdr = P(2);

% Aileron
% The Values are as follows:
% -20 -> 2450
% -10 -> 3150
% -5  -> 3420
% 0   -> 3700
% +5  -> 3975
% +10 -> 4250
% +20 -> 4900

rad = [-20 -10 -5 0 5 10 20]*pi/180;
pwm = [2450 3150 3420 3700 3975 4250 4900];
P =  polyfit(rad,pwm,1);
mda = P(1);
bda = P(2);

% Elevator
% The Values are as follows:
% -15 -> 2750
% -10 -> 3135
% -5  -> 3425
% 0   -> 3700
% +5  -> 4125
% +10 -> 4450
% +15 -> 4850

rad = [-15 -10 -5 0 5 10 15]*pi/180;
pwm = [2750 3135 3425 3700 4125 4450 4850];
P =  polyfit(rad,pwm,1);
mde = P(1);
bde = P(2);

% Throttle
% 0  ->  2500
% 1  ->  4850

rad = [0 1];
pwm = [2500 4850];
P =  polyfit(rad, pwm, 1);
mdt = P(1);
bdt = P(2);

%% INNER OUTER INIT END
% =====================
%% Set up the reverse lookup values for PWM to radians
% Rudder
% The Values are as follows:
% -20 -> 2700
% -10 -> 3250
% -5  -> 3475
% 0   -> 3750
% +5  -> 3950
% +10 -> 4200
% +20 -> 4725

rad = [-20 -10 -5 0 5 10 20]*pi/180;
pwm = [2700 3250 3475 3750 3950 4200 4725];
P =  polyfit(pwm,rad,1);
mPWMdr = P(1);
bPWMdr = P(2);

% Aileron
% The Values are as follows:
% -20 -> 2450
% -10 -> 3150
% -5  -> 3420
% 0   -> 3700
% +5  -> 3975
% +10 -> 4250
% +20 -> 4900

rad = [-20 -10 -5 0 5 10 20]*pi/180;
pwm = [2450 3150 3420 3700 3975 4250 4900];
P =  polyfit(pwm, rad,1);
mPWMda = P(1);
bPWMda = P(2);

% Elevator
% The Values are as follows:
% -15 -> 2750
% -10 -> 3135
% -5  -> 3425
% 0   -> 3700
% +5  -> 4125
% +10 -> 4450
% +15 -> 4850

rad = [-15 -10 -5 0 5 10 15]*pi/180;
pwm = [2750 3135 3425 3700 4125 4450 4850];
P =  polyfit(pwm,rad,1);
mPWMde = P(1);
bPWMde = P(2);

% Throttle
% 0  ->  2500
% 1  ->  4850

rad = [0 1];
pwm = [2500 4850];
P =  polyfit(pwm,rad,1);
mPWMdt = P(1);
bPWMdt = P(2);

%% Override RascalVar values
Pos_0   = [200; 350; 350]';     % Initial position vector (m)
Euler_0 = [0; 0; 0*pi/180]';     % Initial Euler angles    (rad)


%% HIL INIT END
% =============
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

%% 

% The Values are as follows:
% Rudder
% -15 -> 5560
% -10 -> 6300
% -5  -> 6860
% 0   -> 7550
% +5  -> 8100
% +10 -> 8647
% +15 -> 9445
% +16 -> 9500

% rad = [-15 -10 -5 0 5 10 15 16]*pi/180;
% ic = [5560 6300 6860 7550 8100 8647 9445 9500];
% P =  polyfit(ic,rad,1);

% The Values are as follows:
% -15 -> 5570
% -10 -> 6160
% -5  -> 6747
% 0   -> 7549
% +5  -> 7830
% +10 -> 8370
% +15 -> 8987
% +19 -> 9520
% 
% rad = [-15 -10 -5 0 5 10 15 19]*pi/180;
% ic = [5570 6160 6747 7549 7830 8370 8987 9520];
% P =  polyfit(ic,rad,1);

% The Values are as follows:
% -12 -> 5397
% -10 -> 5920
% -5  -> 6605
% 0   -> 7380
% +5  -> 8220
% +10 -> 8960
% +12 -> 9335

% rad = [-12 -10 -5 0 5 10 12]*pi/180;
% ic = [5397 5920 6605 7380 8220 8960 9335];
% P =  polyfit(ic,rad,1);

% The Values are as follows:
% 0   -> 5621
% 1/6 -> 6060
% 2/6 -> 6960
% 3/6 -> 7696
% 4/6 -> 8550
% 5/6 -> 8863
% 1   -> 9500

% rad = [0 1 2 3 4 5 6]./6;
% ic = [5621 6060 6960 7696 8550 8863 9500];
% P =  polyfit(ic,rad,1);

% % Rudder
% mICPWMdr = mdr*mICdr;
% bICPWMdr = mdr*bICdr + bdr;
% 
% % Aileron
% mICPWMda = mda*mICda;
% bICPWMda = mda*bICda + bda;
% 
% % Elevator
% mICPWMde = mde*mICde;
% bICPWMde = mde*bICde + bde;
% 
% 
% %Throttle
% mICPWMdt = mdt*mICdt;
% bICPWMdt = mdt*bICdt + bdt;

%% MCU INIT END
% ===============
%% Generate the flight data
% Raw
% ===
PQR_hil = data(:, rawGxIdx : rawGzIdx);
ACC_hil = data(:, rawAxIdx : rawAzIdx);
MAG_hil = data(:, rawMxIdx : rawMzIdx);
GPS_hil = data(:, gpsLatIdx:gpsSogIdx);
DYN_hil = data(:,rawPitIdx);
STA_hil = data(:,rawBarIdx);
TEM_hil = data(:,rawTheIdx);
POW_hil = data(:,rawPwrIdx);

% Computed
% ========
EUL_comp = data(:, attRollIdx : attYawIdx);
PQR_comp = data(:, attPIdx : attRIdx);
POS_comp = data(:, posXIdx : posZIdx);
VEL_comp = data(:, posVxIdx : posVzIdx);
GBI_comp = data(:, biaGxIdx : biaGzIdx);
ABI_comp = data(:, biaAxIdx : biaAzIdx);


% GS Location. East field location
GS_location = [0 36.9898376464844 -122.051963806152];


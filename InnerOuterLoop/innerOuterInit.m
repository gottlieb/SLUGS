%% General Values
derivativesConstant = 5;
apSampleTime = 0.01;

%% Control Surface Limits
deLimit = single(15*pi/180);
daLimit = single(25*pi/180);
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
bankCommandLimit = single(40*pi/180);

%% Nav Values
R = single(200);
L1_base = single(200);
U_comm = single(25);

%% Curve fitting for PWM . Conversion from Radians to PWM
% Calibration value in radians
calVal = 25*pi/180;

% Rudder
rudMin = 4550;
rudMax = 3300;
P =  polyfit([-calVal calVal],[rudMin rudMax],1);
mdr = P(1);
bdr = P(2);

% Aileron
ailMin = 4550;
ailMax = 3300;
P =  polyfit([-calVal calVal],[ailMin ailMax],1);
mda = P(1);
bda = P(2);

% Elevator
eleMin = 4550;
eleMax = 3300;
P =  polyfit([-calVal calVal],[eleMin eleMax],1);
mde = P(1);
bde = P(2);


%Throttle
thrMin = 4550;
thrMax = 3300;
P =  polyfit([0 1],[thrMin thrMax],1);
mdt = P(1);
bdt = P(2);


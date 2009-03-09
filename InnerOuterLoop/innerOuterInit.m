%% General Values
derivativesConstant = 5;
apSampleTime = 0.01;

%% Control Surface Limits
deLimit = 15*pi/180;
daLimit = 25*pi/180;
dtLimit = 1;
drLimit = 10*pi/180;

%% Integrator Limits
uHoldLimit = 0.85*dtLimit;          % Controls throttle
heightErrorLimit = 15*pi/180;       % this loop generates theta_command
pitchErrorLimit = 0.9*deLimit;      % controls elevator
yawDamperLimit = 0.9*drLimit;       % controls rudder
rollControlLimit = 0.95*daLimit;     % controls aileron

%% Command Limits
pitchCommandLimit = 15*pi/180;
bankCommandLimit = 40*pi/180;

%% Nav Values
R = 200;
L1_base = 200;
U_comm = 25;
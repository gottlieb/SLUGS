%% General Values
derivativesConstant = 5;

%% Control Surface Limits
deLimit = 15*pi/180;
daLimit = 20*pi/180;
dtLimit = 1;
drLimit = 10*pi/180;

%% Integrator Limits
uHoldLimit = 0.85*dtLimit;          % Controls throttle
heightErrorLimit = 15*pi/180;       % this loop generates theta_command
pitchErrorLimit = 0.9*deLimit;      % controls elevator
yawDamperLimit = 0.9*drLimit;       % controls rudder
rollControlLimit = 0.9*daLimit;     % controls aileron

%% Command Limits
pitchCommandLimit = 15*pi/180;
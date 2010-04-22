%% Control Surface Limits
deLimit = single(15*pi/180);
daLimit = single(45*pi/180);
dtLimit = single(1);
drLimit = single(10*pi/180);

%% Integrator Limits
uHoldLimit = single(0.85*dtLimit);          % Controls throttle
heightErrorLimit = single(0.9*20*pi/180);   % this loop generates theta_command
pitchErrorLimit = single(0.9*deLimit);      % controls elevator
yawDamperLimit = single(0.9*drLimit);       % controls rudder
rollControlLimit = single(0.95*daLimit);    % controls aileron

%% Command Limits
pitchCommandLimit = single(30*pi/180);
bankCommandLimit = single(45*pi/180);

%% ?
r_lim=200*pi/180;
 
%% Set up the values for the HIL Simulation
HIL_K = 3;


%% Run the standard setup files
run ../InnerOuterLoop/Rascal_Var.m
run ../InnerOuterLoop/innerOuterInit.m
run ../InnerOuterLoop/failuresInit.m

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

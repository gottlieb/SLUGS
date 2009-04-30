%% Set up the values for the HIL Simulation
HIL_K = 3;


%% Run the standard setup files
run ../InnerOuterLoop/Rascal_Var.m
run ../InnerOuterLoop/innerOuterInit.m
run ../InnerOuterLoop/failuresInit.m

%% Set up the reverse lookup values for PWM to radians
% Rudder
P =  polyfit([rudMin rudMax],[-calVal calVal],1);
mPWMdr = P(1);
bPWMdr = P(2);

% Aileron
P =  polyfit([ailMin ailMax],[-calVal calVal],1);
mPWMda = P(1);
bPWMda = P(2);

% Elevator
P =  polyfit([eleMin eleMax],[-calVal calVal],1);
mPWMde = P(1);
bPWMde = P(2);

% Throttle
P =  polyfit([thrMin thrMax],[0 1],1);
mPWMdt = P(1);
bPWMdt = P(2);

%% Override RascalVar values
Pos_0   = [200; 350; 350]';     % Initial position vector (m)
Euler_0 = [0; 0; 0*pi/180]';     % Initial Euler angles    (rad)

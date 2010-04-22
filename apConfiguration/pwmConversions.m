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
pwm = [3176 4450];
P =  polyfit(rad, pwm, 1);
mdt = P(1);
bdt = P(2);
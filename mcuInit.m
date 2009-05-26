%% General values
% Global Sample Time
T = 0.01;

%% Gains and Biases

% Straight Gains
% ==============
cubeGyroGain = .07326*pi/180;
cubeAccelGain = (2.522e-3)*9.815;

BaroGpsHDif = 20.0;

% Temp Coefficients
% =================
baroTempK = 0;
baroMeanTemp = 0;

magTempK = 0;
magMeanTemp = 0;


% Scale/Offset sets
% =================
baroScale  = 1;
baroOffset = 0;

magScale  = 0.3418;
magOffset = 0;

pitotScale  = 1;
pitotOffset = 0;

tempScale  = 1;
tempOffset = 0;

powerScale  = 1;
powerOffset = 0;

% Baro Altitude Computation
% =========================
basePressure = 98192.64;
baseTemp = 288.215;
lapseRate = -0.00198122;
baseH = 225;




%% Run the HIL init
run ./HILSim/hilInit.m

%% Curve fitting for IC from Pilot Console. 
% Conversion from IC output to Radians

% Calibration value in radians
calVal = 25*pi/180;

% Rudder
rudMin = 4550;
rudMax = 3300;
P =  polyfit([-calVal calVal],[rudMin rudMax],1);
mICdr = P(1);
bICdr = P(2);

% Aileron
ailMin = 4550;
ailMax = 3300;
P =  polyfit([-calVal calVal],[ailMin ailMax],1);
mICda = P(1);
bICda = P(2);

% Elevator
eleMin = 4550;
eleMax = 3300;
P =  polyfit([-calVal calVal],[eleMin eleMax],1);
mICde = P(1);
bICde = P(2);


%Throttle
thrMin = 4550;
thrMax = 3300;
P =  polyfit([0 1],[thrMin thrMax],1);
mICdt = P(1);
bICdt = P(2);

%% Constants for IC to PWM conversion. 
% This values to the following conversion IC -> rad -> PWM
% This was obtained as follows:
%    pwm(RAD) = m * RAD + b 
%    rad(IC) = m_ic * IC + b_ic
%  =>
%    pwm(IC) = m(m_ic * IC + b_ic) + b
%    pwm(IC) = m*m_ic * IC + m*b_ic + b
%  

% Rudder
mICPWMdr = mdr*mICdr;
bICPWMdr = mdr*bICdr + bdr;

% Aileron
mICPWMda = mda*mICda;
bICPWMda = mda*bICda + bda;

% Elevator
mICPWMde = mde*mICde;
bICPWMde = mde*bICde + bde;


%Throttle
mICPWMdt = mdt*mICdt;
bICPWMdt = mdt*bICdt + bdt;


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
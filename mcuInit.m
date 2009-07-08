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

pitotScale  = 0.9258;
pitotOffset = -830.6641;

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




%% Run the HIL init
run ./HILSim/hilInit.m

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

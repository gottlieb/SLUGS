%clc;
%clear;
T=0.01;
r_lim=7;
%  Initial Conditions in ENU (all vector data is represented as a column vectors)
Pos_0   = [0; 0; 1000]';       % Initial position vector (m)
%Vel_0    = [25.; 0; 0]';        % Initial velocity vector (m/s)
Euler_0 = [0; 0; 45]'*pi/180;          % Initial Euler angles    (rad)
%Omega_0   = [0; 0; 0]';                 % Initial Omega           (rad/s)
PQR_0   = [0; 0; 0]';                 % Initial Omega           (rad/s)
Vb_0   = [35; 0; 0]';                 % Initial body-velocity vector (m/s)

% Mass and Geometric Parameters recomputation
S     = 0.897417;    % surface area of wing  (m2)
span  = 2.3368;      % wingspan              (m)
chord = S/span;      % chord                 (m)
mass =  22.5;          % gross weight          (kg)
% Engine Constants
MinThK    = 0.075;%Mariano=0.3892;MinRPM=2000
ThK       = 2.18;% Mariano=0.3664; MaxRPM=7200
TFact     = 0.4;

Ixx   = 3.689084;    % main moment of inertia around axis Ox (kg*sq.m)
%Ixx   = 7;    % main moment of inertia around axis Ox (kg*sq.m)
Iyy   = 7.43789;    % main moment of inertia around axis Oy (kg*sq.m)
Izz   = 10.22202;    % main moment of inertia around axis Oz (kg*sq.m)

% Aerodynamic Derivatives (all per radian)
CL0     = 0.1857;       % lift coefficient at a = 0 = 0.0003;
CLa     = 4.6206;       % lift curve slope
CLa_dot = 1.93;         % lift due to angle of attack rate
CLq     = 8.7465;       % lift due to pitch rate
CLDe    = 0.4032;       % lift due to elevator
CD0     = 0.0219;       % drag coefficient at a = 0
Apolar  = 0.0899;       % drag curve slope (A2)
A1      = 0;   
CYb     = -0.1999;      % side force due to sideslip
CYDr    = 0.0192;     	% sideforce due to rudder
Clb     = -0.0043;      % dihedral effect =-0.0132
Clp     = -0.4425;      % roll damping
Clr     = 0.0675;       % roll due to yaw rate
ClDa    = 0.1695;       % roll control power
ClDr    = 0.0003;       % roll due to rudder
Cm0     = -0.0902;      % pitch moment at a = 0 =>0.0652
Cma     = -1.3995;      % pitch moment due to angle of attack
Cma_dot = -5.29;        % pitch moment due to angle of attack rate
Cmq     = -10.8760;     % pitch moment due to pitch rate
CmDe    = -0.9493;      %  pitch control power
Cnb     = 0.0281;       % weathercock stability = 0.075
Cnp     = -0.0695;      % adverse yaw
Cnr     = -0.1045;      % yaw damping
CnDa    = -0.0031;      % aileron adverse yaw
CnDr    = -0.0882;      % yaw control power
CLDf    = 0.047;        % 
CmDf    = -.021;
% Standartd Atmosphere
ISA_lapse = .0065;          % Lapse rate            (degC/m) 
ISA_hmax  = 2000;           % Altitude limit        (m)
ISA_R     = 287;            % Gas Constant          (degK*m*m/s/s)
ISA_g     = 9.815;          % Gravity               (m/s/s)
ISA_rho0  = 1.225;          % Density at sea level  (kg/m/m/m)
ISA_P0    = 101325;         % Sea-level Pressure    (N/m/m)
ISA_T0    = 289;            % Sea-level Temperature (degK)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Load Wind Profile: YPG capture
%  Optional, if necessary delete correponding block in mdl file
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
load YPGwind.mat;



% Actuators
deg2rad=pi/180;
damin=-25*deg2rad;
damax=25*deg2rad;
demin=-15*deg2rad;
demax=15*deg2rad;
drmin=-25*deg2rad;
drmax=25*deg2rad;
dtmin=0;
dtmax=1;
dfmin=0*deg2rad;
dfmax=30*deg2rad;

% trim
datrim=0*deg2rad;
detrim=-2.4137*deg2rad;
drtrim=0*deg2rad;
dttrim=0.0725;

% landing
dfland=30*deg2rad;



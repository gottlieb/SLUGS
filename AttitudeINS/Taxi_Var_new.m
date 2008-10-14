%% Sig RASCAL 110 data
clc;
T=0.01;
r_lim=7;

% Standartd Atmosphere
   ISA_lapse = .0065;          % Lapse rate            (degC/m)
   ISA_hmax  = 2000;           % Altitude limit        (m)
   ISA_R     = 287;            % Gas Constant          (degK*m*m/s/s)
   ISA_g     = 9.815;          % Gravity               (m/s/s)
   ISA_rho0  = 1.225;          % Density at sea level  (kg/m/m/m)
   ISA_P0    = 101325;         % Sea-level Pressure    (N/m/m)
   ISA_T0    = 289;            % Sea-level Temperature (degK)

% Set the initial conditions based on the Piccolo Doublets File
%  Initial Conditions in ENU (all vector data is represented as a column
%  vectors)
Pos_0   = [0 0 500]';     % Initial position vector (m)
Euler_0 = [0 0 45]'*pi/180;     % Initial Euler angles    (rad)
%Omega_0 = [0; 0; 0]';                              % Initial Omega           (rad/s)
PQR_0   = [ 0 0 0]'*pi/180;      % Initial Omega           (rad/s)
Vb_0    = [35 0 0]';                     % Initial body-velocity vector (m/s)

% Mass and Geometric Parameters recomputation
S     = 0.982;       % surface area of wing  (m2)
span  = 2.795;       % wingspan              (m)
chord = S/span;      % chord                 (m)
mass =  0.45359237*18;        % gross weight          (kg)



Ixx   = 3.8;    % main moment of inertia around axis Ox (kg*sq.m)
Iyy   = 9.58;%5.43789;    % main moment of inertia around axis Oy (kg*sq.m)
Izz   = 9.68;    % main moment of inertia around axis Oz (kg*sq.m)

% Aerodynamic Derivatives (all per radian)
CL0     = 0.38;      % lift coefficient at a = 0 = 0.0003;
CLa     = 18.5;       % lift curve slope
CLa_dot = 2.64;       % lift due to angle of attack rate
CLq     = 7.4;       % lift due to pitch rate
CLDe    = 0.24;       % lift due to elevator
CLDf    = 0.4;       % delta lift due to flaps

CD0     = 0.022;     % drag coefficient at a = 0
Apolar  = 0.057;       % drag curve slope (A2)
A1      = 0.007;

CYb     = -0.98;      % side force due to sideslip
CYDr    = 0.066;        % sideforce due to rudder

Clb     = -0.06;      % roll moment due to beta::dihedral effect =-0.0132
Clp     = -0.88;      % roll damping
Clr     = 0.04;      % roll due to yaw rate
ClDa    = 0.1695;    % roll due to aileron::control power
ClDr    = 0.055;      % roll due to rudder

Cm0     = 0.56;%-0.05;      % pitch moment at a = 0
Cma     = -1.58;%-0.5;       % pitch moment due to angle of attack
Cma_dot = -7.00;      % pitch moment due to angle of attack rate    {Not included in model}
Cmq     = -12;        % pitch moment due to pitch rate              {Not included in model}
CmDe    = -41;        %  pitch control power

Cnb     = 0.73;%0.12;       % weathercock stability = 0.075
Cnp     = -0.1;    % adverse yaw
Cnr     = -0.23;      % yaw damping
CnDa    = -0.032;      % aileron adverse yaw
CnDr    = 0.19;       % yaw control power

CmDf    = -.021;

% Engine Constants
MinThK    = 0.077;%Mariano=0.3892;MinRPM=2000
ThK       = 2.17;% Mariano=0.3664; MaxRPM=7200
TFact     = 0.4;%1.0;
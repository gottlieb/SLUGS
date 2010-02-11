%% Sig RASCAL 110 data
clc;
SampleT=0.005;
r_lim=200*pi/180;

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
Pos_0   = [50; 200 ;230]';     % Initial position vector (m)
Euler_0 = [0; 0; 270*pi/180]';     % Initial Euler angles    (rad)
Omega_0 = [0; 0; 0]';                              % Initial Omega           (rad/s)
PQR_0   = [0;0;0]';      % Initial Omega           (rad/s)
Vb_0    = [ 15; 0;0]';                     % Initial body-velocity vector (m/s)

% Mass and Geometric Parameters recomputation
S     = 0.982;       % surface area of wing  (m2)
span  = 2.795;       % wingspan              (m)
chord = S/span;      % chord                 (m)
elarm  =  1.21;      % elevator arm vr CG    (m)
mass =  0.45359237*18;        % gross weight          (kg)


 Ixx   = 4.12;    % main moment of inertia around axis Ox (kg*sq.m)
 Iyy   = 9.58;%5.43789;    % main moment of inertia around axis Oy (kg*sq.m)
 Izz   = 9.85;    % main moment of inertia around axis Oz (kg*sq.m)

 % Aerodynamic Derivatives (all per radian)
 CL0     = 0.38;      % lift coefficient at a = 0 = 0.0003;
 CLa     = 18.5;       % lift curve slope
 CLa_dot = 2.64;       % lift due to angle of attack rate
 CLq     = 7.4;       % lift due to pitch rate
 CLDe    = 0.24;       % lift due to elevator
 CLDf    = 0.4;       % delta lift due to flaps

 CD0     = 0.022;     % drag coefficient at a = 0
 A1      = 0.007;
 Apolar  = 0.057;       % drag curve slope (A2)

 CYb     = -1.098;      % side force due to sideslip
 CYDr    = 0.143;        % sideforce due to rudder

 Clb     = -0.296;      % roll moment due to beta::dihedral effect =-0.0132
 Clp     = -1.96;      % roll damping
 Clr     = 0.103;      % roll due to yaw rate
 ClDa    = 0.1695;    % roll control power
 ClDr    = 0.106;      % roll due to rudder

Cm0     = 0.3;%-0.05;      % pitch moment at a = 0
Cma     = -1.239;%-0.5;       % pitch moment due to angle of attack
Cma_dot = -7.00;      % pitch moment due to angle of attack rate    {Not included in model}
Cmq     = -2.4;        % pitch moment due to pitch rate             
CmDe    = -3.2;        %  pitch control power

 Cnb     = 0.277;%0.12;       % weathercock stability = 0.075
 Cnp     = -0.0889;    % adverse yaw
 Cnr     = -0.19997;      % yaw damping
 CnDa    = -0.023;      % aileron adverse yaw
% Piccolo user Guide:>The sign convention on the surface deflection has the following rules:
% flaps, ailerons, and elevators are all positive down. Rudders are positive right. 
% For ruddervators the sign convention follows the elevator rule, i.e. positive down.
 CnDr    = -0.1997;       % yaw control power (Sign convention : Positive for TER rudder deflection and Negative for TEL rudder deflection)

 CmDf    = -.021;

 % Engine Constants
 MinThK    = 0.077;
 ThK       = 2.17;
 TFact     = 0.4;%1.0;
 
% Wind Configuration
windBase = 3.5;
windDirTurb = 180;
windDirHor = 180;

% Baro Altitude Computation
% =========================
baseHeight = 180;
baseTemp = 288.215;
lapseRate = -0.00198122;

% GS Location. East field location
GS_location = [0 36.9898376464844 -122.051963806152];

%  Initial Conditions in ENU (all vector data is represented as a column
%  vectors) for the quaternion
Euler_quat = [0; 0;  0]';     % Initial Euler angles    (rad)

% initial quaternion
cph = cos(Euler_quat(1)/2); sph = sin(Euler_quat(1)/2);
cth = cos(Euler_quat(2)/2); sth = sin(Euler_quat(2)/2);
cps = cos(Euler_quat(3)/2); sps = sin(Euler_quat(3)/2);
q_quat(1) = cph*cth*cps + sph*sth*sps;
q_quat(2) = sph*cth*cps - cph*sth*sps;
q_quat(3) = cph*sth*cps + sph*cth*sps;
q_quat(4) = cph*cth*sps - sph*sth*cps;
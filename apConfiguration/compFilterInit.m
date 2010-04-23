%%  Complementary Filters

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

% Position Comp Filters
xCutoff = 10;
yCutoff = 10;
zCutoff = 0.2;
baroCutoff = 0.38/(2*pi);

%Velocity Comp filters
vzCutoff = 2;

% Accelerometer bias rate limiter
accBiasRateLimit = 2*(.014844)/300*apSampleTime;

% Gyro bias rate limiter
gyroBiasRateLimit = 2*(.006393)/500*apSampleTime;

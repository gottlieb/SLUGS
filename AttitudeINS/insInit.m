Qk = diag([0.1 0.1 0.1 0.1 0.1 0.1 0.1]);
Rk = diag([3 3 5]);

%X0 = [quatnormalize(euler2quat(Euler_0)) 0.001 0.001 0.001];
q0 = quatnormalize(euler2quat(Euler_0));
b0 =  [0.01 0.01 0.01];

P0 = diag([.3 .3 .3  0.75 0.75 0.75 ]);

latUp = 100000;
latDown = -100000;

lonUp = 100000;
lonDown = -100000;

heightUp = 3000;
heightDown = 0;

Gw = zeros(6,6);
Gw(1:3,1:3) = -0.5*eye(3);	% Process Noise input
Gw(4:6,4:6) = eye(3);		% Process Noise input

Rwpsd = zeros(6,6);
rwt = 1;					% for sensor noise
rwb = 0.1;					% tune filter, 0.01 for slower response
rvv = 0.25;					% attitude noise, tune for filter response

Rw(1:3,1:3) = rwt^2*eye(3);	% Covariance of process noise
Rw(4:6,4:6) = rwb^2*eye(3);	% Covariance of process noise

Rv = rvv^2*eye(3);

H = [eye(3,3) zeros(3,3)];
Qk = diag([0.01 0.01 0.01 0.01 0.1 0.1 0.1]);
Rk = diag([0.01 0.01 0.01]);

X0 = [quatnormalize(euler2quat(Euler_0)) 0.001 0.001 0.001];
P0 = diag([.3 .3 .3 .3  0.75 0.75 0.75 ]);

latUp = 10000;
latDown = -10000;

lonUp = 10000;
lonDown = -10000;

heightUp = 3000;
heightDown = 0;
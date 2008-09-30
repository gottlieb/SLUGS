Qk = diag([0.1 0.1 0.1 0.1 0.1 0.1 0.1]);
Rk = diag([3 3 5]);

X0 = [quatnormalize(euler2quat(Euler_0)) 0.001 0.001 0.001];
P0 = diag([.3 .3 .3 .3  0.75 0.75 0.75 ]);

latUp = 100000;
latDown = -100000;

lonUp = 100000;
lonDown = -100000;

heightUp = 3000;
heightDown = 0;
% imports spin data, computes correction parameters and corrects data
%  showing plots of all stages

% import data
spin = importVPS('spin.dat');

% plot all data
figure(1);
clf;
title('All Data');
plot(spin.data);

% calculate correction paraters for accelerometers
accelParam = extractParameters2D(spin.raw.accel.X(60000:73000), spin.raw.accel.Y(60000:73000),1);

% plot accelerometers X vs. Y
figure(2);
plot(spin.raw.accel.X, spin.raw.accel.Y, 'k.');

% overlay calculated ellipse
hold on;
plotMisalignment2D(accelParam,'m-');
title('Accelerometer Data');
legend('Origional Data', 'Estimation Ellipse');
axis equal;
hold off;

% correct accelerometer data
[spin.correct.accel.X, spin.correct.accel.Y] = correctSensors2D(spin.raw.accel.X, spin.raw.accel.Y,accelParam);

% plot corrected accelerometer data
figure(3);
clf;
plot(spin.correct.accel.X, spin.correct.accel.Y, 'k.');

% overlay sircle of radius 1
sp.a = 1; sp.b = 1; sp.xo = 0; sp.yo = 0; sp.phi = 0;
hold on;
plotMisalignment2D(sp, 'y-');
title('Corrected Accelerometer Data');
legend('Corrected Data', 'Circle w/ R=1');
zoom(.9);
axis equal;




% calculate correction paraters for magnetometers
magParam = extractParameters3D(spin.raw.mag.X, spin.raw.mag.Y, spin.raw.mag.Z, 1);

% plot magnotometers X vs. Y vs. Z
figure(4);
plot3(spin.raw.mag.X, spin.raw.mag.Y, spin.raw.mag.Z, 'k.');
axis equal;

% overlay calculated ellipse
hold on;
plotMisalignment3D(magParam, 'm.');
title('Magnetometer Data');
legend('Origional Data', 'Estimation Ellipsoid');

axis equal;
zoom(.9);
hold off;

% correct magnetometer data
[spin.correct.mag.X, spin.correct.mag.Y, spin.correct.mag.Z] = correctSensors3D(spin.raw.mag.X, spin.raw.mag.Y, spin.raw.mag.Z, magParam);

% plot corrected accelerometer data
figure(5);
clf;
plot3(spin.correct.mag.X, spin.correct.mag.Y, spin.correct.mag.Z, 'k.');

% overlay sphere of radius 1
sp.a = 1; sp.b = 1; sp.c = 1; sp.xo = 0; sp.yo = 0; sp.zo = 0; sp.phi = 0; sp.row = 0; sp.lambda = 0;
hold on;
plotMisalignment3D(sp, 'y.');
title('Corrected Magnetometer Data');
legend('Corrected Data', 'Sphere w/ R=1');
zoom(.9);
axis equal;


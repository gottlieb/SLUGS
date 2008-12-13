%==============================================
% m-file to simulate two-step mag calibration
% looking at mis-alignment issues.
%==============================================

set(0,'DefaultAxesFontName','Gill Sans MT');
set(0,'DefaultAxesFontSize',10);
set(0,'DefaultTextFontName','Gill Sans MT');
set(0,'DefaultTextFontSize',10);
clc;

% Parameters
Th = [0:0.001:2*pi]';
xo = 2;
yo = -1;
a = 1.5;
b = 0.75;
R = 1;
phi = 35;
x_noise = 0.03;
y_noise = 0.01;

figure(1);
clf;
hold on;
title('Simulation of Two-Step Non-Linear Estimator Compinsating for Sensor Misalignment');

% Generate circle
x = R*cos(Th);
y = R*sin(Th);
plot(x,y,'b-');

% Sensor misalignment
x = x;
y = cos(deg2rad(phi))*y + sin(deg2rad(phi))*x;
plot(x,y,'g-');

% Sensor scaling
x = x*a;
y = y*b;
plot(x,y,'r-');

% Sensor offset
x = x + xo;
y = y + yo;
plot(x,y,'m-');

% Add noise
xsamp = x + x_noise*randn(size(x));
ysamp = y + y_noise*randn(size(y));

% Reduce Samples
beg = floor(sort(rand(2,1)*length(xsamp)));
xsamp = xsamp(beg(1):beg(2));
ysamp = ysamp(beg(1):beg(2));
plot(xsamp,ysamp,'c.');

% Calculate parameters
param = extractParameters2D( xsamp, ysamp, R);
plotMisalignment2D(param, 'k-');

% Reconstruct Truth
[X,Y] =  correctSensors2D (xsamp, ysamp, param);
plot(X,Y,'y.');

legend('Truth', 'Misaligned', 'Scaled', 'Shifted', 'Noisy', 'Calculated', 'Reconstructed');
axis equal;
hold off;

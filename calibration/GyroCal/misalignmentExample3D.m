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
zo = -2.5;
a = 2;
b = 1;
c = .5;
R = 1;
phi = 15;
row = 10;
lambda = 5;
x_noise = .01;
y_noise = .02;
z_noise = .015;

m = 1;
clear x y z;

% Generate circle
for a = -R:R/25:R;
    for b = -R:R/25:R;
        if (a^2+b^2 < R^2)
            x(m) = a;
            y(m) = b;
            m = m+1;
        end;
    end;

    x(m) = a;
    y(m) = sqrt(R^2 - a^2);
    x(m+1) = a;
    y(m+1) = -sqrt(R^2 - a^2);
    m = m+2;

end;

z = sqrt(R^2 - x.^2 - y.^2);

x = [x,x];
y = [y,y];
z = [z,-z];

figure(1);
plot3(x,y,z,'b.');
title('Simulation of Two-Step Non-Linear Estimator Compinsating for Sensor Misalignment');
hold on;

% Sensor misalignment
z = z*cos(deg2rad(row))*cos(deg2rad(lambda)) + x*sin(deg2rad(row))*cos(deg2rad(lambda)) + y*sin(deg2rad(lambda));
y = cos(deg2rad(phi))*y + sin(deg2rad(phi))*x;
x = x;

plot3(x,y,z,'g.');

% Sensor scaling
x = x*a;
y = y*b;
z = z*c;
plot3(x,y,z,'r.');

% Sensor offset
x = x + xo;
y = y + yo;
z = z + zo;
plot3(x,y,z,'m.');

% Add noise
xsamp = x + x_noise*randn(size(x));
ysamp = y + y_noise*randn(size(y));
zsamp = z + z_noise*randn(size(z));

% Reduce Samples
beg = floor(sort(rand(2,1)*length(xsamp)));
xsamp = xsamp(beg(1):beg(2));
ysamp = ysamp(beg(1):beg(2));
zsamp = zsamp(beg(1):beg(2));
plot3(xsamp,ysamp,zsamp,'c.');

%% Calculate parameters
param = extractParameters3D( xsamp, ysamp, zsamp, R);
plotMisalignment3D(param, 'y.');

% Reconstruct Truth
[X,Y,Z] =  correctSensors3D (xsamp, ysamp, zsamp, param);
plot3(X,Y,Z,'k.');

legend('Truth', 'Misaligned', 'Scaled', 'Shifted', 'Noisy', 'Calculated', 'Reconstructed');
axis equal;
hold off;

%function plotMisalignment2D(param, lineType);
function plotMisalignment2D(param, lineType);

    Th = [0:0.001:2*pi]';

    % Generate circle
    x = cos(Th);
    y = sin(Th);

    % Apply misalignment
    y = cos(deg2rad(param.phi))*y + sin(deg2rad(param.phi))*x;

    % Sensor scaling and offset
    x = x*param.a + param.xo;
    y = y*param.b + param.yo;

    plot(x,y,lineType);
    
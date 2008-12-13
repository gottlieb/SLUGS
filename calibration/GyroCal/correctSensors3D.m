function [x, y, z] = correctSensors3D (x, y, z, param)
    x = (x - param.xo) ./ param.a;

    y = (((y - param.yo) ./ param.b) - x.*sin(deg2rad(param.phi))) ./ cos(deg2rad(param.phi));

    z = (((z - param.zo) ./ param.c) - x.*sin(deg2rad(param.row)).*cos(deg2rad(param.lambda)) - y.*sin(deg2rad(param.lambda))) ./ (cos(deg2rad(param.row))*cos(deg2rad(param.lambda)));

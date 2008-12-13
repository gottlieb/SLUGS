function [x, y] = correctSensors2D (x, y, param)
   
    x = (x - param.xo) ./ param.a;
   
    y = (((y - param.yo) ./ param.b) - x.*sin(deg2rad(param.phi))) ./ cos(deg2rad(param.phi));
    
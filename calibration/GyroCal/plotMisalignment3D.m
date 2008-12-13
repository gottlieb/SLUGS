%function plotMisalignment3D(param, lineType);
function plotMisalignment3D(param, lineType);

    m = 1;

    % Generate circle
    for p = -1:.04:1;
        for q = -1:.04:1;
            if (p^2+q^2 < 1)
                x(m) = p;
                y(m) = q;
                m = m+1;
            end;
        end;

        x(m) = p;
        y(m) = sqrt(1 - p^2);
        x(m+1) = p;
        y(m+1) = -sqrt(1 - p^2);
        m = m+2;

    end;

    z = sqrt(1 - x.^2 - y.^2);

    x = [x,x];
    y = [y,y];
    z = [z,-z];
    

    % Sensor misalignment
    z = z*cos(deg2rad(param.row))*cos(deg2rad(param.lambda)) + x*sin(deg2rad(param.row))*cos(deg2rad(param.lambda)) + y*sin(deg2rad(param.lambda));
    y = cos(deg2rad(param.phi))*y + sin(deg2rad(param.phi))*x;
    x = x;

    % Sensor scaling
    x = x*param.a;
    y = y*param.b;
    z = z*param.c;

    % Sensor offset
    x = x + param.xo;
    y = y + param.yo;
    z = z + param.zo;

    plot3(x,y,z,lineType);

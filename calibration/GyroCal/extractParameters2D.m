function param = extractParameters2D (X, Y, R)

    sol = [X.^2, X.*Y, X, Y, ones(length(X),1)] \ Y.^2;

    param.phi = rad2deg(asin(sol(2)/(2*sqrt(-1*sol(1)))));
    param.xo = (-1*sol(3)-(sol(2)*sol(4)/2))/(2*sol(1)+sol(2)^2/2);
    param.yo = (sol(4)+param.xo*sol(2))/2;
    param.b = sqrt((sol(5)-param.xo*param.yo*sol(2)-param.xo^2*sol(1)+param.yo^2)/(R^2*(cos(deg2rad(param.phi)))^2));
    param.a = sqrt(-1*param.b^2/sol(1));

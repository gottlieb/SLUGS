%% Set up the values for the HIL Simulation

% Do not change this variable unless you understand what you are doing.
% This sets the sampling ratio for UDP send/receive data.

HIL_K = 3;


%% Run the standard setup files
run ..\apConfiguration\Rascal_Var.m

% ===== Replace this one with your location file ====
run ..\apConfiguration\gsLocation.m
% ===================================================

run ..\apConfiguration\failuresInit.m
run ..\apConfiguration\limits.m
run ..\apConfiguration\pwmConversions.m
run ..\apConfiguration\baroInit.m

%% Override RascalVar values
Pos_0   = [200; 350; 350]';     % Initial position vector (m)
Euler_0 = [0; 0; 0*pi/180]';     % Initial Euler angles    (rad)

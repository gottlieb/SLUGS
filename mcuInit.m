%% General values
% Global Sample Time
T = 0.01;
apSampleTime = 0.01;

derivativesConstant = 5;

%% Run the configuration files
run .\apConfiguration\Rascal_Var.m

% ===== Replace this one with your location file ====
run .\apConfiguration\gsLocation.m
% ===================================================

run .\apConfiguration\limits.m
run .\apConfiguration\pwmConversions.m
run .\apConfiguration\baroInit.m
run .\apConfiguration\sensorInit.m
run .\apConfiguration\compFilterInit.m
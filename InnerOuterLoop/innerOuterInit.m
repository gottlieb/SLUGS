%% General Values
derivativesConstant = 5;

apSampleTime = 0.01;
T = 0.01;
SampleT=0.005;


%% Run the Required Configuration Files for Simulation
run ..\apConfiguration\Rascal_Var.m
run ..\apConfiguration\compFilterInit.m

% ===== Replace this one with your location file ====
run ..\apConfiguration\gsLocation.m
% ===================================================

run ..\apConfiguration\simulationWPFile.m
run ..\apConfiguration\failuresInit.m
run ..\apConfiguration\limits.m
run ..\apConfiguration\pwmConversions.m
run ..\apConfiguration\baroInit.m

%% Nav Values

L2_base = single(4.5);
U_comm = single(15);
R = single((U_comm)^2/(ISA_g*tan(bankCommandLimit)))+20;

%% Wind Configuration
windBase = 3.5;
windDirTurb = 180;
windDirHor = 180;
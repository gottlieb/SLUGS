%% Gains
% Global Sample Time
T = 0.01;
load gainsAndBiases
gxGainrad = gxGain*pi/180;
gyGainrad = gyGain*pi/180;
gzGainrad = gzGain*pi/180;

%% Run the Inner outer loop init
run ./InnerOuterLoop/innerOuterInit.m
run ./InnerOuterLoop/Rascal_Var.m

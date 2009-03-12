%% Determine the plotting values

for cc = 1:40
    sim('InnerOuter_Sim.mdl');
    debugNav;
    close all;
    clc;
    cc
    clear;
    pack;
end


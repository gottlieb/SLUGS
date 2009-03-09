%% Determine the plotting values

for cc = 1:10
    sim('InnerOuter_Sim.mdl');
    debugNav;
    close all;
    cc
    clear
end


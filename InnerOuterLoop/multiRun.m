%% Initialize failure variables
failuresInit;
figct =85;
compensatorOn = 0;

%% No L1 
L1OF = 0;
L1CS = 0;

% No Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 0;
da_failamp = 0;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;


% Aileron Failure
% ======================
daL_fail = 0;
daR_fail = 1;
dr_fail  = 0;
da_failamp = 20;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

% Rudder Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 1;
da_failamp = 10;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;
% 
%% L1 Output Feedback
L1OF = 1;
L1CS = 0;

% No Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 0;
da_failamp = 0;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;


% Aileron Failure
% ======================
daL_fail = 0;
daR_fail = 1;
dr_fail  = 0;
da_failamp = 20;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

% Rudder Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 1;
da_failamp = 10;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

%% L1 Control Surface
L1OF = 0;
L1CS = 1;

% No Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 0;
da_failamp = 0;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;


% Aileron Failure
% ======================
daL_fail = 0;
daR_fail = 1;
dr_fail  = 0;
da_failamp = 20;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

% Rudder Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 1;
da_failamp = 10;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

%% Smaller rudder failure for the three comparsions
L1OF = 0;
L1CS = 0;


% Rudder Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 1;
da_failamp = 5;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

L1OF = 1;
L1CS = 0;


% Rudder Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 1;
da_failamp = 5;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;

L1OF = 0;
L1CS = 1;


% Rudder Failure
% ======================
daL_fail = 0;
daR_fail = 0;
dr_fail  = 1;
da_failamp = 5;

sim('InnerOuter_Sim.mdl');
debugNav;
close all;
clc;
%% Script written to overide the initial conditions of the UAV
% No pausing on plotting
pauseOn = 0;

%% Random Position
x_ic = randn*1000;
y_ic = randn*1000;
z_ic = getRanVal(750,150,1000);

Pos_0 = [x_ic y_ic z_ic];

%% Random Heading
psi_ic = getRanVal(2*pi,0,2*pi);
Euler_0 = [0; 0; psi_ic]';     

%% Random Commanded Airspeed
U_comm = getRanVal(35,18,40);
%% Random WPs

% determine randomly the number of waypoints to use
wpCount = floor(getRanVal(7,4,10));

% create the array to hold the values
wps = zeros(wpCount,3);

% generate the next waypoint
x_wp = randn*5000;
y_wp = randn*5000;
z_wp = getRanVal(750,550,1000);

% add it to the array
wps(1,:) = [x_wp, y_wp, z_wp];

for ii=2:wpCount
    reiterate = 1;    
    while reiterate == 1
        % generate the next waypoint
        x_wp = randn*5000;
        y_wp = randn*5000;
        z_wp = getRanVal(750,550,1000);

        reiterate = 0;
        % check the separation between all WPs
        for mm = 1:(ii-1)
           if (norm(wps(mm,1:2)-wps(mm+1,1:2)) < 500)
               reiterate = 1;
           end
        end
    end

    wps(ii,:) = [x_wp, y_wp, z_wp];
end


% assemble the variables for Simulink
Xpoints = wps(:,1);
Ypoints = wps(:,2);
Zpoints = wps(:,3);

%% Random Wind
windBase = getRanVal(12,4,15);
windDirTurb = getRanVal(360,0,360);
windDirHor = getRanVal(360,0,360);


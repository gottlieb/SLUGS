load completeDataSet

sw_calibrateGyro = 0;

if ~(sw_calibrateGyro)
    load gainsAndBiases
end
%% Temperature Compensation for Main Sensors
fig_ct = 1;

figure(fig_ct);
    plot(t_Ti(500:end),t_Te(500:end));
    title('Temperature Run');
    xlabel('Time (s)');
    ylabel('Count (12bits)');
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

% Temperature Dependence for each sensor
figure(fig_ct);

subplot(3,3,1)
    plot(t_Te(500:end),t_Gx(500:end));
    title('Gyro X');
    temp =  polyfit(t_Te(500:end),t_Gx(500:end),1);
    gxTGain = temp(1);
    legend(num2str(gxTGain));
    ylabel('Gyro counts');
subplot(3,3,2)
    plot(t_Te(500:end),t_Gy(500:end));
    title('Gyro Y');
    temp =  polyfit(t_Te(500:end),t_Gy(500:end),1);
    gyTGain = temp(1);
    legend(num2str(gyTGain));
 subplot(3,3,3)
    plot(t_Te(500:end),t_Gz(500:end));
    title('Gyro Z');
    temp =  polyfit(t_Te(500:end),t_Gz(500:end),1);
    gzTGain = temp(1);
    legend(num2str(gzTGain));
   
subplot(3,3,4)
    plot(t_Te(500:end),t_Ax(500:end));
    title('Accel X');
    temp =  polyfit(t_Te(500:end),t_Ax(500:end),1);
    axTGain = temp(1);
    legend(num2str(axTGain));
    ylabel('Accel counts');
subplot(3,3,5)
    plot(t_Te(500:end),t_Ay(500:end));
    title('Accel Y');
    temp =  polyfit(t_Te(500:end),t_Ay(500:end),1);
    ayTGain = temp(1);
    legend(num2str(ayTGain));
 subplot(3,3,6)
    plot(t_Te(500:end),t_Az(500:end));
    title('Accel Z');
    temp =  polyfit(t_Te(500:end),t_Az(500:end),1);
    azTGain = temp(1);
    legend(num2str(azTGain));

subplot(3,3,7)
    plot(t_Te(500:end),t_Mx(500:end));
    title('Mag X');
    temp =  polyfit(t_Te(500:end),t_Mx(500:end),1);
    mxTGain = temp(1);
    legend(num2str(mxTGain));
    ylabel('Magn counts');
    xlabel ('Temp counts');
subplot(3,3,8)
    plot(t_Te(500:end),t_My(500:end));
    title('Mag Y');
    temp =  polyfit(t_Te(500:end),t_My(500:end),1);
    myTGain = temp(1);
    legend(num2str(myTGain));
    xlabel ('Temp counts');
 subplot(3,3,9)
    plot(t_Te(500:end),t_Mz(500:end));
    title('Mag Z');
    temp =  polyfit(t_Te(500:end),t_Mz(500:end),1);
    mzTGain = temp(1);
    legend(num2str(mzTGain));
    xlabel ('Temp counts');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

%% Temperature Compensation for Air Data
figure(fig_ct);

subplot(3,1,1)
    plot(t_Te(500:end),t_St(500:end));
    title('Static Pressure vs. Temp');
    temp =  polyfit(t_Te(500:end),t_St(500:end),1);
    stTGain = temp(1);
    legend(num2str(stTGain));
    xlabel ('Temp counts');
    ylabel ('Static Pressure (Pa)');

subplot(3,1,2)
    plot(t_Te(500:end),t_Dy(500:end));
    title('Dynamic Pressure vs. Temp');
    temp =  polyfit(t_Te(500:end),t_Dy(500:end),1);
    dyTGain = temp(1);
    legend(num2str(dyTGain));
    xlabel ('Temp counts');
    ylabel ('Dynamic Pressure (raw)');
    
subplot(3,1,3)
    plot(t_Te(500:end),t_Vl(500:end));
    title('Voltage vs. Temp');
    temp =  polyfit(t_Te(500:end),t_Vl(500:end),1);
    vlTGain = temp(1);
    legend(num2str(vlTGain));
    xlabel ('Temp counts');
    ylabel ('Voltage (raw)');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

%% Plot the Temperature Compensated Air Data
figure(fig_ct);

subplot(3,1,1)
    [t_St_comp, temp, tmeanSt] =  cTemp(t_St, t_Te, stTGain, 0, 0, 0);
    plot(t_Ti(500:end),t_St(500:end), 'b');
    hold on
    plot(t_Ti(500:end),t_St_comp(500:end), 'r');
    title ('Temperature Compensated Static Pressure')
    hold off
    ylabel ('Static (Pa)');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,2)
    [t_Dy_comp, temp, tmeanDy] =  cTemp(t_Dy, t_Te, dyTGain, 0,0,0);
    plot(t_Ti(500:end),t_Dy(500:end), 'b');
    hold on
    plot(t_Ti(500:end),t_Dy_comp(500:end), 'r');
    title ('Temperature Compensated Dynamic Pressure')
    hold off
    ylabel ('Dynamic (Raw)');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,3)
    [t_Vl_comp, temp, tmeanVl] =  cTemp(t_Vl, t_Te, vlTGain, 0,0,0);
    plot(t_Ti(500:end),t_Vl(500:end), 'b');
    hold on
    plot(t_Ti(500:end),t_Vl_comp(500:end), 'r');
    title ('Temperature Compensated Voltage Sensor')
    hold off
    ylabel ('Dynamic (Raw)');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

%% Gyro Calibration
figure(fig_ct);

subplot(3,1,1)
    c_SLU_x_comp =  cTemp(c_SLU_x, c_Tem_x, gxTGain,1,0,0);
    plot(c_Ti_x,c_SLU_x, 'b');
    hold on
    plot(c_Ti_x,c_SLU_x_comp, 'r');
    title ('Temperature Compensated Gyro X')
    hold off
    ylabel ('Gyro counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,2)
    c_SLU_y_comp =  cTemp(c_SLU_y, c_Tem_y, gyTGain,1,0,0);
    plot(c_Ti_y,c_SLU_y, 'b');
    hold on
    plot(c_Ti_y,c_SLU_y_comp, 'r');
    title ('Temperature Compensated Gyro Y')
    hold off
    ylabel ('Gyro counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,3)
    c_SLU_z_comp =  cTemp(c_SLU_z, c_Tem_z, gzTGain,1,0,0);
    plot(c_Ti_z,c_SLU_z, 'b');
    hold on
    plot(c_Ti_z,c_SLU_z_comp, 'r');
    title ('Temperature Compensated Gyro Z')
    hold off
    ylabel ('Gyro counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

%% Compute the Gyro Calibration
if (sw_calibrateGyro)
    % get Gyro Gains from turntable experiment
    figure(fig_ct);
    [gxGain, gxOffset] = getGain(c_KVH_x, c_SLU_x_comp);
    fig_ct= fig_ct+1;    
    eval(['print -depsc  '  num2str(fig_ct)]);

    figure(fig_ct);
    [gyGain, gyOffset] = getGain(c_KVH_y, c_SLU_y_comp);
    fig_ct= fig_ct+1;    
    eval(['print -depsc  '  num2str(fig_ct)]);


    figure(fig_ct);
    [gzGain, gzOffset] = getGain(c_KVH_z, c_SLU_z_comp);
    fig_ct= fig_ct+1;    
    eval(['print -depsc  '  num2str(fig_ct)]);
else
    fig_ct = fig_ct+3;
end
%% Accelerometer Gains from Tumble Experiment

figure(fig_ct);

subplot(3,1,1)
    [tu_Ax_comp, biaTemp, tmeanAx] = cTemp(tu_Ax, tu_Te, axTGain,0,0,0);
    plot(tu_Ti,tu_Ax, 'b');
    hold on
    plot(tu_Ti,tu_Ax_comp, 'r');
    title ('Temperature Compensated Accelerometer X')
    hold off
    ylabel ('Accel counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,2)
    [tu_Ay_comp, biaTemp, tmeanAy] = cTemp(tu_Ay, tu_Te, ayTGain,0,0,0);
    plot(tu_Ti,tu_Ay, 'b');
    hold on
    plot(tu_Ti,tu_Ay_comp, 'r');
    title ('Temperature Compensated Acceleromter Y')
    hold off
    ylabel ('Accel counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');
    
subplot(3,1,3)
    [tu_Az_comp, biaTemp, tmeanAz] = cTemp(tu_Az, tu_Te, azTGain,0,0,0);
    plot(tu_Ti,tu_Az, 'b');
    hold on
    plot(tu_Ti,tu_Az_comp, 'r');
    title ('Temperature Compensated Accel Z')
    hold off
     ylabel ('Accel counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

 AccelParam = extractParameters3D (tu_Ax_comp, tu_Ay_comp, tu_Az_comp, 9.80665);
 
figure(fig_ct);

subplot (1,2,1)
    [X, Y, Z] = correctSensors3D(tu_Ax_comp, tu_Ay_comp, tu_Az_comp, AccelParam);
    plot3(X,Y,Z, '.')
    title ('Corrected Accelerometer Readings');
    xlabel('X Measured (m/s^2)');
    ylabel('Y Measured (m/s^2)');
    zlabel('Z Measured (m/s^2)');
    axis equal
    grid on
    hold on
    [x, y, z] = sphere(30);
    surf(x.*9.81,y.*9.81,z.*9.81);
    
    clear x y z
subplot (1,2,2)
    plot3(tu_Ax_comp, tu_Ay_comp, tu_Az_comp, '.');
    title ('Initial Accelerometer Readings');
    xlabel('X Raw (counts)');
    ylabel('Y Raw (counts)');
    zlabel('Z Raw (counts)');

    axis equal
    grid on

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

%% Magnetometer Gains from Tumble Experiment

figure(fig_ct);

subplot(3,1,1)
    [tu_Mx_comp, biaTemp, tmeanMx] = cTemp(tu_Mx, tu_Te, mxTGain,0,0,0);
    plot(tu_Ti,tu_Mx, 'b');
    hold on
    plot(tu_Ti,tu_Mx_comp, 'r');
    title ('Temperature Compensated Magnetometer X')
    hold off
     ylabel ('Mag counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,2)
    [tu_My_comp, biaTemp, tmeanMy] = cTemp(tu_My, tu_Te, myTGain,0,0,0);
    plot(tu_Ti,tu_My, 'b');
    hold on
    plot(tu_Ti,tu_My_comp, 'r');
    title ('Temperature Compensated Magnetometer Y')
    hold off
    ylabel ('Mag counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

subplot(3,1,3)
    [tu_Mz_comp, biaTemp, tmeanMz] = cTemp(tu_Mz, tu_Te, -mzTGain,0,0,0);
    plot(tu_Ti,tu_Mz, 'b');
    hold on
    plot(tu_Ti,tu_Mz_comp, 'r');
    title ('Temperature Compensated Magnetometer Z')
    hold off
    ylabel ('Mag counts');
    xlabel ('Time (s)');
    legend ('Raw Data','Temp Comp');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

 MagParam = extractParameters3D (tu_Mx_comp, tu_My_comp, tu_Mz_comp, 1);

figure(fig_ct);

subplot (1,2,1)
    [X, Y, Z] = correctSensors3D(tu_Mx_comp, tu_My_comp, tu_Mz_comp, MagParam);
    plot3(X,Y,Z, '.')
    title ('Corrected Magnetometer Readings');
    axis equal
    grid on
    hold on
    [x, y, z] = sphere(30);
    surf(x,y,z);
    xlabel('X Normalized');
    ylabel('Y Normalized)');
    zlabel('Z Normalized');
    
subplot (1,2,2)
    plot3(tu_Mx_comp, tu_My_comp, tu_Mz_comp, '.');
    title ('Initial Magnetometer Readings');
    axis equal
    grid on 
    xlabel('X Raw (counts)');
    ylabel('Y Raw (counts)');
    zlabel('Z Raw (counts)');
 
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear X Y Z

%% Plot the static data, normal and temeprature compensated

clear tu_*
clear c_*
clear t_*


% Gyros
figure(fig_ct)

subplot(2,1,1)
    s_Gx_comp =  cTemp(s_Gx, s_Te, gxTGain,1);
    plot(s_Ti(500:end),s_Gx(500:end), 'b');
    title ('Long Term Gyro X')
    ylabel ('Gyro counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Gx_comp(500:end), 'r');
    title ('Temperature Compensated Gyro X')
    ylabel ('Gyro counts');
    xlabel ('Time (s)');

clear s_Gx_comp s_Gx
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

figure(fig_ct)

subplot(2,1,1)
    s_Gy_comp =  cTemp(s_Gy, s_Te, gyTGain,1);
    plot(s_Ti(500:end),s_Gy(500:end), 'b');
    title ('Long Term Gyro Y')
    ylabel ('Gyro counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Gy_comp(500:end), 'r');
    title ('Temperature Compensated Gyro Y')
    ylabel ('Gyro counts');
    xlabel ('Time (s)');

clear s_Gy_comp s_Gy
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

figure(fig_ct)

subplot(2,1,1)
    s_Gz_comp =  cTemp(s_Gz, s_Te, gzTGain,1);
    plot(s_Ti(500:end),s_Gz(500:end), 'b');
    title ('Long Term Gyro Z')
    ylabel ('Gyro counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Gz_comp(500:end), 'r');
    title ('Temperature Compensated Gyro z')
    ylabel ('Gyro counts');
    xlabel ('Time (s)');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear s_Gz_comp s_Gz

% Accels
figure (fig_ct)

subplot(2,1,1)
    s_Ax_comp = cTemp(s_Ax, s_Te, axTGain,0,1,tmeanAx);
    plot(s_Ti(500:end),s_Ax(500:end), 'b');
    title ('Long Term  Accelerometer X')
    ylabel ('Accel counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Ax_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Accelerometer X')
    hold off
    ylabel ('Accel counts');
    xlabel ('Time (s)');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear s_Ax_comp s_Ax

figure (fig_ct)

subplot(2,1,1)
    s_Ay_comp = cTemp(s_Ay, s_Te, ayTGain,0,1,tmeanAy);
    plot(s_Ti(500:end),s_Ay(500:end), 'b');
    title ('Long Term Acceleromter Y')
    ylabel ('Accel counts');
    xlabel ('Time (s)');
subplot (2,1,2)
    plot(s_Ti(500:end),s_Ay_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Acceleromter Y')
    ylabel ('Accel counts');
    xlabel ('Time (s)');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear s_Ay_comp s_Ay

figure (fig_ct)

subplot(2,1,1)
    s_Az_comp = cTemp(s_Az, s_Te, azTGain,0,1,tmeanAz);
    plot(s_Ti(500:end),s_Az(500:end), 'b');
    title ('Long Term  Accel Z')
    ylabel ('Accel counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti,s_Az_comp, 'r');
    title ('Long Term Temperature Compensated Accel Z')
    ylabel ('Accel counts');
    xlabel ('Time (s)');

fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear s_Az_comp s_Az

% Mags
figure (fig_ct)

subplot(2,1,1)
    s_Mx_comp = cTemp(s_Mx, s_Te, mxTGain,0,1,tmeanMx);
    plot(s_Ti(500:end),s_Mx(500:end), 'b');
    title ('Long Term  Mag X')
    ylabel ('Mag counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Mx_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Mag X')
    ylabel ('Mag counts');
    xlabel ('Time (s)');


fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear s_Mx_comp s_Mx

figure (fig_ct)

subplot(2,1,1)
    s_My_comp = cTemp(s_My, s_Te, myTGain,0,1,tmeanMy);
    plot(s_Ti(500:end),s_My(500:end), 'b');
    title ('Long Term  Mag Y')
    ylabel ('Mag counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_My_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Mag Y')
    ylabel ('Mag counts');
    xlabel ('Time (s)');

clear s_My_comp s_My
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

figure (fig_ct)

subplot(2,1,1)
    s_Mz_comp = cTemp(s_Mz, s_Te, mzTGain,0,1,tmeanMz);
    plot(s_Ti(500:end),s_Mz(500:end), 'b');
    title ('Long Term  Mag Z')
    ylabel ('Mag counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Mz_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Mag z')
    ylabel ('Mag counts');
    xlabel ('Time (s)');

clear s_Mz_comp s_Mz
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
% Air Data

figure (fig_ct)

subplot(2,1,1)
    s_Dy_comp = cTemp(s_Dy, s_Te, dyTGain,0,1,tmeanDy);
    plot(s_Ti(500:end),s_Dy(500:end), 'b');
    title ('Long Term  Dynamic Pressure')
    ylabel ('Dyn counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Dy_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Dynamic Pressure')
    ylabel ('Dyn counts');
    xlabel ('Time (s)');

clear s_Dy_comp s_Dy
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

figure (fig_ct)

subplot(2,1,1)
    s_St_comp = cTemp(s_St, s_Te, stTGain,0,1,tmeanSt);
    plot(s_Ti(500:end),s_St(500:end), 'b');
    title ('Long Term  Static Pressure (Pa)')
    ylabel ('Pa');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_St_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Static Pressure (Pa)')
    ylabel ('Pa');
    xlabel ('Time (s)');


fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);
clear s_St_comp s_St

figure (fig_ct)

subplot(2,1,1)
    s_Vl_comp = cTemp(s_Vl, s_Te, vlTGain,0,1,tmeanVl);
    plot(s_Ti(500:end),s_Vl(500:end), 'b');
    title ('Long Term  Voltage')
    ylabel ('counts');
    xlabel ('Time (s)');
subplot(2,1,2)
    plot(s_Ti(500:end),s_Vl_comp(500:end), 'r');
    title ('Long Term Temperature Compensated Voltage')
    ylabel ('counts');
    xlabel ('Time (s)');

clear s_Vl_comp s_Vl s_Te s_Ti
fig_ct= fig_ct+1;    
eval(['print -depsc  '  num2str(fig_ct)]);

%% Print the complete set of Gains, Biases, Temp Coefficients, etc...
format compact;
format short;
clc
disp(' ===== Temp Coefficients =======');
gxTGain
gyTGain
gzTGain
axTGain
ayTGain
azTGain
tmeanAx
mxTGain
myTGain
disp(' for Z Mag negative');
-mzTGain
tmeanMx
stTGain
tmeanSt
dyTGain
tmeanDy
vlTGain
tmeanVl

disp(' ===== Gains  =======');
gxGain
gyGain
gzGain
disp(' Accel Param a');
AccelParam.a
disp(' Accel Param b');
AccelParam.b
disp(' Accel Param c');
AccelParam.c
disp(' Mag Param a');
MagParam.a
disp(' Mag Param b');
MagParam.b
disp(' Mag Param c');
MagParam.c
disp(' for Air Data use according to calibration');

disp(' ===== Bias  =======');
disp(' for Gyros Grab 1st data Point');
disp(' for Air Data use according to calibration');
disp(' Accel Param x0');
AccelParam.xo
disp(' Accel Param y0');
AccelParam.yo
disp(' Accel Param z0');
AccelParam.zo
disp(' Mag Param x0');
MagParam.xo
disp(' Accel Param Y0');
MagParam.yo
disp(' Accel Param z0');
MagParam.zo

format loose
save gainsAndBiases

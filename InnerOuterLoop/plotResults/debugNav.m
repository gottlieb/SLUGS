%% Extract Files from multidimensional format
x = X(:);
y = Y(:);
z = Z(:);

vn = Vned(:,1);
vn = vn(:);
ve = Vned(:,2);
ve = ve(:);
vd = Vned(:,3);
vd = vd(:);

% housekeeping variables
 l = 1;
 i =  length(eta);
 figct = 1;
 
% Turn the Pause On
pauseOn = 1;

%% Start the Main loop
figure(figct);
%figure(2);
clf;

% Plot the waypoints
plot(Ypoints,Xpoints,'k','LineWidth',3);
hold on
% for nn = 1:wpCount
%     text(Ypoints(nn)+100,Xpoints(nn)+100,num2str(nn))
% end
plot([Ypoints(end) Ypoints(1)],[Xpoints(end) Xpoints(1)],'k','LineWidth',3);
plot(Ypoints,Xpoints,'sk');
title('Reference Path for PM_3 and PM_4');
%Plot the circle turns
plotCirc
axis equal;

 for j=l:25:i
     % plot the UAV postion
      plot(y(j),x(j),'gx');

     %plot the velocity vector
     plot ([y(j) y(j)+ve(j)], [x(j) x(j)+vn(j)], 'r');
     
     %plot the L2 vector
     if j > 10 && L2Enabled(j) == 1
        plot ([y(j) y(j)+L1(j,2)], [x(j) x(j)+L1(j,1)], 'b-');
     end
     % plot N exagerated (multiplied by 20)
      plot ([y(j) y(j)+20*N(j,2)], [x(j) x(j)+20*N(j,1)], 'c-');
      
     %pause the animation
     if pauseOn == 1
        if (mod(j-1,200)==0)
             pause(0.1);
        end
     end
 end
 xlabel('Y(m)');
 ylabel('X(m)');
 grid on;
 hold off
 
%  eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
%      datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;
%%  Collect the rest of the values
%time 

timePl = ctrlCmds.time;

% Collect Euler Data
phiPl = EulerData.signals(1,1).values(:,1);
phi_cPl = EulerData.signals(1,1).values(:,2);
thetaPl = EulerData.signals(1,2).values(:,1);
theta_cPl = EulerData.signals(1,2).values(:,2);
psiPl = EulerData.signals(1,3).values(:,1);

% Collect Airspeed
umPl = AirspeedPsiDot.signals(1,1).values(:,1);
um_cPl = AirspeedPsiDot.signals(1,1).values(:,2);

%collect PsiDot
psidotPl = AirspeedPsiDot.signals(1,2).values(:,1);
psidot_cPl = AirspeedPsiDot.signals(1,2).values(:,2);

% Collect Control Commands and after servos
decPl = ctrlCmds.signals(1,1).values(:,1);
deservoPl = ctrlCmds.signals(1,1).values(:,2);

dacPl = ctrlCmds.signals(1,2).values(:,1);
daservoPl = ctrlCmds.signals(1,2).values(:,2);

drcPl = ctrlCmds.signals(1,3).values(:,1);
drservoPl = ctrlCmds.signals(1,3).values(:,2);

dtcPl = ctrlCmds.signals(1,4).values(:,1);
dtservoPl = ctrlCmds.signals(1,4).values(:,2);

% Wind Data
windTime = windData(:,1);
xw = windData(:,2);
yw = windData(:,3);
zw = windData(:,4);
%% Plot the values
% Euler Angles
figure(figct)
subplot(3,1,1)
  plot(timePl,phiPl*180/pi,'b',timePl,phi_cPl*180/pi,'r');
  xlabel('Time(s)');
  ylabel('\phi (deg)');
  legend('Measured','Commanded');
  axis tight
subplot(3,1,2)
  plot(timePl,thetaPl*180/pi,'b',timePl,theta_cPl*180/pi,'r');
  xlabel('Time(s)');
  ylabel('\theta (deg)');
  axis tight
subplot(3,1,3)
  plot(timePl,psiPl*180/pi,'b');
  xlabel('Time(s)');
  ylabel('\psi (deg)');
  axis tight


 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;
  
 figure(figct)
 subplot(3,1,1)
  hold on
  plot(timePl,umPl,'b','LineWidth',2); 
  plot(timePl,um_cPl,'r','LineWidth',2); 
  %title('Mid Level Commands');
  hold off
  xlabel('Time(s)');
  ylabel('Airspeed (m/s)');
  legend('Measured','Commanded');
  grid on
  axis tight
  box on
 subplot(3,1,2)
  hold on
  plot(timePl,psidotPl,'b','LineWidth',2); 
  plot(timePl,psidot_cPl,'r','LineWidth',2);  
  hold off
  xlabel('Time(s)');
  ylabel('Turn Rate (deg/s)');
  grid on
  axis tight
  box on
 subplot(3,1,3)
  hold on
  plot(timePl,h_c,'b','LineWidth',2); 
  plot(timePl,z,'r','LineWidth',2); 
  hold off
  xlabel('Time(s)');
  ylabel('Altitude (m)');
  grid on
  axis tight
  box on


 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;

 figure(figct)
 subplot(3,1,1)
  hold on
  plot(timePl,(umPl-um_cPl),'b','LineWidth',2); 
  hold off
  xlabel('Time(s)');
  ylabel('Airspeed Error (m/s)');
  axis tight
 subplot(3,1,2)
  hold on
  plot(timePl,(psidotPl-psidot_cPl) ,'b','LineWidth',2);   
  hold off
  xlabel('Time(s)');
  ylabel('Turn Rate Error(deg/s)');
  axis tight
 subplot(3,1,3)
  hold on
  plot(timePl,(h_c-z),'b','LineWidth',2); 
  hold off
  xlabel('Time(s)');
  ylabel('Altitude Error (m)');
  axis tight 

 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;

 

 figure(figct)
 subplot(4,1,1)
   plot(timePl,sqrt(Vxyz(:,1).^2 + Vxyz(:,2).^2 + Vxyz(:,3).^2),'b'); 
   xlabel('Time(s)');
   ylabel('GroundSpeed (m/s)');
   grid on
 subplot(4,1,2)
   plot(timePl,as_c,'b'); 
   xlabel('Time(s)');
   ylabel('Acceleration Command');
   grid on
subplot(4,1,3)
   plot(L2,'b'); 
   xlabel('Time(.01 s)');
   ylabel('L2 Magnitude');
   grid on
subplot(4,1,4)
   plot(rad2deg(eta),'b'); 
   xlabel('Time(.01 s)');
   ylabel('Eta(rad)');
   grid on
   
 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;
 

%% Longitudinal  Channel (Um, Theta, H)

 figure(figct)
 subplot(3,1,1)
  hold on
  plot(timePl,umPl,'b','LineWidth',2);
  plot(timePl,um_cPl,'r','LineWidth',2);
  hold off
title('Longitudinal Channel'); 
  xlabel('Time(s)');
  ylabel('Airspeed (m/s)');
  legend('Measured','Commanded');
  axis tight
  grid on
   box on
subplot(3,1,2)
  hold on
  plot(timePl,thetaPl*180/pi,'b','LineWidth',2);
  plot(timePl,theta_cPl*180/pi,'r','LineWidth',2);
  hold off
  xlabel('Time(s)');
  ylabel('\theta (deg)');
  axis tight
  grid on
    box on
 subplot(3,1,3)
  hold on
  plot(timePl,h_c,'b','LineWidth',2); 
  plot(timePl,z,'r','LineWidth',2); 
  hold off
  xlabel('Time(s)');
  ylabel('Altitude (m)');
  axis tight
  grid on
    box on
  
  eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;
 
%% Lateral Channel (Phi, Ay_b) 

figure(figct)
subplot(2,1,1)
  hold on
  plot(timePl,phiPl*180/pi,'b','LineWidth',2);
  plot(timePl,phi_cPl*180/pi,'r','LineWidth',2);
  hold off
  title('Lateral Channel');
  xlabel('Time(s)');
  ylabel('\phi (deg)');
  legend('Measured','Commanded');
  axis tight
  grid on
    box on
figure(figct)
subplot(2,1,2)
  hold on
  plot(timePl,Ayb_m(:),'b','LineWidth',2);
  plot(timePl,zeros(size(Ayb_m(:))),'r','LineWidth',2);
  hold off
  xlabel('Time(s)');
  ylabel('Lateral Acceleration (m/s)');
  axis tight  
  grid on
    box on
  
   eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;
 
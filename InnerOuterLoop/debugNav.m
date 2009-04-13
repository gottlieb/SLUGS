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
 %i = 7260;
 figct = 1;
 
% Turn the Pause On
pauseOn = 1;
%% Start the Main loop
figure(figct);
clf;

% Plot the waypoints
plot(Ypoints,Xpoints,'k','LineWidth',3);
hold on
for nn = 1:wpCount
    text(Ypoints(nn)+100,Xpoints(nn)+100,num2str(nn))
end
plot([Ypoints(end) Ypoints(1)],[Xpoints(end) Xpoints(1)],'k','LineWidth',3);
plot(Ypoints,Xpoints,'sk');
%Plot the circle turns
plotCirc
axis equal;
 for j=l:50:i
     % plot the UAV postion
     plot(y(j),x(j),'g.');
      
     %plot the velocity vector
     plot ([y(j) y(j)+ve(j)], [x(j) x(j)+vn(j)], 'r');
     
     %plot the L1 vector
     if j > 9000
        plot ([y(j) y(j)+L1(j,2)], [x(j) x(j)+L1(j,1)], 'b-');
     end
     % plot N exagerated (multiplied by 20)
      plot ([y(j) y(j)+20*N(j,2)], [x(j) x(j)+20*N(j,1)], 'c-');
      
     %pause the animation
     if pauseOn == 1
        if (mod(j-1,200)==0)
             pause(0.01);
        end
     end
 end
 
 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
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
  plot(timePl,umPl,'b',timePl,um_cPl,'r'); 
  xlabel('Time(s)');
  ylabel('Airspeed (m/s)');
  legend('Measured','Commanded');
  axis tight
 subplot(3,1,2)
  plot(timePl,psidotPl*180/pi,'b',timePl,psidot_cPl*180/pi,'r'); 
  xlabel('Time(s)');
  ylabel('Turn Rate (deg/s)');
  axis tight
 subplot(3,1,3)
  plot(timePl,h_c,'b',timePl,z,'r'); 
  xlabel('Time(s)');
  ylabel('Altitude (m)');
  axis tight 


 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;

  figure(figct)
  subplot(4,2,1)
    plot(timePl,decPl*180/pi,'b'); 
    xlabel('Time(s)');
    ylabel('Elevator (deg)');
    title('Commanded');
    axis tight
  subplot(4,2,2)
    plot(timePl,deservoPl*180/pi,'r'); 
    xlabel('Time(s)');
    title('After Servo Dynamics');
    axis tight
  subplot(4,2,3)
    plot(timePl,dacPl*180/pi,'b'); 
    xlabel('Time(s)');
    ylabel('Aileron (deg)');
    axis tight
  subplot(4,2,4)
    plot(timePl,daservoPl*180/pi,'r'); 
    xlabel('Time(s)');
    axis tight  
   subplot(4,2,5)
    plot(timePl,drcPl*180/pi,'b'); 
    xlabel('Time(s)');
    ylabel('Rudder (deg)');
    axis tight
  subplot(4,2,6)
    plot(timePl,drservoPl*180/pi,'r'); 
    xlabel('Time(s)');
    axis tight  
  subplot(4,2,7)
    plot(timePl,dtcPl,'b'); 
    xlabel('Time(s)');
    ylabel('Throttle (%)');
    axis tight
  subplot(4,2,8)
    plot(timePl,dtservoPl,'r'); 
    xlabel('Time(s)');
    axis tight    
 

 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;

 
 figure(figct)
 plot3(y,x,z,'b');
 hold on;
 plot3(Ypoints,Xpoints,Zpoints,'sk');
 xlabel('X (m)');
 ylabel('Y (m)');
 zlabel('Z (m)');
 
 grid on
 hold off

 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;

 figure(figct)
 subplot(4,1,1)
   plot(windTime,xw,'b'); 
   xlabel('Time(s)');
   ylabel('Wind X Component (m/s)');
 subplot(4,1,2)
   plot(windTime,yw,'b'); 
   xlabel('Time(s)');
   ylabel('Wind Y Component (m/s)');
 subplot(4,1,3)
   plot(windTime,zw,'b'); 
   xlabel('Time(s)');
   ylabel('Wind Z Component (m/s)');
subplot(4,1,4)
   plot(windTime,sqrt(xw.*xw + yw.*yw+ zw.*zw),'b'); 
   xlabel('Time(s)');
   ylabel('Total Wind Speed  (m/s)');
   legend(['BS = ', num2str(windBase), ' TD = ', num2str(windDirTurb) , ' HD = ' , num2str(windDirHor)])

 eval(['print -depsc  '  num2str(figct) '_'  datestr(now,1) '_' ... 
     datestr(now,'HH') '_' datestr(now,'MM') '_' datestr(now,'SS')]);
 figct = figct + 1;

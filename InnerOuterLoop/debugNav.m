%% Extract Files from multidimensional format

x = X(:);
y = Y(:);
z = Z(:);

vn = Vned(1,1,:);
vn = vn(:);
ve = Vned(2,1,:);
ve = ve(:);
vd = Vned(3,1,:);
vd = vd(:);

% housekeeping variables
 l = 1;
 i =  length(eta);
 %i = 7260;
%% Start the Main loop
figure(1);
clf;

% Plot the waypoints
plot(Ypoints,Xpoints,'k','LineWidth',3);
hold on
plot([Ypoints(end) Ypoints(1)],[Xpoints(end) Xpoints(1)],'k','LineWidth',3);
plot(Ypoints,Xpoints,'sk');
axis equal;
 for j=l:50:i
     % plot the UAV postion
     plot(y(j),x(j),'g.');
      
     %plot the velocity vector
     plot ([y(j) y(j)+ve(j)], [x(j) x(j)+vn(j)], 'r');
     
     %plot the L1 vector
     plot ([y(j) y(j)+L1(j,2)], [x(j) x(j)+L1(j,1)], 'b-');
     
     % plot N exagerated
      plot ([y(j) y(j)+20*N(j,2)], [x(j) x(j)+20*N(j,1)], 'c-');
      
     %pause the animation
     if (mod(j-1,200)==0)
         pause(0.01);
     end
 end
 
%%  Additional Plots

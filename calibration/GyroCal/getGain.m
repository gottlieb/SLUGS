function [alpha, xcOffset] = getGain(KVH, Slugs);
%% Plot the Given data to subtract the mean 
plot(KVH,'r');
str = sprintf('Resize graph to zoom in on the flat section for mean removal\n\nPress Any key when done');
legend(str);
zoom on
pause
Ax = axis;

meanBegin = floor(Ax(1));
meanEnd = ceil(Ax(2));

meanKVH = mean(KVH(meanBegin:meanEnd));

KVH = KVH - meanKVH;

plot(KVH,'r');

plot(Slugs,'b');

str = sprintf('Resize graph to zoom in on the flat section for mean removal\n\nPress Any key when done');
legend(str);
zoom on
pause
Ax = axis;

meanBegin = floor(Ax(1));
meanEnd = ceil(Ax(2));
meanSlugs =  mean(Slugs(meanBegin:meanEnd));

Slugs = Slugs - meanSlugs;

%% Get begin points of data

plot(KVH, 'r');
hold on;
plot( Slugs, 'b');
zoom reset

str = sprintf('Resize graph to zoom in on the first feature\n\nPress Any key when done');
legend(str);
zoom on
pause
str = sprintf('Pick Initial Feature on KVH, Second Click on Slugs');
legend(str);

[x,y] = ginput(2);

KVHBegin = floor(x(1));
SlugsBegin = floor(x(2));


%% Get End points of data
zoom out 
 
str = sprintf('Resize graph to zoom in on the last feature\n\nPress Any key when done');
legend(str);
zoom on
pause
str = sprintf('Pick Last Feature on KVH, Second Click on Slugs');
legend(str);

[x,y] = ginput(2);
 
KVHEnd = ceil(x(1));
SlugsEnd = ceil(x(2));

%% Compute the valid time for KVH
tKVH = [1:length(KVH)]'-KVHBegin;

hold off
clf

plot(tKVH,KVH, 'r');
hold
 
%% Do the time scaling

tSlugs = ([1:length(Slugs)]' - SlugsBegin)*((KVHEnd - KVHBegin)/(SlugsEnd - SlugsBegin));

plot(tSlugs,Slugs,'b');
hold off

%% Do the interpolation

z = [KVHBegin:KVHEnd]';

SlugsPrime = interp1(tSlugs,Slugs,tKVH(z),'spline' );

%% Obtain the preliminary gains and plot the final result
alpha = SlugsPrime\KVH(z);

alpha2= pinv(SlugsPrime)*KVH(z);

alpha3 = inv(SlugsPrime'*SlugsPrime)*SlugsPrime'*KVH(z);

alpha4 = SlugsPrime'*KVH(z)/(SlugsPrime'*SlugsPrime);

clf
plot(tKVH,KVH,'r', tSlugs,alpha*Slugs,'b');
title ('Gain Computation. First Run')
legend('KHV FOG Data','SLUGS Compensated Data');
xlabel('Samples');
ylabel('Rotation Rate (deg/s)');

alpha = (alpha + alpha2 + alpha3 + alpha4)/4;

%% Second Run
% Get begin points of data
figure;
plot(tKVH,KVH, 'r');
hold on;
plot(tSlugs, alpha*Slugs, 'b');
zoom reset

str = sprintf('Resize graph to zoom in on the first feature\n\nPress Any key when done');
legend(str);
zoom on
pause
str = sprintf('Pick Initial Feature on KVH, Second Click on Slugs');
legend(str);

[x,y] = ginput(2);

KVHBegin = tKVH(min(find(tKVH>x(1))));
zBegin = min(find(tKVH>x(1)));
SlugsBegin = tSlugs(min(find(tSlugs>x(2))));

% Get End points of data
zoom out 
 
str = sprintf('Resize graph to zoom in on the last feature\n\nPress Any key when done');
legend(str);
zoom on
pause
str = sprintf('Pick Last Feature on KVH, Second Click on Slugs');
legend(str);

[x,y] = ginput(2);
 
KVHEnd = tKVH(min(find(tKVH>x(1))));
zEnd = min(find(tKVH>x(1)));
SlugsEnd = tSlugs(min(find(tSlugs>x(2))));

tSlugs2 = (tSlugs - (KVHBegin - SlugsBegin))*((KVHEnd - KVHBegin)/(SlugsEnd - SlugsBegin));

% Do the interpolation

z = [zBegin:zEnd]';

SlugsPrime2 = interp1(tSlugs2,Slugs,tKVH(z),'spline' );

%% Obtain the secondary gains and plot the final result
alpha = SlugsPrime2\KVH(z);

alpha2= pinv(SlugsPrime2)*KVH(z);

alpha3 = inv(SlugsPrime2'*SlugsPrime2)*SlugsPrime2'*KVH(z);

alpha4 = SlugsPrime2'*KVH(z)/(SlugsPrime2'*SlugsPrime2);

alpha = (alpha + alpha2 + alpha3 + alpha4)/4;

clf
plot(tKVH,KVH,'r', tSlugs2,alpha*Slugs,'b');
title (['Gain Computation. Final Run. Gain: '  num2str(alpha)])
legend('KHV FOG Data','SLUGS Compensated Data');
xlabel('Samples');
ylabel('Rotation Rate (deg/s)');


%% Find the cross correlation,time vectors and offset value
xcTime = [-length(KVH(z))+1:length(KVH(z))-1];
xcVals = xcorr(KVH(z),SlugsPrime2, 'coeff');
xcOffset = xcTime(find(xcVals == max(xcVals)));



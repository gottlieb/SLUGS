
%% Load the the Data
load Data

KVH = KVH_x (:,1);
Slugs = G_x;


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
hold


%% Do the interpolation

z = [KVHBegin:KVHEnd]';

SlugsPrime = interp1(tSlugs,Slugs,tKVH(z),'spline' );

%% Find the cross correlation,time vectors and offset value
xcTime = [-length(KVH(z))+1:length(KVH(z))-1];
xcVals = xcorr(KVH(z),SlugsPrime, 'coeff');
xcOffset = xcTime(find(xcVals == max(xcVals)));

%% Correct the offset

%% Obtain the gains and plot the final result
alpha = SlugsPrime\KVH(z)

alpha2= pinv(SlugsPrime)*KVH(z)

alpha3 = inv(SlugsPrime'*SlugsPrime)*SlugsPrime'*KVH(z)

alpha4 = SlugsPrime'*KVH(z)/(SlugsPrime'*SlugsPrime)

clf
plot(tKVH,KVH,'r', tSlugs,alpha*Slugs,'b');

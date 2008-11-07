%load ('ST7');
%data = cart1;

drange = 5900:37947; 
%% Extract the columns 
roll    = data(:,1);
pitch   = data(:,2);
yaw     = data(:,3);
p       = data(:,4);
q       = data(:,5);
r       = data(:,6);
x       = data(:,7);
y       = data(:,8);
z       = data(:,9);
vx      = data(:,10);
vy      = data(:,11);
vz      = data(:,12);
year    = data(:,13);
month   = data(:,14);
day     = data(:,15);
hour    = data(:,16);
min     = data(:,17);
sec     = data(:,18);
lat     = data(:,19);
lon     = data(:,20);
height  = data(:,21);
cog     = data(:,22);
sog     = data(:,23);
hdop    = data(:,24);
fix     = data(:,25);
sats    = data(:,26);
newVal  = data(:,27);
gX      = data(:,28);
gY      = data(:,29);
gZ      = data(:,30);
aX      = data(:,31);
aY      = data(:,32);
aZ      = data(:,33);
mX      = data(:,34);
mY      = data(:,35);
mZ      = data(:,36);

%% some plots

figure(1)
plot(lat(drange))

figure(2)
plot(lon(drange))

figure(3)
plot(gX(drange))

figure(4)
plot(gY(drange))

figure(5)
plot(gZ(drange))

figure(6)
plot(aX(drange))

figure(7)
plot(aY(drange))

figure(8)
plot(aZ(drange))

figure(9)
plot(cog(drange))

figure(10)
plot(sog(drange))


figure(11)
plot(x(drange))

figure(12)
plot(y(drange))

figure(13)
plot(z(drange))

figure(14)
plot(vx(drange))

figure(15)
plot(vy(drange))

figure(16)
plot(vz(drange))
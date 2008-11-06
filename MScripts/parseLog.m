load ('ST7');
data = ST7;

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
plot(lat(1193:4510))

figure(2)
plot(lon(1193:4510))

figure(3)
plot(gX(1193:4510))

figure(4)
plot(gY(1193:4510))

figure(5)
plot(gZ(1193:4510))

figure(6)
plot(aX(1193:4510))

figure(7)
plot(aY(1193:4510))

figure(8)
plot(aZ(1193:4510))

figure(9)
plot(cog(1193:4510))

figure(10)
plot(sog(1193:4510))


figure(11)
plot(x(1193:4510))

figure(12)
plot(y(1193:4510))

figure(13)
plot(z(1193:4510))

figure(14)
plot(vx(1193:4510))

figure(15)
plot(vy(1193:4510))

figure(16)
plot(vz(1193:4510))
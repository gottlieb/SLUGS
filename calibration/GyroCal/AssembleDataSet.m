clear

load Temperature

Mags =  getMags(Temperature);

t_Gx = Temperature(:,1);
t_Gy = Temperature(:,2);
t_Gz = Temperature(:,3);
t_Ax = Temperature(:,4);
t_Ay = Temperature(:,5);
t_Az = Temperature(:,6);
t_Mx = Mags(:,1);
t_My = Mags(:,2);
t_Mz = Mags(:,3);
t_Te = Temperature(:,12);
t_Dy = Temperature(:,10);
t_St = Temperature(:,11);
t_Vl = Temperature(:,15);
t_Ti = ((0:size(t_Vl,1)-1)*0.01)';

clear Temperature
clear Mags

load Static
Mags =  getMags(Static);

s_Gx = Static(:,1);
s_Gy = Static(:,2);
s_Gz = Static(:,3);
s_Ax = Static(:,4);
s_Ay = Static(:,5);
s_Az = Static(:,6);
s_Mx = Mags(:,1);
s_My = Mags(:,2);
s_Mz = Mags(:,3);
s_Te = Static(:,12);
s_Dy = Static(:,10);
s_St = Static(:,11);
s_Vl = Static(:,15);
s_Ti = ((0:size(s_Vl,1)-1)*0.01)';

clear Static
clear Mags

load Tumble
Mags =  getMags(tumble);

tu_Gx = tumble(:,1);
tu_Gy = tumble(:,2);
tu_Gz = tumble(:,3);
tu_Ax = tumble(:,4);
tu_Ay = tumble(:,5);
tu_Az = tumble(:,6);
tu_Mx = Mags(:,1);
tu_My = Mags(:,2);
tu_Mz = Mags(:,3);
tu_Te = tumble(:,12);
tu_Dy = tumble(:,10);
tu_St = tumble(:,11);
tu_Vl = tumble(:,15);
tu_Ti = ((0:size(tu_Vl,1)-1)*0.01)';

clear tumble 
clear Mags

load gyroCal
c_KVH_x = KVH_x(:,1);
c_SLU_x = SLUGS_x(:,1);
c_Tem_x = SLUGS_x(:,12);
c_Ti_x = ((0:size(c_Tem_x)-1)*0.01)';

c_KVH_y = KVH_y(:,1);
c_SLU_y = SLUGS_y(:,2);
c_Tem_y = SLUGS_y(:,12);
c_Ti_y = ((0:size(c_Tem_y)-1)*0.01)';

c_KVH_z = KVH_z(:,1);
c_SLU_z = SLUGS_z(:,3);
c_Tem_z = SLUGS_z(:,12);
c_Ti_z = ((0:size(c_Tem_z)-1)*0.01)';

clear gyroCal
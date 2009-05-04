cent = O.signals.values;
Pchs = Pch.signals.values;
PchBs = PchB.signals.values;


tp = 0:0.1:2*pi;

figure(figct)
hold on;
for ii = 6:2:length(cent)
    plot(cent(ii,2)+R*cos(tp), cent(ii,1)+R*sin(tp),'k');
    plot(cent(ii,2), cent(ii,1),'vk');
    
    plot(Pchs(ii,2),Pchs(ii,1), 'vr');
    plot(PchBs(ii,2),PchBs(ii,1), 'vr');
end
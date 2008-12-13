clf
plot(Temperature(:,2),'r')
hold
plot(Temperature(:,12),'b')
plot(1317.02 - Temperature(:,12),'g')
plot(Temperature(:,2)+ (1317.02 - Temperature(:,12) ),'k')
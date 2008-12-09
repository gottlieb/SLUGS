function [sig_white,sig_markov,tau_markov] = analyze_gyro(wx,desc,Ts);
% [sig_white,sig_markov,tau_markov] = analyze_gyro(wx,desc);
%
% This file processes data for Gyros and presents the best model for the gyro.
% The model is based on the following parameterization of the gyros error:
%
% w_meas = (1+sf)w_true + b0 + b1(t) + bw
%
% where: sf    - scale factor
%        b0    - null shift or constant bias              .
%        b1(t) - time varying bias, Gauss-Markov process: b1 = -[1/tau]*b1 + wb1
%        bw    - broadband noise (characterized by stdev [sigma])
%        tau   - Gauss-Markov time constant
%        wb1   - white noise driving term for G-M part (characterized by stdev)
%
% GHE - 02/08/2002 [NavCom]
% assume that we have [wx] for processing and assume that Ts = 1 sec.
%

clc
close all
if (nargin < 3),
    Ts = 1;
end
time = [1:length(wx)]*Ts;
wx = wx - mean(wx);
%
% Plot the time traces
%
zz = [1:300]';
figure(1); clf;
subplot(221), plot(time(zz),wx(zz));
xlabel('time [sec]'),ylabel('rate [deg/s]');
title(['Short Term Plot for ',desc]);
legend(['\sigma_{short}= ',num2str(std(wx(zz))),' [deg/sec]']);
subplot(223), plot(decimate_t(time,60)/3600,decimate_t(wx,60));
xlabel('time [hours]'),ylabel('rate [deg/s]');
title(['Long Term Plot for',desc]);
legend(['\sigma_{long}= ',num2str(std(wx)),' [deg/sec]']);
%
% Compute the allan variance and plot the data 
%
[tau,av] = allanv(wx,floor(1/Ts),0,0);
subplot(222), loglog(tau,av);
xlabel('Time (sec)'), ylabel('Root Allan-Variance'), grid;
title(['Allan Variance for ',desc]);
%
% Compute the autocorrelation
%
navg = [25:5:250]';
Cmax = navg*0;
for i = 1:length(navg),
    jstr = int2str(i);
    wx_dec = decimate_g(wx,navg(i));
    eval(['[c_',jstr,',lags_',jstr,']=xcorr(wx_dec,''biased'');']);
    eval(['Cmax(i) = max(c_',jstr,');']);
    eval(['lags_',jstr,' = navg(i)*lags_',jstr,';']);
end
%
% plot the autocorrelation results
%
figure(2); clf
for i = 1:length(navg),
    jstr = int2str(i);
    eval(['plot(lags_',jstr,',c_',jstr,');']);
    hold on
    Ax=axis; plot(Ax(1:2),exp(-1)*[1 1]*Cmax(i),'r');
end
str = sprintf('Resize graph to zoom in on the crossing\nLeave symmetric for no correlation\n\nPress Any key when done');
legend(str);
sig_markov = sqrt(mean(Cmax));
zoom on
pause
Ax = axis;
tau_markov = floor(mean(Ax(1:2)));
if (tau_markov < 30), tau_markov = inf; end
sig_white = decimate_std(wx,tau_markov);
close(2);
%
% Final Plot to Generate
%
[c,lags]=xcorr(wx,'biased');
figure(1), subplot(224)
plot(lags,c)
xlabel('Lags [sec]'), ylabel('autocorrelation');
title(['AutoCorrelation for ',desc]);
disp(['Final Model for ',desc]);
disp(['Sigma_white = ',num2str(sig_white),' [deg/sec]']);
disp(['Tau_markov = ',int2str(tau_markov),' [sec]']);
disp(['Sigma_markov = ',num2str(sig_markov),' [deg/sec]']);
Ax = axis;
hold on, plot(tau_markov*[-1 -1],Ax(3:4),'r',tau_markov*[1 1],Ax(3:4),'r');
plot(Ax(1:2),sig_markov^2*[1 1],'g');
hold off
legend(['\sigma_w = ',num2str(sig_white),' [deg/sec]'],...
    ['\tau_{ } = ',int2str(tau_markov),' [sec]'],...
    ['\tau_{ } = ',int2str(tau_markov),' [sec]'],...
    ['\sigma_{b_1} = ',num2str(sig_markov),' [deg/sec]']);

subplot(222);
str = sprintf('\\sigma_w = %1.4f [deg/sec]\n\\tau_{ }  = %d [sec]\n\\sigma_{b_1} = %1.4f [deg/sec]',...
    sig_white,tau_markov,sig_markov);
legend(str);
Ax = axis;
hold on, loglog(tau_markov*[1 1],Ax(3:4),'r');
hold off


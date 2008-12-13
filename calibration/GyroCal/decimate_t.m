function t_decimated = decimate_t(x_t,WINDOW_WIDTH);
% function t_decimated = decimate_t(x_t,WINDOW_WIDTH);
%
% x_t is the time stream and WINDOW_WIDTH is the number of samples to average
% togeather. Note that averageing definitely causes a phase distortion.
dim =floor(length(x_t)/WINDOW_WIDTH);
x_shapeshifted = reshape(x_t(1:dim*WINDOW_WIDTH),WINDOW_WIDTH,dim);
t_decimated = x_shapeshifted(1,:)';


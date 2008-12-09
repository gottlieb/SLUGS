function x_decimated = decimate_g(x_g,WINDOW_WIDTH);
% function x_decimated = decimate_g(x_g,WINDOW_WIDTH);
%
% x_g is the data stream and WINDOW_WIDTH is the number of samples to average
% togeather. Note that averageing definitely causes a phase distortion.
if ((WINDOW_WIDTH < 2)|(WINDOW_WIDTH == inf)),
    x_decimated = x_g;
else
    dim =floor(length(x_g)/WINDOW_WIDTH);
    x_shapeshifted = reshape(x_g(1:dim*WINDOW_WIDTH),WINDOW_WIDTH,dim);
    x_decimated = (mean(x_shapeshifted))';
end

	function [tau,av] = allanv(X,fs,cflag,pflag)

%--------------------------------------------------------------------
%
%		[tau,av] = allanv(X,fs,cflag,pflag)
%
%
%       Computes the Allan-Variance for a given data-set.
%	The inputs to this function are:
%
%		X =	A vector that contains the data-set.  X can
%			be a matrix where each column of the matrix
%			one data set. 
%		fs =	The sampling frequency (Hz) at which the data
%			was collected.  Must be an integer.
%		eflag = plot 1-sigma confidence limits.  If the eflag
%			is set to "1" confidence limits will be
%			plotted.  If eflag is set to "0", no confidence
%			limits will be plotted.  The default is "1."
%		pflag =	plot flag.  If this value is set to "1"
%			the function will return a loglog plot 
%			of the root Allan-Variance.  If set to 
%			"0" no plots are drawn.  The default is
%			"1" (i.e., return a loglog plot). 
%			
%
%	The function returns a vector of time constants and a vector
%	of root Allan-Variances.  The returned values tau and av are
%	the time constants and the root allan variances respectively.
%	
%	Ref:	Ng, L.C. and Pines, D.J., "Characterization of Ring
%		Laser Gyro Performance Using the Allan Variance
%		Method," AIAA Journal of Guidance and Control, Vol. 20
%		No. 1, Feb 1997.  pp. 211-214.
%			 
%
%       Demoz Gebre-Egziabher
%       August 11, 1997.
%
%---------------------------------------------------------------------

if (nargin < 2)
	error('Not Enough Arguments.')
end

if (nargin < 3)
	pflag = 1;
	cflag = 1;
end

if (nargin < 4)
	pflag = 1;
end

drl = length(X);
[nr,nc] = size(X);

if (nr < nc)
	X = X';		% just in case X is a row vector
	temp = nr;
	nr = nc;
	nc = temp;			
end	

tau = [2:1:0.5*drl/fs]';
M = fs*tau;
K = fix(drl./M);

for k=1:length(K);		% number of different time constants

	bs = 1;
	es = M(k);

	for kk = 1:K(k);

		omega_bar(kk,:) = mean(X(bs:es,:)); 
		bs = es+1;
		es = bs+M(k)-1;

	end
	
	
	delta = omega_bar(2:K(k),:)-omega_bar(1:K(k)-1,:); 
	av(k,:) = sqrt((diag(delta'*delta))'/(2*(K(k) - 1)));

	clear omega_bar delta;

end

if (pflag == 0)
	return
end

frac_err = 1./sqrt(2*((2*drl)./tau - 1));
up = 1 + frac_err;
dn = 1 - frac_err;

for k = 1:nc

	if (cflag == 1)
		loglog(tau,av(:,k),tau,(av(:,k).*dn),tau,(av(:,k).*up));
	else
		loglog(tau,av(:,k));
	end
	xlabel('Time (sec)');
	ylabel('Root Allan-Variance');
	grid;

	if (k < nc)
		figure
	end

end
%==========================================================================%



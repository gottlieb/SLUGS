function [eul1,eul2]=Process_MetaSensor
% Process_MetaSensor
%
% m-file to process the attitude from measurements of a simple metasensor
%
% Gabriel Elkaim - 29/Mar/2006
%
close all, clear, clc
H_nav = [0.2709   -0.0240    0.3626]';
H_b1 = [-0.1057    0.4166   -0.1430]';
H_b2 = [-0.0943    0.1796    0.4048]';
A_b1 = [0.6629 -0.0124 0]';
A_b2 = [0.8122 -0.0126 0]';

qhat1 = iter_quat(H_b1,A_b1, H_nav, [1 0 0 0]');
qhat2 = iter_quat(H_b2,A_b2, H_nav, [1 0 0 0]');
eul1 = quat2eul(qhat1)*180/pi;
eul2 = quat2eul(qhat2)*180/pi;



function qhat = iter_quat(H_body,A_body,H_nav,initial_q)
% function qhat = iter_quat(H_body,A_body,H_nav,initial_q)
%
% funciton that uses the iterated quaternion solution to
% compute the attitude based on the inputs from an accelerometer
% and magnetometer.
%
% H_body - the body fixed readings of the magnetometers [Gauss]
% A_body - the body fixed accelerometer readings [G's]
% H_nav - The Navigation Frame earth's magnetic field [Gauss]
% initial_q - the initial guess quaternion

if (nargin==3),
    initial_q = [1 0 0 0]';
end
nIter = 10;
alfa = 0.1;

mI = H_nav;
aI = [0 0 -1]';
qI = initial_q;
qC = qI;

if(A_body(3)==0),
    th = asin(-A_body(1));
    ph = asin(A_body(2));
    C1=[1 0 0; 0 cos(ph) sin(ph); 0 -sin(ph) cos(ph)];
    C2=[cos(th) 0 -sin(th); 0 1 0; sin(th) 0 cos(th)];
    C = C1*C2;
    Hnb = C'*H_nav;
    resA = A_body(1)^2+A_body(2)^2;
    if (resA >1), A_body(3)=0; end
    A_body(3) = sqrt(1-resA);
    if (Hnb(3)*H_body(3) < 0),
        A_body(3) = -A_body(3);
    end
end
    
for k=1:nIter,
    mHat = qtrans(qC,H_body);		% transform mB into mI using q-hat
    aHat = qtrans(qC,A_body);		% transform aB into aI using q-hat
    dmI = mI - mHat;				% form the error in measurements of m
    daI = aI - aHat;				% form the error in measurements of a
    H = -2*[sk(mHat);sk(aHat)];	    % form the skew symetric
    qe = alfa*(pinv(H)*[dmI;daI]);	% calculate the error quaternion
    qC = qmult([1;qe],qC);	        % rotate q-hat
    qC = qC/norm(qC);				% renormalize
end

qhat = qC;


%==========================================================================
%           Helper Function
%==========================================================================
function [ri]=qtrans(q,rb);
% function [ri]=qtrans(q,rb);
%
% this function transforms the vector rb
% into the coordinate frame represented by
% the quaternion, q, by applying the rotation
% as defined as: ri = q* x rb x q

qstar = [q(1);-q(2:4)];
Rb = [0;rb(1);rb(2);rb(3)];

Ri = qmult(q,qmult(Rb,qstar));
%Ri = qmult(qstar,qmult(Rb,q));
ri = Ri(2:4);

function [qout]=qmult(q,p);
% function [qout]=qmult(q,p);
%
% multiplies the quaternions: q x p
% in order to do coordinate transformations,
% ri = q x rb x q*, implemented in another m-file.
qo  = q(1);
q1  = q(2);
q2  = q(3);
q3  = q(4);

P = [p(1) p(2) p(3) p(4)]';

Qplus= [qo -q1 -q2 -q3;
        q1  qo -q3  q2;
        q2  q3  qo -q1;
        q3 -q2  q1  qo];
        
qout = Qplus*p;

function as=sk(a)
%-----------------------------------------------------------
%		            function as=sk(a)
%
%
% This function determines the skew-symmetric matrix
% corresponding to a given vector a with three elements.

	as=[0 -a(3) a(2); a(3) 0 -a(1); -a(2) a(1) 0];
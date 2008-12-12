function mag_k  = M_out(M_in)
    persistent M_old;
    persistent clk;
    persistent magOld;
     
    if isempty(M_old)
        M_old = [0; 0; 0];
        clk = 1;
        magOld = 0;
    end

    rnMax = find (M_in == max(M_in));
    
    sampDif =  M_in(rnMax(1))- M_old(rnMax(1));
    
    if ~(sampDif > -15 && sampDif < 15)
        clk = -clk;
        mag_k = clk*(M_in-M_old).*0.5;
    else
        mag_k = magOld.*[1 1 -1]';
    end;
    mag_k(3)=-mag_k(3);
    M_old = M_in;
    magOld = mag_k;
end

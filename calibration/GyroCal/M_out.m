function mag_k  = M_out(M_in)
    persistent M_old;
    persistent clk;
    persistent magOld;
    persistent cycCount; 
    persistent zSign; 
    persistent myCount;
    %persistent oldMean;
    
    if isempty(M_old)
        M_old = [0; 0; 0];
        clk = 1;
        magOld = 0;
        cycCount =0;
        zSign =1;
        myCount = 0;
        oldMean = [0;0;0];
    end
    
    myCount = myCount + 1;
    
    if myCount > 2711
        cycCount = cycCount;
    end
    
    newMean =  (M_Old - M_in)/2;
    
    if cycCount  < 50
        cycCount = cycCount + 1;
    end
    
    % find the reading that has the biggest difference
    temp = abs(M_old - M_in);

    %rnMax = find (temp == max(temp));
    % Code replacement for find function (not supported in EML)
    if temp(1) > temp(2)
        if temp(1)> temp(3)
            rnMax = 1;
        else
            rnMax = 3;
        end
    else
        if temp(2)>temp(3)
            rnMax = 2;
        else
            rnMax = 3;
        end;
    end
    
    sampDif =  M_in(rnMax(1))- M_old(rnMax(1));
     
    if ~(sampDif > -15 && sampDif < 15)
        clk = -clk;
        mag_k = clk*(M_in-M_old).*0.5;
    else
        mag_k = magOld.*[1 1 zSign]';
    end;
    
    if cycCount == 50
        if mag_k(3)> 0
            zSign = -1;
        end
        cycCount = cycCount +1;
    end
    
    mag_k(3)= zSign*mag_k(3);
    M_old = M_in;
    magOld = mag_k;
    %oldMean = newMean;
end
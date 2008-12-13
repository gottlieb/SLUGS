function [dataComp, biaIni, tempIni]  = cTemp(data, temperature, alpha, sw_gyros, useExtMean, extMean);
if (sw_gyros)
    biaIni = mean(data(1:500));
    tempIni = mean(temperature(1:500));
else
    if (useExtMean)
        tempIni = extMean;
    else
        tempIni = mean(temperature);
    end
    biaIni =0;
end

dataComp = data-biaIni - alpha*(temperature- tempIni);
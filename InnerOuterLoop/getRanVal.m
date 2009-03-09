function rVal = getRanVal (upLimit, lowLimit, scale)
rVal = randn*scale;
while ((rVal < lowLimit) || (rVal>upLimit))
    rVal = randn*scale;
end
end
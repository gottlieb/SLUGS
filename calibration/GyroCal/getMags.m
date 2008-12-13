function Mags = getMags(data)

Mags =zeros(size(data,1),3);
clear M_out;
for (i=1:1:size(data,1))
    Mags(i,:) = M_out(data(i,7:9)')';
end;
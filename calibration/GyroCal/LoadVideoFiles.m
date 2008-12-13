% function to load each video file into video player for recording
%
% Each class is loaded into a separate variable that is then called
% for loading the class into the browser.
%
clc
clear
close all

fid = fopen('VideoURLs.txt','r');
nameMatrix = [];
tline = fgetl(fid);
while(tline~=-1),                                   % not end of file
    while(isempty(tline)),                           % blank line
        tline = fgetl(fid);
    end
    if (~isempty(tline)),
        name = tline(1:min(find(tline==' ')-1));
        eval([name,'=[];']);
        nameMatrix = strvcat(nameMatrix,name);
        tline = fgetl(fid);
        while(isempty(tline)),
            tline = fgetl(fid);
        end
        while(~isempty(tline)),
            eval([name,'=strvcat(',name,',tline);']);
            tline = fgetl(fid);
        end
    end
    tline = fgetl(fid);
    if (isempty(tline)), tline = fgetl(fid); end
end

[n,m]=size(nameMatrix);
for i=1:n,
    fprintf('\n%u --> %s',i,nameMatrix(i,:));
end
i = input('\n\nInput the class to send to browser: ');
eval(['[n,m]=size(',nameMatrix(i,:),');']);
for j = 1:n,
    eval(['str=',nameMatrix(i,:),'(',int2str(j),',:);']);
    eval(['!"C:\Program Files\Mozilla Firefox\firefox.exe" -new-window "',str,'"']);
    pause(2);
end
    



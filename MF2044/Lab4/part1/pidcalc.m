function [result] = pidcalc(data, r, y)
%PIDCALC Summary of this function goes here
%   Detailed explanation goes here

    persistent oldI;
    persistent oldD;
    persistent oldY;
    if isempty(oldI)
        oldI = 0;
        oldD = 0;
        oldY = 0;
    end
    
    P = data.K * (data.B*r - y);
    I = oldI + (data.K * data.h / data.Ti)*(r - y);
    D = (data.Td / (data.Td+data.N*data.h))*oldD + ((data.K*data.Td*data.N)/(data.Td+data.N*data.h))*(oldY-y);
    
    result = P + oldI + D;

    oldY = y;
    oldI = I;
    oldD = D;
end


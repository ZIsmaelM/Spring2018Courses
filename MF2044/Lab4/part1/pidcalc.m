function data = pidcalc(data, r, y)
%PIDCALC Summary of this function goes here
%   Detailed explanation goes here
    
    P = data.K * (data.B*r - y);
    I = data.oldI;
    D = (data.Td / (data.Td+data.N*data.h))*data.oldD + ((data.K*data.Td*data.N)/(data.Td+data.N*data.h))*(data.oldY-y);
    
    data.u = P + I + D;

    data.oldY = y;
    data.oldI = data.oldI + (data.K * data.h / data.Ti)*(r - y);
    data.oldD = D;
end


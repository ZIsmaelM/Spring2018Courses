function [exectime, data] = P1_task2_code(seg, data)

global glbData;
%data = 0;
%ID = 2;
switch seg      
    % set global x
    case 1
        ttTake('P1_sema');
        exectime = 0;
    case 2
        glbData.x = 2;
        exectime = data.wcetX;
        
    % set global y
    case 3
        glbData.y = 2;
        exectime = data.wcetY;
    case 4
        sum = glbData.x + glbData.y;
        glbData.sum = sum;
        ttAnalogOut(2, sum);
        exectime = 0;
    case 5
        ttGive('P1_sema');
        exectime = -1;
end
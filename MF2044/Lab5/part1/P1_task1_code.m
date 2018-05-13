function [exectime, data] = P1_task1_code(seg, data)

global glbData;
%data = 0;
switch seg      
    % set global x
    case 1
        ttTake('P1_sema');
        exectime = 0;
    case 2
        glbData.x = 1;
        exectime = data.wcetX;
        
    % set global y
    case 3
        glbData.y = 1;
        exectime = data.wcetY;
    case 4
        sum = glbData.x + glbData.y;
        glbData.sum = sum;
        ttAnalogOut(1, sum);
        exectime = 0;
    case 5
        ttGive('P1_sema');
        exectime = -1;
end
function [exectime, data] = P1_task_code(seg, taskID)

global glbData;
data = 0;
switch seg
    case 1
        glbData.x = taskID;
        exectime = 0.6;
        
    case 2
        glbData.y = taskID;
        exectime = 0.4;
        
    case 3
        data = glbData.x + glbData.y;
        ttAnalogOut(glbData.out, data);
        exectime = -1;
end
end     % End of main
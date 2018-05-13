function [exectime, data] = P3_task3_code(seg, data)

switch seg
    case 1
        ttEnterMonitor('P3_monitor');
        exectime = 0;    
    case 2
        exectime = data.wcetT3;       
    case 3
        ttExitMonitor('P3_monitor');
        exectime = -1;
end
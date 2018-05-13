function [exectime, data] = P2_task3_code(seg, data)

switch seg
    case 1
        ttEnterMonitor('P2_monitor');
        exectime = 0;    
    case 2
        exectime = data.wcetT3;       
    case 3
        ttExitMonitor('P2_monitor');
        exectime = -1;
end
function [exectime, data] = disturb_code(segement, data)
switch segement
    case 1
        exectime = 0.1;
    case 2
        exectime = -1;
end
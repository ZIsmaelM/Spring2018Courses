function [exectime, data] = handler_code(segement, data)
switch segement
    case 1
        fprintf(2,'WARNING: ctrl_code has overrun deadline\n\r');
        exectime = 0.001;
    case 2
        exectime = -1;
end
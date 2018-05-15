function [exectime, data] = pid_code(seg, data)

switch seg
    case 1
        r = ttAnalogIn(1); % Read references
        y = ttAnalogIn(2); % Read process output
        data = pidcalc(data, r, y); % Calculate PID action
        
        exectime = data.wcet; % Execution time = 1.3ms
    case 2
        ttAnalogOut(1, data.u); % Output control signal
        exectime = -1;
end
end     % End of main
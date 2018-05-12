function [exectime, data] = pid_code(seg, data)

switch seg
    case 1
        r = ttAnalogIn(data.rChan); % Read reference
        y = ttAnalogIn(data.yChan); % Read process output
        data = pidcalc(data, r, y); % Calculate PID action
        
        exectime = data.wcet; % Execution time = 1.3ms
    case 2
        ttAnalogOut(data.uChan, data.result); % Output control signal
        exectime = -1;
end
end     % End of main
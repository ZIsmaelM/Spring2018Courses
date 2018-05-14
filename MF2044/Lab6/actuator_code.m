function [exectime, data] = actuator_code(seg, data)

switch seg
    case 1
        msg = ttGetMsg;
        if ~isempty(msg)
            data.signal = msg;
            while ~isempty(msg)
                msg = ttGetMsg;
            end
            exectime = data.wcet;
        else
            fprintf(2, 'ERROR: message is empty');
            exectime = -1;
        end
    case 2
        ttAnalogOut(1, data.signal);    % single output channel
        exectime = -1;
end
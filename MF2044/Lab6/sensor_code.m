function [exectime, data] = sensor_code(seg, data)

switch seg
    case 1
        data.signal = ttAnalogIn(1);    % single input port
        exectime = data.wcet;
    case 2
        msg = [data.ID, data.signal];
        ttSendMsg(3, msg, 40);
        exectime = -1;
end
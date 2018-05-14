function [exectime, data] = control_code(seg, data)

switch seg
    case 1
        msg = ttGetMsg;
        if isempty(msg)
            fprintf(2, 'ERROR: mailbox is empty\r');
            exectime = -1;
        end
        exectime = 0;
    case 2
        r = ttAnalogIn(1);
        y = data.signal;
        data = pidcalc(data, r, y);
        
        exectime = data.wcet;
    case 3
        msg = [data.ID, data.signal];
        ttSendMsg(2, msg, 40);
        exectime = -1;
end
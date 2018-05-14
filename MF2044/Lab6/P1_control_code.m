function [exectime, data] = P3_control_code(seg, data)

global glbMessage;

switch seg
    case 1
%         ttFetch('P3_mailbox');
        exectime = 0;
        glbMessage = ttTryFetch('P3_mailbox');
        if isempty(glbMessage)
            fprintf(2, 'ERROR: mailbox is empty\r');
            exectime = -1;
        end
    case 2
%         glbMessage = ttRetrieve('P3_mailbox');
        r = glbMessage(1);
        y = glbMessage(2);
        data = pidcalc(data, r, y);
        
        exectime = data.wcet;
    case 3
        ttAnalogOut(data.outChan, data.result); % Output control signal
        exectime = -1;
end
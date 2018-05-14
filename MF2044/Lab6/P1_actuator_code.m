function [exectime, data] = P1_actuator_code(seg, data)

global glbMessage
switch seg
    case 1
        r = ttAnalogIn(data.rChan); % Read reference
        y = ttAnalogIn(data.yChan); % Read process output
        
        glbMessage = [r, y];
%         ok = ttTryPost('P3_mailbox', glbMessage);
%         if(~ok)
%             fprintf(2, 'ERROR: mailbox full\r');
%         end
        exectime = data.wcet; % Execution time
    case 2
        %ttPost('P3_mailbox', glbMessage);
        exectime = 0;
        
        ok = ttTryPost('P3_mailbox', glbMessage);
        if isempty(ok)
            exectime = -1;
        end
        
    case 3
        exectime = -1;
end
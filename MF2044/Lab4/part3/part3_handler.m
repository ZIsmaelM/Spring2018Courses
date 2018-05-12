function [exectime, data] = part3_handler(segement, data)

%find the name of the invoking task
task = sscanf(ttGetInvoker, 'DLtimer:%s');

%print the error message
%disp([task ' missed deadline at ' num2str(ttCurrentTime)]);
fprintf(2,[task ' missed deadline at ' num2str(ttCurrentTime) '\n\r']);
if ~isempty(task)
    ttKillJob(task); %kill the delayed job
end

exectime = -1;
function part3_init(arg)

% Task scheduling and control.
%
% This example extends the simple PID control example (located in
% $DIR/examples/servo) to the case of three PID-tasks running
% concurrently on the same CPU controlling three different servo
% systems. The effect of the scheduling policy on the global control
% performance is demonstrated.

% Initialize TrueTime kernel

% Task parameters
starttimes = [0 0 0];
periods = [0.006 0.005 0.004];
tasknames = {'pid_task1', 'pid_task2', 'pid_task3'};
setPriorities = false;

switch arg
 case 1   % DM scheduling
  ttInitKernel('prioDM')
  codefcn = 'pid_code';
 case 2
  ttInitKernel('prioFP')
  setPriorities = true;
  codefcn = 'pid_code';
 case 3   % EDF scheduling, skip next job if current one late
  ttInitKernel('prioEDF')
  codefcn = 'pid_code';
 otherwise
  error('Illegal init argument')
end

ttCreateHandler('deadline_handler', 0, 'part3_handler');

% Create the three tasks
for i = 1:3
%   data.late = 0;

    data.h = periods(i);      % sampling period  
    data.K = 1;         % pid proportional gain
    data.Ti = 0.12;     % integration time
    data.Td = 0.049;    % derivative time
    data.B = 0.5;       % fraction of control reference
    data.N = 10;        % high-freq gain limit
    data.rChan = 1;
    data.yChan = i+1;
    data.uChan = i;
    data.oldY = 0;
    data.oldI = 0;
    data.oldD = 0;
    
    data.wcet = 0.0016;     % worst-case execution time
    
    ttCreatePeriodicTask(tasknames{i}, starttimes(i), periods(i), codefcn, data);
    if (setPriorities)
        ttSetPriority((i+1), tasknames{i}); %Assign priority number
    end
    ttAttachDLHandler(tasknames{i}, 'deadline_handler');
    %ttCreateLog(tasknames{i},1,['response' num2str(i)],1000)
end

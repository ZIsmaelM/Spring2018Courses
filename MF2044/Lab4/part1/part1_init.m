function part1_init(Ts)
%The initilzation script of the TrueTime kernel
%The input argument Ts is the sampling period of the P controller
%The argument is specified in the second parameter of the TrueTme dialog

    ttInitKernel('prioFP')%Fixed priority scheduling
    
    %The data structure passes data to the pid task
    data.h = Ts;        % sampling period  
    data.K = 1;         % pid proportional gain
    data.Ti = 0.12;     % integration time
    data.Td = 0.049;    % derivative time
    data.B = 0.5;       % fraction of control reference
    data.N = 10;        % high-freq gain limit
    
    data.wcet = 0.0013;     % worst-case execution time
    
    starttime=0.0;      %pid task start time
    period = Ts;        %pid task period

    %The next command created control task and its periodicity (Ts)
    %The task run the matlab program named 'pid_code'
    ttCreatePeriodicTask('pid_task', starttime, period, 'pid_code', data);
    ttSetPriority(1, 'pid_task');      %Assign priority number 2 to the task

end

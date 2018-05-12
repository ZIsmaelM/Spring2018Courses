function simple_init(Ts)
%The initilzation script of the TrueTime kernel
%The input argument Ts is the sampling period of the P controller
%The argument is specified in the second parameter of the TrueTme dialog

    ttInitKernel('prioFP')%Fixed priority scheduling
    
    %The data structure passes data to the control task
    data.K =2;          %controller proportional gain
    data.wcet = Ts;     % The worst-case execution time of the control task

    starttime=0.0;      %control task start time
    period = Ts;        %control task period

    %The next command created control task and its periodicity (Ts)
    %The task run the matlab program named 'ctrl_code'
    ttCreatePeriodicTask('ctrl_task', starttime, period, 'ctrl_code', data);
    ttSetPriority(1, 'ctrl_task');      %Assign priority number 2 to the task
    
    %Disturb code initializer
    ttCreatePeriodicTask('disturb_task', 0, Ts, 'disturb_code');
    ttSetPriority(2, 'disturb_task');
    
    %DL code initializer
    ttCreateHandler('simple_handler', 0, 'handler_code');
    ttAttachDLHandler('ctrl_task', 'simple_handler');

end

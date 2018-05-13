function part3_init(~)

global glbMessage;

% Task fuunctional data
ttInitKernel('prioFP')          %priority model
taskNames = {'sensor', 'control'};
taskCode = {'P3_sensor_code', 'P3_control_code'};
startTime = [0.0 0.0];          %control task start time
priority = [2 1];
period = 0.005;                     %control task period

% initialize mailbox
ttCreateMailbox('P3_mailbox', 1);


for taskID = 1:2
    
    % Task input data
    data.h = period;    % sampling period  
    data.K = 1;         % pid proportional gain
    data.Ti = 0.12;     % integration time
    data.Td = 0.049;    % derivative time
    data.B = 0.5;       % fraction of control reference
    data.N = 10;        % high-freq gain limit
    data.rChan = 1;
    data.yChan = taskID+1;
    data.outChan = 1;
    data.oldY = 0;
    data.oldI = 0;
    data.oldD = 0;
    data.wcet = 0.001;
    
    ttCreatePeriodicTask(taskNames{taskID}, startTime(taskID), period, taskCode{taskID}, data);
    ttSetPriority(priority(taskID), taskNames{taskID});

end
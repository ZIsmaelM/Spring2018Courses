function part1_init(~)

global glbMessage;

% Task fuunctional data
ttInitKernel('prioFP')          %priority model
taskNames = {'refTask', 'senseTask', 'actTask', 'ctrlTask'};
taskCode = {'P1_ref_code', 'P1_sensor_code', 'P1_actuator_code', 'P1_control_code'};
nodeID = [1 2 3];
msgID = [1 2 3];    %also serves as the priority of each message
period = 0.005;
offset = 0.0;


% initialize mailbox
ttCreateMailbox('P3_mailbox', 1);


for taskID = 1:4
    
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
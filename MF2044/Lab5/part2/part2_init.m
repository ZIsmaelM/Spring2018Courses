function part2_init(~)

global glbData;
glbData.x = 0;
glbData.y = 0;
glbData.sum = 0;

% Task fuunctional data
ttInitKernel('prioFP')          %priority model
taskNames = {'task1', 'task2', 'task3'};
taskCode = {'P2_task1_code', 'P2_task2_code', 'P2_task3_code'};
startTime = [0.0 0.5 0.8];          %control task start time
priority = [3 1 2];
period = 3;                     %control task period

% Task input data
data.wcetX = 0.6;
data.wcetY = 0.4;
data.wcetT3 = 0.5;
data.taskID = [1 2 3];

% Mutual exclusion
%ttCreateSemaphore('P2_sema', 1, 1);

% initialize system monitor
ttCreateMonitor('P2_monitor');


for taskID = 1:3
    ttCreatePeriodicTask(taskNames{taskID}, startTime(taskID), period, taskCode{taskID}, data);
    ttSetPriority(priority(taskID), taskNames{taskID});

end
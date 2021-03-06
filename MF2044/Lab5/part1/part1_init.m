function part1_init(~)

global glbData;
glbData.x = 0;
glbData.y = 0;
glbData.sum = 0;

% Task fuunctional data
ttInitKernel('prioFP')          %priority model
taskNames = {'task1', 'task2'};
taskCode = {'P1_task1_code', 'P1_task2_code'};
startTime = [0.0 0.5];          %control task start time
priority = [1 1];
period = 3;                     %control task period

% Task input data
data.wcetX = 0.6;
data.wcetY = 0.4;
data.taskID = [1 2];

% Mutual exclusion
ttCreateSemaphore('P1_sema', 1, 1);


for taskID = 1:2
    ttCreatePeriodicTask(taskNames{taskID}, startTime(taskID), period, taskCode{taskID}, data);
    ttSetPriority(priority(taskID), taskNames{taskID});

end
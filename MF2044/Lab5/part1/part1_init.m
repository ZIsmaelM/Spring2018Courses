function part1_init(arg)

global glbData;
glbData.x = 0;
glbData.y = 0;
glbData.sum = 0;
glbData.out = 0;

ttInitKernel('prioFP')%Fixed priority scheduling

taskNames = {'task1', 'task2'};
startTime = [0.0 0.5];      %control task start time
priority = [1 1];
period = 3;        %control task period

ttInitKernel('prioFP')
for taskID = 1:2
    glbData.out = taskID;
    ttCreatePeriodicTask(taskNames{taskID}, startTime(taskID), period, 'P1_task_code', taskID);
    ttSetPriority(priority(taskID), taskNames{taskID});

end
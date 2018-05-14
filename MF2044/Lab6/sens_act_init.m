function sens_act_init(arg)

ttInitKernel('prioFP')

period = 0.005;
offset = 0.0;

data.wcet = 0.001;
data.ID = 2;

% initialize sensor
ttCreatePeriodicTask('sensTask', offset, period, 'sensor_code', data);
ttSetPriority(data.ID, 'sensTask');

% initialize actuator
ttCreatePeriodicTask('actTask', offset, period, 'act_code', data);
ttSetPriority(data.ID, 'actTask');

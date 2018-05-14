function reference_init(arg)

ttInitKernel('prioFP')

period = 0.005;
offset = 0.0;

data.wcet = 0.001;
data.ID = 1;

ttCreatePeriodicTask('refTask', offset, period, 'reference_code', data);
ttSetPriority(1, 'refTask');
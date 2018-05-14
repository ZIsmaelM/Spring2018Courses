function control_init(arg)

ttInitKernel('prioFP')

period = 0.005;
offset = 0.0;

% Task input data
data = arg;
data.h = period;    % sampling period  
data.K = 1;         % pid proportional gain
data.Ti = 0.12;     % integration time
data.Td = 0.049;    % derivative time
data.B = 0.5;       % fraction of control reference
data.N = 10;        % high-freq gain limit
data.oldY = 0;
data.oldI = 0;
data.oldD = 0;
data.wcet = 0.0015;
data.ID = 3;

% initialize sensor
ttCreatePeriodicTask('ctrlTask', offset, period, 'control_code', data);
ttSetPriority(data.ID, 'ctrlTask');
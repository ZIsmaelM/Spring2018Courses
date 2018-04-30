function [exectime, data]=ctrl_code(segement, data)
 %The output exectime returns the execution time of the task. The value is
 %used by the TrueTime simulator to calculate the delays.
 
 %The structure data is both input and output. The initial value of data is
 %given by ttCreatePeridocTask in the init script.
 
 %The input argument segment is internally maintained by the TrueTime
 %kernel.
 
 switch segement
     case 1 
         targetPos = ttAnalogIn(1); %Read sensor input of the target position
         motorPos = ttAnalogIn(2);  %Read sensor input of the motor position
         
         data.motorVel=data.K*(targetPos - motorPos);   %Compute the motor velocity
         exectime = rand*data.wcet;                     %The execution time is random between 0 and WCET
     case 2
         ttAnalogOut(1, data.motorVel);     %Send control command to the motor.The value of
                                            % motorel is computed in segment 1. The data structure
                                            % is used to pass the value between the two segments.
         exectime = -1;     %Instruct the kernet to terminate the current job of the task, set the task as IDLE
end
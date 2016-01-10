function [] = startPID(port, dT, T, setpoint, Kp, Ki, Kd)

% dT,(seconds) sampletime for graphing/Arduino UART polling = 0.1
% T,(seconds) Total time for test to run
% setpoint,(cm), 10,20,30,40 or 50
% Kp,K-constant to send '2.2', send '22', because its divided with 10 in Arduino
% Ki,I-constant to send '2', send '20', because its divided with 10 in Arduino
% Kd,D-constant to send '1.5', send '15', because its divided with 10 in Arduino

% Example 
% startPID('COM13', 0.2, 60, 10, 60, 9, 40)

%Before running, dont forget to put something to disable reflection of
%motor to sensor(like a scarf or something)

arduino = serial(port, 'BaudRate', 115200,'databits', 8);
fopen(arduino);

e = [];
o = [];
d = [];
sp = [];

N = T / dT;
disp('N=')
disp(N)

x = 1:N;

%Clear uart buffer
flushinput(arduino);
flushoutput(arduino);

pause(1);
fwrite(arduino, 1, 'int8');
pause(1);
fwrite(arduino, Kp, 'int8');
pause(1);
fwrite(arduino, Ki, 'int8');
pause(1);
fwrite(arduino, Kd, 'int8');
pause(1);
fwrite(arduino, setpoint, 'int8');
pause(1);

disp('Start loop')
disp(['Kp: ' num2str(Kp)]) 
disp(['Ki: ' num2str(Ki)]) 
disp(['Kd: ' num2str(Kd)]) 
disp(['Setpoint: ' num2str(setpoint)]) 

%Clear uart buffer
flushinput(arduino);
flushoutput(arduino)
for i = 1:N
    start = cputime; %startar en timer för att kunna mäta tiden för en loop
    
    % Signal Arduino Matlab wants values now
    fwrite(arduino, 1, 'int8');
    
    %disp('Wait for values')
    %Wait here until Arduino sends values
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
% startPID('com3', 0.5, 120, 30, 165, 125, 31, 5)
    %disp('Reading values')
    
    %Read values from Arduino
    error =  fscanf(arduino,'%d')
    pid_output =  fscanf(arduino,'%d')
    distance =  fscanf(arduino,'%d')
    setPoint = fscanf(arduino, '%d')

    e(i) = error;
    o(i) = pid_output;
    d(i) = distance;
    sp(i) = setPoint;
    
    plot(x(1:i), sp,'magenta',x(1:i),e,'red',x(1:i),o,'black',x(1:i),d,'blue');
    ylim([-2000 4000 ]);
    xlabel('Iterations (N)');
    ylabel('Position');
    title('PingPong System');
    legend('Setpoint','Error','Output Value', 'Distance');
    grid on
    
    elapsed=cputime-start; % räknar åtgången tid i sekunder
    ok=(dT-elapsed); % sparar tidsmarginalen i ok
    pause(ok); % pausar resterande samplingstid
end

fclose(instrfind);
delete(instrfind);
clear instrfind

end


function [] = startPID(port, dT, T, setpoint, Kp, Ki, Kd, sampletime)

arduino = serial(port, 'BaudRate', 115200,'databits', 8);
fopen(arduino);

disp('sampletime=')
disp(sampletime)

% %setpoint = ' ';
% Kp= ' ';
% %Ki= ' ';
% Kd= ' ';


disp('sampletime=')
disp(sampletime)


e = [];
o = [];
d = [];
sp = [];

N = T / dT;
disp('N=')
disp(N)

x = 1:N;

flushinput(arduino);
flushoutput(arduino);

pause(1);
fwrite(arduino, Kp, 'int8');
pause(1);
fwrite(arduino, Ki, 'int8');
pause(1);
fwrite(arduino, Kd, 'int8');
pause(1);
fwrite(arduino, sampletime, 'int8');
pause(1);
fwrite(arduino, setpoint, 'int8');
pause(1);

%Clear uart buffer
flushinput(arduino);
flushoutput(arduino);

disp('Start loop')

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
    etemp =  fscanf(arduino,'%d')
    otemp =  fscanf(arduino,'%d')
    dtemp =  fscanf(arduino,'%d')
    sptemp = fscanf(arduino, '%d')
    
    e(i) =etemp;
    o(i) =otemp;
    d(i) =dtemp;
    sp(i) =sptemp;
    
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


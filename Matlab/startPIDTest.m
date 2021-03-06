function [] = startPIDTest(port, dT, N, setpoint, Kp, Ki, Kd)

arduino = serial(port, 'BaudRate', 115200,'databits', 8);
fopen(arduino);

e = zeros(1,N);
o = zeros(1,N);
d = zeros(1,N);
sp = zeros(1,N);
t= zeros(1,N);
ok=0;
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

flushinput(arduino);
flushoutput(arduino);
for i = 1:N
    start = cputime; %startar en timer f�r att kunna m�ta tiden f�r en loop
   
    % Signal Arduino Matlab wants values now
    fwrite(arduino, 1, 'int8');
    
    %disp('Wait for values')
    %Wait here until Arduino sends values
    while(arduino.BytesAvailable <= 0)
        pause(0.01);
    end
% startPID('com3', 0.5, 120, 30, 165, 125, 31, 5)
    %disp('Reading values')
    t(i)=i;
    %Read values from Arduino
    error =  fscanf(arduino,'%d')
    pid_output =  fscanf(arduino,'%d')
    distance =  fscanf(arduino,'%d')
    setPoint = fscanf(arduino, '%d')

    e(i) = error;
    o(i) = pid_output;
    d(i) = distance;
    sp(i) = setPoint;
    
    
    t(i)= i*dT;
    plot(t, sp,'magenta',t,e,'red',t,o,'black',t,d,'blue');
   
    
    elapsed=cputime-start; % r�knar �tg�ngen tid i sekunder
    ok=(dT-elapsed); % sparar tidsmarginalen i ok
    pause(ok); % pausar resterande samplingstid
end

    fclose(instrfind);
    delete(instrfind);
    clear instrfind

    plot(t, sp,'magenta',t,e,'red',t,o,'black',t,d,'blue');
    ylim([-2000 4000 ]);
    xlabel('Sekunder (s)');
    ylabel('Position');
    title('PingPong System');
    legend('Setpoint','Error','Output Value', 'Distance');
    grid on
    
end
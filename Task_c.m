% Create a Map similar to the simulation-map.txt

figure()
% plot([-0.5,0.5,0.5,-0.5,-0.5],[0.5,0.5,-0.5,-0.5,0.5],'Linewidth',1.25);     %FIRST RUN
% plot([-0.5,0.5,0.5,0,-0.5,-0.5],[0.5,0.5,-0.5,-0.5,0,0.5],'Linewidth',1.25); %SECOND RUN
plot([-0.5,0.5,0.5,0,-0.5,-0.5],[0.5,0.5,-0.5,-0.5,0,0.5],'Linewidth',1.25); %THIRD RUN

hold on
Data = readtable('opendlv.sim.Frame-0.csv');    %CHANGE TO THE FILENAME IN THE FOLDER

% The X position of the robot
x_d = Data.x;

% The Y position of the robot
y_d = Data.y;

plot(x_d,y_d,'Linewidth',1.15);

%Set the limits based on the Map
xlim([-0.65,0.65])
ylim([-0.65,0.65])
grid on
title('Path followed by the robot')
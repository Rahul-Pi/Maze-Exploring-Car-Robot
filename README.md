# Maze Exploring Car/Robot

An OpenDLV microservices program developed for a Maze exploring Robot. 

OpenDLV is a modern open source software developed by [Chalmers Revere](https://github.com/chalmers-revere/opendlv) for self-driving vehicles. 


The basic templete for the code is available at \
[opendlv-sim-motor-kiwi](https://github.com/chalmers-revere/opendlv-sim-motor-kiwi) \
[opendlv-logic-test-kiwi](https://github.com/chalmers-revere/opendlv-logic-test-kiwi)


# How to get the program running:

Pre-requisite:
1. Docker must be installed.
2. Data is processed using MATLAB but you can change it to Python or C++.

################################### Part A: ##############################################

This is to remove any images and containers that can create a conflict with the program.

#Caution: This will wipe out all the containers so do it only if it is necessary.

1. Stop all running containers using:\
docker stop $(docker ps -a -q)

2. Clear all containers:\
docker rm $(docker ps -a -q)

3. Remove all images:\
docker rmi -f $(docker images -a -q)


################################### Part B: ##############################################

This is to build the docker from the files.

1. Open a terminal in the folder "opendlv-logic-test-kiwi-master" and run the following command:\
   docker build -f Dockerfile.amd64 -t chalmersrevere/opendlv-logic-test-kiwi-amd64:v0.0.6 .

2. Open a terminal in the folder "opendlv-sim-motor-kiwi-master" and run the following command:\
   docker build -f Dockerfile.amd64 -t chalmersrevere/opendlv-sim-motor-kiwi-amd64:v0.0.6 .


################################### Part C: ##############################################

This part is to run the file and record the output.

1. Open a terminal in the main folder and run the following code to start the interface.\
   docker-compose -f interface-kiwi.yml up

2. Open a browser and enter http://localhost:8081/

3. Launch another terminal in the same main folder and run the following code to simulate the kiwi.\
docker-compose -f simulate-kiwi.yml up

4. Use the record button to record and the file button to view the recorded file


################################### Part D: ##############################################

Visualising the path followed by the robot.

1. Download the .CSV file of the recording.

2. Unzip and copy the .CSV file onto the main folder

3. Run the the code in the Matlab script "Task_c.m"


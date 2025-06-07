# Line-Follower Robot
A line following robot car with Raspberry pi board. This project involved a real time system developed using Linux and C programming language. Line detection was implemented using Infra-red sensors and object detection using Infra-red and ultrasonic sensors. 
 
## Design Pattern
* Line Detection - Two Infra-Red sensors placed underneath the car were  detect black line to which the robot car follows. 
* Object Detection - Two Infra-Red sensors placed on the two sides front of the car  detect object at a short-range.
* Control - Drives the robot if  the  black  line is detected. Robots finds the black line if it losses it. Robot stops if an object is detected within a specified range.

## Tool Stack
* The C Programming Language - The software development was implemented  using C.
* Linux OS - Linux was the base operating system for real-time design.

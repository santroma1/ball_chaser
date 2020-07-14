# ball_chaser

## ROS package with 2 nodes, a differential driver node, and an image analyzer

This package works in collaborations with the my_robot package.

In this package, 2 nodes are contained. The drive_bot node is in charge of publishing moving commands to the Robot, and the process_image node is in charge of identifying the position of a white ball that is set in the my_robot world.

A service is provided, in order to publish to the cmd_vel topic that moves the robot. 

### Installation

Full ROS desktop installation is required.


Clone to your catkin_ws/src folder and compile for it to run.

#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

class DriveBot
{
    public:
        DriveBot()
        {
            //Publisher is defined to publish TWIST msg to topic, queue size is 10
            motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

            //Service created
            service = n.advertiseService("/ball_chaser/command_robot", &DriveBot::handle_drive_request, this);

        }

        // TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
        // This function should publish the requested linear x and angular velocities to the robot wheel joints
        // After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
        bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
        {
            geometry_msgs::Twist motor_command;

            //Set the values you recieved
            motor_command.linear.x = req.linear_x;
            motor_command.angular.z = req.angular_z;

            //Publish
            motor_command_publisher.publish(motor_command);


            res.msg_feedback = "linear_x: " +
            std::to_string(req.linear_x) + " ,angular_z: " +
            std::to_string(req.angular_z)  + "\n";

            ROS_INFO_STREAM(res.msg_feedback);
            return true;
        }

    private:
        ros::NodeHandle n;
        ros::Publisher motor_command_publisher;
        ros::ServiceServer service;
};

int main(int argc, char** argv)
{

    //initalize the node
    ros::init(argc, argv, "drive_bot");

    //Instantiate object

    DriveBot driveBot;

    ROS_INFO("ROBOT READY");


    //LOOP
    ros::spin();

    return 0;

}

#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <ros/console.h>
#include <string.h>


class ProcessImage
{
public:
    ProcessImage()
    {
        client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

        image_sub = n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);

    }

    // This function calls the command_robot service to drive the robot in the specified direction
    void drive_robot(float lin_x, float ang_z)
    {
        // TODO: Request a service and pass the velocities to it to drive the robot
        ball_chaser::DriveToTarget srv;
        srv.request.linear_x = lin_x;
        srv.request.angular_z = ang_z;

        if (!client.call(srv))
            ROS_ERROR("Failed to call service safe_move");

    }

    void process_image_callback(const sensor_msgs::Image img)
    {

        int white_pixel = 255;
        int left_counter = 0;
        int middle_counter = 0;
        int right_counter = 0;
        int total_counter = 0;

        // TODO: Loop through each pixel in the image and check if there's a bright white one
        for(int i = 0; i<img.height*img.step;i+=3)
        {

            if(img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel)
            {
                // Then, identify if this pixel falls in the left, mid, or right side of the image

                int position = i%img.step;
                total_counter++;
                if(position < img.step/3)
                {
                    left_counter++;
                }
                else if(position >= img.step/3 && position<((img.step*2)/3))
                {
                    middle_counter++;
                }else
                {
                    right_counter++;
                 }

            }
            // Depending on the white ball position, call the drive_bot function and pass velocities to it



            // Request a stop when there's no white ball seen by the camera

        }
        if(left_counter> middle_counter && left_counter >right_counter)
        {
            drive_robot(0.2, 0.5);
        }else if(middle_counter > left_counter && middle_counter > right_counter)
        {
            drive_robot(0.2, 0.0);
        }else if(right_counter > middle_counter && right_counter > left_counter)
        {
            drive_robot(0.2, -0.5);
        }

        if(total_counter > (img.height*img.step)/12)
        {
            drive_robot(0.0, 0.0);
        }
        if(left_counter == 0 && right_counter == 0 && middle_counter == 0)
        {
            drive_robot(0.0, 0.0);
        }


    }

private:
    ros::NodeHandle n;
    ros::Subscriber image_sub;
    ros::ServiceClient client;

};

int main(int argc, char** argv)
{

    //initialize node
    ros::init(argc, argv, "process_image");

    ProcessImage process_image;
    ROS_INFO("CAMERA READY");


    //HANDLE ROS COMmunication events
    ros::spin();

    return 0;


}

/*
 * calibrate_linear.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: fan
 */

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv) {
	ros::init(argc,argv,"calibrate_linear");

	ros::NodeHandle n;
	ros::Publisher cmd_vel_pub=n.advertise<geometry_msgs::Twist>("cmd_vel",1000);
	ros::Rate loop_rate(1000);

	geometry_msgs::Twist cmd_vel;
	cmd_vel.linear.x=0;
	cmd_vel.linear.y=0;
	cmd_vel.linear.z=0;
	cmd_vel.angular.x=0;
	cmd_vel.angular.y=0;
	cmd_vel.angular.z=0;
//	ros::Duration d(0.01);
	ros::Time start_time,current_time;
	double T;
	start_time=ros::Time::now();
	ROS_INFO("Robot Calibrate Linear Start...");

	while(ros::ok())
        {
		current_time=ros::Time::now();
		if((current_time-start_time).toSec()<=20)
                {
			cmd_vel.linear.x=0.2;
			T=(current_time-start_time).toSec();
		}
		else 
                {
	           cmd_vel.linear.x=0;
		}
		ROS_INFO("Stop Using Time %f second.",T);
		cmd_vel_pub.publish(cmd_vel);
		loop_rate.sleep();
	}

	return 0;
}




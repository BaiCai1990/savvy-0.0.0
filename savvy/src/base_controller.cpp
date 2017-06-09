/*************************************************************************
> File Name: base_controller.cpp
> Function: 接收cmd_vel话题消息，将消息指令下发底盘控制器，并读回编码器数据
> Author: Lv Chaoshun
> Mail:   lvchaoshun@outlook.com
> Created Time: 2017年5月12日
************************************************************************/

#include "ros/ros.h"
#include "savvy/fourvel.h"
#include "savvy/ultrasonicStamped.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point32.h"
#include <cstdlib>
#include <math.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "SocketClient.h"
#include "savvyParameter.h"

// 串口服务器地址
const char* s_ip = "192.168.0.253";
// 串口1-4对应端口
const int port1 = 1031; 
const int port2 = 1032; 
const int port3 = 1033; 
const int port4 = 1034; 

// 速度指令初始化
static float Vx = 0.0;
static float Vy = 0.0;
static float W = 0.0;

// 处理从 cmd_vel 话题接收到的消息
void callBack(const geometry_msgs::Twist &msg);

/***********************************主函数***********************************/
int main(int argc, char **argv)
{
    ros::init(argc, argv, "base_controller_node"); 

    ros::NodeHandle n;

    // 消息订阅器，订阅 cmd_vel 话题的消息
    ros::Subscriber sub = n.subscribe("cmd_vel", 10, callBack);

    // 消息发布器1，将四个电机实际速度数据发到 vel_real 话题
    ros::Publisher vel_real_pub = n.advertise<savvy::fourvel>("vel_real",10);

    // 消息发布器2，将里程计信息发布到 odom 话题
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom",10);
    
    // 消息发布器3，将超声波传感器数据发布到ultrasonic话题
    ros::Publisher ultra_pub = n.advertise<savvy::ultrasonicStamped>("ultrasonic",10);

    /******************************/
    ros::Publisher kf_angle_pub = n.advertise<geometry_msgs::Point32>("KF_TEST",10);
   
    // tf广播， 将tf变换广播出去
    tf::TransformBroadcaster tf_broadcaster;

    geometry_msgs::Vector3 msg_real_vel;
    savvy::fourvel msg_real_vel_temp;
    savvy::ultrasonicStamped msg_ultrasonic;

    // 时间变量
    ros::Time current_time, last_time;
    double dt = 0.0;

    // 机器人位置和速度变量
    double x = 0.0;
    double y = 0.0;
    double th = 0.0;
    
    // 指向串口1的socket对象
    ns_SerialServer::ControllerClient sock_port1(port1, s_ip);
    
    // 指向串口2的socket对象
    ns_SerialServer::CompassClient sock_port2(port2, s_ip);

    ros::Rate loop_rate(60);

    while(ros::ok())
    {
        current_time = ros::Time::now();
         
        dt = (current_time - last_time).toSec();
        last_time = ros::Time::now();
        
        sock_port1.sockConnect();
        sock_port2.sockConnect();
       
        // 发送V，告诉电机下一时刻的目标速度
        sock_port1.write_Data(Vx, Vy, W); 

        // 通过串口1读四个电机的编码器数据
        sock_port1.read_Data(); 
        // 通过串口2读电子罗盘方位角!!!由于电磁干扰原因，并未使用该数据!!!
        int current_angle = sock_port2.get_Raw_Angle();        
        
        short encoder[4];
	unsigned short ultrasonic_data[6];
        sock_port1.get_Encoder(encoder);
	sock_port1.get_Ultrasonic(ultrasonic_data);

	//根据运动学模型逆推出笛卡尔空间速度
        msg_real_vel.x =  (encoder[1] - encoder[0]) / (2*K); 
        msg_real_vel.y =  (encoder[0] - encoder[2] ) / (2*K); 
        msg_real_vel.z = (encoder[0]  + encoder[3]) / (0.9*K); 
            
        msg_real_vel_temp.n1 = encoder[0];
        msg_real_vel_temp.n2 = encoder[1];
        msg_real_vel_temp.n3 = encoder[2];
        msg_real_vel_temp.n4 = encoder[3];
          
	//根据四个编码器推算出的速度，发到 vel_real 话题
        vel_real_pub.publish(msg_real_vel_temp);
	
	msg_ultrasonic.header.stamp = current_time;
	msg_ultrasonic.d1 = ultrasonic_data[0];
	msg_ultrasonic.d2 = ultrasonic_data[1];
	msg_ultrasonic.d3 = ultrasonic_data[2];
	msg_ultrasonic.d4 = ultrasonic_data[3];
	msg_ultrasonic.d5 = ultrasonic_data[4];
	msg_ultrasonic.d6 = ultrasonic_data[5];
	
	// 将六个超声波传感器的数据发到 ultrasonic 话题
	ultra_pub.publish(msg_ultrasonic);
	
        // 断开socket 连接
        sock_port1.close_Socket();
        sock_port2.close_Socket();

        double delta_x = (msg_real_vel.x * cos(th) - msg_real_vel.y * sin(th)) * dt;
        double delta_y = (msg_real_vel.x * sin(th) + msg_real_vel.y * cos(th)) * dt;
        double delta_th = msg_real_vel.z * dt;
        
        x += delta_x * odom_linear_scale_correction;
        y += delta_y * odom_linear_scale_correction;
        th += delta_th * odom_angular_scale_correction;
 
        // 创建一个四元数变量
        geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

        geometry_msgs::TransformStamped tf_trans;
        tf_trans.header.stamp = current_time;
        tf_trans.header.frame_id = "odom";
        tf_trans.child_frame_id = "base_link";
        
        tf_trans.transform.translation.x = x ;
        tf_trans.transform.translation.y = y;
        tf_trans.transform.translation.z = 0.0;
        tf_trans.transform.rotation = odom_quat;

        // 将tf变换广播出去
        tf_broadcaster.sendTransform(tf_trans);

        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";

        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = odom_quat;

        odom.twist.twist.linear.x = msg_real_vel.x;
        odom.twist.twist.linear.y = msg_real_vel.y;
        odom.twist.twist.angular.z = msg_real_vel.z;

        // 将里程计消息广播出去
        odom_pub.publish(odom);
        ROS_DEBUG("Odometry:: Position: %f, %f, %f",odom.pose.pose.position.x, odom.pose.pose.position.y,odom.pose.pose.position.z);
        
        ros::spinOnce();
        
        loop_rate.sleep();
    }

    return 0;
}

void callBack(const geometry_msgs::Twist &msg)
{
    Vx = msg.linear.x;
    Vy = msg.linear.y;
    W = msg.angular.z;
}






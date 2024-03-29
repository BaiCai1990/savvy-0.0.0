/*************************************************************************
	> File Name: savvy_teleop_node.cpp
	> Auther: Lv Chaoshun
	> Function: 通过键盘控制机器人的运动
	> Created Time: 2016年12月15日
 ************************************************************************/

#include <termios.h>  
#include <signal.h>  
#include <math.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/poll.h>  
  
#include <boost/thread/thread.hpp>  
#include <ros/ros.h>  
#include <geometry_msgs/Vector3.h>  
#include <geometry_msgs/Twist.h>  
  
#define KEYCODE_W 0x77  
#define KEYCODE_A 0x61  
#define KEYCODE_S 0x73  
#define KEYCODE_D 0x64

#define KEYCODE_SPACE 0x20  

#define KEYCODE_R 0x72  //R键旋转

#define KEYCODE_Q 0x71  //Q键改变旋转方向 
  
#define KEYCODE_R_CAP 0x52  
#define KEYCODE_A_CAP 0x41  
#define KEYCODE_D_CAP 0x44  
#define KEYCODE_S_CAP 0x53  
#define KEYCODE_W_CAP 0x57  

bool dirty = false;  
float speed_x = 0;  
float speed_y = 0; 
float turn = 0;  

  
class SmartCarKeyboardTeleopNode  
{  
    private:  
        double walk_vel_;  
        double run_vel_;  
        double yaw_rate_;  
        double yaw_rate_run_;  
          
        geometry_msgs::Twist cmdvel_;  
        ros::NodeHandle n_;  
        ros::Publisher pub_;  
  
    public: 
        SmartCarKeyboardTeleopNode()  
        {  
            pub_ = n_.advertise<geometry_msgs::Twist>("cmd_vel", 10);  
              
            ros::NodeHandle n_private("~");  
            n_private.param("walk_vel", walk_vel_, 0.1);  
            n_private.param("run_vel", run_vel_, 0.2);  
            n_private.param("yaw_rate", yaw_rate_, 0.1);  
            n_private.param("yaw_rate_run", yaw_rate_run_, 0.2);  
        }  
          
        ~SmartCarKeyboardTeleopNode() { }  
        void keyboardLoop();  
          
        void stopRobot()  
        {  
            cmdvel_.linear.x = 0.0;  
            cmdvel_.linear.y = 0.0;  
            cmdvel_.linear.z = 0.0;  
            cmdvel_.angular.x = 0.0;  
            cmdvel_.angular.y = 0.0;  
            cmdvel_.angular.z = 0.0;  
            pub_.publish(cmdvel_);  
        }  
};  
  
SmartCarKeyboardTeleopNode* tbk;  
int kfd = 0;  
struct termios cooked, raw;  
bool done;  
  
int main(int argc, char** argv)  
{  
    ros::init(argc,argv,"tbk", ros::init_options::AnonymousName | ros::init_options::NoSigintHandler);  
    SmartCarKeyboardTeleopNode tbk;  
      
    boost::thread t = boost::thread(boost::bind(&SmartCarKeyboardTeleopNode::keyboardLoop, &tbk));  
      
    ros::spin();  
      
    t.interrupt();  
    t.join();  
    tcsetattr(kfd, TCSANOW, &cooked);  
      
    return(0);  
}  
  
void SmartCarKeyboardTeleopNode::keyboardLoop()  
{  
    char c;  
    double max_tv = walk_vel_;  
    double max_rv = yaw_rate_;  
      
    // get the console in raw mode  
    tcgetattr(kfd, &cooked);  
    memcpy(&raw, &cooked, sizeof(struct termios));  
    raw.c_lflag &=~ (ICANON | ECHO);  
    raw.c_cc[VEOL] = 1;  
    raw.c_cc[VEOF] = 2;  
    tcsetattr(kfd, TCSANOW, &raw);  
      
    puts("Reading from keyboard");  
    puts("Use WASD keys to control the robot");  
    puts("Press Shift to move faster");  
      
    struct pollfd ufd;  
    ufd.fd = kfd;  
    ufd.events = POLLIN;  
      
    for(;;)  
    {  
        boost::this_thread::interruption_point();  
          
        // get the next event from the keyboard  
        int num;  
          
        if ((num = poll(&ufd, 1, 250)) < 0)  
        {  
            perror("poll():");  
            return;  
        }  
        else if(num > 0)  
        {  
            if(read(kfd, &c, 1) < 0)  
            {  
                perror("read():");  
                return;  
            }  
        }  
        else  
        {  
            if (dirty == true)  
            {  
                dirty = false;  
            }  
              
            continue;  
        }  
          
        switch(c)  
        {  
            case KEYCODE_W:  
                max_tv = walk_vel_;  
                speed_x += 0.05;  
                turn = 0;  
                dirty = false;  
                break;  
            case KEYCODE_S:  
                max_tv = walk_vel_;  
                speed_x -= 0.05;  
                turn = 0;  
                dirty = false;  
                break;  
            case KEYCODE_A:  
                max_rv = yaw_rate_;  
                speed_y += 0.05;
                turn = 0;  
                dirty = false;  
                break;  
            case KEYCODE_D:  
                max_rv = yaw_rate_;  
                speed_y -= 0.05; 
                turn = 0;  
                dirty = false;  
                break; 
            case KEYCODE_R:  
                max_rv = yaw_rate_;  
                speed_x = 0;
                speed_y = 0; 
                turn += 0.05;  
                dirty = false;  
                break; 
            case KEYCODE_R_CAP:  
                max_rv = yaw_rate_;  
                speed_x = 0;
                speed_y = 0; 
                turn += 0.1;  
                dirty = false;  
                break; 
            case KEYCODE_Q:  
                max_rv = yaw_rate_;  
                speed_x = 0;
                speed_y = 0; 
                turn -= 0.05;  
                dirty = false;  
                break;             
            case KEYCODE_W_CAP:  
                max_tv = run_vel_;  
                speed_x += 0.1;  
                turn = 0;  
                dirty = false;  
                break;
            case KEYCODE_S_CAP:  
                max_tv = run_vel_;  
                speed_x -= 0.1;
                turn = 0;  
                dirty = false;  
                break;  
            case KEYCODE_A_CAP:  
                max_rv = yaw_rate_run_;  
                speed_y += 0.1;  
                turn = 0;  
                dirty = false;  
                break;  
            case KEYCODE_D_CAP:  
                max_rv = yaw_rate_run_;  
                speed_y -= 0.1;  
                turn = 0;
                dirty = false;
                break; 
           case KEYCODE_SPACE:
                max_tv = 0;
                max_rv = 0;
                speed_x = 0;
                speed_y = 0;
                turn = 0;
                dirty = true;               
            default:  
                max_tv = walk_vel_;  
                max_rv = yaw_rate_;   
                dirty = false;  
        }  

        cmdvel_.linear.x = speed_x * max_tv;  
        cmdvel_.linear.y = speed_y * max_tv;  
        cmdvel_.angular.z = turn * max_rv; 

        pub_.publish(cmdvel_);  
    }  
}

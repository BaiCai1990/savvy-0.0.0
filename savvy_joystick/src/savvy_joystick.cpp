    #include <ros/ros.h>  
    #include <sensor_msgs/Joy.h>  
    #include <geometry_msgs/Twist.h>  
    #include <signal.h>  
    #include <termios.h>  
    #include <stdio.h>  
    
    class TeleopTurtleJoyStick  
    { 
 
    public:  
      TeleopTurtleJoyStick();  
      void keyLoop();  
      void callBack(const sensor_msgs::Joy::ConstPtr& joy);  
      ros::Publisher twist_pub_;  
      ros::Subscriber twist_sub_;
      int but_0, but_1, but_2, but_3, but_7, axe_0, axe_2, axe_4, axe_3;
      double linear_, angular_, l_scale_, a_scale_, k_scale_; 
      
    private:  
      ros::NodeHandle nh_;  

    };  
      
    TeleopTurtleJoyStick::TeleopTurtleJoyStick():  
      linear_(0),  
      angular_(0),  
      l_scale_(2.0),  
      a_scale_(2.0),
      k_scale_(0.01),
      but_0(0),
      but_1(0),
      but_2(0),
      but_3(0),
      but_7(0),
      axe_0(0),
      axe_3(0),
      axe_4(0),
      axe_2(0)
    {  
      nh_.param("scale_angular", a_scale_, a_scale_);  
      nh_.param("scale_linear", l_scale_, l_scale_);  
      twist_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);  
      twist_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, &TeleopTurtleJoyStick::callBack, this);
    }
  
    void TeleopTurtleJoyStick::callBack(const sensor_msgs::Joy::ConstPtr& joy)  
    {  
        but_0 = joy->buttons[0];
        but_1 = joy->buttons[1];  
        but_2 = joy->buttons[2];  
        but_3 = joy->buttons[3];  
        axe_0 = joy->axes[0];
        axe_2 = joy->axes[2];
        axe_3 = joy->axes[3];
        axe_4 = joy->axes[4];
        but_7 = joy->buttons[7];       
    } 

    int kfd = 0;
  
    struct termios cooked, raw;  
      
    int main(int argc, char** argv)  
    {  
      ros::init(argc, argv, "savvy_joystick"); 
       
      TeleopTurtleJoyStick teleop_turtle;
       
      geometry_msgs::Twist twist;
      
      ros::Rate r(40);
      
      while(ros::ok())
      { 
        if(teleop_turtle.but_7==0)
       {  
          if(teleop_turtle.but_0==1||teleop_turtle.but_2==1)
          {
            twist.linear.x = (teleop_turtle.but_0-teleop_turtle.but_2)*teleop_turtle.l_scale_;
          }
          if(teleop_turtle.but_1==1||teleop_turtle.but_3==1)
          {
            twist.linear.y = (teleop_turtle.but_3-teleop_turtle.but_1)*teleop_turtle.l_scale_;
          }
          if(teleop_turtle.axe_4==1||teleop_turtle.axe_4==-1)
          {
            twist.angular.z = teleop_turtle.axe_4*teleop_turtle.a_scale_; 
          }
	  if(teleop_turtle.axe_2==-1||teleop_turtle.axe_2==1)
	  {
	    twist.linear.x +=0.001*teleop_turtle.axe_2;
	  }
	  if(teleop_turtle.axe_3==-1||teleop_turtle.axe_3==1)
	  {
	    twist.linear.y+=0.001*teleop_turtle.axe_3;
	  }
	  if(teleop_turtle.axe_0==1||teleop_turtle.axe_0==-1)
	  {
	    twist.angular.z+=0.001*teleop_turtle.axe_0;
	  }
	 
       }
        else
       {
          twist.linear.x = 0;
          twist.linear.y = 0;
          twist.angular.z = 0;
       }
       
	teleop_turtle.twist_pub_.publish(twist);
	ros::spinOnce();
	r.sleep();
      }
      
    }  








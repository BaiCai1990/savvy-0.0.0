/*************************************************************************
> File Name: SocketClient.h
>Function: 通过socket和串口服务器通信
> Auther :  Lv Chaoshun
> Mail:   lvchaoshun@outlook.com
> Completed Time: 2017.5.12
************************************************************************/

#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <stdio.h>  
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/un.h>  
#include <arpa/inet.h>  
#include <netinet/in.h> 
#include <boost/concept_check.hpp>

namespace ns_SerialServer
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               基类：实现和串口服务器的通信
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SocketClient
{
private:
  const int port;                               // 端口号，根据端口号确定读写哪个串口
  const char* ip;                              // 串口服务器IP地址，目前为 192.168.1.253
  struct sockaddr_in addr;   // 参数结构体
  socklen_t addr_len;            // sockaddr结构体的字节长度
  int serial_socket;
  
public:
  SocketClient();
  SocketClient(const int arg_port, const char* arg_ip);
  
  void sockConnect();            // 创建socket连接
  int write_Socket(char* buf, int size);       // 向串口服务器写指令 
  int read_Socket(char* buf,int size);         // 读来自串口服务器的数据
  void close_Socket();                                  // 关闭socket连接
  
  virtual ~SocketClient() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               派生类1：通过串口服务器和STM32通信
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ControllerClient : public SocketClient
{
private:
    // Vx Vy W 速度数据
    union floatdata
    {
        float f_data[3];
        unsigned char c_data[12];
    }vel_data;
    
    // 编码器数据
    union encoder_data
    {
        char data[8]; 
        struct encoder_val
        {
            short encoder_n1;
            short encoder_n2;
            short encoder_n3;
            short encoder_n4;
        }speed;
    }encoder_speed;
    
    // 1-6号超声波数据
    union ultrasonic_data
    {
      char data[12];
      struct distance
      {
	unsigned short d1;
	unsigned short d2;
	unsigned short d3;
	unsigned short d4;
	unsigned short d5;
	unsigned short d6;
      }value;
    }ultrasonic_distance;
    
public:
    ControllerClient(const int arg_port, const char* arg_ip);
    int write_Data(float vx, float vy, float w);                           // 写速度指令
    int read_Data();                                                                    // 读编码器数据
    void get_Encoder(short* encoder) const;                         // 将四个编码器的数据存放在encoder指针指向的数组里
    void get_Ultrasonic(unsigned short* ultra) const;           // 将六个超声波传感器的数据存放到ultra指针指向的数组
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               派生类2：通过串口服务器和电子罗盘通信
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CompassClient : public SocketClient
{
private:
    int angle;  // 罗盘的方位角
public:
    CompassClient(const int arg_port, const char* arg_ip); 
    
    // 读取罗盘的方位角
    int get_Angle();                         
    
    // 校准罗盘周围的磁场环境(需要40s的时间，40s的时间内均匀地将罗盘旋转360度)，然后保存
    // 成功返回1, 失败返回0
    bool calibrate();
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               派生类3：编写自己的串口数据采集类
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // SOCKETCLIENT_H











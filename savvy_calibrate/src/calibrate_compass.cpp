/*************************************************************************
> File Name: calibrate.h
>Function:  校准电子罗盘DCM230B
> Auther :  Lv Chaoshun
> Mail:   lvchaoshun@outlook.com
> Completed Time: 2017.5.12
************************************************************************/

#include "SocketClient.h"

int main()
{
    // 串口服务器地址
    const char* s_ip = "192.168.0.253";
    const int port2 = 1032;
    ns_SerialServer::CompassClient sock_port2(port2, s_ip);
    
    sock_port2.sockConnect();
    
    // 开始校准
    sock_port2.calibrate();
}
#include "SocketClient.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               基类 SocketClient 的方法实现
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 构造函数，初始化基类和派生类
ns_SerialServer::SocketClient::SocketClient(const int arg_port, const char* arg_ip):port(arg_port),ip(arg_ip)
{
    addr.sin_family = AF_INET;   
    addr.sin_port = htons(port);     
    addr.sin_addr.s_addr = inet_addr(ip);        // inet_addr函数将用点分十进制字符串表示的IPv4地址转化为用网络   
    // 字节序整数表示的IPv4地址 
    addr_len = sizeof(addr);
}

// 创建socket连接
void ns_SerialServer::SocketClient::sockConnect()
{
    if( (serial_socket = socket(AF_INET, SOCK_STREAM, 0) )< 0 )
    {
        perror("socket"); 
    }
    if(connect(serial_socket, (struct sockaddr*)&addr, addr_len) == -1)
    {  
        perror("connect");  
    } 
}

// 下发指令 
int ns_SerialServer::SocketClient::write_Socket(char* buf, int size)
{
    return write(serial_socket, buf, size);   //发送数据
}

// 读数据
int ns_SerialServer::SocketClient::read_Socket(char* buf,int size)
{
    return read(serial_socket, buf, size);
}  

// 断开socket连接
void ns_SerialServer::SocketClient::close_Socket()
{
    close(serial_socket);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               派生类1 ControllerClient 的方法实现
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 构造函数，初始化基类和派生类
ns_SerialServer::ControllerClient::ControllerClient(const int arg_port, const char* arg_ip):SocketClient(arg_port,arg_ip)
{
    vel_data.f_data[0] = 0;
    vel_data.f_data[1] = 0;
    vel_data.f_data[2] = 0;
    
    for(int i=0;i<8;i++)
    {
        encoder_speed.data[i] = 0;
    }
}

// 下发速度指令
int ns_SerialServer::ControllerClient::write_Data(float vx, float vy, float w)
{
    // 整理下发速度指令数据
    char sbuf[17];
    
    vel_data.f_data[0] = vx;
    vel_data.f_data[1] = vy;
    vel_data.f_data[2] = w;
    
    sbuf[0] = '\r';
    sbuf[1] = '\n';
    for(int i=2;i<14;i++)
    {
        sbuf[i] = vel_data.c_data[i-2];
    }
    sbuf[14] = '\n';
    sbuf[15] = '\r';
    sbuf[16] = '\0';
    
    // 写入数据
    int retv = write_Socket(sbuf, sizeof(sbuf)-1);
    return retv;
}

// 读编码器数据
int ns_SerialServer::ControllerClient::read_Data()
{
    bool flag_over = false;
    int i=0;
    int count = 0;
    int retv;
    char rbuf[1]; 
    
    //std::cout << "ready for receiving data..." << std::endl;
    
    while(flag_over == false)
    {
        retv = read_Socket(rbuf, 1);
        switch(count)
        {
            case 0:
                if(*rbuf == '\n') 
                {
                    count++;
                }  
                else
                    count = 0;
                break;
            case 1:
                if(*rbuf == '\r')
                {
                    i = 0;
                    count++;
                }
                else if(*rbuf == '\n');
                else
                    count = 0;
                break;
            case 2:
                if(i>=8)
                {
                    ultrasonic_distance.data[i-8] = *rbuf;
                    i++;
                }
                else
                {
                    encoder_speed.data[i] = *rbuf;
                    i++;
                }
                if(i>=24)
                {
                    i=0;
                    count++;
                }
                break;
            case 3: 
                if(*rbuf == '\r')
                    count++;
                else
                    count = 0;
                break;
            case 4:
                if(*rbuf == '\n') 
                {
                    //std::cout << "Receiving over!"<<std::endl;
                    flag_over = true;
                }
                count = 0;
                break;
            default:
                count = 0;
                break; 
        }
    }
    
    //std::cout << encoder_speed.speed.encoder_n1<<"    "
    //<< encoder_speed.speed.encoder_n2<<"    "
    //<< encoder_speed.speed.encoder_n3<<"    "
    //<< encoder_speed.speed.encoder_n4<<"    "
    //<< std::endl;
    
    return 1;
}

// 获取编码器数据
void ns_SerialServer::ControllerClient::get_Encoder(short* encoder) const
{
    encoder[0] = encoder_speed.speed.encoder_n1;
    encoder[1] = encoder_speed.speed.encoder_n2;
    encoder[2] = encoder_speed.speed.encoder_n3;
    encoder[3] = encoder_speed.speed.encoder_n4;
}

// 获取超声波传感器数据
void ns_SerialServer::ControllerClient::get_Ultrasonic(unsigned short* ultra) const
{
    ultra[0] = ultrasonic_distance.value.d1;
    ultra[1] = ultrasonic_distance.value.d2;
    ultra[2] = ultrasonic_distance.value.d3;
    ultra[3] = ultrasonic_distance.value.d4;
    ultra[4] = ultrasonic_distance.value.d5;
    ultra[5] = ultrasonic_distance.value.d6;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               派生类2 CompassClient 的方法实现
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 构造函数，初始化基类和派生类
ns_SerialServer::CompassClient::CompassClient(const int arg_port, const char* arg_ip):SocketClient(arg_port, arg_ip),angle(0)
{
    
}

// 读电子罗盘方位角数据
int ns_SerialServer::CompassClient::get_Raw_Angle()
{
    char wbuf[5] = {0x68, 0x04, 0x00, 0x03, 0x07};
    
    char rbuf[1];
    int count=0;
    int retv=0;
    bool flag_over = false;
    
    retv = write_Socket(wbuf,sizeof(wbuf)); //发送数据
    
    if(retv == -1)
    {
        printf("Port1 write failed!\n");
        perror("Port1 write failed!");
        return -1;
    }
    
    while(!flag_over)
    {
        retv = read_Socket(rbuf, 1);
        if(retv <=0)
        {
            return 0;
        }
        switch(count)
        {
            case 0:
                if(*rbuf == 0x68)
                    count++;
                else
                    count = 0;
                break;
            case 1:
                if(*rbuf == 0x06)
                    count++;
                else if(*rbuf == 0x68);
                else
                    count =0;
                break;
            case 2:
                if(*rbuf == 0x00)
                    count++;
                else
                    count=0;
                break;
            case 3:
                if(*rbuf == 0x53)
                    count++;
                else
                    count=0;
                break;
            case 4:
                angle = (*rbuf & 0x0f) * 100 ;
                count++;
                break;
            case 5:
                angle += (*rbuf & 0x0f) + ((*rbuf & 0xf0)>>4) *10; //按位与的优先级比较低
                flag_over = true;
                count=0;
                break;
            default:
                count = 0;
                break;
        }
    }
    
    //printf("角度=：%d\n", angle);
    
    return angle;
}

// 对罗盘角度进行卡尔曼滤波
float ns_SerialServer::CompassClient::get_Kf_Angle(float q_val, float r_val)
{
  // 先获取罗盘原始方位角
   kf_angle = get_Raw_Angle();
      
   Kalman_Filter kf;   
   kf.Set_KF_Pram(q_val, r_val);
   
   kf.kf_Process(kf_angle);
      
   return kf_angle;
}

// 罗盘周围磁的校准
bool ns_SerialServer::CompassClient::calibrate()
{
    char wbuf_cali[] = {0x68, 0x04, 0x00, 0x08, 0x0C};              // 校准命令
    char wbuf_save[]={0x68, 0x04, 0x00, 0x09, 0x0D};             // 保存校准命令
    
    int retv=0;
    bool flag_over=false;
    int count=0;
    char rbuf[1];
    
    retv = write_Socket(wbuf_cali,sizeof(wbuf_cali)); //发送数据
    
    if(retv == -1)
    {
        printf("下发校准命令失败!\n");
        perror("Port2 write failed!");
        return false;
    }
    
    while(!flag_over)
    {
        retv = read_Socket(rbuf, 1);
        switch(count)
        {
            case 0:
                if(*rbuf==0x68)
                    count++;
                else
                    count=0;
                break;
            case 1:
                if(*rbuf==0x05)
                    count++;
                else if(*rbuf==0x68);
                else
                    count=0;
                break;
            case 2:
                if(*rbuf==0x00)
                    count++;
                else
                    count=0;
                break;
            case 3:
                if(*rbuf==0x58)
                    count++;
                else
                    count = 0;
                break;
            case 4:
                if(*rbuf==0x00)
                {
                    std::cout<<"--------------------校准开始--------------------"<<std::endl;
                    std::cout<<"请在40s内旋转罗盘360度......"<<std::endl;
                    flag_over = true;
                    count = 0;
                }
                break;
            default:
                count=0;
                break;
        }
    }
    
    flag_over = false;
    
    sleep(40);                                                                       // 40s时间内将罗盘旋转360度
    
    retv = write_Socket(wbuf_save,sizeof(wbuf_save));   // 发送保准校准命令
    if(retv == -1)
    {
        printf("发送保存校准命令失败\n");
        perror("write failed!");
        return false;
    }
    
    while(!flag_over)
    {
        retv = read_Socket(rbuf, 1);
        switch(count)
        {
            case 0:
                if(*rbuf==0x68)
                    count++;
                else
                    count=0;
                break;
            case 1:
                if(*rbuf==0x05)
                    count++;
                else if(*rbuf==0x68);
                else
                    count=0;
                break;
            case 2:
                if(*rbuf==0x00)
                    count++;
                else
                    count=0;
            case 3:
                if(*rbuf==0x59)
                    count++;
                else
                    count = 0;
            case 4:
                if(*rbuf==0x00)
                {
                    std::cout<<"--------------------校准成功--------------------"<<std::endl;
                    flag_over = true;
                    return true;
                    count = 0;
                }
                break;
            default:
                count=0;
                break;
        }
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                               派生类3：编写自己的串口数据采集类方法
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



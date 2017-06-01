/*************************************************************************
> File Name: savvyParameter.h
> Function: 定义机器人本体参数
> Auther :  Lv Chaoshun
> Mail:   lvchaoshun@outlook.com
> Completed Time: 2017.5.12
************************************************************************/

const float L_1 = 0.284;    // 宽 
const float L_2 = 0.330;    // 长
const float R = 0.076;       // 轮子半径
const float pi = 3.14159;  // 圆周率

const int red_ratio = 33;   // 减速比

const float K = red_ratio*60/(2*pi*R);   // 正运动学系数

const float odom_linear_scale_correction = 0.947653;   // 直线tf标定修正参数
const float odom_angular_scale_correction = 0.642;  // 转向tf标定修正参数

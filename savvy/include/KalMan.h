/*
 * kalman.h
 *
 *  Created on: May 15, 2017
 *      Author: fan
 */

#ifndef PRISON_ROBOT_SRC_KALMAN_H_
#define PRISON_ROBOT_SRC_KALMAN_H_

class Kalman_Filter
{
public:
	Kalman_Filter();                  //卡尔曼滤波构造函数
	Kalman_Filter(float Q_Val, float R_Val, float P_pre_Val, float P_Val, float X_pre_Val, float X_kf_Val, float Kg_Val);
	~Kalman_Filter() {};            //卡尔曼滤波析构函数
	void Set_KF_Pram(float Q_Val, float R_Val); //卡尔曼滤波参数设置函数
	void Display_KF_Pram();
	void kf_Process(float &X);  //卡尔曼滤波函数
private:
	float Q;
	float R;
	float P_pre;     //P_pre是X(k|k - 1)对应的covariance
	float P;            //P是X(k|k-1)对应的covariance
	float X_pre;
	float X_kf;
	float Kg;
};

#endif /* PRISON_ROBOT_SRC_KALMAN_H_ */

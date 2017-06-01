/*
 * kalman.cpp
 *
 *  Created on: May 15, 2017
 *      Author: fan
 */

#include "KalMan.h"
#include <iostream>
using namespace std;
/*
卡尔曼实现函数
*/

Kalman_Filter::Kalman_Filter()
	:Q(0), R(0), P_pre(0), P(0), X_pre(0), X_kf(0), Kg(0)
{
}

// 
Kalman_Filter::Kalman_Filter(float Q_Val, float R_Val, float P_pre_Val, float P_Val, float X_pre_Val, float X_kf_Val, float Kg_Val)
	: Q(Q_Val), R(R_Val), P_pre(P_pre_Val), P(P_Val), X_pre(X_pre_Val), X_kf(X_kf_Val), Kg(Kg_Val)
{
}

// q 0.001  r 0.01 
void Kalman_Filter::Set_KF_Pram(float Q_Val, float R_Val)
{
	Q = Q_Val;
	R = R_Val;
// 	P_pre = P_pre_Val;
 	P = 1;
// 	X_pre = X_pre_Val;
// 	X_kf = X_kf_Val;
// 	Kg = Kg_Val;
}
void Kalman_Filter::Display_KF_Pram()
{
	cout << "卡尔曼滤波器参数：" << endl;
	cout << "    " << "Q: " << Q << "  " << ",R: " << R << "  " << ",P_pre: " << P_pre << endl;
	cout << "    " << ",P: " << P << "  " << ",X_Pre: " << X_pre << "  " << ",X_kf: " << X_kf << "  " << ",Kg" << Kg << endl;
}
void Kalman_Filter::kf_Process(float &X)
{
	X_pre = X_kf;
	P_pre = P + Q;
	Kg = P_pre / (P_pre + R);
	X_kf = X_pre + Kg*(X - X_pre);
	P = (1 - Kg)*P_pre;
}





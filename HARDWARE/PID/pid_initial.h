#ifndef _PID_INITIAL_H
#define _PID_INITIAL_H
/*****变量定义*****/
typedef struct Pid
{
	float set_velocity;
	float test_velocity;
	float Kp;
	float Ki;
	float Kd;
	float PidOut;	
}PidParameters;

/***函数声明****/
int PidMotorsets(void);
#endif
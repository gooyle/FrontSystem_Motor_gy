#ifndef _PID_INITIAL_H
#define _PID_INITIAL_H
#include "sys.h"

#define TIME_SAMPLEVALUE 10  //10ms
#define MOTOR1_ARRVALUE 1000-1 //����ֵΪ1000

/*****��������*****/
typedef struct Pid
{
	float set_velocity;
	float test_velocity;
	float Kp;
	float Ki;
	float Kd;
	float PidOut;	
}PidParameters;

/***��������****/
int PidMotorsets(void);
float Pid_SetsGet(uint16_t);
int Pid_PwmContrl(uint16_t Time_MotorSample);

#endif
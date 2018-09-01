#ifndef _PID_INITIAL_H
#define _PID_INITIAL_H
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
#endif
#include "pid_initial.h"
#include "main.h"

PidParameters PidMotor_1;

/*********��ʼ��pid��������************/
int PidMotorsets(void)
{
	
	PidMotor_1.set_velocity = 400; //���ؼ���Ϊ500������ȡ300
	return 0;
}
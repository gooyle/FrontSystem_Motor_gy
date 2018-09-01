#include "pid_initial.h"
#include "main.h"

PidParameters PidMotor_1;

/*********初始化pid基础参数************/
int PidMotorsets(void)
{
	
	PidMotor_1.set_velocity = 400; //满载计数为500，这里取300
	return 0;
}
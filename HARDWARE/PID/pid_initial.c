#include "pid_initial.h"
#include "encoder.h"
#include "main.h"
#include "math.h"
#include "delay.h"

PidParameters PidMotor_1;

/*********初始化pid基础参数************/
int PidMotorsets(void)
{
	PidMotor_1.Kp = 10;
	PidMotor_1.Ki = 0;
	//PidMotor_1.set_velocity ; 
	PidMotor_1.set_Encoders = 200;
	return 0;
    }

/**************************************************
*数值迭代、设定循环值以保证相同循环时间内CNT值保持不变
*输入：采样时间Time_MotorSample
*输出：Encoder_DifferValue
******************************************/
int Pid_SetsGet(void)
{
	int Encoder_DifferValue = 0;

	Encoder_DifferValue =  abs(TIM_GetCounter(TIM2) - Encoder_InitialValue);//这个是更新的变量
	TIM_SetCounter(TIM2,Encoder_InitialValue);//未防止数据溢出，重置CNT

	//delay_ms(TIME_SAMPLEVALUE);
	printf("%d\n",Encoder_DifferValue);
	return Encoder_DifferValue;
}

/**************************************************
*输入：采样周期Time_MotorSample
*输出：PWM——CCR的数值
*在中断中调用此函数
*************************************/
int Pid_PwmContrl(void)
{
	int CcrValue = 0;
	static float Et = 0;
	static float Sum_Et = 0;//Et:设定值与实际值的差，对应Kp
												//Sum_Et:离散化，对所有差值进行求和，对应Ki
	
	PidMotor_1.test_Encoders = Pid_SetsGet();//这里直接将测量的编码器差值赋给	
	Et = PidMotor_1.set_Encoders - PidMotor_1.test_Encoders;
	Sum_Et = Sum_Et + Et;
	CcrValue = PidMotor_1.Kp * Et + PidMotor_1.Ki * Sum_Et;

	if(CcrValue >= MOTOR1_ARRVALUE)
		return MOTOR1_ARRVALUE -1 ;
	else if(CcrValue <= MOTOR1_ARRVALUE)
		return 0 + 1;
	else
		return CcrValue;
}
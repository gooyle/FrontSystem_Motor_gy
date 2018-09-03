#include "pid_initial.h"
#include "encoder.h"
#include "main.h"
#include "math.h"
#include "delay.h"

PidParameters PidMotor_1;

/*********��ʼ��pid��������************/
int PidMotorsets(void)
{
	PidMotor_1.Kp = 10;
	PidMotor_1.Ki = 0;
	//PidMotor_1.set_velocity ; 
	PidMotor_1.set_Encoders = 200;
	return 0;
    }

/**************************************************
*��ֵ�������趨ѭ��ֵ�Ա�֤��ͬѭ��ʱ����CNTֵ���ֲ���
*���룺����ʱ��Time_MotorSample
*�����Encoder_DifferValue
******************************************/
int Pid_SetsGet(void)
{
	int Encoder_DifferValue = 0;

	Encoder_DifferValue =  abs(TIM_GetCounter(TIM2) - Encoder_InitialValue);//����Ǹ��µı���
	TIM_SetCounter(TIM2,Encoder_InitialValue);//δ��ֹ�������������CNT

	//delay_ms(TIME_SAMPLEVALUE);
	printf("%d\n",Encoder_DifferValue);
	return Encoder_DifferValue;
}

/**************************************************
*���룺��������Time_MotorSample
*�����PWM����CCR����ֵ
*���ж��е��ô˺���
*************************************/
int Pid_PwmContrl(void)
{
	int CcrValue = 0;
	static float Et = 0;
	static float Sum_Et = 0;//Et:�趨ֵ��ʵ��ֵ�Ĳ��ӦKp
												//Sum_Et:��ɢ���������в�ֵ������ͣ���ӦKi
	
	PidMotor_1.test_Encoders = Pid_SetsGet();//����ֱ�ӽ������ı�������ֵ����	
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
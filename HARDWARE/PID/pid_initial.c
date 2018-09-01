#include "pid_initial.h"
#include "encoder.h"
#include "main.h"
#include "math.h"
#include "delay.h"

PidParameters PidMotor_1;

/*********��ʼ��pid��������************/
int PidMotorsets(void)
{
	PidMotor_1.Kp = 52;
	PidMotor_1.Ki = 0.02;
	PidMotor_1.set_velocity = 400; //���ؼ���Ϊ500������ȡ300
	return 0;
}

/**************************************************
*��ֵ�������趨ѭ��ֵ�Ա�֤��ͬѭ��ʱ����CNTֵ���ֲ���
*���룺
*�����Encoder_DifferValue
******************************************/
float Pid_SetsGet(uint16_t Time_MotorSample)
{
	float Encoder_DifferValue = 0;

	Encoder_DifferValue = fabs( TIM_GetCounter(TIM2) - Encoder_InitialValue );//����Ǹ��µı���
	TIM_SetCounter(TIM2,Encoder_InitialValue);//δ��ֹ�������������CNT

	delay_ms(Time_MotorSample);
	printf("%f\n",Encoder_DifferValue);
	return Encoder_DifferValue;
}

/**************************************************
*���룺��������
*�����PWM����CCR����ֵ
*
*************************************/
int Pid_PwmContrl(uint16_t Time_MotorSample)
{
	int CcrValue = 0;
	static float Et = 0;
	static float Sum_Et = 0;//Et:�趨ֵ��ʵ��ֵ�Ĳ��ӦKp
												//Sum_Et:��ɢ���������в�ֵ������ͣ���ӦKi
	
	PidMotor_1.test_velocity = Pid_SetsGet(Time_MotorSample);//����ֱ�ӽ������ı�������ֵ���������ٶ�	
	Et = PidMotor_1.set_velocity - PidMotor_1.test_velocity;
	Sum_Et += Et;
	CcrValue =PidMotor_1.Kp * Et + PidMotor_1.Ki * Sum_Et;

	if(CcrValue >= MOTOR1_ARRVALUE)
		return MOTOR1_ARRVALUE;
	else if(CcrValue <= MOTOR1_ARRVALUE)
		return 0;
	else
		return CcrValue;
}
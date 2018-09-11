#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "pwm.h"
#include "pid_initial.h"
#include "encoder.h"
#include "rcc_config.h"
#include "stdio.h"


extern PidParameters PidMotor_1;
/***����sprintf������ɱ������**/
void LCD_Show(void)
{
	char tmp[5];
	char tmp1[5];
	sprintf(tmp,"%d",PidMotor_1.set_Encoders);
	LCD_ShowString(30,200,200,24,24,tmp);

	sprintf(tmp1,"%d",PidMotor_1.test_Encoders);
	LCD_ShowString(30,240,200,24,24,tmp1);
	}

int main(void)
{ 
	RCC_Config();//ʱ����������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	/************lcd��������*************/
 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	POINT_COLOR=BLACK;      //������ɫ����ɫ
	LCD_Clear(WHITE);	
	POINT_COLOR=BLACK;	  
	LCD_ShowString(30,40,280,24,24,"Embeded System ");	
	LCD_ShowString(30,80,280,24,24,"Course Design");	
	LCD_ShowString(30,120,210,24,24,"SX1715007 GuYu");	      					 
	LCD_ShowString(30,160,200,24,24,"2018-9-5");	
/*************���pid����**************/
	PidMotorsets();//���pid�����趨
	Gpio_Initial();//���GPIO����
	TIM14_PWM_Init(MOTOR1_ARRVALUE - 1,84 - 1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.
	Encoder_Init_TIM2();
	MotorUse(DIR_POS,ENABLE);
  	while(1) 
	{	
		PidMotor_1.PwmCcrvalue = Pid_PwmContrl();
 		delay_ms(TIME_SAMPLEVALUE);	
		LCD_Show();
	} 
	return 0;
}



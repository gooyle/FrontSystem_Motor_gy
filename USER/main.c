#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "pwm.h"
#include "pid_initial.h"
#include "encoder.h"


int main(void)
{ 
	uint16_t count = 0;
 	u8 x=0;
	u8 lcd_id[12];				//���LCD ID�ַ���
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
	LCD_ShowString(30,160,200,24,24,"2018-9-1");	
/*************���pid����**************/
	PidMotorsets();//��������趨
	Gpio_Initial();//���GPIO����
	TIM14_PWM_Init(MOTOR1_ARRVALUE - 1,84 - 1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ1000������PWMƵ��Ϊ 1M/1000=1Khz.
	Encoder_Init_TIM2();

  	while(1) 
	{		 
		EncoderEnable();
		MotorUse(DIR_NEG,ENABLE);
		delay_ms(TIME_SAMPLEVALUE);
	} 
}


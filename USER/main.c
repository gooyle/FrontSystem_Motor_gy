#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "pwm.h"
#include "pid_initial.h"

int main(void)
{ 
	uint16_t count = 0;
 	u8 x=0;
	u8 lcd_id[12];				//���LCD ID�ַ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200	
	PidMotorsets();//��������趨
	Gpio_Initial();//���GPIO����
	TIM14_PWM_Init(1000-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.

 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	POINT_COLOR=BLACK;      //������ɫ����ɫ
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
	LCD_Clear(WHITE);	
  	while(1) 
	{		 
		POINT_COLOR=BLACK;	  
		LCD_ShowString(30,40,280,24,24,"Embeded Course Design");	
		LCD_ShowString(30,85,210,24,24,"SX1715007 GuYu");	      					 
		LCD_ShowString(30,130,200,24,24,"2018-8-30");	
		MotorUse(DIR_NEG,ENABLE);
		delay_ms(20000);
	} 
}

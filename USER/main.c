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
	u8 lcd_id[12];				//存放LCD ID字符串
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200	
	PidMotorsets();//电机参数设定
	Gpio_Initial();//电机GPIO配置
	TIM14_PWM_Init(1000-1,84-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.

 	LCD_Init();           //初始化LCD FSMC接口
	POINT_COLOR=BLACK;      //画笔颜色：红色
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
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

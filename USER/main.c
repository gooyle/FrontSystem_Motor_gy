#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "pwm.h"
#include "pid_initial.h"
#include "encoder.h"

extern PidParameters PidMotor_1;

int main(void)
{ 
	u16 led0pwmval=0;    
	u8 dir=1;
	
	uint16_t count = 0;
 	u8 x=0;
	u8 lcd_id[12];				//存放LCD ID字符串
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	/************lcd参数设置*************/
// 	LCD_Init();           //初始化LCD FSMC接口
//	POINT_COLOR=BLACK;      //画笔颜色：红色
//	LCD_Clear(WHITE);	
//	POINT_COLOR=BLACK;	  
//	LCD_ShowString(30,40,280,24,24,"Embeded System ");	
//	LCD_ShowString(30,80,280,24,24,"Course Design");	
//	LCD_ShowString(30,120,210,24,24,"SX1715007 GuYu");	      					 
//	LCD_ShowString(30,160,200,24,24,"2018-9-1");	
/*************电机pid调试**************/
	PidMotorsets();//电机参数设定
	Gpio_Initial();//电机GPIO配置
	TIM14_PWM_Init(MOTOR1_ARRVALUE - 1,84 - 1);	//84M/84=1Mhz的计数频率,重装载值1000，所以PWM频率为 1M/1000=1Khz.
	Encoder_Init_TIM2();

  	while(1) 
	{		 
		EncoderEnable();
		MotorUse(DIR_POS,ENABLE);
		//PidMotor_1.PwmCcrvalue = Pid_PwmContrl();
 		delay_ms(10);	 
		if(dir)led0pwmval++;//dir==1 led0pwmval递增
		else led0pwmval--;	//dir==0 led0pwmval递减 
 		if(led0pwmval>300)dir=0;//led0pwmval到达300后，方向为递减
		if(led0pwmval==0)dir=1;	//led0pwmval递减到0后，方向改为递增
 
		TIM_SetCompare1(TIM14,led0pwmval);	//修改比较值，修改占空比
	} 
}



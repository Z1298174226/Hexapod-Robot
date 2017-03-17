/******************************************************************************
  * 文件路径  ：   User/main.c
  * 作者      ：   倾听枫声   QQ：1298174226
  * 固件库版本：   V3.5.0
  * 日期      ：   2015-8-2
  * 文件描述  ：   主函数
  ******************************************************************************/
/*******************main函数**********************/
#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "gui.h"
#include "delay.h"
#include "usart.h"
#include "ucos_ii.h"
#include "pwm.h"
#include "control.h"
#include "app_cfg.h"
#include "bsp.h"
#include "24l01.h"
#include "spi.h"
#include "TIM6.h"
#include "UltrasonicWave.h"
#include "mpu6050.h"
#include "bsp_i2c.h"
#include "kalman.h"

uint8_t buffercontorl[3];
uint8_t ch;
short Acel[3];
short Gyro[3];
short Temp;





void Communication_Decode(void)  
{	
	if(buffercontorl[0]==0x02)																 
	{
		switch(buffercontorl[1])
		{
			case 0x01:  Go_straight();     break;
			case 0x03:  Turn();     break;
			case 0x02:  Go_back();    break;  
			case 0x04:  Stamp();     break;
			case 0x05:  PWM_Init();     break;
			case 0x06:  Action_Init(20);	   break;
		
			default: break;
		}	
	}
		else if(buffercontorl[0]==0x01)
	{
		switch(buffercontorl[1])
		{
		case 0x01:
		 if(buffercontorl[2]>35&&buffercontorl[2]<181)
			 TIM1->CCR1 = buffercontorl[2];	
		break; 
		case 0x02:
		 if(buffercontorl[2]>35&&buffercontorl[2]<181)
			 TIM1->CCR2 = buffercontorl[2];	
	    break; 
        case 0x03:
		 if(buffercontorl[2]>35&&buffercontorl[2]<181)
			 TIM1->CCR3 = buffercontorl[2];	
	    break; 
		case 0x04:
		 if(buffercontorl[2]>35&&buffercontorl[2]<181)
			 TIM1->CCR4 = buffercontorl[2];	
	    break;
		case 0x05:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM2->CCR3 = buffercontorl[2];	
	    break;
		case 0x06:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM2->CCR4 = buffercontorl[2];	
	    break;
		case 0x07:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM3->CCR1 = buffercontorl[2];	
	    break;
		case 0x08:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM3->CCR2 = buffercontorl[2];	
     	break;
		case 0x09:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM3->CCR3 = buffercontorl[2];	
	    break;
		case 0x0A:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM3->CCR4 = buffercontorl[2];	
    	break;	
		case 0x0B:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM4->CCR1 = buffercontorl[2];	
    	break;
		case 0x0C:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM4->CCR2 = buffercontorl[2];	
	    break;
		case 0x0D:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM4->CCR3 = buffercontorl[2];	
	    break;
		case 0x0E:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM4->CCR4 = buffercontorl[2];	
	    break;
	    case 0x0F:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM5->CCR1 = buffercontorl[2];	
     	break;
		case 0x10:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM5->CCR2 = buffercontorl[2];	
     	break;
		case 0x11:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM5->CCR3 = buffercontorl[2];	
	    break;
		case 0x12:
		 if(buffercontorl[2]>36&&buffercontorl[2]<180)
			 TIM5->CCR4 = buffercontorl[2];	
	    break;
		default:	break;
	  }
	 }
	
}
	


int main(void)
{
  
    

   	SysTick_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
 /******************MPU6050初始化***************************/
	//I2C初始化
	I2C_EE_Init();
	//MPU6050初始化
	MPU6050_Init();

    TIM_Init();

  /***************超声波初始化*******************************/
	TIM6_Configuration();	  //超声波
	TIM6_NVIC_Configuration();
	UltrasonicWave_Configuration();	   //超声波
	USART1_Config();
    NVIC_Configuration();


   /****************卡尔曼定时7初始化**************************/
    TIM7_Configuration();
    TIM7_NVIC_Configuration();

 /*********************舵机初始化****************************/


	PWM_Init();
	while(1)
	{
	   
//	    printf("\r\nx轴角度： %f      \r\ny轴加速度：	%f\n	",Angle,Gyro_y);
		delay_ms(1000);
  
	}
	

 
	
//	Go_straight();
	
//	Action_Init();
 //   Go_straight();
   

}

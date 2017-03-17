 /******************************************************************************
  * 文件路径  ：   User/main.c
  * 作者      ：   倾听枫声   QQ：1298174226
  * 固件库版本：   V3.5.0
  * 日期      ：   2015-8-2
  * 文件描述  ：   主函数
  ******************************************************************************/
/*******************main函数**********************/

#include "key.h"
#include "delay.h"


void KEY_Init(void) //IO初始化
{ 
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO结构体定义
	//初始化KEY0-->GPIOA.13,KEY1-->GPIOA.15  输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
			
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 /*
	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
*/		 

}
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//按键按松开标志	
 
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)
		{
			return 1;
		}
		else if(KEY1==0)
		{ 
			return 2;
		}
		else if(KEY2==0)
		{
			return 3;
		}
	}else if(KEY0==1&&KEY1==1&&KEY2==1)key_up=1; 	    
 
	return 0;// 无按键按下
}

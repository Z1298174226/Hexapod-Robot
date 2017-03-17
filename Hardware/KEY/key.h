/*----------------------------------------------------------------
 * 文件名称： KEY驱动程序  
 *          
 * 文件说明： KEY分别接PA1至PA3 
 *      	  按键是共阴接法
 *		
 *		
 * 创建标识：416实验室  曹毅超
 * 创建时间：2013.4.14   
**----------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
	 

#define KEY0 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) //PA13
#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)	//PA14 
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)	//PA15
	 
void KEY_Init(void);//IO初始化
u8   KEY_Scan(void);  //按键扫描函数					    
#endif

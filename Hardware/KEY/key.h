/*----------------------------------------------------------------
 * �ļ����ƣ� KEY��������  
 *          
 * �ļ�˵���� KEY�ֱ��PA1��PA3 
 *      	  �����ǹ����ӷ�
 *		
 *		
 * ������ʶ��416ʵ����  ���㳬
 * ����ʱ�䣺2013.4.14   
**----------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
	 

#define KEY0 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) //PA13
#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)	//PA14 
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)	//PA15
	 
void KEY_Init(void);//IO��ʼ��
u8   KEY_Scan(void);  //����ɨ�躯��					    
#endif

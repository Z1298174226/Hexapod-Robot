#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"                                                                         //����ͷ�ļ�

#define On      1                                                                               //����LED��
#define OFF     0                                                                               //����LED��
#define LED0(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_12)):(GPIO_ResetBits(GPIOD,GPIO_Pin_12)))       //����LED0�Ŀ��ؿ���
#define LED1(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_13)):(GPIO_ResetBits(GPIOD,GPIO_Pin_13)))         //����LED1�Ŀ��ؿ���
#define LED2(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_14)):(GPIO_ResetBits(GPIOD,GPIO_Pin_14)))       //����LED2�Ŀ��ؿ���
#define LED3(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_15)):(GPIO_ResetBits(GPIOD,GPIO_Pin_15)))         //����LED3�Ŀ��ؿ���

void LED_Init(void);
#endif

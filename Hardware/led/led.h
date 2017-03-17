#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"                                                                         //包含头文件

#define On      1                                                                               //定义LED开
#define OFF     0                                                                               //定义LED关
#define LED0(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_12)):(GPIO_ResetBits(GPIOD,GPIO_Pin_12)))       //定义LED0的开关控制
#define LED1(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_13)):(GPIO_ResetBits(GPIOD,GPIO_Pin_13)))         //定义LED1的开关控制
#define LED2(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_14)):(GPIO_ResetBits(GPIOD,GPIO_Pin_14)))       //定义LED2的开关控制
#define LED3(x) (x?(GPIO_SetBits(GPIOD,GPIO_Pin_15)):(GPIO_ResetBits(GPIOD,GPIO_Pin_15)))         //定义LED3的开关控制

void LED_Init(void);
#endif

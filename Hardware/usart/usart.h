#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"
#include "stdio.h"
 /******************************************************************************
  * 文件路径  ：   Hardware/usart/usart.h 
  * 作者      ：   农晓明   QQ：382421307
  * 固件库版本：   V1.0.0
  * 日期      ：   2012-03-28
  * 文件描述  ：   提供对板上串口的配置
  ******************************************************************************/
/*******************************************************************************************************************************
 * 函数名：USART1_Config()
 * 参数：无
 *返回值：无
 * 功能：配置USART1，并初始化
********************************************************************************************************************************/																		
void USART1_Config(void);
 void NVIC_Configuration(void);
/********************************************************************************************************************************
*函数名：fputc()
* 参数：int ch，FILE *f
* 返回值：int
* 功能：重新定义stdio.h中的fputc()函数，使printf()输出到USART1
*********************************************************************************************************************************/
int fputc(int ch,FILE *f);
#endif

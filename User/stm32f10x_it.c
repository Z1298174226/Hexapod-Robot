/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "ucos_ii.h"



extern uint8_t buffer[3];
extern uint8_t number=0;
		

extern uint8_t rec_flag=0;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
  /***********
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
extern void TimeTick_Decrement(void);	    //引入外部中断计数函数
/**********************************************************************************************************
*???:SysTick_Handler()
*??:void
*???:void
*??:???????????
**********************************************************************************************************/
/*************************************************


void SysTick_Handler(void)
{     
    OS_CPU_SR  cpu_sr;
	TimeTick_Decrement();
    OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
  //  OSIntNesting++;
  //  OS_EXIT_CRITICAL();
 //   OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */
 //   OSIntExit();   //	 调用中断计数函数
//  OS_TimeMS++;
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/




void SysTick_Handler(void)
{
	TimingDelay_Decrement();	
}

  void USART1_IRQHandler(void)                	//usart1????
{
	/*****************************************
		uint8_t ch;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    //ch = USART1->DR;
			ch = USART_ReceiveData(USART1);
	  	printf( "%c", ch );    //?????????????
		  
	} 
	************************************************/
	 //ch = USART1->DR;
	  
  
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==1)
  {
		 
    USART_ClearFlag(USART1,USART_FLAG_RXNE);
    if(rec_flag==0)
    {
      if(USART_ReceiveData(USART1)==0xff)
      {
        rec_flag=1;	
        number=0;
      }			
    }
    else
    {
      if(USART_ReceiveData(USART1)==0xff)
      {
        rec_flag=0;	
        if(number==3)
        {
          Communication_Decode();		
        }
        number=0;
      }
      else
      {
        buffer[number]=USART_ReceiveData(USART1);
        number++;
      }
    }		
  }
  /*
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==1)
  {
    USART_ClearFlag(USART1,USART_FLAG_RXNE);

        buffer[i]=USART_ReceiveData(USART1);
        i++;
        if(i>2)i=0;
    	
  }*/
  else
  {
    USART_ClearFlag(USART1,USART_FLAG_LBD);
  }	
  
}
/*配置定时器6中断*/
void TIM6_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM6 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);    
	}		 	
}

/*配置定时器7中断*/

void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		Angle_Calculate();
	}
}


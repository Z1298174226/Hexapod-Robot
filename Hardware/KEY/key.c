 /******************************************************************************
  * �ļ�·��  ��   User/main.c
  * ����      ��   ��������   QQ��1298174226
  * �̼���汾��   V3.5.0
  * ����      ��   2015-8-2
  * �ļ�����  ��   ������
  ******************************************************************************/
/*******************main����**********************/

#include "key.h"
#include "delay.h"


void KEY_Init(void) //IO��ʼ��
{ 
	GPIO_InitTypeDef GPIO_InitStructure;	// GPIO�ṹ�嶨��
	//��ʼ��KEY0-->GPIOA.13,KEY1-->GPIOA.15  ����
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
			
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 /*
	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
*/		 

}
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//�������ɿ���־	
 
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0))
	{
		delay_ms(10);//ȥ���� 
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
 
	return 0;// �ް�������
}

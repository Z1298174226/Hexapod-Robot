/******************************************************************************
  * 文件路径  ：   HardWard/control.c
  * 作者      ：   倾听枫声   QQ：1298174226
  * 固件库版本：   V3.5.0
  * 日期      ：   2015-8-2
  * 文件描述  ：   主控函数
  ******************************************************************************/
/*******************主控函数**********************/
#include "control.h"
#include "delay.h"
#include <math.h>
#include "ucos_ii.h"
#include "pwm.h"
#include "UltrasonicWave.h"
#include "TIM6.h"
#include "mpu6050.h"
#include "bsp_i2c.h"
#include "kalman.h"

//default angle of all the engine 
//int pwm_init[26] = { 0,	   //no use	 
//	 			     590,  535,    0,  475,  605,		   //( 1 - 5 )
//				     795,  355,  530,  605,    0,	   	   //( 6 - 10)
//				       0,  475,    0,    0,  803,	       //( 11- 15)
//				     575,    0,  535,  535,  795,	       //( 16- 20)
//				     375,  575,  575,  365,    0,	       //( 21- 25)
//				    };    

//default angle of all the engine 
//int pwm_init[26] = { 0,	   //no use	 
//	 			     108,  108,   115,  106,  112,		   //( 1 - 5 )
//				     108,  108,   95,  108,  108,	   	   //( 6 - 10)
//				     108,  105,   101,  98,  112,	       //( 11- 15)
//				     108,  108,   119,  125,  90,	       //( 16- 20)
//				     85,   139,   99,  108,  108,	       //( 21- 25)
//				    }; 
					
int pwm_init[26] = { 0,	   //no use	 
	 			     142-Height1,  140-Height1,   125,  138-Height1,  140-Height1,		   //( 1 - 5 )
				     108,  133-Height1,   127-Height1,  90,  76+Height1,	   	   //( 6 - 10)
				     70+Height1,  89,  67+Height1,  68+Height1,  112,	           //( 11- 15)
				    76+Height1,  89+Height1,   139,  125,  90,	           //( 16- 20)
				     85,   139,   99,  108,  108,	       //( 21- 25)
				    };    		
					   			   

void PWM_Init(void)
{
		TIM_SetCompare1(TIM1,pwm_init[1]);	 //1-1-1  	   
		TIM_SetCompare2(TIM1,pwm_init[2]);	 //1-2-2  	   
		TIM_SetCompare3(TIM1,pwm_init[19]);	 //1-3-3  	   
		TIM_SetCompare4(TIM1,pwm_init[4]);	 //2-1-4

		TIM_SetCompare3(TIM2,pwm_init[5]);	 //2-2-5  	   
		TIM_SetCompare4(TIM2,pwm_init[6]);	 //2-3-6
																   
		TIM_SetCompare1(TIM3,pwm_init[7]);	 //3-1-7  	   
		TIM_SetCompare2(TIM3,pwm_init[8]);	 //3-2-8  	   
		TIM_SetCompare3(TIM3,pwm_init[20]);	 //3-3-9  	   
		TIM_SetCompare4(TIM3,pwm_init[10]);	 //4-1-10

		TIM_SetCompare1(TIM4,pwm_init[11]);	 //4-2-11  	   
		TIM_SetCompare2(TIM4,pwm_init[21]);	 //4-3-12  	   
		TIM_SetCompare3(TIM4,pwm_init[13]);	 //5-1-13  	   
		TIM_SetCompare4(TIM4,pwm_init[14]);	 //5-2-14

		TIM_SetCompare1(TIM5,pwm_init[15]);	 //5-3-15  	   
		TIM_SetCompare2(TIM5,pwm_init[16]);	 //6-1-16  	   
		TIM_SetCompare3(TIM5,pwm_init[17]);	 //6-2-17  	   
		TIM_SetCompare4(TIM5,pwm_init[22]);	 //6-3-18

		TIM_SetCompare1(TIM2,pwm_init[19]);	  //yun-1-19
		TIM_SetCompare2(TIM2,pwm_init[20]);	  //yun-2-20


}

void Sit_Down(int delay_time)
{
		int pwm_tmp = 0;						//motor 2
		int pwm_tmp2 = 0;						//motor 1
		for (;pwm_tmp<=STAND_HIGHT;)				 //150 efect the height of stand
		{
            delay_ms(delay_time);
//			OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒
			TIM_SetCompare2(TIM3,pwm_init[8]  + pwm_tmp);	 //3-2-8  
		    TIM_SetCompare2(TIM1,pwm_init[2]  + pwm_tmp);    //1-2-2  
			TIM_SetCompare3(TIM2,pwm_init[5]  + pwm_tmp);	 //2-2-5  		   	   

			TIM_SetCompare1(TIM4,pwm_init[11] - pwm_tmp);	 //4-2-11  
			TIM_SetCompare3(TIM5,pwm_init[17] - pwm_tmp);	 //6-2-17  	   
			TIM_SetCompare4(TIM4,pwm_init[14] - pwm_tmp);	 //5-2-14
			
			TIM_SetCompare1(TIM1,pwm_init[1] + pwm_tmp2);	 //1-1-1  	   
			TIM_SetCompare4(TIM1,pwm_init[4] + pwm_tmp2);	 //2-1-4
			TIM_SetCompare1(TIM3,pwm_init[7] + pwm_tmp2);	 //3-1-7  
			
			TIM_SetCompare4(TIM3,pwm_init[10]- pwm_tmp2);	 //4-1-10 
			TIM_SetCompare3(TIM4,pwm_init[13]- pwm_tmp2);	 //5-1-13  	 
			TIM_SetCompare2(TIM5,pwm_init[16]- pwm_tmp2);	 //6-1-16  	   	   
				   
			pwm_tmp += ACTION_SPEED;	
			pwm_tmp2 += SHRINK_SPEED;	
		}
//		OSTimeDlyHMSM(0,0,0,100);//延时，参数：时，分，秒，微秒
		delay_ms(100);
	//	Close_All_TIM();		//close all timer
}

void Stand_Up(int delay_time)
{
		int pwm_tmp = 0;
		int pwm_tmp2 = 0;
		Open_All_TIM();			//Open all timer
		TIM_SetCompare4(TIM2,pwm_init[6]);	 //2-3-6
     	TIM_SetCompare2(TIM4,pwm_init[12]);	 //4-3-12  	   
		TIM_SetCompare4(TIM5,pwm_init[18]);	 //6-3-18
	    TIM_SetCompare3(TIM1,pwm_init[3]);	 //1-3-3  	 
		TIM_SetCompare3(TIM3,pwm_init[9]);	 //3-3-9     
	    TIM_SetCompare1(TIM5,pwm_init[15]);	 //5-3-15  	   
		for (;pwm_tmp<=STAND_HIGHT;)				 //150 efect the height of stand
		{
			delay_ms(delay_time);	
//			OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒
			
		
		    TIM_SetCompare2(TIM3,pwm_init[8] + STAND_HIGHT - pwm_tmp);	 //3-2-8  	   
			TIM_SetCompare2(TIM1,pwm_init[2] + STAND_HIGHT - pwm_tmp);	 //1-2-2  	   
	   	   	TIM_SetCompare3(TIM2,pwm_init[5] + STAND_HIGHT - pwm_tmp);	 //2-2-5  	

		
			TIM_SetCompare1(TIM4,pwm_init[11]  - STAND_HIGHT + pwm_tmp);	 //4-2-11  	   	
			TIM_SetCompare3(TIM5,pwm_init[17]  - STAND_HIGHT + pwm_tmp);	 //6-2-17  	    
		    TIM_SetCompare4(TIM4,pwm_init[14]  - STAND_HIGHT + pwm_tmp);	 //5-2-14
			
			TIM_SetCompare1(TIM1,pwm_init[1] + SHRINK_DEGREE - pwm_tmp2);	 //1-1-1  	
			TIM_SetCompare4(TIM1,pwm_init[4] + SHRINK_DEGREE - pwm_tmp2);	 //2-1-4	   
		    TIM_SetCompare1(TIM3,pwm_init[7] + SHRINK_DEGREE - pwm_tmp2);	 //3-1-7 
			 	 
			TIM_SetCompare4(TIM3,pwm_init[10] - SHRINK_DEGREE + pwm_tmp2);	 //4-1-10  	   
		    TIM_SetCompare3(TIM4,pwm_init[13] - SHRINK_DEGREE + pwm_tmp2);	 //5-1-13  	   	   
	     	TIM_SetCompare2(TIM5,pwm_init[16] - SHRINK_DEGREE + pwm_tmp2);	 //6-1-16  	  	   
			
			pwm_tmp += ACTION_SPEED;	
			pwm_tmp2 += SHRINK_SPEED;	
		}
}

void Pace_135_Motor1(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);		
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒						 
		TIM_SetCompare1(TIM1,pwm_init[1]  + pwm_default + pwm_tmp);	 //1-1-1  	   
		TIM_SetCompare1(TIM3,pwm_init[7]  + pwm_default + pwm_tmp);	 //3-1-7 	   
		TIM_SetCompare3(TIM4,pwm_init[13]  - pwm_default - pwm_tmp);	 //5-1-13  	   	 
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_135_Motor2(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);	
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒						 
	
	    TIM_SetCompare2(TIM1,pwm_init[2]  + pwm_default + pwm_tmp);  //1-2-2  
	    TIM_SetCompare2(TIM3,pwm_init[8]  +  pwm_default + pwm_tmp);	 //3-2-8  
		TIM_SetCompare4(TIM4,pwm_init[14]  - pwm_default - pwm_tmp);	 //5-2-14
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_135_Motor3(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒	
	
		TIM_SetCompare3(TIM1,pwm_init[19] + pwm_default + pwm_tmp);	 //1-3-3  	 
	    TIM_SetCompare3(TIM3,pwm_init[20] + pwm_default + pwm_tmp);	 //3-3-9        
     	TIM_SetCompare1(TIM5,pwm_init[15] - pwm_default - pwm_tmp);	 //5-3-15  	   
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_135_Motor3_Different(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒	
	    TIM_SetCompare3(TIM1,pwm_init[19] - pwm_default - pwm_tmp);	 //1-3-3  
	    TIM_SetCompare3(TIM3,pwm_init[20] - pwm_default - pwm_tmp);	 //3-3-9      	   
	 	TIM_SetCompare1(TIM5,pwm_init[15] - pwm_default - pwm_tmp);	 //5-3-15  	       
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_246_Motor2(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒		TIM_SetCompare1(TIM5,pwm_init[6]  - pwm_default - pwm_tmp);	 //2-2-6  
	
	   	TIM_SetCompare1(TIM4,pwm_init[11]  - pwm_default - pwm_tmp);	 //4-2-11  
		TIM_SetCompare3(TIM5,pwm_init[17]  - pwm_default - pwm_tmp);	 //6-2-17  	
	    TIM_SetCompare3(TIM2,pwm_init[5]  + pwm_default + pwm_tmp);	 //2-2-5  	   
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_246_Motor3(int pwm_default,int amplitude,int delay_time)
{	   
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒		TIM_SetCompare1(TIM5,pwm_init[6]  - pwm_default - pwm_tmp);	 //2-2-6  
	
		TIM_SetCompare4(TIM2,pwm_init[6]  + pwm_default + pwm_tmp);	 //2-3-6  
	    TIM_SetCompare2(TIM4,pwm_init[21] - pwm_default - pwm_tmp);	 //4-3-12  	
		TIM_SetCompare4(TIM5,pwm_init[22] - pwm_default - pwm_tmp);	 //6-3-18  
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_246_Motor3_Different(int pwm_default,int amplitude,int delay_time)
{	   
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒		TIM_SetCompare1(TIM5,pwm_init[6]  - pwm_default - pwm_tmp);	 //2-2-6  
		TIM_SetCompare4(TIM2,pwm_init[6]  - pwm_default - pwm_tmp);	 //2-3-6  
	    TIM_SetCompare2(TIM4,pwm_init[21] - pwm_default - pwm_tmp);	 //4-3-12  	
		TIM_SetCompare4(TIM5,pwm_init[22] - pwm_default - pwm_tmp);	 //6-3-18  
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_135_246_Motor3(int pwm_def1,int pwm_def2,int amplitude,int delay_time)
{	   
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
	    delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒		

	
		TIM_SetCompare3(TIM1,pwm_init[19]  - pwm_def1 - pwm_tmp);	 //1-3-3  
		TIM_SetCompare3(TIM3,pwm_init[10]  - pwm_def1 - pwm_tmp);	 //3-3-9       
		TIM_SetCompare1(TIM5,pwm_init[15] - pwm_def1 - pwm_tmp);	 //5-3-15  	        

	    TIM_SetCompare4(TIM2,pwm_init[6]  - pwm_def2 - pwm_tmp);	 //2-3-6  
		TIM_SetCompare2(TIM4,pwm_init[21] - pwm_def2 - pwm_tmp);	 //4-3-12  	
		TIM_SetCompare4(TIM5,pwm_init[22] - pwm_def2 - pwm_tmp);	 //6-3-18  
		
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
//void Go_straight(u8 Com_Num,u8 * Input_num)
void  Go_back (void)
{
   
	Pace_135_Motor2(0,16,STRAIGHT_DELAY);		//UP
	while(1)
	{
		Pace_246_Motor3(0,15,STRAIGHT_DELAY);		//FRONT
	   	Pace_135_Motor2(16,-16,STRAIGHT_DELAY);	//DOWM
		Pace_246_Motor2(0,16,STRAIGHT_DELAY);		//UP
		Pace_246_Motor3(15,-15,STRAIGHT_DELAY);		//RETURN
		Pace_135_Motor3(0,15,STRAIGHT_DELAY);		//FRONT
		Pace_246_Motor2(16,-16,STRAIGHT_DELAY);	//DOWM
		Pace_135_Motor2(0,16,STRAIGHT_DELAY);		//UP
		Pace_135_Motor3(15,-15,STRAIGHT_DELAY);		//RETURN
	}
	Pace_135_Motor2(16,-16,STRAIGHT_DELAY);		//DOWM
}
//void Go_back(u8 Com_Num,u8 * Input_num)  
 void Go_straight(void)
{
   
	Pace_135_Motor2(0,16,ACTION_DELAY);		//UP
//	while(Com_Num == *Input_num)
     while(1)
	{
		Pace_246_Motor3(0,-15,ACTION_DELAY);	//BACK
	   	Pace_135_Motor2(16,-16,ACTION_DELAY);	//DOWM
		Pace_246_Motor2(0,16,ACTION_DELAY);	//UP
		Pace_246_Motor3(-15,15,ACTION_DELAY);	//RETURN
		Pace_135_Motor3(0,-15,ACTION_DELAY);	//BACK
		Pace_246_Motor2(16,-16,ACTION_DELAY);	//DOWM
		Pace_135_Motor2(0,16,ACTION_DELAY);	//UP
		Pace_135_Motor3(-15,15,ACTION_DELAY);	//RETURN
	}
	Pace_135_Motor2(16,-16,ACTION_DELAY);	//DOWM
}
//void Stamp(u8 Com_Num,u8 * Input_num)
//{

void Stamp(void)
{
	Pace_135_Motor2(0,16,STAMP_DELAY);		//UP
//	while(Com_Num == *Input_num)
while(1)
	{
	   	Pace_135_Motor2(16,-16,STAMP_DELAY);	//DOWM
		Pace_246_Motor2(0,16,STAMP_DELAY);	//UP
		Pace_246_Motor2(16,-16,STAMP_DELAY);	//DOWM
		Pace_135_Motor2(0,16,STAMP_DELAY);	//UP
	}
	Pace_135_Motor2(16,-16,STAMP_DELAY);	//DOWM
}
//void Turn(u8 Com_Num,u8 * Input_num)
void Turn(void)
{						 
//	while(Com_Num == *Input_num)
while(1)
	{
	   	UltrasonicWave_StartMeasure();
		/**********************陀螺仪*******************************/
	//	MPU6050ReadAcc(Acel);
    //	printf("加速度：%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
	//	MPU6050ReadGyro(Gyro);
	//	printf("    陀螺仪%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
		MPU6050_ReturnTemp(&Temp);
//		printf("    温度%d\r\n",Temp);
        
	  //  printf("角度： %f       y轴加速度：	%f	",Angle,Gyro_y);	
		
		Pace_135_246_Motor3(0,0,15,TURN_DELAY);     //turn body left

		Pace_246_Motor2(0,16,TURN_DELAY);			  //UP
		Pace_246_Motor3_Different(15,-15,TURN_DELAY);	  //2,4,6 leg return
		Pace_246_Motor2(16,-16,TURN_DELAY);		      //DOWM
		
		Pace_135_Motor2(0,16,TURN_DELAY);			  //UP
		Pace_135_Motor3_Different(15,-15,TURN_DELAY);	  //1,3,5 leg return
		Pace_135_Motor2(16,-16,TURN_DELAY);		      //DOWM
		
	}

}




void Action_Init(int delay_time)
{
    int pwm_tmp3=0;	
	for (;pwm_tmp3<=Init_Height;)				 //150 efect the height of stand
		{
	    delay_ms(delay_time);	

        TIM_SetCompare1(TIM1,pwm_init[1]);	 //1-1-1  	   
		TIM_SetCompare2(TIM1,pwm_init[2]+pwm_tmp3);	 //1-2-2  	   
		TIM_SetCompare3(TIM1,pwm_init[19]);	 //1-3-3  	   
		TIM_SetCompare4(TIM1,pwm_init[4]);	 //2-1-4

		TIM_SetCompare3(TIM2,pwm_init[5]+pwm_tmp3);	 //2-2-5  	   
		TIM_SetCompare4(TIM2,pwm_init[6]);	 //2-3-6
																   
		TIM_SetCompare1(TIM3,pwm_init[7]);	 //3-1-7  	   
		TIM_SetCompare2(TIM3,pwm_init[8]+pwm_tmp3);	 //3-2-8  	   
		TIM_SetCompare3(TIM3,pwm_init[20]);	 //3-3-9  	   
		TIM_SetCompare4(TIM3,pwm_init[10]);	 //4-1-10

		TIM_SetCompare1(TIM4,pwm_init[11]-pwm_tmp3);	 //4-2-11  	   
		TIM_SetCompare2(TIM4,pwm_init[21]);	 //4-3-12  	   
		TIM_SetCompare3(TIM4,pwm_init[23]);	 //5-1-13  	   
		TIM_SetCompare4(TIM4,pwm_init[14]-pwm_tmp3);	 //5-2-14

		TIM_SetCompare1(TIM5,pwm_init[15]);	 //5-3-15  	   
		TIM_SetCompare2(TIM5,pwm_init[16]);	 //6-1-16  	   
		TIM_SetCompare3(TIM5,pwm_init[17]-pwm_tmp3);	 //6-2-17  	   
		TIM_SetCompare4(TIM5,pwm_init[22]);	 //6-3-18

		TIM_SetCompare1(TIM2,pwm_init[19]);	  //yun-1-19
		TIM_SetCompare2(TIM2,pwm_init[20]);	  //yun-2-20
		
		pwm_tmp3 += ACTION_SPEED;	
	
		}
}
void Pace_123_Motor1(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);		
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒						 
		TIM_SetCompare1(TIM1,pwm_init[1]  + pwm_default + pwm_tmp);	 //1-1-1 
		TIM_SetCompare4(TIM1,pwm_init[4]  + pwm_default + pwm_tmp);	 //2-1-4 	   
		TIM_SetCompare1(TIM3,pwm_init[7]  + pwm_default + pwm_tmp);	 //3-1-7 	   
	  	 
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_123_Motor2(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);	
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒						 
	
	    TIM_SetCompare2(TIM1,pwm_init[2]  + pwm_default + pwm_tmp);  //1-2-2 
	    TIM_SetCompare3(TIM2,pwm_init[5]  + pwm_default + pwm_tmp);	 //2-2-5   
	    TIM_SetCompare2(TIM3,pwm_init[8]  + pwm_default + pwm_tmp);	 //3-2-8  
	
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}
void Pace_456_Motor2(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒		TIM_SetCompare1(TIM5,pwm_init[6]  - pwm_default - pwm_tmp);	 //2-2-6  
	
	   	TIM_SetCompare1(TIM4,pwm_init[11]  - pwm_default - pwm_tmp);	 //4-2-11  
		TIM_SetCompare3(TIM5,pwm_init[17]  - pwm_default - pwm_tmp);	 //6-2-17 
		TIM_SetCompare4(TIM4,pwm_init[14]  - pwm_default - pwm_tmp);	 //5-2-14 	
	      
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}

void Pace_456_Motor1(int pwm_default,int amplitude,int delay_time)
{
	int pwm_tmp = 0;
	for(;fabs(pwm_tmp)<=fabs(amplitude);)
	{
		delay_ms(delay_time);
//		OSTimeDlyHMSM(0,0,0,delay_time);//延时，参数：时，分，秒，微秒		TIM_SetCompare1(TIM5,pwm_init[6]  - pwm_default - pwm_tmp);	 //2-2-6  
		TIM_SetCompare4(TIM3,pwm_init[10]  - pwm_default - pwm_tmp);	 //4-1-10
		TIM_SetCompare3(TIM4,pwm_init[13]  - pwm_default - pwm_tmp);	 //5-1-13 
		TIM_SetCompare2(TIM5,pwm_init[16]  - pwm_default - pwm_tmp);	 //6-1-16     
		if(amplitude > 0)
			pwm_tmp += ACTION_SPEED;
		else 
			pwm_tmp -= ACTION_SPEED;
	}
}


 
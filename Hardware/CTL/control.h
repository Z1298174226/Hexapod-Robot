
#ifndef __CONTROL_H_
#define __CONTROL_H_
#include "stm32f10x.h"
#define PWM_MAX  		180
#define PWM_MIN  		36
#define PWM_TO_ANGLE	((PWM_MAX-PWM_MIN)/180) 

#define ACTION_SPEED 	(u16)2		 //range:0 - 10
#define SHRINK_SPEED 	(u16)2                             //((u16)((0.6)*ACTION_SPEED))
#define ACTION_DELAY 	(u16)30      //ms	    //20
#define TURN_DELAY 		(u16)30    //4
#define STRAIGHT_DELAY 	(u16)30     //ms	   //3
#define STAMP_DELAY 	(u16)30      //stamp delay
#define STAND_HIGHT 	(u16)46
#define SHRINK_DEGREE 	(u16)18                 //((u16)((0.6)*STAND_HIGHT))
#define Init_Height		(u16)16
#define Height1         (u16)0


extern short Acel[3];
extern short Gyro[3];
extern short Temp;

void PWM_Init(void);
void Sit_Down(int delay_time);
void Stand_Up(int delay_time);

void Pace_135_Motor1(int pwm_default,int amplitude,int delay_time);
void Pace_135_Motor2(int pwm_default,int amplitude,int delay_time);
void Pace_135_Motor3(int pwm_default,int amplitude,int delay_time);
void Pace_246_Motor2(int pwm_default,int amplitude,int delay_time);
void Pace_246_Motor3(int pwm_default,int amplitude,int delay_time);
void Pace_123_Motor1(int pwm_default,int amplitude,int delay_time);
void Pace_123_Motor2(int pwm_default,int amplitude,int delay_time);
void Pace_456_Motor2(int pwm_default,int amplitude,int delay_time);
void Pace_456_Motor1(int pwm_default,int amplitude,int delay_time);

//void Go_straight(u8 Com_Num,u8 * Input_num);
void Go_straighe(void);
//void Go_back(u8 Com_Num,u8 * Input_num);
void Go_back(void);
//void Stamp(u8 Com_Num,u8 * Input_num);
//void Turn(u8 Com_Num,u8 * Input_num);
void Action_Init(int delay_time);
void Turn(void);
void Stamp(void);

#endif

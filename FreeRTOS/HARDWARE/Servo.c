#include "Servo.h"
#include "stm32f4xx.h"                  // Device header

void Servo_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义一个引脚初始化的结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //定义一个定时中断的结构体	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //定义一个PWM输出的结构体
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //使能GPIOE时钟，GPIOE挂载在AHB1时钟下，在STM32中使用IO口前都要使能对应时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //使能通用定时器1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE); //使能通用定时器9时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_13|GPIO_Pin_14;           //GPIOE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PE
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);//GPIOE5复用为
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);//GPIOE6复用为
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);//GPIOE13复用为
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);//GPIOE14复用为

	TIM_TimeBaseInitStrue.TIM_Period=arr; //计数模式为向上计数时，定时器从0开始计数，计数超过到arr时触发定时中断服务函数
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数，决定每一个计数的时长
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数模式：向上计数
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //一般不使用，默认TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStrue); //根据TIM_TimeBaseInitStrue的参数初始化定时器TIM9
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStrue); //根据TIM_TimeBaseInitStrue的参数初始化定时器TIM1

	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM2; //PWM模式1，当定时器计数小于TIM_Pulse时，定时器对应IO输出有效电平
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCNPolarity_High; //输出有效电平为高电平
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //使能PWM输出
//	TIM_OCInitTypeStrue.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OC1Init(TIM9, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器9通道1
	TIM_OC2Init(TIM9, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器9通道2
	TIM_OC3Init(TIM1, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器1通道3
	TIM_OC4Init(TIM1, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器1通道4

  //TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效

	TIM_ARRPreloadConfig(TIM9, ENABLE); //TIM2预装载使能
	TIM_ARRPreloadConfig(TIM1, ENABLE); //TIM2预装载使能

	TIM_Cmd(TIM9, ENABLE); //使能定时器TIM9
	TIM_Cmd(TIM1, ENABLE); //使能定时器TIM1
	
	
}




#include "TB6612.h"  

/**************************************************************************
函数功能：TB6612初始化函数
入口参数：定时器2计数上限 定时器2预分频系数
返回  值：无
**************************************************************************/
void MOTOR_Init()
{
	TB6612_Init(100-1,168-1);  
	motor_mode();
//输出0占空比
     TIM_SetCompare1(TIM5,0);
	 TIM_SetCompare2(TIM5,0); 
	 TIM_SetCompare3(TIM5,0);    
     TIM_SetCompare4(TIM5,0);    //左前轮
			
}

void TB6612_Init(int arr, int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义一个引脚初始化的结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //定义一个定时中断的结构体	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //定义一个PWM输出的结构体
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //使能GPIOA时钟，GPIOA挂载在AHB2时钟下，在STM32中使用IO口前都要使能对应时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //使能通用定时器2时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;           //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA0
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);//GPIOA0复用为
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);//GPIOA0复用为
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);//GPIOA0复用为
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);//GPIOA0复用为

	TIM_TimeBaseInitStrue.TIM_Period=arr; //计数模式为向上计数时，定时器从0开始计数，计数超过到arr时触发定时中断服务函数
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数，决定每一个计数的时长
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数模式：向上计数
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //一般不使用，默认TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStrue); //根据TIM_TimeBaseInitStrue的参数初始化定时器TIM2
	
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM1; //PWM模式1，当定时器计数小于TIM_Pulse时，定时器对应IO输出有效电平
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCNPolarity_High; //输出有效电平为高电平
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //使能PWM输出
//	TIM_OCInitTypeStrue.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OC1Init(TIM5, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器2通道1
	TIM_OC2Init(TIM5, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器2通道1
	TIM_OC3Init(TIM5, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器2通道1
	TIM_OC4Init(TIM5, &TIM_OCInitTypeStrue); //根TIM_OCInitTypeStrue参数初始化定时器2通道1

  //TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1预装载使能 使能后改变TIM_Pulse(即PWM)的值立刻生效，不使能则下个周期生效

	TIM_ARRPreloadConfig(TIM5, ENABLE); //TIM2预装载使能
	
	TIM_Cmd(TIM5, ENABLE); //使能定时器TIM2
}
void motor_mode()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//使能PORTF时钟	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //初始化PF9
    M1 = 1;
	M2 = 1;
			
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOG,&GPIO_InitStructure); 
    M3 = 1;
	M4 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
    M5 = 1;
	M6 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
    M7 = 1;
	M8 = 1;

}

/**************************************************************************
函数功能：设置TIM2通道1PWM值
入口参数：PWM值
返回  值：无
**************************************************************************/
void SetPWM(int pwm)
{
  if(pwm>=0)//pwm>=0 (BIN1, BIN2)=(0, 1) 正转 顺时针
  {
		M1=0; //BIN1=0
		M2=1; //BIN2=1
//		TIM5->CCR1=pwm;
		TIM_SetCompare1(TIM5, pwm);
  }
  else if(pwm<0)//pwm<0 (BIN1, BIN2)=(1, 0) 反转 逆时针
  {
		M1=1; //BIN1=1
		M2=0; //BIN2=0
//		TIM5->CCR1=-pwm;
		TIM_SetCompare1(TIM5, -pwm);
  }
}


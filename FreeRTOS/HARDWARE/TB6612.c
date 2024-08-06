#include "TB6612.h"  

/**************************************************************************
�������ܣ�TB6612��ʼ������
��ڲ�������ʱ��2�������� ��ʱ��2Ԥ��Ƶϵ��
����  ֵ����
**************************************************************************/
void MOTOR_Init()
{
	TB6612_Init(100-1,168-1);  
	motor_mode();
//���0ռ�ձ�
     TIM_SetCompare1(TIM5,0);
	 TIM_SetCompare2(TIM5,0); 
	 TIM_SetCompare3(TIM5,0);    
     TIM_SetCompare4(TIM5,0);    //��ǰ��
			
}

void TB6612_Init(int arr, int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //����һ��PWM����Ľṹ��
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ�ӣ�GPIOA������AHB2ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʹ��ͨ�ö�ʱ��2ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;           //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA0
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);//GPIOA0����Ϊ
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);//GPIOA0����Ϊ
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);//GPIOA0����Ϊ
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);//GPIOA0����Ϊ

	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM2
	
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM1; //PWMģʽ1������ʱ������С��TIM_Pulseʱ����ʱ����ӦIO�����Ч��ƽ
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCNPolarity_High; //�����Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //ʹ��PWM���
//	TIM_OCInitTypeStrue.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC1Init(TIM5, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1
	TIM_OC2Init(TIM5, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1
	TIM_OC3Init(TIM5, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1
	TIM_OC4Init(TIM5, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1

  //TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч

	TIM_ARRPreloadConfig(TIM5, ENABLE); //TIM2Ԥװ��ʹ��
	
	TIM_Cmd(TIM5, ENABLE); //ʹ�ܶ�ʱ��TIM2
}
void motor_mode()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //��ʼ��PF9
    M1 = 1;
	M2 = 1;
			
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOG,&GPIO_InitStructure); 
    M3 = 1;
	M4 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
    M5 = 1;
	M6 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
    M7 = 1;
	M8 = 1;

}

/**************************************************************************
�������ܣ�����TIM2ͨ��1PWMֵ
��ڲ�����PWMֵ
����  ֵ����
**************************************************************************/
void SetPWM(int pwm)
{
  if(pwm>=0)//pwm>=0 (BIN1, BIN2)=(0, 1) ��ת ˳ʱ��
  {
		M1=0; //BIN1=0
		M2=1; //BIN2=1
//		TIM5->CCR1=pwm;
		TIM_SetCompare1(TIM5, pwm);
  }
  else if(pwm<0)//pwm<0 (BIN1, BIN2)=(1, 0) ��ת ��ʱ��
  {
		M1=1; //BIN1=1
		M2=0; //BIN2=0
//		TIM5->CCR1=-pwm;
		TIM_SetCompare1(TIM5, -pwm);
  }
}


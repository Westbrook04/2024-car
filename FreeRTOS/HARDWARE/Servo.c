#include "Servo.h"
#include "stm32f4xx.h"                  // Device header

void Servo_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //����һ��PWM����Ľṹ��
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //ʹ��GPIOEʱ�ӣ�GPIOE������AHB1ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʹ��ͨ�ö�ʱ��1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE); //ʹ��ͨ�ö�ʱ��9ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_13|GPIO_Pin_14;           //GPIOE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PE
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);//GPIOE5����Ϊ
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);//GPIOE6����Ϊ
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);//GPIOE13����Ϊ
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);//GPIOE14����Ϊ

	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM9
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM1

	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM2; //PWMģʽ1������ʱ������С��TIM_Pulseʱ����ʱ����ӦIO�����Ч��ƽ
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCNPolarity_High; //�����Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //ʹ��PWM���
//	TIM_OCInitTypeStrue.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC1Init(TIM9, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��9ͨ��1
	TIM_OC2Init(TIM9, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��9ͨ��2
	TIM_OC3Init(TIM1, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��1ͨ��3
	TIM_OC4Init(TIM1, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��1ͨ��4

  //TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч

	TIM_ARRPreloadConfig(TIM9, ENABLE); //TIM2Ԥװ��ʹ��
	TIM_ARRPreloadConfig(TIM1, ENABLE); //TIM2Ԥװ��ʹ��

	TIM_Cmd(TIM9, ENABLE); //ʹ�ܶ�ʱ��TIM9
	TIM_Cmd(TIM1, ENABLE); //ʹ�ܶ�ʱ��TIM1
	
	
}




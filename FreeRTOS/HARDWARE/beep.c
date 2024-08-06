#include "stm32f4xx.h"                  // Device header
#include "beep.h"
#include "delay.h"
void BEEP_Init(void)
{   
	 GPIO_InitTypeDef GPIO_InitStructure;

	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//ʹ��ʱ��

	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	 GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	 GPIO_Init(GPIOF,&GPIO_InitStructure);//��ʼ��GPIO  PG11
	 GPIO_ResetBits(GPIOF,GPIO_Pin_8); //�͵�ƽ����
}
void Beep_one(void)
{
	BEEP=~BEEP;
	delay_s(4);
	BEEP=~BEEP;
}


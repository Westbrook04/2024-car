#include "stm32f4xx.h"                  // Device header
#include "key.h"
#include "delay.h"
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	  
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOB,ENABLE);
	  
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	  GPIO_Init(GPIOG,&GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY4���� KEY4
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY4!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
		else if(KEY4==1)return 4;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==0)key_up=1; 	    
 	return 0;// �ް�������
}

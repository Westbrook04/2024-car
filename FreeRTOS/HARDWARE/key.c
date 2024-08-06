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
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY4按下 KEY4
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY4!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
		else if(KEY4==1)return 4;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==0)key_up=1; 	    
 	return 0;// 无按键按下
}

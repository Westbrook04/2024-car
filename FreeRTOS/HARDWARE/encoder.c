#include "encoder.h"
#include "stm32f4xx.h"                  // Device header


/**************************************************************************
Function: Initialize TIM8 as the encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM8��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
�� �� ֵ����
**************************************************************************/
void Encoder_Init_TIM8(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   //ʹ�ܶ�ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  //ʹ��C��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //PC6
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PC7
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);   //����ΪTIM8 �������ӿ�
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);   //����ΪTIM8 �������ӿ�
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //����Ƶ
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���    
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);  //��ʼ����ʱ��
  
  TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM8, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM8, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM8,0);
  TIM_Cmd(TIM8, ENABLE); 
}
/**************************************************************************
Function: Initialize TIM4 as the encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
�� �� ֵ����
**************************************************************************/
void Encoder_Init_TIM4(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //ʹ�ܶ�ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //ʹ��D��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  //PD12
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  //PD13
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);   //����ΪTIM4 �������ӿ�
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);   //����ΪTIM4 �������ӿ�
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //����Ƶ
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���    
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //��ʼ����ʱ��
  
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}
/**************************************************************************
Function: Initialize TIM3 as the encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM3��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
�� �� ֵ����
**************************************************************************/
void Encoder_Init_TIM3(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //ʹ�ܶ�ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //ʹ��A��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PA7
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //PA6
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);   //����ΪTIM8 �������ӿ�
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);   //����ΪTIM2 �������ӿ�
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //����Ƶ
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���    
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //��ʼ����ʱ��
  
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM3,0);
  TIM_Cmd(TIM3, ENABLE); 
}
/**************************************************************************
Function: Initialize TIM1 as the encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM1��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
�� �� ֵ����
**************************************************************************/
void Encoder_Init_TIM1(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //ʹ�ܶ�ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);  //ʹ��E��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //PE9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  //PE11
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);   //����ΪTIM8 �������ӿ�
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);   //����ΪTIM2 �������ӿ�
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //����Ƶ
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���    
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //��ʼ����ʱ��
  
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM1,0);
  TIM_Cmd(TIM1, ENABLE); 
}

/**************************************************************************
Function: Read the encoder count
Input   : The timer
Output  : Encoder value (representing speed)
�������ܣ���ȡ����������
��ڲ�������ʱ��
����  ֵ����������ֵ(�����ٶ�)
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
 int Encoder_TIM;    
 switch(TIMX)
 {
	case 8:  Encoder_TIM= (short)TIM8 -> CNT;   TIM8 -> CNT=0;  break;
	case 4:  Encoder_TIM= (short)TIM4 -> CNT;   TIM4 -> CNT=0;  break;
	case 3:  Encoder_TIM= (short)TIM3 -> CNT;   TIM3 -> CNT=0;  break;	
	case 1:  Encoder_TIM= (short)TIM1 -> CNT;   TIM1 -> CNT=0;  break;	
	default: Encoder_TIM=0;
 }
	return Encoder_TIM;
}

/**************************************************************************
Function: Tim8 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM8�жϷ�����
��ڲ�������
�� �� ֵ����
**************************************************************************/
void TIM8_IRQHandler(void)
{ 		    		  			    
	if(TIM8->SR&0X0001) //Overflow interrupt //����ж�
	{    				   				     	    	
	}				   
	TIM8->SR&=~(1<<0); //Clear the interrupt flag bit //����жϱ�־λ 	    
}
/**************************************************************************
Function: Tim4 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM4�жϷ�����
��ڲ�������
�� �� ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001) //Overflow interrupt //����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0); //Clear the interrupt flag bit //����жϱ�־λ 	    
}
/**************************************************************************
Function: Tim3 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM3�жϷ�����
��ڲ�������
�� �� ֵ����
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001) //Overflow interrupt //����ж�
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0); //Clear the interrupt flag bit //����жϱ�־λ 	    
}
/**************************************************************************
Function: Tim1 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM1�жϷ�����
��ڲ�������
�� �� ֵ����
**************************************************************************/
void TIM1_IRQHandler(void)
{ 		    		  			    
	if(TIM1->SR&0X0001) //Overflow interrupt //����ж�
	{    				   				     	    	
	}				   
	TIM1->SR&=~(1<<0); //Clear the interrupt flag bit //����жϱ�־λ 	    
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
	if(TIM12->SR&0X0001) //Overflow interrupt //����ж�
	{    				   				     	    	
	}				   
	TIM12->SR&=~(1<<0); //Clear the interrupt flag bit //����жϱ�־λ  	 

}

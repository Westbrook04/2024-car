#include "stm32f4xx.h"                  // Device header
#include "IIC3.h"
#include "delay.h"

//��ʼ��IIC
void IIC3_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_I2C3); //GPIOA9����ΪUSART1
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_I2C3); //GPIOA10����ΪUSART1

  //GPIOA8,C9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��

	IIC3_SCL=1;
	IIC3_SDA=1;
}
//����IIC��ʼ�ź�
void IIC3_Start(void)
{
	IIC3_SDA_OUT();     //sda�����
	IIC3_SDA=1;	  	  
	IIC3_SCL=1;
	delay_us(4);
 	IIC3_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC3_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC3_Stop(void)
{
	IIC3_SDA_OUT();//sda�����
	IIC3_SCL=0;
	IIC3_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC3_SCL=1; 
	IIC3_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC3_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC3_SDA_IN();      //SDA����Ϊ����  
	IIC3_SDA=1;delay_us(1);	   
	IIC3_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC3_Stop();
			return 1;
		}
	}
	IIC3_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC3_Ack(void)
{
	IIC3_SCL=0;
	IIC3_SDA_OUT();
	IIC3_SDA=0;
	delay_us(2);
	IIC3_SCL=1;
	delay_us(2);
	IIC3_SCL=0;
}
//������ACKӦ��		    
void IIC3_NAck(void)
{
	IIC3_SCL=0;
	IIC3_SDA_OUT();
	IIC3_SDA=1;
	delay_us(2);
	IIC3_SCL=1;
	delay_us(2);
	IIC3_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC3_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC3_SDA_OUT(); 	    
    IIC3_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC3_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC3_SCL=1;
		delay_us(2); 
		IIC3_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC3_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC3_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC3_SCL=0; 
        delay_us(2);
		IIC3_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC3_NAck();//����nACK
    else
        IIC3_Ack(); //����ACK   
    return receive;
}




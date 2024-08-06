#include "sys.h"
#include "delay.h"
#include "led.h"
#include "bool.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "key.h"
#include "beep.h"
#include "encoder.h"

void start_task(void * pvParameters);//������
TaskHandle_t StartTask_Handler;      //������

void task1_task(void * pvParameters);//������
TaskHandle_t Task1_Handler;      //������

void task2_task(void * pvParameters);//������
TaskHandle_t Task2_Handler;      //������

void task3_task(void * pvParameters);//������
TaskHandle_t Task3_Handler;      //������

void Init()
{
 	Stm32_Clock_Init(336,8,2,7);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�ж����ȼ�����
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	KEY_Init();
	BEEP_Init();
}
int main(void)
{ 
	Init();
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )120,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������

}
void start_task(void * pvParameters)
{
	 //���񴴽�task1
	xTaskCreate((TaskFunction_t) task1_task,
				(char*         ) "task1_task",
				(uint16_t      ) 120,
				(void*         ) NULL,
				(UBaseType_t   ) 2,
				(TaskHandle_t* ) &Task1_Handler);
	 //���񴴽�task2
	xTaskCreate((TaskFunction_t) task2_task,
				(char*         ) "task2_task",
				(uint16_t      ) 120,
				(void*         ) NULL,
				(UBaseType_t   ) 3,
				(TaskHandle_t* ) &Task2_Handler);
	 //���񴴽�task3
	xTaskCreate((TaskFunction_t) task3_task,
				(char*         ) "task3_task",
				(uint16_t      ) 120,
				(void*         ) NULL,
				(UBaseType_t   ) 4,
				(TaskHandle_t* ) &Task3_Handler);
    vTaskDelete(StartTask_Handler);
}	
void task1_task(void * pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		delay_ms(500);
	}
}
void task2_task(void * pvParameters)
{
	while(1)
	{
		LED1=~LED1;
		delay_ms(1000);
	}
}
void task3_task(void * pvParameters)
{
	while(1)
	{
		delay_ms(1000);
		BEEP=!BEEP;
	}
}


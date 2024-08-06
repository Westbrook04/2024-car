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

void start_task(void * pvParameters);//任务函数
TaskHandle_t StartTask_Handler;      //任务句柄

void task1_task(void * pvParameters);//任务函数
TaskHandle_t Task1_Handler;      //任务句柄

void task2_task(void * pvParameters);//任务函数
TaskHandle_t Task2_Handler;      //任务句柄

void task3_task(void * pvParameters);//任务函数
TaskHandle_t Task3_Handler;      //任务句柄

void Init()
{
 	Stm32_Clock_Init(336,8,2,7);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断优先级分组
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	KEY_Init();
	BEEP_Init();
}
int main(void)
{ 
	Init();
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )120,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度

}
void start_task(void * pvParameters)
{
	 //任务创建task1
	xTaskCreate((TaskFunction_t) task1_task,
				(char*         ) "task1_task",
				(uint16_t      ) 120,
				(void*         ) NULL,
				(UBaseType_t   ) 2,
				(TaskHandle_t* ) &Task1_Handler);
	 //任务创建task2
	xTaskCreate((TaskFunction_t) task2_task,
				(char*         ) "task2_task",
				(uint16_t      ) 120,
				(void*         ) NULL,
				(UBaseType_t   ) 3,
				(TaskHandle_t* ) &Task2_Handler);
	 //任务创建task3
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


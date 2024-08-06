#include "F4_flash.h"

#define FLASH_SAVE_ADDR  0x08040000 	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
u16 Flash_Parameter[10];

float Position1=SERVO_INIT,Position2=SERVO_INIT,Position3=SERVO_INIT,Position4=SERVO_INIT; 
float Velocity1=0,Velocity2=0,Velocity3=0,Velocity4=0;     //电机PWM变量
float	Position_KP=2,Position_KI=0,Position_KD=1;  //位置控制PID参数 
short Moveit_Angle1_init=0,Moveit_Angle2_init=0,Moveit_Angle3_init=0,Moveit_Angle4_init=0; //舵机初始位置值微调
int Servo_init_angle_adjust=0;//零点调整标志位

//读取指定地址的半字(16位数据) 
//faddr:读地址 
//返回值:对应数据.
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}  
//获取某个地址所在的flash扇区
//addr:flash地址
//返回值:0~11,即addr所在的扇区
uint16_t STMFLASH_GetFlashSector(u32 addr)
{
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10; 
	return FLASH_Sector_11;	
}
//从指定地址开始写入指定长度的数据
//特别注意:因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
//         写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
//         写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
//         没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写. 
//该函数对OTP区域也有效!可以用来写OTP区!
//OTP区域地址范围:0X1FFF7800~0X1FFF7A0F
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.) 
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u32 NumToWrite)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%2)return;	//非法地址
	FLASH_Unlock();									//解锁 
  FLASH_DataCacheCmd(DISABLE);		//FLASH擦除期间,必须禁止数据缓存
 		
	addrx=WriteAddr;				//写入的起始地址
	endaddr=WriteAddr+NumToWrite*2;	//写入的结束地址
	if(addrx<0X1FFF0000)			//只有主存储区,才需要执行擦除操作!!
	{
		while(addrx<endaddr)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{
			if(STMFLASH_ReadHalfWord(addrx)!=0XFFFF)//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V之间!!
				if(status!=FLASH_COMPLETE)break;	//发生错误了
			}else addrx+=2;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//写数据
		{
			if(FLASH_ProgramHalfWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//写入数据
			{ 
				break;	//写入异常
			}
			WriteAddr+=2;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
	FLASH_Lock();//上锁
} 

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(4位)数
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}


/**************************************************************************
函数功能：从Flash读取指定数据
入口参数：无
返回  值：无
**************************************************************************/
void Flash_Read(void)
{
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)Flash_Parameter,10);
	if(Flash_Parameter[0]==65535&&Flash_Parameter[1]==65535&&Flash_Parameter[2]==65535&&Flash_Parameter[3]==65535)
	{
    Moveit_Angle1_init=0,Moveit_Angle2_init=0,Moveit_Angle3_init=0,Moveit_Angle4_init=0;
	}
  else 
	{		
		Moveit_Angle1_init=Flash_Parameter[0];	//读取舵机机械臂微调的初始位置
		Moveit_Angle2_init=Flash_Parameter[1];	
		Moveit_Angle3_init=Flash_Parameter[2];	
		Moveit_Angle4_init=Flash_Parameter[3];	
	
	}
}	
/**************************************************************************
函数功能：向Flash写入指定数据
入口参数：无
返回  值：无
**************************************************************************/
void Flash_Write(void)
{
	Flash_Parameter[0]=(u16)Moveit_Angle1_init;	//存储
	Flash_Parameter[1]=(u16)Moveit_Angle2_init;	//存储	
	Flash_Parameter[2]=(u16)Moveit_Angle3_init;	//存储	
	Flash_Parameter[3]=(u16)Moveit_Angle4_init;	//存储		
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)Flash_Parameter,10);	
}	
























#ifndef __PCA9685_H
#define __PCA9685_H

#include "sys.h"
#include "IIC3.h"

    //PCA9685设备地址
#define PCA9685_adrr 0x80

//相关寄存器地址
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

//MODE1寄存器地址
#define PCA9685_MODE1 0x0

//PRE_SCALE寄存器地址
#define PCA9685_PRESCALE 0xFE

//0通道的ON和OFF寄存器地址
#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD
/* Exported functions --------------------------------------------------------*/					
void PCA9685_write(unsigned char reg,unsigned char data);
u8 PCA9685_read(unsigned char reg);
void setPWMFreq(u8 freq);
void setPWM(u8 num, u16 on, u16 off);
u16 calculate_PWM(u8 angle);
void crazyMe(int i,u16 a,u16 b,u16 tim,u8 xf);

#endif

/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/







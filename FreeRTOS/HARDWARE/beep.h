#ifndef __BEEP_H
#define __BEEP_H 			   
#include "sys.h"	 

#define BEEP PFout(8)	// 蜂鸣器控制IO位带操作。
#define Beep Beep_one
void BEEP_Init(void);//初始化		
void Beep_one(void);
#endif



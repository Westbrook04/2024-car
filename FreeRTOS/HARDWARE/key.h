#ifndef __KEY_H
#define __KEY_H 			   
#include "sys.h"	 

#define KEY1 		PGin(13)   	  //PE4
#define KEY2 		PGin(10)		 //PE3 
#define KEY3 		PGin(15)		//P32
#define KEY4 		PBin(3)		 //PA0 

#define KEY_UP         1
#define KEY_DOWN	   2 
#define KEY_CONFIRM	   3
#define KEY_CANCEL     4

void KEY_Init(void);
u8 KEY_Scan(u8);  		//°´¼üÉ¨Ãèº¯Êý	

#endif


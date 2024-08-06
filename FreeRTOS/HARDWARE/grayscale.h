#ifndef _GRAYSCALE_H
#define _GRAYSCALE_H
#include "sys.h"

//1路激光传感器模块
#define HDIO1 PCin(0)
#define HDIO2 PCin(1)
#define HDIO3 PCin(2)
#define HDIO4 PCin(3)
#define HDIO5 PBin(0)
#define HDIO6 PBin(1)
#define HDIO7 PAin(4)
#define HDIO8 PAin(5)
//8路灰度1
#define EDIO1 PFin(0)
#define EDIO2 PFin(1)
#define EDIO3 PFin(2)
#define EDIO4 PFin(4)
#define EDIO5 PFin(5)
#define EDIO6 PFin(6)
#define EDIO7 PFin(7)
#define EDIO8 PFin(8)
//8路灰度2
#define EDIO9 PEin(1)
#define EDIO10 PEin(0)
#define EDIO11 PBin(9)
#define EDIO12 PBin(8)
#define EDIO13 PBin(7)
#define EDIO14 PBin(6)
#define EDIO15 PBin(5)
#define EDIO16 PBin(4)

void HDIO_Init(void);
void eight_gray1(void);
void eight_gray2(void);
void Grayscale_Init(void);

#endif





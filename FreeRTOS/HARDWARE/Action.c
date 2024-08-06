#include "Action.h"
#include "delay.h"
#include "LobotSerialServo.h"
//运用static，将数据存储为静态，可大大减轻cpu的存储负担
static u16 Zeroservo[18]={ 520,399,326,533,483	,529,830,876,447,499,463,423,508,543,464,132,126,500};
	                // 1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16	   17    18    
#define null 500//转过来的过程中会出现许多null,这样就解决了报错


void zero()//初态
{
		static s16 pose1[18]={489,505	,493	,499	,528	,871,	502	,495	,465,	497	,434,	497	,92	,503};slowpose(pose1,1000);
}

//语音识别
void front_run(void)//前进
{
	int i;
	
//	static s16 pose14[18]={489,491,487,502,524,873,503,498,504,499,436,499,93,504,null,null,null,null};slowpose(pose14,600);
	for(i=1;i>=0;i--)
	{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,300);
	static s16 pose2[18]={425,491,487,502,330,873,503,385,504,499,436,305,105,504};slowpose(pose2,600);
	static s16 pose3[18]={425,570,565,502,370,873,503,315,585,580,436,400,93,504};slowpose(pose3,600);
	static s16 pose4[18]={500,570,565,502,524,873,503,505,585,580,436,499,93,504};slowpose(pose4,800);
	static s16 pose5[18]={610,570,565,502,665,873,503,560,550,590,436,715,93,504};slowpose(pose5,600);
	static s16 pose6[18]={605,380,360,502,635,873,535,560,395,380,436,610,93,504};slowpose(pose6,1000);
	static s16 pose7[18]={605,355,360,502,524,873,503,525,370,355,436,499,93,504};slowpose(pose7,800);
	static s16 pose8[18]={475,330,275,502,340,873,503,460,360,395,470,340,93,504};slowpose(pose8,1000);
	static s16 pose9[18]={430,370,340,502,524,873,503,380,365,390,436,499,93,504};slowpose(pose9,1000);
	static s16 pose10[18]={425,405,360,502,524,873,503,385,405,435,436,499,93,504};slowpose(pose10,500);
	static s16 pose11[18]={425,405,360,502,524,873,503,420,450,480,436,499,93,504};slowpose(pose11,300);
	static s16 pose12[18]={425,505,500,502,524,873,503,340,485,480,436,499,93,504};slowpose(pose12,600);
	static s16 pose13[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose13,800);
	}
}
void back_run(void)//后退
{
	int i;
	for(i=1;i>=0;i--)
	{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={425,505,500,502,524,873,503,340,485,480,436,499,93,504};slowpose(pose2,800);
	static s16 pose3[18]={425,405,360,502,524,873,503,420,450,480,436,499,93,504};slowpose(pose3,600);
	static s16 pose4[18]={425,405,305,502,524,873,503,385,405,490,436,499,93,504};slowpose(pose4,1000);
	static s16 pose5[18]={430,370,285,502,524,873,503,380,365,440,430,499,93,504};slowpose(pose5,800);
	static s16 pose6[18]={430,370,285,480,524,873,503,455,360,440,415,499,93,504};slowpose(pose6,800);
	static s16 pose7[18]={605,355,360,502,524,873,503,525,370,355,436,499,93,504};slowpose(pose7,1000);
	static s16 pose8[18]={605,380,360,502,635,873,535,560,395,380,436,610,93,504};slowpose(pose8,1000);
	static s16 pose9[18]={610,570,565,502,665,873,503,560,550,590,436,715,93,504};slowpose(pose9,800);
	static s16 pose10[18]={500,570,565,502,524,873,503,505,585,580,436,499,93,504};slowpose(pose10,800);
	static s16 pose11[18]={425,570,565,502,370,873,503,315,585,580,436,400,93,504};slowpose(pose11,800);
	static s16 pose12[18]={425,491,487,502,330,873,503,385,504,499,436,305,105,504};slowpose(pose12,800);
	static s16 pose13[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose13,600);
  }
//	static s16 pose14[18]={465,660,610,520,521,872,502,450,500,530,455,499,92,502,500,500,500,500};slowpose(pose14,600);
//	static s16 pose15[18]={465,605,610,510,521,872,502,450,545,530,450,499,92,502,500,500,500,500};slowpose(pose15,600);
//	static s16 pose16[18]={415,605,610,510,521,872,502,310,545,530,450,499,92,502,500,500,500,500};slowpose(pose16,1000);
//	static s16 pose17[18]={415,605,610,510,521,872,502,375,405,385,450,499,92,502,500,500,500,500};slowpose(pose17,600);
//	static s16 pose18[18]={445,605,610,510,521,872,502,375,405,385,450,499,92,502,500,500,500,500};slowpose(pose18,600);
//	static s16 pose19[18]={500,605,610,510,521,872,502,495,405,385,450,499,92,502,500,500,500,500};slowpose(pose19,1000);
}

void tuiyibu(void)//后退一步
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={425,505,500,502,524,873,503,340,485,480,436,499,93,504};slowpose(pose2,800);
	static s16 pose3[18]={425,405,360,502,524,873,503,420,450,480,436,499,93,504};slowpose(pose3,600);
	static s16 pose4[18]={425,405,305,502,524,873,503,385,405,490,436,499,93,504};slowpose(pose4,1000);
	static s16 pose5[18]={430,370,285,502,524,873,503,380,365,440,430,499,93,504};slowpose(pose5,800);
	static s16 pose6[18]={430,370,285,480,524,873,503,455,360,440,415,499,93,504};slowpose(pose6,800);
	static s16 pose7[18]={605,355,360,502,524,873,503,525,370,355,436,499,93,504};slowpose(pose7,1000);
	static s16 pose8[18]={605,380,360,502,635,873,535,560,395,380,436,610,93,504};slowpose(pose8,1000);
	static s16 pose9[18]={610,570,565,502,665,873,503,560,550,590,436,715,93,504};slowpose(pose9,800);
	static s16 pose10[18]={500,570,565,502,524,873,503,505,585,580,436,499,93,504};slowpose(pose10,800);
	static s16 pose11[18]={425,570,565,502,370,873,503,315,585,580,436,400,93,504};slowpose(pose11,800);
	static s16 pose12[18]={425,491,487,502,330,873,503,385,504,499,436,305,105,504};slowpose(pose12,800);
	static s16 pose13[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose13,600);
}
void left_move_pose(void)//左移
{
	int i;
	for(i=6;i>=0;i--)
	{
	static s16 pose1[18]={493,489,499,499,531,872,502,490,504,494,433,495,92,502,null,null,null,null};slowpose(pose1,800);
	static s16 pose2[18]={685,489,499,585,531,872,502,490,504,494,433,495,92,502,500,500,500,500};slowpose(pose2,700);
	static s16 pose3[18]={465,489,499,515,531,872,502,365,504,494,433,495,92,502,500,500,500,500};slowpose(pose3,700);
  }
	static s16 pose1[18]={493,489,499,499,531,872,502,490,504,494,433,495,92,502,null,null,null,null};slowpose(pose1,800);

}


void zuoyisibu(void)//左移四步
{
	int i;
	for(i=3;i>=0;i--)
	{
	static s16 pose1[18]={493,489,499,499,531,872,502,490,504,494,433,495,92,502,null,null,null,null};slowpose(pose1,800);
	static s16 pose2[18]={685,489,499,585,531,872,502,490,504,494,433,495,92,502,500,500,500,500};slowpose(pose2,700);
	static s16 pose3[18]={465,489,499,515,531,872,502,365,504,494,433,495,92,502,500,500,500,500};slowpose(pose3,700);
  }
	static s16 pose1[18]={493,489,499,499,531,872,502,490,504,494,433,495,92,502,null,null,null,null};slowpose(pose1,800);

}

void right_move_pose(void)//右移
{
	int i;
	for(i=7;i>=0;i--)
	{
	static s16 pose1[18]={491,491,499,499,530,871,502,495,503,494,432,495,92,502,null,null,null,null};slowpose(pose1,800);
	static s16 pose2[18]={490,491,499,499,530,871,502,315,503,494,365,495,92,502,500,500,500,500};slowpose(pose2,700);
	static s16 pose3[18]={615,491,499,495,530,871,502,510,503,494,450,495,92,502,500,500,500,500};slowpose(pose3,700);
  }
	static s16 pose1[18]={493,489,499,499,531,872,502,490,504,494,433,495,92,502,null,null,null,null};slowpose(pose1,800);
}

void youyisibu(void)//右移四步
{
	int i;
	for(i=3;i>=0;i--)
	{
	static s16 pose1[18]={491,491,499,499,530,871,502,495,503,494,432,495,92,502,null,null,null,null};slowpose(pose1,800);
	static s16 pose2[18]={490,491,499,499,530,871,502,315,503,494,365,495,92,502,500,500,500,500};slowpose(pose2,700);
	static s16 pose3[18]={615,491,499,495,530,871,502,510,503,494,450,495,92,502,500,500,500,500};slowpose(pose3,700);
  }
	static s16 pose1[18]={493,489,499,499,531,872,502,490,504,494,433,495,92,502,null,null,null,null};slowpose(pose1,800);
}


void turn_left(void)//左转
{
	int i;
	for(i=7;i>=0;i--)
	{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={470,499,504,515,533,854,502,395,467,458,470,483,92,501,500,500,500,500};slowpose(pose2,800);
	static s16 pose3[18]={495,495,465,555,533,854,502,370,430,375,490,483,92,501,500,500,500,500};slowpose(pose3,800);
	static s16 pose4[18]={440,515,500,565,533,854,502,355,445,365,500,483,92,501,500,500,500,500};slowpose(pose4,800);
	static s16 pose5[18]={440,515,500,565,533,854,502,355,500,480,500,483,92,501,500,500,500,500};slowpose(pose5,1000);
	
  }
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
//	static s16 pose7[18]={489,491,493,499,528,871,502,495,503,497,434,497,92,503,null,null,null,null};slowpose(pose7,1000);
}
void turn_right(void)//右转
{
	int i;
	for(i=8;i>=0;i--)
	{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={625,491,493,499,528,871,502,535,480,497,434,497,92,503};slowpose(pose2,800);
	static s16 pose3[18]={625,465,569,499,528,871,502,525,470,490,434,497,92,503,};slowpose(pose3,800);
	static s16 pose4[18]={625,465,569,499,528,871,502,555,485,495,400,497,92,503};slowpose(pose4,800);
	static s16 pose5[18]={645,515,510,499,528,871,502,555,485,495,400,497,92,503};slowpose(pose5,800);
//static s16 pose6[18]={590,515,510,499,528,871,502,520,485,495,430,497,92,503};slowpose(pose6,800);
 }
	static s16 pose1[18]={489,505	,493	,499	,528	,871,	502	,495	,465,	497	,434,	497	,92	,503};slowpose(pose1,800);
//  static s16 pose6[18]={590,515,510,499,528,871,502,520,485,495,430,497,92,503};slowpose(pose6,800);
//	static s16 pose7[18]={489,491,493,499,528,871,502,495,503,497,434,497,92,503};slowpose(pose7,800);
}
void turn_lefthand(void)//举左手
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={489,505,493,499,528,210,502,495,465,497,434,497,92,503};slowpose(pose2,800);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
}
void turn_twohand(void)//举双手
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={489,505,493,499,528,210,502,495,465,497,434,497,700,502};slowpose(pose2,800);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
}
void one_leg_stand(void)//单脚撑
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503,null,null,null,null};slowpose(pose1,1000);
	static s16 pose2[18]={605,505,497,499,530,857,501,497,465,494,439,495,92,502,500,500,500,500};slowpose(pose2,1000);
	static s16 pose3[18]={605,505,497,499,530,500,501,555,470,494,415,495,470,502,500,500,500,500};slowpose(pose3,1000);
	static s16 pose4[18]={560,505,497,490,530,500,501,555,470,494,415,495,470,502,500,500,500,500};slowpose(pose4,1000);
	static s16 pose5[18]={490,160,505,490,530,500,501,555,470,494,405,495,470,502,500,500,500,500};slowpose(pose5,1000);
	delay_s(2);
	delay_ms(500);
	static s16 pose6[18]={560,505,497,490,530,500,501,540,470,494,405,495,470,502,500,500,500,500};slowpose(pose6,1000);
	static s16 pose7[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503,null,null,null,null};slowpose(pose7,1000);
}



void dianjiao(void)//踮脚
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={630,510,504,504,530,520,499,385,465,453,444,482,455,487};slowpose(pose2,1000);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,800);
}

void xiadun(void)//下蹲
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={487,645,683,498,530,855,499,505,330,297,447,495,102,502};slowpose(pose2,1000);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,800);
}

void llrr(void)//左手在左右手在右
{                      //1  2   3    4   5   6   7   8   9   10  11 12  13  14
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,1000);
	static s16 pose2[18]={493,504,493,503,530,867,186,497,465,497,444,482,104,866};slowpose(pose2,1000);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,1000);
}

//视觉识别

void shijuechutai(void)//视觉识别初态
{
	static s16 pose1[18]={499,475,475,516,527,871,501,505,505,505,455,495,92,503,500,500,500,500};slowpose(pose1,1000);
}

void chayao(void)//叉腰
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,800);
	static s16 pose2[18]={491,505,500,497,528,745,770,499,480,491,438,495,200,215};slowpose(pose2,800);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,800);
  shijuechutai();
}

void big_stand_pose(void)//大字站立
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,1000);
	static s16 pose2[18]={491,485,500,497,528,495,499,499,510,491,438,495,470,502,500,500,500,500};slowpose(pose2,1000);
	static s16 pose3[18]={565,510,500,540,528,495,499,450,490,491,405,495,470,502,500,500,500,500};slowpose(pose3,1000);
	delay_s(2);
	static s16 pose4[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose4,1000);
	shijuechutai();
}
void twohands_up(void)//双手上举
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,1000);
	static s16 pose2[18]={491,505,493,497,528,495,140,499,465,497,438,495,470,885};slowpose(pose2,1000);
		delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,1000);
	shijuechutai();
}
void lefthand_up_righthand_down(void)//左手上右手下
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,1000);
	static s16 pose2[18]={491,505,493,497,528,510,150,499,470,497,438,495,470,110};slowpose(pose2,1000);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,1000);
	shijuechutai();
}
void leftleg_move(void)//单脚站立
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,1000);
	static s16 pose2[18]={625,505,500,465,528,510,499,499,480,491,438,495,440,502,500,500,500,500};slowpose(pose2,1000);
	static s16 pose3[18]={625,505,500,465,528,510,499,545,480,491,380,495,440,502,500,500,500,500};slowpose(pose3,1000);
	static s16 pose4[18]={570,505,500,485,528,510,499,555,480,491,400,495,440,502,500,500,500,500};slowpose(pose4,1000);
	delay_s(2);
	static s16 pose5[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose5,1000);
	shijuechutai();
}
void left_jingli(void)//敬礼
{
	static s16 pose1[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose1,1000);
	static s16 pose2[18]={494,505,493,504,530,855,499,495,465,497,445,482,914,627};slowpose(pose2,1000);
	delay_s(2);
	static s16 pose3[18]={489,505,493,499,528,871,502,495,465,497,434,497,92,503};slowpose(pose3,1000);
	shijuechutai();
}


//韵律识别
void dance_one(void)//三首歌
{
	
	static s16 pose1[18]={489,498,495,499,526,868,501,501,475,496,441,497,90,502};slowpose(pose1,1000);
	static s16 pose2[18]={500,495,486,513,151,508,533,499,510,516,454,852,455,504};slowpose(pose2,800);
	static s16 pose3[18]={483,488,489,504,530,509,534,293,522,516,374,505,453,503};slowpose(pose3,900);
	static s16 pose4[18]={597,491,489,510,530,780,260,533,515,516,442,495,565,375};slowpose(pose4,800);
	static s16 pose5[18]={490,491,489,510,530,780,260,490,515,516,442,495,565,375};slowpose(pose5,400);
	static s16 pose6[18]={483,488,489,504,151,509,534,293,522,516,374,852,453,503};slowpose(pose6,800);
	static s16 pose7[18]={597,491,489,510,530,245,760,533,515,516,442,495,185,755};slowpose(pose7,800);
	static s16 pose8[18]={490,491,489,510,530,780,260,490,515,516,442,495,565,375};slowpose(pose8,800);
	
	static s16 pose9[18]={510,499,495,499,526,868,501,423,497,496,343,498,222,272};slowpose(pose9,600);
	static s16 pose10[18]={510,499,495,520,526,868,501,275,497,496,343,498,222,272};slowpose(pose10,400);
	static s16 pose11[18]={510,499,495,499,526,868,501,423,497,496,343,498,222,272};slowpose(pose11,400);
	static s16 pose12[18]={510,499,495,520,526,868,501,275,497,496,343,498,222,272};slowpose(pose12,400);
	static s16 pose13[18]={502,504,495,518,526,505,497,478,478,478,423,497,480,502};slowpose(pose13,600);
	static s16 pose14[18]={502,505,495,519,707,505,497,478,478,478,425,291,482,502};slowpose(pose14,300);
	static s16 pose15[18]={502,505,495,518,707,505,722,478,478,478,425,292,463,347};slowpose(pose15,300);
	static s16 pose16[18]={502,504,495,519,706,769,721,478,478,478,424,292,170,350};slowpose(pose16,300);
	static s16 pose17[18]={501,505,495,519,195,769,721,478,478,478,424,770,169,349};slowpose(pose17,600);
	static s16 pose18[18]={501,504,494,519,195,848,721,478,478,478,424,771,70,349};slowpose(pose18,200);
	static s16 pose19[18]={502,504,495,519,32,859,722,478,478,478,424,689,70,349};slowpose(pose19,500);
	static s16 pose20[18]={502,504,495,519,347,858,721,478,478,478,424,1000,70,347};slowpose(pose20,500);


}

void dance_two(void)//三首歌
{
		static s16 pose1[18]={615,494,496,520,57,858,722,490,496,479,451,679,70,349};slowpose(pose1,600);
	static s16 pose2[18]={510,494,495,520,57,858,722,513,497,479,451,680,70,349};slowpose(pose2,400);
	static s16 pose3[18]={480,495,495,530,336,858,721,402,497,479,447,957,70,347};slowpose(pose3,600);
	static s16 pose4[18]={483,495,495,515,336,858,721,490,497,480,446,957,70,347};slowpose(pose4,400);
	static s16 pose5[18]={496,497,495,516,526,723,761,491,483,478,447,479,221,260};slowpose(pose5,700);
	static s16 pose6[18]={548,499,486,560,151,504,514,497,358,357,446,852,453,521};slowpose(pose6,800);
	static s16 pose7[18]={548,499,483,560,151,607,675,497,358,356,446,852,323,344};slowpose(pose7,400);
	static s16 pose8[18]={548,499,483,560,151,871,683,497,357,357,446,852,92,328};slowpose(pose8,400);
	static s16 pose9[18]={548,499,483,560,151,634,683,497,356,357,446,852,266,331};slowpose(pose9,500);
	static s16 pose10[18]={547,499,483,560,151,892,683,497,356,357,446,852,59,328};slowpose(pose10,500);
	static s16 pose11[18]={500,495,486,513,151,508,533,499,510,516,454,852,455,504};slowpose(pose11,900);
	static s16 pose12[18]={497,620,596,529,151,508,533,498,495,518,466,852,455,504};slowpose(pose12,800);
	static s16 pose13[18]={496,620,597,532,151,594,693,497,495,518,466,852,293,310};slowpose(pose13,400);
	static s16 pose14[18]={497,612,596,532,151,900,693,498,499,518,466,852,73,311};slowpose(pose14,500);
	static s16 pose15[18]={496,620,597,532,151,594,693,497,495,518,466,852,293,310};slowpose(pose15,500);
	static s16 pose16[18]={496,502,489,511,530,504,496,495,497,499,442,495,466,483};slowpose(pose16,800);
	static s16 pose17[18]={499,499,489,513,528,781,208,495,497,499,443,495,705,287};slowpose(pose17,500);
	static s16 pose18[18]={499,499,489,514,527,195,799,497,497,499,443,495,151,750};slowpose(pose18,500);
	static s16 pose19[18]={499,499,489,514,529,814,228,495,497,499,442,495,701,295};slowpose(pose19,500);
	static s16 pose20[18]={499,499,489,513,528,495,512,496,497,499,443,495,469,523};slowpose(pose20,500);
	static s16 pose21[18]={499,499,489,514,135,495,512,496,497,499,443,833,458,499};slowpose(pose21,350);
	static s16 pose22[18]={499,499,489,514,136,495,727,495,497,499,444,833,458,271};slowpose(pose22,200);

}

void dance_three(void)//三首歌
{
	static s16 pose1[18]={499,502,485,514,136,924,727,495,497,501,443,832,56,270};slowpose(pose1,500);
	static s16 pose2[18]={487,504,485,521,135,903,520,360,497,501,413,833,55,271};slowpose(pose2,500);
	static s16 pose3[18]={493,504,488,502,136,903,520,483,498,501,426,833,56,270};slowpose(pose3,350);
	static s16 pose4[18]={619,505,486,510,136,904,520,510,498,501,426,832,97,507};slowpose(pose4,500);
	static s16 pose5[18]={493,504,487,509,135,880,520,494,497,501,436,831,95,505};slowpose(pose5,350);
	static s16 pose6[18]={489,506,487,524,135,734,784,392,497,501,438,830,95,504};slowpose(pose6,500);
	static s16 pose7[18]={492,504,487,515,136,734,784,486,498,501,435,831,95,505};slowpose(pose7,350);
	static s16 pose8[18]={612,506,487,520,136,734,784,510,497,501,437,830,211,244};slowpose(pose8,500);
	static s16 pose9[18]={505,504,487,520,136,734,784,495,497,501,440,830,211,244};slowpose(pose9,350);
	static s16 pose10[18]={506,497,488,521,136,500,533,495,497,499,440,832,436,510};slowpose(pose10,600);
	static s16 pose11[18]={560,513,489,589,135,499,532,551,475,495,519,830,436,508};slowpose(pose11,800);
	static s16 pose12[18]={506,497,488,521,136,500,533,495,497,499,440,832,436,510};slowpose(pose12,600);
	static s16 pose13[18]={450,505,491,443,136,499,531,431,495,498,355,830,435,508};slowpose(pose13,800);
	static s16 pose14[18]={506,497,488,521,136,500,533,495,497,499,440,832,436,510};slowpose(pose14,600);
	static s16 pose15[18]={489,498,495,499,526,868,501,501,475,496,441,497,90,502};slowpose(pose15,800);
}


void dance_zixuan_one(void)//自选歌曲
{
	static s16 pose1[18]={489,500,490,499,528,870,502,495,491,497,434,497,90,503};slowpose(pose1,1000);
	static s16 pose2[18]={491,498,490,499,499,223,211,497,491,497,437,504,767,755};slowpose(pose2,1000);
	static s16 pose3[18]={491,499,490,499,761,223,211,497,491,498,436,230,769,755};slowpose(pose3,500);
	static s16 pose4[18]={491,499,490,499,761,113,211,497,491,498,436,230,546,754};slowpose(pose4,400);
	static s16 pose5[18]={491,499,490,500,761,360,281,496,491,498,437,229,874,755};slowpose(pose5,400);
	static s16 pose6[18]={491,499,490,499,761,109,241,497,491,498,436,229,823,755};slowpose(pose6,400);
	static s16 pose7[18]={494,620,626,499,513,750,529,497,343,323,434,497,181,521};slowpose(pose7,1000);
	static s16 pose8[18]={489,505,493,499,528,750,502,495,465,497,434,497,181,503};slowpose(pose8,800);
	static s16 pose9[18]={521,504,494,519,526,750,504,561,487,494,496,495,470,145};slowpose(pose9,800);
	static s16 pose10[18]={417,504,495,439,526,510,895,451,487,494,402,495,254,476};slowpose(pose10,800);
	static s16 pose11[18]={521,504,494,519,526,750,504,561,487,494,496,495,460,125};slowpose(pose11,800);
	static s16 pose12[18]={417,504,495,439,526,510,920,451,487,494,402,495,254,476};slowpose(pose12,800);
	static s16 pose13[18]={489,505,493,499,528,855,502,495,465,497,434,497,95,503};slowpose(pose13,600);
	static s16 pose14[18]={447,497,495,483,526,853,503,393,487,479,411,890,92,254};slowpose(pose14,600);
	static s16 pose15[18]={450,497,495,466,526,853,502,461,487,478,404,890,434,499};slowpose(pose15,600);
	static s16 pose16[18]={606,497,499,462,162,859,820,516,489,478,408,890,434,499};slowpose(pose16,800);
	static s16 pose17[18]={497,523,499,506,162,497,533,502,468,479,454,890,434,499};slowpose(pose17,600);
	static s16 pose18[18]={466,516,499,517,515,716,799,379,468,479,450,517,773,390};slowpose(pose18,800);
	static s16 pose19[18]={640,516,499,519,515,716,798,538,469,478,454,517,773,390};slowpose(pose19,700);
	static s16 pose20[18]={497,515,499,515,515,716,798,498,470,479,457,517,773,390};slowpose(pose20,400);

}

void dance_zixuan_two(void)//自选歌曲
{
	
	static s16 pose1[18]={496,515,499,515,516,782,244,495,471,479,455,516,165,863};slowpose(pose1,600);
	static s16 pose2[18]={495,657,651,516,293,782,244,495,343,339,456,320,165,863};slowpose(pose2,900);
	static s16 pose3[18]={496,515,499,515,670,782,244,495,471,479,455,690,165,863};slowpose(pose3,900);
	static s16 pose4[18]={495,657,651,516,293,782,244,495,343,339,456,320,165,863};slowpose(pose4,900);
	static s16 pose5[18]={496,515,499,515,495,740,820,495,471,479,455,885,145,515};slowpose(pose5,900);
	static s16 pose6[18]={502,510,504,524,495,501,186,503,474,474,457,483,457,820};slowpose(pose6,800);
	static s16 pose7[18]={511,530,461,522,650,750,185,504,565,628,453,710,274,820};slowpose(pose7,1000);
	static s16 pose8[18]={502,510,504,524,495,730,186,503,474,474,457,483,215,820};slowpose(pose8,800);
	static s16 pose9[18]={521,530,540,516,339,732,185,523,341,361,450,292,215,819};slowpose(pose9,1000);
	static s16 pose10[18]={502,510,504,524,495,730,186,503,474,474,457,483,215,820};slowpose(pose10,800);
	static s16 pose11[18]={478,516,502,536,494,742,819,365,473,478,454,881,143,515};slowpose(pose11,400);
	static s16 pose12[18]={502,516,502,525,494,742,819,494,473,478,455,881,143,515};slowpose(pose12,400);
	static s16 pose13[18]={641,516,502,536,493,742,819,529,473,477,457,881,143,515};slowpose(pose13,400);
	static s16 pose14[18]={533,516,502,553,493,742,819,526,473,478,477,881,143,515};slowpose(pose14,400);
	static s16 pose15[18]={489,500,490,499,528,870,502,495,491,497,434,497,90,503};slowpose(pose15,500);
	static s16 pose16[18]={491,499,494,502,170,868,501,496,489,495,436,849,87,504};slowpose(pose16,500);
	static s16 pose17[18]={491,499,494,502,170,890,672,497,489,495,436,849,28,311};slowpose(pose17,300);
	static s16 pose18[18]={491,499,494,502,170,868,501,496,489,495,436,849,87,504};slowpose(pose18,300);
	static s16 pose19[18]={491,499,494,502,170,890,672,497,489,495,436,849,28,311};slowpose(pose19,300);
	static s16 pose20[18]={491,499,494,502,170,868,501,496,489,495,436,849,87,504};slowpose(pose20,300);

}

void dance_zixuan_three(void)//自选歌曲
{
	static s16 pose1[18]={494,498,494,501,520,304,360,496,489,490,434,683,118,309};slowpose(pose1,600);
	static s16 pose2[18]={615,498,494,490,520,304,360,515,489,490,405,683,118,309};slowpose(pose2,300);
	static s16 pose3[18]={494,498,494,501,520,304,360,496,489,490,434,683,118,309};slowpose(pose3,300);
	static s16 pose4[18]={495,498,494,500,306,787,750,491,489,489,430,478,731,411};slowpose(pose4,700);
	static s16 pose5[18]={475,498,494,500,306,787,750,400,489,489,430,478,731,411};slowpose(pose5,300);
	static s16 pose6[18]={495,498,494,500,306,787,750,491,489,489,430,478,731,411};slowpose(pose6,300);
	static s16 pose7[18]={489,500,490,499,528,870,502,495,491,497,434,497,90,503};slowpose(pose7,800);
	static s16 pose8[18]={605,498,493,526,520,499,509,332,489,491,434,483,446,504};slowpose(pose8,800);
	static s16 pose9[18]={606,499,494,526,520,750,509,332,489,490,434,483,716,504};slowpose(pose9,500);
	static s16 pose10[18]={605,498,494,526,520,353,509,332,489,491,434,482,299,504};slowpose(pose10,500);
	static s16 pose11[18]={605,499,494,526,352,512,509,333,489,491,434,322,451,504};slowpose(pose11,400);
	static s16 pose12[18]={598,498,494,533,708,512,509,334,489,491,435,668,452,504};slowpose(pose12,300);
	static s16 pose13[18]={598,498,494,533,220,850,735,334,489,491,435,775,150,210};slowpose(pose13,600);
	static s16 pose14[18]={598,498,494,533,220,905,735,334,489,491,435,775,65,210};slowpose(pose14,200);
	static s16 pose15[18]={598,498,494,533,220,710,735,334,489,491,435,775,165,210};slowpose(pose15,200);
	static s16 pose16[18]={598,498,494,533,220,515,505,334,489,491,435,775,445,505};slowpose(pose16,500);
	static s16 pose17[18]={489,500,490,499,528,870,502,495,491,497,434,497,90,503};slowpose(pose17,1000);

}


void slowpose(s16 *begin,u16 time)//time最好不要超过1800，不然会出问题
{
	for(int i=0;i<14;i++)//本来是18个舵机的函数，但只要用14个，因此这里改为14
	{
		LobotSerialServoMove(i+1,*(begin++),time);
	}
	delay_ms(time-1);
}
/*void mode()
{
	static s16 pose0[18]={};slowpose(pose0,1000);
	static s16 pose1[18]={};slowpose(pose1,1000);
	static s16 pose2[18]={};slowpose(pose2,1000);
	static s16 pose3[18]={};slowpose(pose3,1000);
	static s16 pose4[18]={};slowpose(pose4,1000);
	static s16 pose5[18]={};slowpose(pose5,1000);
	static s16 pose6[18]={};slowpose(pose6,1000);
	static s16 pose7[18]={};slowpose(pose7,1000);
	static s16 pose8[18]={};slowpose(pose8,1000);
	static s16 pose9[18]={};slowpose(pose9,1000);
	static s16 pose10[18]={};slowpose(pose10,1000);
	static s16 pose11[18]={};slowpose(pose11,1000);
	static s16 pose12[18]={};slowpose(pose12,1000);
	static s16 pose13[18]={};slowpose(pose13,1000);
	static s16 pose14[18]={};slowpose(pose14,1000);
	static s16 pose15[18]={};slowpose(pose15,1000);
	static s16 pose16[18]={};slowpose(pose16,1000);
	static s16 pose17[18]={};slowpose(pose17,1000);
	static s16 pose18[18]={};slowpose(pose18,1000);
	static s16 pose19[18]={};slowpose(pose19,1000);
	static s16 pose20[18]={};slowpose(pose20,1000);
	static s16 pose21[18]={};slowpose(pose21,1000);
	static s16 pose22[18]={};slowpose(pose22,1000);
	static s16 pose23[18]={};slowpose(pose23,1000);
	static s16 pose24[18]={};slowpose(pose24,1000);
	static s16 pose25[18]={};slowpose(pose25,1000);
	static s16 pose26[18]={};slowpose(pose26,1000);
	static s16 pose27[18]={};slowpose(pose27,1000);
	static s16 pose28[18]={};slowpose(pose28,1000);
	static s16 pose29[18]={};slowpose(pose29,1000);
	static s16 pose30[18]={};slowpose(pose30,1000);
	static s16 pose31[18]={};slowpose(pose31,1000);
	static s16 pose32[18]={};slowpose(pose32,1000);
	static s16 pose33[18]={};slowpose(pose33,1000);
	static s16 pose34[18]={};slowpose(pose34,1000);
	static s16 pose35[18]={};slowpose(pose35,1000);
	static s16 pose36[18]={};slowpose(pose36,1000);
	static s16 pose37[18]={};slowpose(pose37,1000);
	static s16 pose38[18]={};slowpose(pose38,1000);
	static s16 pose39[18]={};slowpose(pose39,1000);
	static s16 pose40[18]={};slowpose(pose40,1000);
	static s16 pose41[18]={};slowpose(pose41,1000);
	static s16 pose42[18]={};slowpose(pose42,1000);
	static s16 pose43[18]={};slowpose(pose43,1000);
	static s16 pose44[18]={};slowpose(pose44,1000);
	static s16 pose45[18]={};slowpose(pose45,1000);
	static s16 pose46[18]={};slowpose(pose46,1000);
	static s16 pose47[18]={};slowpose(pose47,1000);
	static s16 pose48[18]={};slowpose(pose48,1000);
	static s16 pose49[18]={};slowpose(pose49,1000);
	static s16 pose50[18]={};slowpose(pose50,1000);
	static s16 pose51[18]={};slowpose(pose51,1000);
	static s16 pose52[18]={};slowpose(pose52,1000);
	static s16 pose53[18]={};slowpose(pose53,1000);
	static s16 pose54[18]={};slowpose(pose54,1000);
	static s16 pose55[18]={};slowpose(pose55,1000);
	static s16 pose56[18]={};slowpose(pose56,1000);
	static s16 pose57[18]={};slowpose(pose57,1000);
	static s16 pose58[18]={};slowpose(pose58,1000);
	static s16 pose59[18]={};slowpose(pose59,1000);
	static s16 pose60[18]={};slowpose(pose60,1000);
	static s16 pose61[18]={};slowpose(pose61,1000);
	static s16 pose62[18]={};slowpose(pose62,1000);
	static s16 pose63[18]={};slowpose(pose63,1000);
	static s16 pose64[18]={};slowpose(pose64,1000);
	static s16 pose65[18]={};slowpose(pose65,1000);
	static s16 pose66[18]={};slowpose(pose66,1000);
	static s16 pose67[18]={};slowpose(pose67,1000);
	static s16 pose68[18]={};slowpose(pose68,1000);
	static s16 pose69[18]={};slowpose(pose69,1000);
	static s16 pose70[18]={};slowpose(pose70,1000);
	static s16 pose71[18]={};slowpose(pose71,1000);
	static s16 pose72[18]={};slowpose(pose72,1000);
	static s16 pose73[18]={};slowpose(pose73,1000);
	static s16 pose74[18]={};slowpose(pose74,1000);
	static s16 pose75[18]={};slowpose(pose75,1000);
	static s16 pose76[18]={};slowpose(pose76,1000);
	static s16 pose77[18]={};slowpose(pose77,1000);
	static s16 pose78[18]={};slowpose(pose78,1000);
	static s16 pose79[18]={};slowpose(pose79,1000);
	static s16 pose80[18]={};slowpose(pose80,1000);
	static s16 pose81[18]={};slowpose(pose81,1000);
	static s16 pose82[18]={};slowpose(pose82,1000);
	static s16 pose83[18]={};slowpose(pose83,1000);
	static s16 pose84[18]={};slowpose(pose84,1000);
	static s16 pose85[18]={};slowpose(pose85,1000);
	static s16 pose86[18]={};slowpose(pose86,1000);
	static s16 pose87[18]={};slowpose(pose87,1000);
	static s16 pose88[18]={};slowpose(pose88,1000);
	static s16 pose89[18]={};slowpose(pose89,1000);
	static s16 pose90[18]={};slowpose(pose90,1000);
	static s16 pose91[18]={};slowpose(pose91,1000);
	static s16 pose92[18]={};slowpose(pose92,1000);
	static s16 pose93[18]={};slowpose(pose93,1000);
	static s16 pose94[18]={};slowpose(pose94,1000);
	static s16 pose95[18]={};slowpose(pose95,1000);
	static s16 pose96[18]={};slowpose(pose96,1000);
	static s16 pose97[18]={};slowpose(pose97,1000);
	static s16 pose98[18]={};slowpose(pose98,1000);
	static s16 pose99[18]={};slowpose(pose99,1000);
	static s16 pose100[18]={};slowpose(pose100,1000);
	static s16 pose101[18]={};slowpose(pose101,1000);
	static s16 pose102[18]={};slowpose(pose102,1000);
	static s16 pose103[18]={};slowpose(pose103,1000);
	static s16 pose104[18]={};slowpose(pose104,1000);
	static s16 pose105[18]={};slowpose(pose105,1000);
	static s16 pose106[18]={};slowpose(pose106,1000);
	static s16 pose107[18]={};slowpose(pose107,1000);
	static s16 pose108[18]={};slowpose(pose108,1000);
	static s16 pose109[18]={};slowpose(pose109,1000);
	static s16 pose110[18]={};slowpose(pose110,1000);
	static s16 pose111[18]={};slowpose(pose111,1000);
	static s16 pose112[18]={};slowpose(pose112,1000);
	static s16 pose113[18]={};slowpose(pose113,1000);
	static s16 pose114[18]={};slowpose(pose114,1000);
	static s16 pose115[18]={};slowpose(pose115,1000);
	static s16 pose116[18]={};slowpose(pose116,1000);
	static s16 pose117[18]={};slowpose(pose117,1000);


}*/
//void segmentation(u16 * a,u16* b,u16 tim,u8 xf)
//{
//	u16 k[18],m;
//	u8 i,s;
//	for(s=0;s<=xf;s++)
//	{
//		for(i=0;i<18;i++)
//		{
//			if(a[i]>b[i])
//			{
//			  k[i]=a[i]-b[i];
//			}
//			else{k[i]=b[i]-a[i];}	
//		}
//		for(i=0;i<18;i++)
//		{
//		   if(a[i]>b[i])
//			{
//			   m=a[i]-k[i]*s/xf;
//			}
//			else
//			{
//			   m=a[i]+k[i]*s/xf;
//			   ControlAServo(i+1,m);
//			}		
//		}	
//		delay_ms(tim);	
//	}
//}
//void   SlowAngle(s16 *begin,s16 *end,u16 tim,u8 xf)
//{
//	u16 a[18];
//	u16 b[18];
//	u8 i;
//	for(i=0;i<18;i++)
//	{
//		a[i] = begin[i];
//		b[i] = end[i];
//	}
//	segmentation(a,b,tim,xf);
//}
//void ControlAServo(u8 ID,u16 Angel){	
//	
//	
//	NowAngle[ID-1] = Angel;
//	
//	
//	LobotSerialServoMove(ID, Angel,000 );
//	
//	
//}



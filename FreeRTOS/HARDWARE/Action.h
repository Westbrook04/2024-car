#ifndef ACTION_H_
#define ACTION_H_

#include "sys.h"

//以下三个函数为工作室学长以前的分段函数代码
void SlowAngle(s16 *begin,s16 *end,u16 tim,u8 xf);
void segmentation(u16 * a,u16* b,u16 s,u8 xf);	
void ControlAServo(u8 ID,u16 Angel);
//这个函数为本人自创的，只需复制粘贴动作组，再添加时间即可。
void slowpose(s16 *begin,u16 time);

//初态
void zero(void);//零度

//语音识别动作
void front_run(void);//向前走
void back_run(void);//向后走
void left_move_pose(void);//左移
void right_move_pose(void);//右移
void turn_left(void);//左转
void turn_right(void);//右转
void turn_lefthand(void);//伸左手
void turn_twohand(void);//伸双手
void one_leg_stand(void);//单脚撑
void chayao(void);//叉腰
void dianjiao(void);//踮脚
void xiadun(void);//下蹲
void tuiyibu(void);//后退一步
void zuoyisbu(void);//左移四步
void youyisbu(void);//右移四步

//视觉识别动作
void shijuechutai(void);//视觉识别初态
void big_stand_pose(void);//大字站立
void twohands_up(void);//两手向上
void lefthand_up_righthand_down(void);//左手向上右手向下
void leftleg_move(void);//伸左脚
void left_jingli(void);//敬礼
void llrr(void);//左左右右

//韵律识别舞蹈
void dance_one(void);
void dance_two(void);
void dance_three(void);
void dance_zixuan_one(void);
void dance_zixuan_two(void);
void dance_zixuan_three(void);

#endif

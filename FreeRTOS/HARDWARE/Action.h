#ifndef ACTION_H_
#define ACTION_H_

#include "sys.h"

//������������Ϊ������ѧ����ǰ�ķֶκ�������
void SlowAngle(s16 *begin,s16 *end,u16 tim,u8 xf);
void segmentation(u16 * a,u16* b,u16 s,u8 xf);	
void ControlAServo(u8 ID,u16 Angel);
//�������Ϊ�����Դ��ģ�ֻ�踴��ճ�������飬�����ʱ�伴�ɡ�
void slowpose(s16 *begin,u16 time);

//��̬
void zero(void);//���

//����ʶ����
void front_run(void);//��ǰ��
void back_run(void);//�����
void left_move_pose(void);//����
void right_move_pose(void);//����
void turn_left(void);//��ת
void turn_right(void);//��ת
void turn_lefthand(void);//������
void turn_twohand(void);//��˫��
void one_leg_stand(void);//���ų�
void chayao(void);//����
void dianjiao(void);//�ڽ�
void xiadun(void);//�¶�
void tuiyibu(void);//����һ��
void zuoyisbu(void);//�����Ĳ�
void youyisbu(void);//�����Ĳ�

//�Ӿ�ʶ����
void shijuechutai(void);//�Ӿ�ʶ���̬
void big_stand_pose(void);//����վ��
void twohands_up(void);//��������
void lefthand_up_righthand_down(void);//����������������
void leftleg_move(void);//�����
void left_jingli(void);//����
void llrr(void);//��������

//����ʶ���赸
void dance_one(void);
void dance_two(void);
void dance_three(void);
void dance_zixuan_one(void);
void dance_zixuan_two(void);
void dance_zixuan_three(void);

#endif

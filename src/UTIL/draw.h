#ifndef __DRAW_H
#define __DRAW_H
#include "sys.h"
#include "basic_draw.h"

//��ʼ��������һ��һ����Ϸ��ֻ��ʹ��һ��
void draw_start_page(void);
void init_play_interface(void);
void draw_end(int *score,int *score_2, int *score_3);

//����Ⱦ����Ⱦ�������
//��Щ�����ҲҪ��Ⱦ����һ���̶��Ͻ���Ч��
void draw_play_all(int score,int life, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2]);
#endif

#ifndef __RUN_H
#define __RUN_H	
#include "sys.h"  
#include "util.h"
#include "draw.h"

//���ɵ��˷ɻ�
void generate_enemy_planes(int level, int enemy_planes[10][2]);


//������������
void switch_my_act(int my_plane[2],int my_buttles[300][2]);

//�Զ������ҵ������ӵ�
void update_my_buttles(int my_buttles[100][2]);

//���µ��˷ɻ�λ��
void update_enemy_planes(int enemy_planes[10][2]);

void check_my_plane_to_enemy_plane_collide(int *score,int *life,	int my_plane[2], int enemy_planes[10][2]);
void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[300][2], int enemy_planes[10][2]);

void clear_all_enemy_plane(int my_plane[2], int enemy_plane[10][2]);

#endif

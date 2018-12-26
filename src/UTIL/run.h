#ifndef __RUN_H
#define __RUN_H	
#include "sys.h"  
#include "util.h"
#include "draw.h"

//生成敌人飞机
void generate_enemy_planes(int level, int enemy_planes[10][2]);


//检测操作来更新
void switch_my_act(int my_plane[2],int my_buttles[300][2]);

//自动更新我的所有子弹
void update_my_buttles(int my_buttles[100][2]);

//更新敌人飞机位置
void update_enemy_planes(int enemy_planes[10][2]);

void check_my_plane_to_enemy_plane_collide(int *score,int *life,	int my_plane[2], int enemy_planes[10][2]);
void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[300][2], int enemy_planes[10][2]);

void clear_all_enemy_plane(int my_plane[2], int enemy_plane[10][2]);

#endif

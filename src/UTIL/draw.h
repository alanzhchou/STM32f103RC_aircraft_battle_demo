#ifndef __DRAW_H
#define __DRAW_H
#include "sys.h"
#include "basic_draw.h"

//初始化函数，一般一次游戏中只会使用一次
void draw_start_page(void);
void init_play_interface(void);
void draw_end(int *score,int *score_2, int *score_3);

//懒渲染，渲染所有组件
//有些不变的也要渲染，会一定程度上降低效率
void draw_play_all(int score,int life, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2]);
#endif

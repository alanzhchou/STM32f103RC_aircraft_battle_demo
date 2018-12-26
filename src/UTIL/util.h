#ifndef __UTIL_H
#define __UTIL_H
#include "sys.h"  
#include "delay.h"
#include "key.h"
#include "remote.h"
#include "lcd.h"

typedef struct{int x;	int y;} Point;

u8 get_remote(void);
void KEY0_or_POWER_to_skip(void);
u8* get_remote_string(int key);

void print_string(int x,int y,u8 *str);
void print_num(int x,int y,int num);



void arrange_my_buttles(int my_buttles[100][2]);
void arrange_enemy_planes(int enemy_planes[10][2]);
void arrange_enemy_buttles(int enemy_buttles[300][2]);
	
#endif

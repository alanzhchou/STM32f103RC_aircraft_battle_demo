#include "lcd.h"
#include "draw.h"


//初始化函数，一般一次游戏中只会使用一次
void draw_start_page(void){
	LCD_ShowString(70,80,200,24,24,"AIRCRAFT");
	LCD_ShowString(82,103,200,24,24,"BATTLE");		
	
	draw_my_plane(90,180);
	draw_my_plane(120,180);
	draw_my_plane(150,180);
	
	LCD_ShowString(107,250,200,12,12,"PRESS");	
	LCD_ShowString(82,263,200,12,12,"KEY0 or POWER");
}

void init_play_interface(void){
	//设置基础界面
	LCD_DrawLine(1,1,239,1);
	LCD_DrawLine(1,40,239,40);
	
	LCD_DrawLine(1,1,1,40);
	LCD_DrawLine(239,1,239,40);
	
	LCD_DrawLine(130,1,130,40);
	
	LCD_ShowString(5,8,90,24,24,"SCROE:");	
	LCD_ShowString(135,8,90,24,24,"LIFE");
}

void draw_end(int *score,int *score_2, int *score_3){
	LCD_Clear(GRAY);
	
	LCD_ShowString(70,40,200,24,24,"GAME OVER");
	LCD_ShowString(87,93,200,24,24,"My SCORE:");
	LCD_ShowxNum(100,120,*score,4,24,0);	
	
	if(*score_2 == 0 && *score_3 == 0){
		*score_2 = *score;
	}else if(*score_2 != 0 && *score_3 == 0){
		*score_3 = *score_2;
		*score_2 = *score;
		LCD_ShowString(87,143,200,24,24,"P2 SCORE:");
		LCD_ShowxNum(100,170,*score_2,4,24,0);	
	}else if(*score_2 != 0 && *score_3 != 0){
		LCD_ShowString(87,143,200,24,24,"P2 SCORE:");
		LCD_ShowxNum(100,170,*score_2,4,24,0);	
		LCD_ShowString(87,203,200,24,24,"P3 SCORE:");
		LCD_ShowxNum(100,230,*score_3,4,24,0);	
	}
	*score = 0;
	
	draw_my_plane(90,260);
	draw_my_plane(120,260);
	draw_my_plane(150,260);
	
	draw_star(200,300);
	draw_star(20,130);
	draw_star(50,230);
	
	draw_star(150,120);
	draw_star(80,30);
}


//渲染函数，帧动画调用渲染
//包含分数/生命渲染
//我方子弹渲染
//敌方飞机渲染
//敌方子弹渲染

//其他渲染可调用 basic_draw.h
//1. 我方飞机渲染
//2. boss渲染
//3. cross渲染
void draw_play_title(int score, int life){
	//填充信息
	int i=0;
	int start_x = 195;
	
	//LCD_Fill(75,8,130,32,GRAY);
	LCD_ShowxNum(75,8,score,4,24,0);		//显示分数
	
	LCD_Fill(190,15,226,25,BACK_COLOR);
	for(i=0; i<life; i++){	//显示生命值
		draw_heart(start_x+i*13, 20);
	}
}

//#define my_buttle_max 100
//#define enemy_buttle_max 300
//#define enemy_plane_max 10
//过滤 0，0
void draw_all_my_buttles(int my_buttles[100][2]){
	int i =0;
	for(i=0; i<100; i++){
		if(my_buttles[i][0] == 0){
			break;
		}else{
			draw_my_bullet(my_buttles[i][0],my_buttles[i][1]);
		}
	}
}

//过滤 0，0
void draw_all_enemy_planes(int enemy_planes[10][2]){
	int i = 0;
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] == 0){
			break;
		}else{
			draw_enemy_plane(enemy_planes[i][0],enemy_planes[i][1]);
		}
	}
}

//过滤 0，0
void draw_all_enemy_buttles(int enemy_buttles[300][2]){
	int i =0;
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] == 0){
			break;
		}else{
			draw_enemy_bullet(enemy_buttles[i][0],enemy_buttles[i][1]);
		}
	}
}



//懒渲染，渲染所有组件，
//有些不变的也要渲染，会降低效率
void draw_play_all(int score,int life, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2]){
	draw_play_title(score,life);
	
	draw_my_plane(my_plane[0],my_plane[1]);
	draw_all_my_buttles(my_buttles);
	
	draw_boss(boss[0],boss[1]);

	draw_all_enemy_planes(enemy_planes);
	draw_all_enemy_buttles(enemy_buttles);
}


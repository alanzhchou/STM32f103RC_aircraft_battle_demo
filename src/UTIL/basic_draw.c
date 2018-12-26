#include "lcd.h"
#include "basic_draw.h"

//x,y������ʶ���ĵ�λ��
//�������³ߴ綼���յ���������

int big_trigon_width = 21;
int big_trigon_height = 35;

int small_trigon_width = 11;
int small_trigon_height = 11;

int cross_width = 15; 
int cross_height = 15;

//����˵������ʵ���޹�
int heart_width = 11;
int heart_height = 11;

//����˵������ʵ���޹�
int buttle_width = 3; 
int buttle_height = 3;

int star_width = 5;
int star_height = 9;

//�����������Σ�ֻ��ָ���ױ�����λ�ú͵׳�/�߼���
//����������
void draw_forward_trigon(int x,int y,int width, int height);
//����������
void draw_reversed_trigon(int x,int y,int width, int height);

void draw_my_plane(int x, int y){
	draw_forward_trigon(x,y+15,big_trigon_width,big_trigon_height);
	draw_forward_trigon(x,y+20,small_trigon_width,small_trigon_height);
}

void draw_enemy_plane(int x ,int y){
	draw_reversed_trigon(x,y-15,big_trigon_width,big_trigon_height);
	draw_reversed_trigon(x,y-20,small_trigon_width,small_trigon_height);
}

//���˳�ʼ����0��0
void draw_boss(int x, int y){
	if(x != 0){
		if(y != 0){
			draw_reversed_trigon(x,y-15,big_trigon_width*2,big_trigon_height);
			draw_reversed_trigon(x,y-20,small_trigon_width*2,small_trigon_height);
		}
	}
}

void draw_my_bullet(int x, int y){
	LCD_DrawPoint(x,y-1);
	
	LCD_DrawPoint(x-1,y);
	LCD_DrawPoint(x,y);
	LCD_DrawPoint(x+1,y);

	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x,y+1);
	LCD_DrawPoint(x+1,y+1);
}

void draw_enemy_bullet(int x, int y){
	LCD_DrawPoint(x-1,y-1);
	LCD_DrawPoint(x,y-1);
	LCD_DrawPoint(x+1,y-1);
	
	LCD_DrawPoint(x-1,y);
	LCD_DrawPoint(x,y);
	LCD_DrawPoint(x+1,y);

	LCD_DrawPoint(x,y+1);
}

void draw_cross(int x, int y){
	LCD_DrawLine(x-cross_width/2,y-cross_height/2, x+cross_width/2,y+cross_height/2);
	LCD_DrawLine(x-cross_width/2,y+cross_height/2, x+cross_width/2,y-cross_height/2);
}

void draw_heart(int x, int y){
	LCD_DrawLine(x-heart_width/2,y-heart_height/2, x+heart_width/2,y+heart_height/2);
	LCD_DrawLine(x-heart_width/2,y+heart_height/2, x+heart_width/2,y-heart_height/2);
	
	LCD_DrawLine(x-heart_width/2,y, x+heart_width/2,y);
	LCD_DrawLine(x,y+heart_height/2, x,y-heart_height/2);
}


void draw_star(int x,int y){
	//����ϳ�
	LCD_DrawLine(x,y-star_height/2, x,y+star_height/2);
	//����϶�
	LCD_DrawLine(x-star_width/2,y, x+star_width/2,y);
}






void draw_forward_trigon(int x,int y,int width, int height){
	int x1,y1,x2,y2,x3,y3;
	x1 = x-width/2;	y1 = y;
	x2 = x;	y2 = y - height;
	x3 = x+width/2;	y3 = y;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
}

void draw_reversed_trigon(int x,int y,int width, int height){
	int x1,y1,x2,y2,x3,y3;
	x1 = x-width/2;	y1 = y;
	x2 = x;	y2 = y + height;
	x3 = x+width/2;	y3 = y;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
}


#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "remote.h"
#include "key.h"
#include "stdlib.h"

#include "data.h"

//LCD 为240 * 320 分辨率
#include "draw.h"
#include "run.h"

void all_init(void);
void init_interface_info(void);
void init_interface_info_second_time(void);

void draw_all_through_struct(void);


 int main(void)
 {		
	all_init();
	draw_all_through_struct();
	delay_ms(500);
	 
	while(1){
		while(1){		
			if(interface.life == 0){break;}
			if(interface.score !=0 && interface.score % 5 == 0){
				interface.level = interface.score/5;
				
				//clear_all_enemy_plane(interface.my_plane,interface.enemy_planes);
				//interface.boss[0] = 1;
				
				if(interface.level > 3){
					interface.level =3;
				}
			}
			
			switch_my_act(interface.my_plane,interface.my_buttles);
			update_my_buttles(interface.my_buttles);
			
			if(interface.boss[0] == 0){
				update_enemy_planes(interface.enemy_planes);
				generate_enemy_planes(interface.level,interface.enemy_planes);
				check_my_plane_to_enemy_plane_collide(&(interface.score),&(interface.life),	interface.my_plane,interface.enemy_planes);
				check_my_buttles_to_enemy_plane_collide(&(interface.score),	interface.my_buttles, interface.enemy_planes);
			}
			
			draw_all_through_struct();	 
			delay_ms(15);
		}	
		
		draw_end(&(interface.score),&(interface.score_2),&(interface.score_3));		
		KEY0_or_POWER_to_skip(); 
		
		//初始界面初始化
		draw_start_page(); 
		KEY0_or_POWER_to_skip();
		LCD_Clear(GRAY);
		
		//游玩界面数据初始化
		init_interface_info_second_time();
		
		//游玩界面初始化
		init_play_interface();
		
		draw_all_through_struct();
		delay_ms(500);
	}
}
 




void draw_all_through_struct(void){
	draw_play_all(interface.score,interface.life,	interface.my_plane,interface.my_buttles,	interface.boss,	interface.enemy_planes,interface.enemy_buttles);
}


void all_init(void){
	//库函数 和 硬件 初始化
	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	uart_init(9600);	 	//串口初始化为9600
	 
	LED_Init();	LED1=0;	//初始化与LED连接的硬件接口
	
	KEY_Init();          	//初始化与按键连接的硬件接口
	 
 	LCD_Init();
	BACK_COLOR=GRAY; 
	
	POINT_COLOR=BLACK;//设置字体为黑色 
	LCD_Clear(GRAY);
	 
	Remote_Init();			//红外接收初始化	
	
	//初始界面初始化
	draw_start_page(); 
	KEY0_or_POWER_to_skip();
	LCD_Clear(GRAY);
	
	//游玩界面数据初始化
	init_interface_info();
	
	//游玩界面初始化
	init_play_interface();
}



void init_interface_info(void){
	int i=0;
	
	interface.score = 0;
	interface.score_2 = 0;
	interface.score_3 = 0;
	
	interface.life = 3;
	
	interface.my_plane[0] = 120;	interface.my_plane[1] = 290;
	
	for(i=0; i<my_buttle_max; i++){
		interface.my_buttles[i][0] = 0;
		interface.my_buttles[i][1] = 0;
	}
	
	interface.level = 1;
	interface.boss[0] = 0;	 interface.boss[1] = 0;
	interface.boss_life = 0;
		
	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}
	
	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}

void init_interface_info_second_time(void){
	int i=0;
	
	interface.life = 3;
	
	interface.my_plane[0] = 120;	interface.my_plane[1] = 290;
	
	for(i=0; i<my_buttle_max; i++){
		interface.my_buttles[i][0] = 0;
		interface.my_buttles[i][1] = 0;
	}
	
	interface.level = 1;
	interface.boss[0] = 0;	 interface.boss[1] = 0;
	interface.boss_life = 0;
		
	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}
	
	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}





















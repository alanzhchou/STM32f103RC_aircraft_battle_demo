#include "run.h"

int left_limit = 2;
int right_limit = 238;
int up_limit = 42;
int down_limit = 318;


//敌人数 <= 关卡 * 3,	
//一次只生成一个飞机
//生成飞机概率 => 对应关卡
void generate_enemy_planes(int level, int enemy_planes[10][2]){
	int i = 0;
	int possibility_range = 0;
	
	if(level == 1){
		possibility_range = 4;
	}else if(level == 2 ){
		possibility_range = 5;
	}else if(level == 3 ){
		possibility_range = 6;
	}
		
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] == 0){
			if(i < level*3){
				if(rand()%100 < possibility_range){
					enemy_planes[i][0] = rand()%217 + 11;
					enemy_planes[i][1] = 61;
				}
			}
			break;
		}
	}
}



void switch_my_act(int my_plane[2],int my_buttles[100][2]){
	int i=0;
	int temp = get_remote();
	int key = KEY_Scan(0);
	
	if(temp){
		//清除之前所画
		LCD_Fill(my_plane[0]-10,my_plane[1]-20,	my_plane[0]+10,my_plane[1]+20,BACK_COLOR);
		
		if(temp == 98){
			if(my_plane[1]-20 > up_limit){
				my_plane[1] = my_plane[1]-3;
			}
		}else if(temp == 168){
			if(my_plane[1]+20 < down_limit){
				my_plane[1] = my_plane[1]+3;
			}
		}else if(temp == 34){
			if(my_plane[0]-10 > left_limit){
				my_plane[0] = my_plane[0]-3;
			}
		}else if(temp == 194){
			if(my_plane[0]+10 < right_limit){
				my_plane[0] = my_plane[0]+3;
			}
		}else if(temp == 2){
			for(i=0; i<100; i++){
				if(my_buttles[i][0] == 0){
					my_buttles[i][0] = my_plane[0];
					my_buttles[i][1] = my_plane[1]-22;
					
					//print_num(190,220,i);
					break;	
				}
			}
		}
	}
}

void update_my_buttles(int my_buttles[100][2]){
	int i=0;
	
	for(i=0; i<100; i++){
		if(my_buttles[i][0] != 0){
			//清除之前所画
			LCD_Fill(my_buttles[i][0]-1,my_buttles[i][1]-1,	my_buttles[i][0]+1,my_buttles[i][1]+1,BACK_COLOR);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			
			//当到达边界时销毁
			if(my_buttles[i][1] < 42){				
				my_buttles[i][0] = 0;
				my_buttles[i][1] = 0;
			}
		}
	}
	//再将后续数组值前移，覆盖数组值为0的元素
	//这里子弹数组y值随index增大，所以一次更新 -3 时，最多只会销毁第一个元素（buttle_height >= 3）
	arrange_my_buttles(my_buttles);
}


void update_enemy_planes(int enemy_planes[10][2]){
	int i=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			//清除之前所画
			LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
			
			enemy_planes[i][1] = enemy_planes[i][1] + 1;
			
			//当到达边界时销毁，再将后续数组值前移，补足
			if(enemy_planes[i][1] > 298){			
				enemy_planes[i][0] = 0;
				enemy_planes[i][1] = 0;
			}
		}
	}
	//再将后续数组值前移，覆盖数组值为0的元素
	//这里敌方飞机数组y值随index减小，所以一次更新 +1 时，最多只会销毁第一个元素（enemy_plane_height >= 1）
	arrange_enemy_planes(enemy_planes);
}


void check_my_plane_to_enemy_plane_collide(int *score,int *life,	int my_plane[2], int enemy_planes[10][2]){
	int i=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			//盒模型碰撞检测
			if(abs(enemy_planes[i][0] - my_plane[0]) <= 20){
				if(abs(enemy_planes[i][1] - my_plane[1]) <= 40){
					LCD_Fill(my_plane[0]-10,my_plane[1]-20,	my_plane[0]+10,my_plane[1]+20,BACK_COLOR);
					LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
					
					my_plane[0] = 120;
					my_plane[1] = 290;
					
					enemy_planes[i][0] = 0;
					enemy_planes[i][1] = 0;
					
					temp = (*score);
					(*score) = temp+1;
					
					temp = (*life);
					(*life) = temp-1;
					break;
				}
			}
		}
	}
	
	//由于敌方飞机有生成间隔，所以在一帧内碰撞最多只会存在一次  敌方飞机间隔(最少为3) > 每帧运动像素(1)
	arrange_enemy_planes(enemy_planes);
}


void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[100][2], int enemy_planes[10][2]){
	int i=0;
	int j=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			for(j=0; j<100; j++){
				//碰撞检测
				if(abs(my_buttles[j][0] - enemy_planes[i][0]) <= 12){
					if(abs(my_buttles[j][1] - enemy_planes[i][1]) <= 22){
						LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
					
						my_buttles[j][0] = 0;
						my_buttles[j][1] = 0;
						
						enemy_planes[i][0] = 0;
						enemy_planes[i][1] = 0;
						
						temp = (*score);
						(*score) = temp+1;
						break;
					}
				}
			}
			//飞机只可能碰撞一个
			arrange_enemy_planes(enemy_planes);
		}
	}
	//这里因为 碰撞一次 后就退出了，所以子弹只在第一次发现碰撞时被销毁
	//即使可以有两个子弹满足碰撞条件 => 子弹高度 3 < 每帧相对运动像素(3+1)，但只碰撞第一个
	arrange_my_buttles(my_buttles);
}


void clear_all_enemy_plane(int my_plane[2],	int enemy_plane[10][2]){
	int i=0;
	
	for(i=0; i<10; i++){
		enemy_plane[i][0] = 0;
		enemy_plane[i][1] = 0;
	}
	LCD_Fill(1,41,239,318,BACK_COLOR);
	
	draw_my_plane(my_plane[0],my_plane[1]);
}










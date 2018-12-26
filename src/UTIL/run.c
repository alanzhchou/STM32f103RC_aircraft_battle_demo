#include "run.h"

int left_limit = 2;
int right_limit = 238;
int up_limit = 42;
int down_limit = 318;


//������ <= �ؿ� * 3,	
//һ��ֻ����һ���ɻ�
//���ɷɻ����� => ��Ӧ�ؿ�
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
		//���֮ǰ����
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
			//���֮ǰ����
			LCD_Fill(my_buttles[i][0]-1,my_buttles[i][1]-1,	my_buttles[i][0]+1,my_buttles[i][1]+1,BACK_COLOR);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			
			//������߽�ʱ����
			if(my_buttles[i][1] < 42){				
				my_buttles[i][0] = 0;
				my_buttles[i][1] = 0;
			}
		}
	}
	//�ٽ���������ֵǰ�ƣ���������ֵΪ0��Ԫ��
	//�����ӵ�����yֵ��index��������һ�θ��� -3 ʱ�����ֻ�����ٵ�һ��Ԫ�أ�buttle_height >= 3��
	arrange_my_buttles(my_buttles);
}


void update_enemy_planes(int enemy_planes[10][2]){
	int i=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			//���֮ǰ����
			LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
			
			enemy_planes[i][1] = enemy_planes[i][1] + 1;
			
			//������߽�ʱ���٣��ٽ���������ֵǰ�ƣ�����
			if(enemy_planes[i][1] > 298){			
				enemy_planes[i][0] = 0;
				enemy_planes[i][1] = 0;
			}
		}
	}
	//�ٽ���������ֵǰ�ƣ���������ֵΪ0��Ԫ��
	//����з��ɻ�����yֵ��index��С������һ�θ��� +1 ʱ�����ֻ�����ٵ�һ��Ԫ�أ�enemy_plane_height >= 1��
	arrange_enemy_planes(enemy_planes);
}


void check_my_plane_to_enemy_plane_collide(int *score,int *life,	int my_plane[2], int enemy_planes[10][2]){
	int i=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			//��ģ����ײ���
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
	
	//���ڵз��ɻ������ɼ����������һ֡����ײ���ֻ�����һ��  �з��ɻ����(����Ϊ3) > ÿ֡�˶�����(1)
	arrange_enemy_planes(enemy_planes);
}


void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[100][2], int enemy_planes[10][2]){
	int i=0;
	int j=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			for(j=0; j<100; j++){
				//��ײ���
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
			//�ɻ�ֻ������ײһ��
			arrange_enemy_planes(enemy_planes);
		}
	}
	//������Ϊ ��ײһ�� ����˳��ˣ������ӵ�ֻ�ڵ�һ�η�����ײʱ������
	//��ʹ�����������ӵ�������ײ���� => �ӵ��߶� 3 < ÿ֡����˶�����(3+1)����ֻ��ײ��һ��
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










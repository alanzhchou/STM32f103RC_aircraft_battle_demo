#include "util.h"

struct{u8 key;	u8 times;	u8 *str;}remote;

u8 get_remote(void){
	remote.key = Remote_Scan();
	remote.times = RmtCnt;
	remote.str = "TEST";
	
	return remote.key;
}

void KEY0_or_POWER_to_skip(void){
	//KEY0_PRESS 或者 remote_key=162("power")退出
	while(1){
		if(KEY_Scan(0) == KEY0_PRES){break;}
		if(get_remote() == 162){break;}
		else{delay_ms(10);}
	}
}


u8* get_remote_string(int key){
	u8* str = 0;
	
	switch(key)
	{
		case 0:str="ERROR";break;			   
		case 162:str="POWER";break;	    
		case 98:str="UP";break;	    
		case 2:str="PLAY";break;		 
		case 226:str="ALIENTEK";break;		  
		case 194:str="RIGHT";break;	   
		case 34:str="LEFT";break;		  
		case 224:str="VOL-";break;		  
		case 168:str="DOWN";break;		   
		case 144:str="VOL+";break;		    
		case 104:str="1";break;		  
		case 152:str="2";break;	   
		case 176:str="3";break;	    
		case 48:str="4";break;		    
		case 24:str="5";break;		    
		case 122:str="6";break;		  
		case 16:str="7";break;			   					
		case 56:str="8";break;	 
		case 90:str="9";break;
		case 66:str="0";break;
		case 82:str="DELETE";break;		 
	}
	return str;
}

//测试输出字符串
void print_string(int x,int y,u8 *str){
	LCD_ShowString(x,y,90,12,12,str);	
}

//测试输出数字
void print_num(int x,int y, int num){
	LCD_ShowxNum(x,y,num,4,12,0);
}


//数组前移
void arrange_my_buttles(int my_buttles[100][2]){
	int i=0;
	if(my_buttles[0][0] == 0){
		for(i=0; i<99; i++){
			my_buttles[i][0] = my_buttles[i+1][0];
			my_buttles[i][1] = my_buttles[i+1][1];
		}
	}
}

//数组前移
void arrange_enemy_planes(int enemy_planes[10][2]){
	int i=0;
	if(enemy_planes[0][0] == 0){
		for(i=0; i<9; i++){
			enemy_planes[i][0] = enemy_planes[i+1][0];
			enemy_planes[i][1] = enemy_planes[i+1][1];
		}
	}
}

//数组前移
void arrange_enemy_buttles(int enemy_buttles[300][2]){
	int i=0;
	if(enemy_buttles[0][0] == 0){
		for(i=0; i<299; i++){
			enemy_buttles[i][0] = enemy_buttles[i+1][0];
			enemy_buttles[i][1] = enemy_buttles[i+1][1];
		}
	}
}

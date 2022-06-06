#include <iostream>
#include <graphics.h>

#define MAP_LONG   10
#define MAP_HEIGHT 5

#define plant_w 71
#define plant_h 71

#define zombie_w 71
#define zombie_h 120

#define ben_w   71
#define ben_h   71

using namespace std ;

/***************************************************************************************/
/*                                                                                     */
/*  �� �� �� ��                                                                        */
/*  �㶹    ֲ��   ��ʬ                                                                */
/*                                                                                     */
/***************************************************************************************/
struct bens     { // �㶹 bens_x     bens_y                     display_mood
	int  bens_x       = 0;       // x����
	int  bens_y       = 0;       // y����
	bool display_mood = 0;       // ��ʾģʽ
};
struct plants  { // ֲ�� plants_x   plants_y    plants_blood   display_mood
	int  plants_x     = 0;       // x����
	int  plants_y     = 0;       // y����
	int  plants_blood = 100;     // ֲ��Ѫ��
	bool attack_mood  = 0;       // ����ģʽ
	bool display_mood = 1;       // ��ʾģʽ
};
struct zombies { // ��ʬ zombies_x  zombies_y   zombies_blood  display_mood
	int  zombies_x     = 0;       // x����
	int  zombies_y     = 0;       // y����
	int  zombies_blood = 100;     // ��ʬѪ��
	bool attack_mood   = 0;       // ����ģʽ
	bool display_mood  = 1;       // ��ʾģʽ
};

/***************************************************************************************/
/*                                                                                     */
/*  �������                                                                           */
/*                                                                                     */
/***************************************************************************************/
int Game_frame_second = 0;

int mouse_x, mouse_y;

int zombies_in_line0;  int zombies_in_line1;  int zombies_in_line2;
int zombies_in_line3;  int zombies_in_line4;  int score;

bens      game_ben1;
bens      game_ben2;
bens      game_ben3;
plants    game_plants;
zombies   game_zombies;
mouse_msg game_mouse;

/***************************************************************************************/
/*                                                                                     */
/*  ����ͼƬָ��                                                                       */
/*                                                                                     */
/***************************************************************************************/
PIMAGE plant1;      PIMAGE plant2;      PIMAGE plant3;
PIMAGE plant4;      PIMAGE plant5;      PIMAGE plant6;
PIMAGE plant7;      PIMAGE plant8;      PIMAGE plant9;
PIMAGE plant10;     PIMAGE plant11;     PIMAGE plant12;

PIMAGE zombie1;     PIMAGE zombie2;     PIMAGE zombie3;
PIMAGE zombie4;     PIMAGE zombie5;     PIMAGE zombie6;
PIMAGE zombie7;     PIMAGE zombie8;     PIMAGE zombie9;
PIMAGE zombie10;    PIMAGE zombie11;    PIMAGE zombie12;

PIMAGE ben;        PIMAGE background;
PIMAGE lose;        PIMAGE win;  PIMAGE start;

/***************************************************************************************/
/*                                                                                     */
/*  ���庯��                                                                           */
/*                                                                                     */
/***************************************************************************************/
void game_init        ();       // ��Ŀ��ʼ��
void game_loadimages  ();       // ����ͼƬ
int  game_ui          ();       // ��Ϸ����
void game_show        ();       // ��ӡ��ͼ
void game_update      ();       // ������Ϸ����


int main(){
		
	game_init();
	game_zombies.zombies_x = MAP_LONG * plant_w;
	game_zombies.zombies_y = 2 ;
	
	putimage_transparent(NULL,start,0,0,WHITE);
	getch();
	
    for ( ; is_run() ; delay_ms(100)){
//		game_mouse = {0};
		if(Game_frame_second > 1200) Game_frame_second = 0;
		else                         Game_frame_second ++ ;
		while (mousemsg()){
			game_mouse = getmouse();
		}
		cleardevice();
		game_show();
		game_update();
	}
	
	
	return 0;
}

void game_init        (){       // ��Ŀ��ʼ��
    setcaption("shy's PVZ new remake");
    initgraph(plant_w * (MAP_LONG), plant_h * (MAP_HEIGHT + 1));
    setrendermode(RENDER_MANUAL); // �ֶ�
    ege_enable_aa(true);
    setbkcolor(EGERGB(0, 0, 0));
    showmouse(0);  // ���
    
    game_loadimages();
	
	score = 0;
	
	
	
	game_ben1.bens_x = 71 * 3;
	game_ben2.bens_x = 71 * 6;
	game_ben3.bens_x = 71 * 9;
}

void game_loadimages (){
    // ����ͼƬ����
    plant1  = newimage();      plant2  = newimage();      plant3  = newimage();
    plant4  = newimage();      plant5  = newimage();      plant6  = newimage();
    plant7  = newimage();      plant8  = newimage();      plant9  = newimage();
    plant10 = newimage();      plant11 = newimage();      plant12 = newimage();
    
    zombie1 = newimage();      zombie2 = newimage();      zombie3 = newimage();
    zombie4 = newimage();      zombie5 = newimage();      zombie6 = newimage();
    zombie7 = newimage();      zombie8 = newimage();      zombie9 = newimage();
    zombie10= newimage();      zombie11= newimage();      zombie12= newimage();
    
    ben= newimage(); background= newimage(); lose= newimage(); win= newimage();
	start = newimage();

    // ����ͼƬ
    getimage(plant1 ,"./image/plant/1.jpg" ,plant_w,plant_h);
    getimage(plant2 ,"./image/plant/2.jpg" ,plant_w,plant_h);
    getimage(plant3 ,"./image/plant/3.jpg" ,plant_w,plant_h);
    getimage(plant4 ,"./image/plant/4.jpg" ,plant_w,plant_h);
    getimage(plant5 ,"./image/plant/5.jpg" ,plant_w,plant_h);
    getimage(plant6 ,"./image/plant/6.jpg" ,plant_w,plant_h);
    getimage(plant7 ,"./image/plant/7.jpg" ,plant_w,plant_h);
    getimage(plant8 ,"./image/plant/8.jpg" ,plant_w,plant_h);
    getimage(plant9 ,"./image/plant/9.jpg" ,plant_w,plant_h);
    getimage(plant10,"./image/plant/10.jpg",plant_w,plant_h);
    getimage(plant11,"./image/plant/11.jpg",plant_w,plant_h);
    getimage(plant12,"./image/plant/12.jpg",plant_w,plant_h);
    
    getimage(zombie1 ,"./image/zombie/1.jpg" ,zombie_w,zombie_h);
    getimage(zombie2 ,"./image/zombie/2.jpg" ,zombie_w,zombie_h);
    getimage(zombie3 ,"./image/zombie/3.jpg" ,zombie_w,zombie_h);
    getimage(zombie4 ,"./image/zombie/4.jpg" ,zombie_w,zombie_h);
    getimage(zombie5 ,"./image/zombie/5.jpg" ,zombie_w,zombie_h);
    getimage(zombie6 ,"./image/zombie/6.jpg" ,zombie_w,zombie_h);
    getimage(zombie7 ,"./image/zombie/7.jpg" ,zombie_w,zombie_h);
    getimage(zombie8 ,"./image/zombie/8.jpg" ,zombie_w,zombie_h);
    getimage(zombie9 ,"./image/zombie/9.jpg" ,zombie_w,zombie_h);
    getimage(zombie10,"./image/zombie/10.jpg",zombie_w,zombie_h);
    getimage(zombie11,"./image/zombie/11.jpg",zombie_w,zombie_h);
    getimage(zombie12,"./image/zombie/12.jpg",zombie_w,zombie_h);
    
    getimage(ben        ,"./image/ben/1.jpg",ben_w,ben_h);
    getimage(background ,"./image/others/background.jpg",MAP_LONG * plant_w , MAP_HEIGHT * plant_h);
    getimage(lose       ,"./image/others/lose.jpg",MAP_LONG * plant_w , MAP_HEIGHT * plant_h);
    getimage(win        ,"./image/others/win.jpg",MAP_LONG * plant_w , MAP_HEIGHT * plant_h);
	getimage(start      ,"./image/others/start.jpg",MAP_LONG * plant_w , MAP_HEIGHT * plant_h);
	
}

int  game_ui          (){       // ��Ϸ����

    return 0;
}

void game_show        (){       // ��ӡ��ͼ
//	putimage_transparent(NULL,plant1,0,0,WHITE);
	cleardevice();
	putimage(0,0,background);
	if(game_plants.display_mood){    // ��ӡֲ��
		switch (Game_frame_second % 12){
		case 0 :
			putimage_transparent(NULL,plant1 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 1 :
			putimage_transparent(NULL,plant2 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 2 :
			putimage_transparent(NULL,plant3 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 3 :
			putimage_transparent(NULL,plant4 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 4 :
			putimage_transparent(NULL,plant5 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 5 :
			putimage_transparent(NULL,plant6 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 6 :
			putimage_transparent(NULL,plant7 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 7 :
			putimage_transparent(NULL,plant8 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 8 :
			putimage_transparent(NULL,plant9 ,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 9 :
			putimage_transparent(NULL,plant10,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 10 :
			putimage_transparent(NULL,plant11,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
		case 11 :
			putimage_transparent(NULL,plant12,game_plants.plants_x * plant_w,game_plants.plants_y * plant_h,WHITE);
			break;
			
		}
	}
	if(game_zombies.display_mood){   // ��ӡ��ʬ
		switch (Game_frame_second % 12){
		case 0 :
			putimage_transparent(NULL,zombie1 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 1 :
			putimage_transparent(NULL,zombie2 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 2 :
			putimage_transparent(NULL,zombie3 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 3 :
			putimage_transparent(NULL,zombie4 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 4 :
			putimage_transparent(NULL,zombie5 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 5 :
			putimage_transparent(NULL,zombie6 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 6 :
			putimage_transparent(NULL,zombie7 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 7 :
			putimage_transparent(NULL,zombie8 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 8 :
			putimage_transparent(NULL,zombie9 ,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 9 :
			putimage_transparent(NULL,zombie10,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 10 :
			putimage_transparent(NULL,zombie11,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
		case 11 :
			putimage_transparent(NULL,zombie12,game_zombies.zombies_x,game_zombies.zombies_y * plant_h - 60,WHITE);
			break;
			
		}
	}
	if (1) {                         // ��ӡ�㶹
		if (game_ben1.display_mood){
			putimage_transparent(NULL,ben,game_ben1.bens_x,game_ben1.bens_y * ben_h,WHITE);
		}
		if (game_ben2.display_mood){
			putimage_transparent(NULL,ben,game_ben2.bens_x,game_ben2.bens_y * ben_h,WHITE);
		}
		if (game_ben3.display_mood){
			putimage_transparent(NULL,ben,game_ben3.bens_x,game_ben3.bens_y * ben_h,WHITE);
		}
	}
	
}

void game_update      (){       // ������Ϸ����
	
	game_plants.plants_x = game_mouse.x / 71;
	game_plants.plants_y = game_mouse.y / 71;
	
	
	
	if (game_plants.plants_x == 9) game_plants.plants_x = 8;
	if (game_plants.plants_y == 0) game_plants.plants_y = 1;
	
	if (1) {  // �㶹�ƶ�
		if (game_ben1.bens_x > MAP_LONG * plant_w) {
			game_ben1.display_mood = 1;
			game_ben1.bens_x = game_plants.plants_x * ben_w;
			game_ben1.bens_y = game_plants.plants_y ;
		}
		else {
			game_ben1.bens_x += 20;
		}
		
		if (game_ben2.bens_x > MAP_LONG * plant_w) {
			game_ben2.display_mood = 1;
			game_ben2.bens_x = game_plants.plants_x * ben_w;
			game_ben2.bens_y = game_plants.plants_y ;
		}
		else {
			game_ben2.bens_x += 20;
		}
		
		if (game_ben3.bens_x > MAP_LONG * plant_w) {
			game_ben3.display_mood = 1;
			game_ben3.bens_x = game_plants.plants_x * ben_w;
			game_ben3.bens_y = game_plants.plants_y ;
		}
		else {
			game_ben3.bens_x += 20;
		}
	}
	
	randomize();
	game_zombies.zombies_x -= 3;
	if (game_zombies.display_mood == 0){
		game_zombies.display_mood = 1;
		game_zombies.zombies_blood = 100;
		game_zombies.zombies_y = random(MAP_HEIGHT - 1) + 1;
		game_zombies.zombies_x = MAP_LONG * plant_w;
	}
	
	
	if (game_zombies.display_mood == 1) {  // �㶹����
		if (game_ben1.display_mood == 1 && game_ben1.bens_x > game_zombies.zombies_x && game_ben1.bens_x < game_zombies.zombies_x + 100 && game_ben1.bens_y == game_zombies.zombies_y){
			game_ben1.display_mood = 0;
			game_zombies.zombies_blood -= 10;
		}
		if (game_ben2.display_mood == 1 && game_ben2.bens_x > game_zombies.zombies_x && game_ben2.bens_x < game_zombies.zombies_x + 100 && game_ben2.bens_y == game_zombies.zombies_y){
			game_ben2.display_mood = 0;
			game_zombies.zombies_blood -= 10;
		}
		if (game_ben3.display_mood == 1 && game_ben3.bens_x > game_zombies.zombies_x && game_ben3.bens_x < game_zombies.zombies_x + 100 && game_ben3.bens_y == game_zombies.zombies_y){
			game_ben3.display_mood = 0;
			game_zombies.zombies_blood -= 10;
		}
	}
	if (game_zombies.zombies_blood < 0){
		game_zombies.display_mood = 0;
		score ++ ;
	}

	if (game_zombies.zombies_x < -144){
		putimage_transparent(NULL,lose,0,0,WHITE);
		getch();
		game_zombies.zombies_x = MAP_LONG * plant_w;
		game_zombies.zombies_y = 2;
		score = 0;
	}
	
	if (score > 9){
		putimage_transparent(NULL,win,0,0,WHITE);
		getch();
		game_zombies.zombies_x = MAP_LONG * plant_w;
		game_zombies.zombies_y = 2;
		score = 0;
		
	}
	
	LOGFONTA f;
	getfont(&f);                                  // ��ȡ��ǰ��������
	f.lfHeight = 50;                              // ��������߶�Ϊ 48�������оࣩ
	strcpy(f.lfFaceName, "JetBrains Moon NL");    // ��������Ϊ
	f.lfQuality = ANTIALIASED_QUALITY;            // �������Ч��Ϊ�����  
	setfont(&f);                                  // ����������ʽ
	
	// �����ֵ���Ƚ����ָ�ʽ�����Ϊ�ַ���
	char s[5];
	sprintf(s, "%d", score);
	outtextxy(71 * 7, 10, s);


}






















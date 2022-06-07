/************************************************************************************/
/*                                                                                  */
/*                         项目名称：植物大战僵尸（重制版）                         */
/*                         项目作者：宋韩尧                                         */
/*                         学    校：南京晓庄学院                                   */
/*                         院    系：信息工程学院、人工智能学院                     */
/*                         学    号：21130112                                       */
/*                                                                                  */
/*                         指导老师：周恺                                           */
/*                                                                                  */
/*                         起止时间：2022.5.1--2022.6.6                             */
/*                                                                                  */
/************************************************************************************/

/************************************************************************************/
/*                                                                                  */
/*                                   MIT License                                    */
/*                                                                                  */
/*  Copyright (c) 2022 xiaomeng                                                     */
/*                                                                                  */
/*  Permission is hereby granted, free of charge, to any person obtaining a copy    */
/*  of this software and associated documentation files (the "Software"), to deal   */
/*  in the Software without restriction, including without limitation the rights    */
/*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       */
/*  copies of the Software, and to permit persons to whom the Software is           */
/*  furnished to do so, subject to the following conditions:                        */
/*                                                                                  */
/*  The above copyright notice and this permission notice shall be included in all  */
/*  copies or substantial portions of the Software.                                 */
/*                                                                                  */
/*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      */
/*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        */
/*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     */
/*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          */
/*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   */
/*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   */
/*  SOFTWARE.                                                                       */
/*                                                                                  */
/************************************************************************************/

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
/*  定 义 结 构                                                                        */
/*  豌豆    植物   僵尸                                                                */
/*                                                                                     */
/***************************************************************************************/
struct bens     { // 豌豆 bens_x     bens_y                     display_mood
	int  bens_x       = 0;       // x坐标
	int  bens_y       = 0;       // y坐标
	bool display_mood = 0;       // 显示模式
};
struct plants  { // 植物 plants_x   plants_y    plants_blood   display_mood
	int  plants_x     = 0;       // x坐标
	int  plants_y     = 0;       // y坐标
	int  plants_blood = 100;     // 植物血量
	bool attack_mood  = 0;       // 攻击模式
	bool display_mood = 1;       // 显示模式
};
struct zombies { // 僵尸 zombies_x  zombies_y   zombies_blood  display_mood
	int  zombies_x     = 0;       // x坐标
	int  zombies_y     = 0;       // y坐标
	int  zombies_blood = 100;     // 僵尸血量
	bool attack_mood   = 0;       // 攻击模式
	bool display_mood  = 1;       // 显示模式
};

/***************************************************************************************/
/*                                                                                     */
/*  定义变量                                                                           */
/*                                                                                     */
/***************************************************************************************/
int Game_frame_second = 0;
int mouse_x, mouse_y;
int score;

bens      game_ben1;
bens      game_ben2;
bens      game_ben3;
plants    game_plants;
zombies   game_zombies;
mouse_msg game_mouse;

/***************************************************************************************/
/*                                                                                     */
/*  定义图片指针                                                                       */
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

PIMAGE ben;         PIMAGE background;  PIMAGE start;
PIMAGE lose;        PIMAGE win;


/***************************************************************************************/
/*                                                                                     */
/*  定义音乐指针                                                                       */
/*                                                                                     */
/***************************************************************************************/
MUSIC music_background_start;
MUSIC music_background_play;
MUSIC music_zombies_hurt;
MUSIC music_win;
MUSIC music_lose;

/***************************************************************************************/
/*                                                                                     */
/*  定义函数                                                                           */
/*                                                                                     */
/***************************************************************************************/
void game_init      ();       // 项目初始化
void game_loaddata  ();       // 载入图片
void game_ui        ();       // 游戏载入
void game_show      ();       // 打印地图
void game_update    ();       // 更新游戏数据
void game_lose      ();       // 游戏获胜
void game_win       ();       // 游戏失败


/***************************************************************************************/
/*                                                                                     */
/*  游戏主函数                                                                         */
/*                                                                                     */
/***************************************************************************************/
int main(){
		
	game_init();
	game_zombies.zombies_x = MAP_LONG * plant_w;
	game_zombies.zombies_y = 2 ;
	
	
    for ( ; is_run() ; delay_ms(100)){
		// 游戏帧数记录
		if(Game_frame_second > 1200) Game_frame_second = 0;
		else                         Game_frame_second ++ ;
		
		// 检测鼠标消息
		while (mousemsg()){
			game_mouse = getmouse();
		}
		
		cleardevice(); // 清屏
		game_show();   // 打印屏幕
		game_update(); // 游戏数据更新
	}
	return 0;
}

/***************************************************************************************/
/*                                                                                     */
/*  项目初始化                                                                         */
/*                                                                                     */
/***************************************************************************************/
void game_init(){
    setcaption("shy's PVZ new remake");                          // 设置窗口名称
    initgraph(plant_w * (MAP_LONG), plant_h * (MAP_HEIGHT + 1)); // 设置窗口大小
    setrendermode(RENDER_MANUAL);                                // 设置窗口更新模式-手动
    ege_enable_aa(true);                                         // 设置窗口抗锯齿
    setbkcolor(EGERGB(0, 0, 0));                                 // 窗口背景色
    showmouse(0);                                                // 鼠标显示模式-隐藏
    
    game_loaddata();          // 调用加载图片
	
	game_ui();                  // 调用开始游戏窗口
	
	score = 0;                  // 初始化得分
	
	game_ben1.bens_x = 71 * 3;  // 初始化豌豆位置
	game_ben2.bens_x = 71 * 6;
	game_ben3.bens_x = 71 * 9;
}

/***************************************************************************************/
/*                                                                                     */
/*  载入 图片 音频                                                                     */
/*                                                                                     */
/***************************************************************************************/
void game_loaddata (){
    // 创建图片对象
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

    // 载入图片
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
	
	music_background_start.OpenFile("./musics/background/game_start_music.mp3");
	music_background_play.OpenFile("./musics/background/game_start_music.mp3");
	music_lose.OpenFile("./musics/background/Laura Shigihara - Graze the Roof.mp3");
	music_win.OpenFile("./musics/background/Laura Shigihara - Graze the Roof.mp3");
	music_zombies_hurt.OpenFile("./musics/background/Laura Shigihara - Graze the Roof.mp3");
}
/***************************************************************************************/
/*                                                                                     */
/*  游戏载入                                                                           */
/*                                                                                     */
/***************************************************************************************/
void game_ui(){
	putimage_transparent(NULL,start,0,0,WHITE);
	getch();
}

/***************************************************************************************/
/*                                                                                     */
/*  打印地图                                                                           */
/*                                                                                     */
/***************************************************************************************/
void game_show(){
	cleardevice();
	putimage(0,0,background);
	if(game_plants.display_mood){    // 打印植物
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
	if(game_zombies.display_mood){   // 打印僵尸
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
	if (1) {                         // 打印豌豆
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

/***************************************************************************************/
/*                                                                                     */
/*  更新游戏数据                                                                       */
/*                                                                                     */
/***************************************************************************************/
void game_update(){
	
	// 获取鼠标位置
	game_plants.plants_x = game_mouse.x / 71;
	game_plants.plants_y = game_mouse.y / 71;
	
	// 防止植物出界
	if (game_plants.plants_x == 9) game_plants.plants_x = 8;
	if (game_plants.plants_y == 0) game_plants.plants_y = 1;
	
	if (1) {  // 豌豆移动
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
	
	// 重置僵尸位置
	randomize();
	game_zombies.zombies_x -= 3;
	if (game_zombies.display_mood == 0){
		game_zombies.display_mood = 1;
		game_zombies.zombies_blood = 100;
		game_zombies.zombies_y = random(MAP_HEIGHT - 1) + 1;
		game_zombies.zombies_x = MAP_LONG * plant_w;
	}
	
	// 豌豆攻击
	if (game_zombies.display_mood == 1) {
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
	
	// 删除僵尸
	if (game_zombies.zombies_blood < 0){
		game_zombies.display_mood = 0;
		score ++ ;
	}
	
	// 游戏结束
	if (game_zombies.zombies_x < -144){
		game_lose();
	}
	
	// 游戏胜利
	if (score > 9){
		game_win();
	}
	
	// 输出得分
	LOGFONTA f;
	getfont(&f);                                  // 获取当前字体设置
	f.lfHeight = 50;                              // 设置字体高度为 48（包含行距）
	strcpy(f.lfFaceName, "JetBrains Moon NL");    // 设置字体为
	f.lfQuality = ANTIALIASED_QUALITY;            // 设置输出效果为抗锯齿  
	setfont(&f);                                  // 设置字体样式
	
	// 输出数值，先将数字格式化输出为字符串
	char s[5];
	sprintf(s, "%d", score);
	outtextxy(71 * 7, 10, s);


}

/***************************************************************************************/
/*                                                                                     */
/*  游戏失败                                                                           */
/*                                                                                     */
/***************************************************************************************/
void game_lose (){
	putimage_transparent(NULL,lose,0,0,WHITE);
	getch();
	game_zombies.zombies_x = MAP_LONG * plant_w;
	game_zombies.zombies_y = 2;
	score = 0;
}

/***************************************************************************************/
/*                                                                                     */
/*  游戏胜利                                                                           */
/*                                                                                     */
/***************************************************************************************/
void game_win(){
	putimage_transparent(NULL,win,0,0,WHITE);
	getch();
	game_zombies.zombies_x = MAP_LONG * plant_w;
	game_zombies.zombies_y = 2;
	score = 0;
}


















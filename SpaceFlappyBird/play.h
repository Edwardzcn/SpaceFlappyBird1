#ifndef PLAY_H
#define PLAY_H

#include <graphics.h>

#define GAP 214				//前一根柱子右侧与后一根柱子左侧之间的距离
#define BIRD_WIDTH 34		//小鸟图片的宽度
#define BIRD_HEIGHT 24		//小鸟图片的高度
#define STONE_WIDTH 140		//柱子图片的宽度
#define STONE_HEIGHT 600	//柱子图片的高度


typedef struct bird_construction
{
	IMAGE bird_mask[5]; //小鸟的五张掩码图
	IMAGE bird_real[5]; //小鸟的五张精灵图
	int bird_x;			//小鸟的横坐标
	int bird_y;			//小鸟的纵坐标
	int bird_change;    //小鸟的飞行姿势
	int bird_up;		//小鸟上行状态
	int bird_down;		//小鸟下行状态
	bool alive;			//小鸟是否存活
	
}Bird;

typedef struct stone_construction
{
	IMAGE stone_mask[2];		//柱子的掩码图（0为上，1为下）
	IMAGE stone_real[2];		//柱子的精灵图（0为上，1为下）
	int stone_x[5];				//柱子组横坐标
	int stone_y[5];				//柱子组纵坐标

}Stones;


char user_name[10] = "";
int user_present_score = 0;
int user_best_record = 0;
int esc = 0;
IMAGE bg_play, bg_score, game_over;



//初始化账户游戏开始
void initial_play();
//初始化每局游戏
void initial_game(Bird* newbird,Stones* newstones);

//小鸟移动与柱子移动
void bird_move(Bird* newbird);
void stone_move(Stones* newstones);
//绘制左侧游戏主界面
void print_play(Bird* newbird,Stones* newstones);
void print_bird(Bird* newbird);
void print_stone(Stones* newstones);
//绘制右侧分数界面
void print_score(Bird* newbird,Stones* newstones);
static void show_score();

//小鸟生存情况的判定
bool judgement(Bird* newbird,Stones* newstones);
//游戏结束动画
void gameover(Bird* newbird,Stones* newstones);


#endif // !PLAY_H

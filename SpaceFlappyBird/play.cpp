#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "play.h"
#include "file.h"
void play()
{
	//每一个账户进行游戏前进行的初始化
	initial_play();
	settextstyle(30, 0, _T("Volter (Goldfish)"));//设定字体样式
	setbkmode(TRANSPARENT);//设定字体背景透明

	//登陆窗口显示，储存username
	user_login();
	//查看帐户名对应的成绩
	user_history();
	//打印初始用户信息
	show_score();
	
	//新建小鸟
	Bird newbird;
	Stones newstones;
	//设定随机数种子
	int t = time(NULL);
	srand(t*t);
	//加载背景图片
	loadimage(&bg_play, "D:\\SpaceFlappyBird\\bgbig.gif");
	loadimage(&bg_score, "D:\\SpaceFlappyBird\\playscorebg1.jpg");
	loadimage(&game_over, "D:\\SpaceFlappyBird\\game_over.jpg");
	//加载小鸟掩码
	loadimage(&(newbird.bird_mask)[0], "D:\\SpaceFlappyBird\\bird_mask1.gif");
	loadimage(&(newbird.bird_mask)[1], "D:\\SpaceFlappyBird\\bird_mask2.gif");
	loadimage(&(newbird.bird_mask)[2], "D:\\SpaceFlappyBird\\bird_mask3.gif");
	loadimage(&(newbird.bird_mask)[3], "D:\\SpaceFlappyBird\\bird_mask1.gif");
	loadimage(&(newbird.bird_mask)[4], "D:\\SpaceFlappyBird\\bird_mask4.gif");
	//加载小鸟位图
	loadimage(&(newbird.bird_real)[0], "D:\\SpaceFlappyBird\\bird_real1.gif");
	loadimage(&(newbird.bird_real)[1], "D:\\SpaceFlappyBird\\bird_real2.gif");
	loadimage(&(newbird.bird_real)[2], "D:\\SpaceFlappyBird\\bird_real3.gif");
	loadimage(&(newbird.bird_real)[3], "D:\\SpaceFlappyBird\\bird_real1.gif");
	loadimage(&(newbird.bird_real)[4], "D:\\SpaceFlappyBird\\bird_real4.gif");
	//加载柱子掩码
	loadimage(&(newstones.stone_mask)[0], "D:\\SpaceFlappyBird\\stone_maskup.gif");
	loadimage(&(newstones.stone_mask)[1], "D:\\SpaceFlappyBird\\stone_maskdown.gif");
	//加载柱子位图
	loadimage(&(newstones.stone_real)[0], "D:\\SpaceFlappyBird\\stone_realup.gif");
	loadimage(&(newstones.stone_real)[1], "D:\\SpaceFlappyBird\\stone_realdown.gif");
	//开启批量绘图模式，图片一同显示，防止屏幕闪烁，
	BeginBatchDraw();
	

	while (!esc)
	{
		initial_game(&newbird,&newstones); //每回合游戏初始化
		while (newbird.alive)
		{
			bird_move(&newbird);							//小鸟移动
			stone_move(&newstones);							//柱子移动
			print_play(&newbird,&newstones);				//绘制游戏主界面
			print_score(&newbird,&newstones);				//绘制计分界面（判定有经过柱子才执行）
			newbird.alive = judgement(&newbird,&newstones);	//判断小鸟状态
			if (esc)
				break;
		}
		if (!esc)
		{
			gameover(&newbird,&newstones);
			user_savescore();
		}
		user_history();//刷新历史成绩

	}

	EndBatchDraw(0, 0, 640, 600);


}


void initial_play()
{
	esc = 0;
	user_present_score = 0;
	user_best_record = 0;
}



void initial_game(Bird* newbird,Stones* newstones)
{
	//初始化鸟的信息
	//鸟的像素大小为34*24
	newbird->bird_x = 80;
	newbird->bird_y = 300;
	newbird->bird_change = 0;
	newbird->bird_up = 0;
	newbird->bird_down = 1;
	newbird->alive = true;

	//初始化游戏者当前分数
	user_present_score = 0;


	for (int i = 0; i < 5; i++)
	{
		(newstones->stone_x)[i] = 200 + GAP * i;
		(newstones->stone_y)[i] = rand() % 220 - 545;
	}



	putimage(0, 0, &bg_play);
	print_bird(newbird);
	print_stone(newstones);
	show_score();
	FlushBatchDraw();

	_getch(); //制造停顿
}

void bird_move(Bird* newbird)
{
	char key;
	if (_kbhit()) //检测是否有键盘输入
	{
		key = _getch();
		switch (key)
		{
		case ' ':
			newbird->bird_y -= 17;
			newbird->bird_up = 15;
			break;
		case 27:
			esc = 1;
		default:
			break;
		}
	}
	else if(newbird->bird_up-2)
	{
		newbird->bird_y -= newbird->bird_up-2;
		newbird->bird_up = newbird->bird_up - 1;

	}
	else if (newbird->bird_down)
	{
		newbird->bird_y += 4;
	}
}

void stone_move(Stones* newstones)
{
	if ((newstones->stone_x)[0] < -140)
	{
		for (int i = 0; i < 4; i++)
		{
			(newstones->stone_x)[i] = (newstones->stone_x)[i + 1];
			(newstones->stone_y)[i] = (newstones->stone_y)[i + 1];
		}
		(newstones->stone_x)[4] = (newstones->stone_x)[3] + 240;
		(newstones->stone_y)[4] = rand() % 220 - 545;
	}
	for (int i = 0; i < 5; i++)
		(newstones->stone_x)[i]--;
}

void print_play(Bird* newbird,Stones* newstones)
{
	Sleep(25);
	putimage(0, 0, &bg_play);//背景图像
	print_bird(newbird);
	print_stone(newstones);
	FlushBatchDraw(0, 0, 640, 600);
}


void print_bird(Bird* newbird)
{
	putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_mask)[newbird->bird_change % 4], SRCERASE);//掩码图
	putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_real)[newbird->bird_change % 4], SRCINVERT);//精灵图
	newbird->bird_change = (newbird->bird_change + 1) % 4;
}


//
void print_stone(Stones* newstones)
{
	for (int i = 0; i < 5; i++)
	{
		putimage((newstones->stone_x)[i], (newstones->stone_y)[i], &(newstones->stone_mask)[0], SRCERASE);
		putimage((newstones->stone_x)[i], (newstones->stone_y)[i], &(newstones->stone_real)[0], SRCINVERT);
		putimage((newstones->stone_x)[i], (newstones->stone_y)[i] + 750, &(newstones->stone_mask)[1], SRCERASE);
		putimage((newstones->stone_x)[i], (newstones->stone_y)[i] + 750, &(newstones->stone_real)[1], SRCINVERT);
	}
}


void print_score(Bird* newbird,Stones* newstones)
{
	if ((newstones->stone_x)[0] == newbird->bird_x - STONE_WIDTH)
	{
		user_present_score++;
		show_score();
		FlushBatchDraw();
	}
}

static void show_score()
{
	//从新打印分数版
	putimage(640, 0, &bg_score);
	//打印用户名
	outtextxy(675, 105, user_name);
	//打印当前分数
	char present_score[5] = " ";
	_itoa_s(user_present_score, present_score, sizeof(present_score), 10);
	outtextxy(675, 205, present_score);
	//打印历史最高分数
	char best_record[5] = " ";
	_itoa_s(user_best_record, best_record, sizeof(best_record), 10);
	outtextxy(675, 305, best_record);
}

bool judgement(Bird* newbird,Stones* newstones)
{
	if ((newstones->stone_x)[0] > newbird->bird_x - STONE_WIDTH && (newstones->stone_x)[0] < newbird->bird_x + BIRD_WIDTH)//小鸟后方没有柱子的时候判断是否与柱子碰撞
	{
		if (newbird->bird_y > (newstones->stone_y)[0] + STONE_HEIGHT && newbird->bird_y < (newstones->stone_y)[0] + STONE_HEIGHT + 150 - BIRD_HEIGHT)
		{
			return true;
		}
		else
		{
			//_getch();//调试代码
			return false;
		}
	}
	else if ((newstones->stone_x)[0] < newbird->bird_x + BIRD_WIDTH - GAP)//小鸟后方有一根柱子的时候判断是否与柱子碰撞
	{
		if (newbird->bird_y > (newstones->stone_y)[1] + STONE_HEIGHT && newbird->bird_y < (newstones->stone_y)[1] + STONE_HEIGHT + 150 - BIRD_HEIGHT)
		{
			return true;
		}
		else
		{
			//_getch();//调试代码
			return true
;
		}
	}
	else if (newbird->bird_y > 480 - BIRD_HEIGHT)//小鸟没有和柱子相撞，判断是否和上下边界碰撞
	{
		return false;
	}
	else
	{
		return true;
	}
}

void gameover(Bird* newbird,Stones* newstones)
{
	if (newbird->bird_y < 480 - 34)
	{
		while (newbird->bird_y < 480 - 34)
		{
			Sleep(20);
			putimage(0, 0, &bg_play);//背景图像
			print_stone(newstones);
			putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_mask)[4], SRCERASE);//掩码图
			putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_real)[4], SRCINVERT);//精灵图
			FlushBatchDraw(0, 0, 640, 600);
			newbird->bird_y += 5;
		}

	}
	putimage(100, 100, &game_over);
	FlushBatchDraw(0, 0, 640, 600);
	Sleep(1000);
	_getch();

}






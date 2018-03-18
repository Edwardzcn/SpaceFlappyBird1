#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "menu.h"
#include "file.h"





//
//int main()
//{
//	beforegame();//游戏前准备，开启图形界面窗口，设置标题
//	ingame(); //欢迎界面（含基本信息，操作
//	aftergame();//关闭图形界面窗口
//	return 0;
//}

void ingame()
{
	int key = 1;
	while (key)
	{
		key = begin();//内含登录操作
		switch (key)
		{
		case 'a':
		case 'A':
			play();
			break;
		case 'b':
		case 'B':
			information(); 
			break;
		case 'c':
		case 'C':
			record(); //显示最高分排名
			break;
		case 'd':
		case 'D':
			key = 0;
			break;
		default:
			break;
		}
	}
}

void beforegame()
{
	//初始化窗口界面
	initgraph(640 + SCORE_WIDTH, 480);
	//设置窗口标题文字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "Edward张的Space Flappy Bird!");
}

void aftergame()
{
	closegraph();
}

int begin()
{

	IMAGE bg_welcome, scorebg;
	loadimage(&bg_welcome, "D:\\SpaceFlappyBird\\welcome.jpg");
	loadimage(&scorebg, "D:\\SpaceFlappyBird\\playscorebg1.jpg");
	putimage(0, 0, &bg_welcome);
	putimage(640, 0, &scorebg);
	int key=_getch();
	return key;


}

void information()
{
	IMAGE bg_rule;
	loadimage(&bg_rule, "D:\\SpaceFlappyBird\\bg_rule.jpg");
	putimage(0, 0, &bg_rule);
	_getch();
}





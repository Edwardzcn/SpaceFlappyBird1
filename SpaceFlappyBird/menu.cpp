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
//	beforegame();//��Ϸǰ׼��������ͼ�ν��洰�ڣ����ñ���
//	ingame(); //��ӭ���棨��������Ϣ������
//	aftergame();//�ر�ͼ�ν��洰��
//	return 0;
//}

void ingame()
{
	int key = 1;
	while (key)
	{
		key = begin();//�ں���¼����
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
			record(); //��ʾ��߷�����
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
	//��ʼ�����ڽ���
	initgraph(640 + SCORE_WIDTH, 480);
	//���ô��ڱ�������
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "Edward�ŵ�Space Flappy Bird!");
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





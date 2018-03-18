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
	//ÿһ���˻�������Ϸǰ���еĳ�ʼ��
	initial_play();
	settextstyle(30, 0, _T("Volter (Goldfish)"));//�趨������ʽ
	setbkmode(TRANSPARENT);//�趨���屳��͸��

	//��½������ʾ������username
	user_login();
	//�鿴�ʻ�����Ӧ�ĳɼ�
	user_history();
	//��ӡ��ʼ�û���Ϣ
	show_score();
	
	//�½�С��
	Bird newbird;
	Stones newstones;
	//�趨���������
	int t = time(NULL);
	srand(t*t);
	//���ر���ͼƬ
	loadimage(&bg_play, "D:\\SpaceFlappyBird\\bgbig.gif");
	loadimage(&bg_score, "D:\\SpaceFlappyBird\\playscorebg1.jpg");
	loadimage(&game_over, "D:\\SpaceFlappyBird\\game_over.jpg");
	//����С������
	loadimage(&(newbird.bird_mask)[0], "D:\\SpaceFlappyBird\\bird_mask1.gif");
	loadimage(&(newbird.bird_mask)[1], "D:\\SpaceFlappyBird\\bird_mask2.gif");
	loadimage(&(newbird.bird_mask)[2], "D:\\SpaceFlappyBird\\bird_mask3.gif");
	loadimage(&(newbird.bird_mask)[3], "D:\\SpaceFlappyBird\\bird_mask1.gif");
	loadimage(&(newbird.bird_mask)[4], "D:\\SpaceFlappyBird\\bird_mask4.gif");
	//����С��λͼ
	loadimage(&(newbird.bird_real)[0], "D:\\SpaceFlappyBird\\bird_real1.gif");
	loadimage(&(newbird.bird_real)[1], "D:\\SpaceFlappyBird\\bird_real2.gif");
	loadimage(&(newbird.bird_real)[2], "D:\\SpaceFlappyBird\\bird_real3.gif");
	loadimage(&(newbird.bird_real)[3], "D:\\SpaceFlappyBird\\bird_real1.gif");
	loadimage(&(newbird.bird_real)[4], "D:\\SpaceFlappyBird\\bird_real4.gif");
	//������������
	loadimage(&(newstones.stone_mask)[0], "D:\\SpaceFlappyBird\\stone_maskup.gif");
	loadimage(&(newstones.stone_mask)[1], "D:\\SpaceFlappyBird\\stone_maskdown.gif");
	//��������λͼ
	loadimage(&(newstones.stone_real)[0], "D:\\SpaceFlappyBird\\stone_realup.gif");
	loadimage(&(newstones.stone_real)[1], "D:\\SpaceFlappyBird\\stone_realdown.gif");
	//����������ͼģʽ��ͼƬһͬ��ʾ����ֹ��Ļ��˸��
	BeginBatchDraw();
	

	while (!esc)
	{
		initial_game(&newbird,&newstones); //ÿ�غ���Ϸ��ʼ��
		while (newbird.alive)
		{
			bird_move(&newbird);							//С���ƶ�
			stone_move(&newstones);							//�����ƶ�
			print_play(&newbird,&newstones);				//������Ϸ������
			print_score(&newbird,&newstones);				//���ƼƷֽ��棨�ж��о������Ӳ�ִ�У�
			newbird.alive = judgement(&newbird,&newstones);	//�ж�С��״̬
			if (esc)
				break;
		}
		if (!esc)
		{
			gameover(&newbird,&newstones);
			user_savescore();
		}
		user_history();//ˢ����ʷ�ɼ�

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
	//��ʼ�������Ϣ
	//������ش�СΪ34*24
	newbird->bird_x = 80;
	newbird->bird_y = 300;
	newbird->bird_change = 0;
	newbird->bird_up = 0;
	newbird->bird_down = 1;
	newbird->alive = true;

	//��ʼ����Ϸ�ߵ�ǰ����
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

	_getch(); //����ͣ��
}

void bird_move(Bird* newbird)
{
	char key;
	if (_kbhit()) //����Ƿ��м�������
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
	putimage(0, 0, &bg_play);//����ͼ��
	print_bird(newbird);
	print_stone(newstones);
	FlushBatchDraw(0, 0, 640, 600);
}


void print_bird(Bird* newbird)
{
	putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_mask)[newbird->bird_change % 4], SRCERASE);//����ͼ
	putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_real)[newbird->bird_change % 4], SRCINVERT);//����ͼ
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
	//���´�ӡ������
	putimage(640, 0, &bg_score);
	//��ӡ�û���
	outtextxy(675, 105, user_name);
	//��ӡ��ǰ����
	char present_score[5] = " ";
	_itoa_s(user_present_score, present_score, sizeof(present_score), 10);
	outtextxy(675, 205, present_score);
	//��ӡ��ʷ��߷���
	char best_record[5] = " ";
	_itoa_s(user_best_record, best_record, sizeof(best_record), 10);
	outtextxy(675, 305, best_record);
}

bool judgement(Bird* newbird,Stones* newstones)
{
	if ((newstones->stone_x)[0] > newbird->bird_x - STONE_WIDTH && (newstones->stone_x)[0] < newbird->bird_x + BIRD_WIDTH)//С���û�����ӵ�ʱ���ж��Ƿ���������ײ
	{
		if (newbird->bird_y > (newstones->stone_y)[0] + STONE_HEIGHT && newbird->bird_y < (newstones->stone_y)[0] + STONE_HEIGHT + 150 - BIRD_HEIGHT)
		{
			return true;
		}
		else
		{
			//_getch();//���Դ���
			return false;
		}
	}
	else if ((newstones->stone_x)[0] < newbird->bird_x + BIRD_WIDTH - GAP)//С�����һ�����ӵ�ʱ���ж��Ƿ���������ײ
	{
		if (newbird->bird_y > (newstones->stone_y)[1] + STONE_HEIGHT && newbird->bird_y < (newstones->stone_y)[1] + STONE_HEIGHT + 150 - BIRD_HEIGHT)
		{
			return true;
		}
		else
		{
			//_getch();//���Դ���
			return true
;
		}
	}
	else if (newbird->bird_y > 480 - BIRD_HEIGHT)//С��û�к�������ײ���ж��Ƿ�����±߽���ײ
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
			putimage(0, 0, &bg_play);//����ͼ��
			print_stone(newstones);
			putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_mask)[4], SRCERASE);//����ͼ
			putimage(newbird->bird_x, newbird->bird_y, &(newbird->bird_real)[4], SRCINVERT);//����ͼ
			FlushBatchDraw(0, 0, 640, 600);
			newbird->bird_y += 5;
		}

	}
	putimage(100, 100, &game_over);
	FlushBatchDraw(0, 0, 640, 600);
	Sleep(1000);
	_getch();

}






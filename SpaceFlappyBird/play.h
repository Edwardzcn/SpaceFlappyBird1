#ifndef PLAY_H
#define PLAY_H

#include <graphics.h>

#define GAP 214				//ǰһ�������Ҳ����һ���������֮��ľ���
#define BIRD_WIDTH 34		//С��ͼƬ�Ŀ��
#define BIRD_HEIGHT 24		//С��ͼƬ�ĸ߶�
#define STONE_WIDTH 140		//����ͼƬ�Ŀ��
#define STONE_HEIGHT 600	//����ͼƬ�ĸ߶�


typedef struct bird_construction
{
	IMAGE bird_mask[5]; //С�����������ͼ
	IMAGE bird_real[5]; //С������ž���ͼ
	int bird_x;			//С��ĺ�����
	int bird_y;			//С���������
	int bird_change;    //С��ķ�������
	int bird_up;		//С������״̬
	int bird_down;		//С������״̬
	bool alive;			//С���Ƿ���
	
}Bird;

typedef struct stone_construction
{
	IMAGE stone_mask[2];		//���ӵ�����ͼ��0Ϊ�ϣ�1Ϊ�£�
	IMAGE stone_real[2];		//���ӵľ���ͼ��0Ϊ�ϣ�1Ϊ�£�
	int stone_x[5];				//�����������
	int stone_y[5];				//������������

}Stones;


char user_name[10] = "";
int user_present_score = 0;
int user_best_record = 0;
int esc = 0;
IMAGE bg_play, bg_score, game_over;



//��ʼ���˻���Ϸ��ʼ
void initial_play();
//��ʼ��ÿ����Ϸ
void initial_game(Bird* newbird,Stones* newstones);

//С���ƶ��������ƶ�
void bird_move(Bird* newbird);
void stone_move(Stones* newstones);
//���������Ϸ������
void print_play(Bird* newbird,Stones* newstones);
void print_bird(Bird* newbird);
void print_stone(Stones* newstones);
//�����Ҳ��������
void print_score(Bird* newbird,Stones* newstones);
static void show_score();

//С������������ж�
bool judgement(Bird* newbird,Stones* newstones);
//��Ϸ��������
void gameover(Bird* newbird,Stones* newstones);


#endif // !PLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include "file.h"

struct userdata_node
{
	char user_name[10];
	int user_score;
	char user_date[10];
	char user_time[10];

};

struct userdata
{
	struct userdata_node user_list[50];

};
typedef struct userdata *User;




void record()
{
	settextstyle(20, 0, _T("Volter (Goldfish)"));//设定字体样式
	setbkmode(TRANSPARENT);//设定字体背景透明

	IMAGE bg_record;
	loadimage(&bg_record, "D:\\SpaceFlappyBird\\bg_record.jpg");
	putimage(0, 0, &bg_record);
	//动态打印最高分
	FILE *fp;
	//将文件内容读出
	User newuser = creat_udcpy();

	fp = fopen("all.txt", "at+");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	int num = 0; //记录有效信息条数
	for (int i = 0;; i++)
	{
		fscanf(fp, "%s", newuser->user_list[i].user_name);
		fscanf(fp, "%d", &newuser->user_list[i].user_score);
		fscanf(fp, "%s", newuser->user_list[i].user_date);
		fscanf(fp, "%s", newuser->user_list[i].user_time);
		if (feof(fp))
		{
			num = i;
			break;
		}
	}
	quick_sort(newuser, 0, num - 1);	//对all成绩进行排序
										//打印
	int k = 13;//当前最大承载数量
	for (int i = num - 1; k>0; i--, k--)
	{
		//打印排名
		char user_rank[5] = " ";
		_itoa_s(num - i, user_rank, sizeof(user_rank), 10);
		outtextxy(50, 230 + 15 * (num - i - 1), user_rank);
		//打印玩家
		outtextxy(100, 230 + 15 * (num - i - 1), (newuser->user_list)[i].user_name);
		//打印分数
		char user_score[5] = " ";
		_itoa_s((newuser->user_list)[i].user_score, user_score, sizeof(user_score), 10);
		outtextxy(190, 230 + 15 * (num - i - 1), user_score);
		//打印日期
		outtextxy(250, 230 + 15 * (num - i - 1), (newuser->user_list)[i].user_date);
		////打印时间
		//outtextxy(500, 230 + 15 * (num - i - 1), (newuser->user_list)[i].user_time);
	}

	_getch();
}



void user_login()
{
	InputBox(user_name, 10, "Please log in\n", "Log in", "stranger", 250, 0, true);
	while (strcmp(user_name, "") == 0)
		InputBox(user_name, 10, "Please log in\n", "Log in", "stranger", 250, 0, true);
}

void user_history()
{
	FILE *fp;
	char save_user_name[20] = "";
	strcpy(save_user_name, user_name);
	//将文件内容读出
	strcat(save_user_name, ".txt");
	User user1=creat_udcpy(); 
	
	fp = fopen(save_user_name, "at+");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	int num = 0; //记录有效信息条数
	for (int i = 0; i < 1000; i++)
	{
		fscanf(fp, "%s", (user1->user_list)[i].user_name);
		fscanf(fp, "%d", &(user1->user_list)[i].user_score);
		fscanf(fp, "%s", (user1->user_list)[i].user_date);
		fscanf(fp, "%s", (user1->user_list)[i].user_time);
		if (feof(fp))
		{
			printf("end of fie,%drecords\n", i);
			num = i;
			break;
		}
	}
	if (!num)
	{
		user_best_record = 0;
	}
	else
	{
		quick_sort(user1, 0, num-1); //对记录数组排序
		user_best_record = (user1->user_list)[num-1].user_score;
	}	
	destroy_udcpy(user1);
}

void user_savescore()
{
	//存入信息
	FILE *fp;
	//存入账户个人文件中
	char save_user_name[20] = "";
	strcpy(save_user_name, user_name);//(save_user_name, user_name);
	fp = fopen(strcat(save_user_name, ".txt"), "at+");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	int size = strlen(user_name);
	fprintf(fp, user_name);//存入用户名;
	for (int i = 0; i < 10 - size; i++)
		fprintf(fp, " ");//空格保持等间距；
	fprintf(fp, "%-10d", user_present_score);//存入本次分数；
											 //strftime格式化保存时间
	time_t tt;
	char gametime[80];

	tt = time(NULL);
	strftime(gametime, 80, "%Y-%m-%d      %H:%M:%S\n", localtime(&tt));
	fprintf(fp, gametime);
	fclose(fp);

	//存入all文件中
	fp = fopen("all.txt","at+");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	fprintf(fp, user_name);
	for (int i = 0; i < 10 - size; i++)
		fprintf(fp, " ");
	fprintf(fp,"%-10d", user_present_score);
	fprintf(fp, gametime);
	fclose(fp);
}

void quick_sort(User namelist, int left, int right)
{
	int i, j, marknum;
	if (left < right)
	{
		i = left;
		j = right;
		marknum = (namelist->user_list)[i].user_score;
		struct userdata_node trans = (namelist->user_list)[i];
		//while (i < j)
		//{
		//	while (i < j && (namelist->user_list)[j].user_score > marknum)
		//		j--; // 从右向左找第一个小于marknum的数 
		//	if (i < j) //结构成员换位置左边标记位置右移一个单位
		//		(namelist->user_list)[i++] = (namelist->user_list)[j];
		//	while (i < j && (namelist->user_list)[i].user_score < marknum)
		//		i++; //从左向右找第一个大于marknum的数
		//	if (i < j)
		//		(namelist->user_list)[j--] = (namelist->user_list)[i];

		//}
		//(namelist->user_list)[i].user_score = marknum; //标记数复位


		while (i < j)
		{
			while (i < j && (namelist->user_list)[j].user_score > marknum)
				j--; // 从右向左找第一个小于marknum的数 
			if (i < j) //结构成员换位置左边标记位置右移一个单位
				(namelist->user_list)[i++] = (namelist->user_list)[j];
			while (i < j && (namelist->user_list)[i].user_score < marknum)
				i++; //从左向右找第一个大于marknum的数
			if (i < j)
				(namelist->user_list)[j--] = (namelist->user_list)[i];

		}
		(namelist->user_list)[i].user_score = marknum; //标记数复位
		(namelist->user_list)[i] = trans;







		quick_sort(namelist, left, i - 1); /* 递归调用 */
		quick_sort(namelist, i + 1, right);
	}
}



User creat_udcpy()
{
	User userpoint = (User)malloc(sizeof(struct userdata));
	if (userpoint == NULL)
		terminate("Error in create userpoint!\n");
	return userpoint;
}

static void terminate(const char* errorsentence)
{
	printf("%s", errorsentence);
	exit(EXIT_FAILURE);
}

void destroy_udcpy(User partlist)
{
	free(partlist);
	partlist = NULL;
}
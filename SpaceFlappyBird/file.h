#ifndef FILE_H
#define FILE_H

extern char user_name[10];
extern int user_present_score;
extern int user_best_record;



typedef struct userdata *User;

User creat_udcpy();



static void terminate(const char* errorsentence);

void record();

void destroy_udcpy(User partlist);

void quick_sort(User namelist, int left, int right);

void user_login();//登录界面，登录后显示使用的账户名

void user_history(); //查询历史最高分，如果空的话则返回0

void user_savescore();//每局游戏结束，记录并且存储分值；


#endif // !FILE_H

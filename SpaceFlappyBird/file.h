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

void user_login();//��¼���棬��¼����ʾʹ�õ��˻���

void user_history(); //��ѯ��ʷ��߷֣�����յĻ��򷵻�0

void user_savescore();//ÿ����Ϸ��������¼���Ҵ洢��ֵ��


#endif // !FILE_H

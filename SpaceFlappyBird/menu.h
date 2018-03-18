#ifndef MENU_H
#define MENU_H

#define SCORE_WIDTH 200

void beforegame();//游戏前初始设定，打开窗口设定标题
void ingame();//载入游戏界面
void aftergame();//结束游戏关闭窗口

int begin();//载入背景图片(gif动图)，显示游戏信息
void play();//游戏进行
void information();//显示操作规则
extern void record();//显示高分记录


#endif // !MENU_H

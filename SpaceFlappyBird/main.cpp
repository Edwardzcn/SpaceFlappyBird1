#include "menu.h"

int main()
{
	beforegame();//游戏前准备，开启图形界面窗口，设置标题
	ingame(); //欢迎界面（含基本信息，操作
	aftergame();//关闭图形界面窗口
	return 0;
}
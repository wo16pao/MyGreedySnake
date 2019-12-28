#include "tools.h"
#include <windows.h>
#include <iostream>

//设置窗口大小
void Tool::setWindowSize(int length, int width)
{
	system("title YH贪吃蛇");//设置窗口标题
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", length*2, width);//一个图形■占两个字符，故宽度乘以2
	system(cmd);//system(mode con cols=88 lines=88)设置窗口宽度和高度
}

//设置光标位置
void Tool::setCursorPosition(const int x, const int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//光标输出位置为pos位置
}

//设置字体颜色
void Tool::setColor(int color_id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_id);
}

//设置字体背景颜色
void Tool::setBackColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

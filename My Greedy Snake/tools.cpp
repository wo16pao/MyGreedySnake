#include "tools.h"
#include <windows.h>
#include <iostream>

//���ô��ڴ�С
void Tool::setWindowSize(int length, int width)
{
	system("title YH̰����");//���ô��ڱ���
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", length*2, width);//һ��ͼ�Ρ�ռ�����ַ����ʿ�ȳ���2
	system(cmd);//system(mode con cols=88 lines=88)���ô��ڿ�Ⱥ͸߶�
}

//���ù��λ��
void Tool::setCursorPosition(const int x, const int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//������λ��Ϊposλ��
}

//����������ɫ
void Tool::setColor(int color_id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_id);
}

//�������屳����ɫ
void Tool::setBackColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

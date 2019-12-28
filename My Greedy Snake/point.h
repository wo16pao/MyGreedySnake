#ifndef POINT_H
#define POINT_H

#include "tools.h"

class Point : public Tool
{
public:

	Point() {}

	Point(int x, int y);

	void printRect();//绘制方块

	void printCircle();//绘制圆形

	void clearPrint();//清除绘制

	void changePosition(const int x, const int y);//改变位置

	bool operator==(const Point &point);//重载==

	int getX();//获取X值

	int getY();//获取Y值

private:

	int m_x;
	int m_y;
	//Tool m_tool;

};


#endif // POINT_H


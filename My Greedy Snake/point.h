#ifndef POINT_H
#define POINT_H

#include "tools.h"

class Point : public Tool
{
public:

	Point() {}

	Point(int x, int y);

	void printRect();//���Ʒ���

	void printCircle();//����Բ��

	void clearPrint();//�������

	void changePosition(const int x, const int y);//�ı�λ��

	bool operator==(const Point &point);//����==

	int getX();//��ȡXֵ

	int getY();//��ȡYֵ

private:

	int m_x;
	int m_y;
	//Tool m_tool;

};


#endif // POINT_H


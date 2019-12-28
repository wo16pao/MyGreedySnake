#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"
#include "food.h"
#include <deque>
using namespace std;

class Food;//����Food��
class Snake : public Point
{

public:
	enum Direction//ö�ٷ���
	{
		UP,DOWN,LEFT,RIGHT
	};

	Snake();

	void initSnake();//��ʼ���߲���ӡ

	void addSnake();//�������ƶ�

	void moveSnake();//����ʳ��֮��䳤

	bool hitSomething();//ײ���������ж���Ϸ�Ƿ����

	bool changeDirection();//�ı䷽��

	bool getFood(const Food&);//�Ե�ʳ��

private:

	deque<Point> m_snake;//deque�����ļ�¼
	Direction m_direction;//����
	friend class Food;//��Food��Ϊ��Ԫ
};

#endif // SNAKE_H


#ifndef FOOD_H
#define FOOD_H

#include "point.h"
#include "snake.h"

class Snake;//����Snake��
class Food : public Point
{

public:

	Food();

	void drawFood(Snake& snake);//����ʳ��

private:
	int m_x;
	int m_y;
	friend class Snake;//��Snake��Ϊ��Ԫ

};

#endif // FOOD_H

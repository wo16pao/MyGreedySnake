#ifndef FOOD_H
#define FOOD_H

#include "point.h"
#include "snake.h"

class Snake;//声明Snake类
class Food : public Point
{

public:

	Food();

	void drawFood(Snake& snake);//生成食物

private:
	int m_x;
	int m_y;
	friend class Snake;//将Snake设为友元

};

#endif // FOOD_H

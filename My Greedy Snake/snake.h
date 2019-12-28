#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"
#include "food.h"
#include <deque>
using namespace std;

class Food;//声明Food类
class Snake : public Point
{

public:
	enum Direction//枚举方向
	{
		UP,DOWN,LEFT,RIGHT
	};

	Snake();

	void initSnake();//初始化蛇并打印

	void addSnake();//蛇正常移动

	void moveSnake();//吃了食物之后变长

	bool hitSomething();//撞到东西，判断游戏是否结束

	bool changeDirection();//改变方向

	bool getFood(const Food&);//吃到食物

private:

	deque<Point> m_snake;//deque存放设的记录
	Direction m_direction;//方向
	friend class Food;//将Food设为友元
};

#endif // SNAKE_H


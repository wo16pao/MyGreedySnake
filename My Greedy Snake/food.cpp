#include "food.h"
#include <iostream>

Food::Food() 
{

}

//生成食物
void Food::drawFood(Snake& snake)
{
	int food_x;//食物坐标
	int food_y;
	bool flag;//判断食物是否出现在蛇身上
	while (true)
	{
		food_x = rand() % 30;//随机产生食物坐标
		food_y = rand() % 30;
		if (food_x < 2) food_x += 2;//若余数为1，则+2
		if (food_y < 2) food_y += 2;
		Point * food_point = new Point(food_x, food_y);
		flag = false;
		for(auto &point : snake.m_snake)
		{
			if (*food_point == point)
			{
				flag = true;//食物和蛇重叠
				break;
			}
		}
		if(flag)//重新生成食物
			continue;
		m_x = food_x;
		m_y = food_y;
		this->setCursorPosition(food_x, food_y);//绘制食物
		this->setColor(15);
		cout << "★";//食物符号
		break;
	}
}


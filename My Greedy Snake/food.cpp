#include "food.h"
#include <iostream>

Food::Food() 
{

}

//����ʳ��
void Food::drawFood(Snake& snake)
{
	int food_x;//ʳ������
	int food_y;
	bool flag;//�ж�ʳ���Ƿ������������
	while (true)
	{
		food_x = rand() % 30;//�������ʳ������
		food_y = rand() % 30;
		if (food_x < 2) food_x += 2;//������Ϊ1����+2
		if (food_y < 2) food_y += 2;
		Point * food_point = new Point(food_x, food_y);
		flag = false;
		for(auto &point : snake.m_snake)
		{
			if (*food_point == point)
			{
				flag = true;//ʳ������ص�
				break;
			}
		}
		if(flag)//��������ʳ��
			continue;
		m_x = food_x;
		m_y = food_y;
		this->setCursorPosition(food_x, food_y);//����ʳ��
		this->setColor(15);
		cout << "��";//ʳ�����
		break;
	}
}


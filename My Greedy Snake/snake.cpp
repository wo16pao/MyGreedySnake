#include "snake.h"
#include <conio.h>

Snake::Snake()//Snake构造函数，蛇一开始只有两节，方向随机
{
	m_snake.emplace_back(Point(14, 14));
	m_snake.emplace_back(Point(14, 15));
	int direction = rand() % 4;//随机方向
	switch (direction)
	{
	case 0:
		m_direction = Direction::UP;
		break;
	case 1:
		m_direction = Direction::DOWN;
		break;
	case 2:
		m_direction = Direction::LEFT;
		break;
	case 3:
		m_direction = Direction::RIGHT;
		break;
	default:
		break;
	}
}

//画最初的两节蛇
void Snake::initSnake()
{
	this->setColor(6);
	for (auto &point : m_snake)
	{
		point.printCircle();
	}
}

//蛇头加长
void Snake::addSnake()
{
	//不同方向蛇头加的位置不同
	switch (m_direction)
	{
	case Snake::UP:
		m_snake.emplace_front(Point(m_snake.front().getX(), m_snake.front().getY() - 1));
		break;
	case Snake::DOWN:
		m_snake.emplace_front(Point(m_snake.front().getX(), m_snake.front().getY() + 1));
		break;
	case Snake::LEFT:
		m_snake.emplace_front(Point(m_snake.front().getX() - 1, m_snake.front().getY()));
		break;
	case Snake::RIGHT:
		m_snake.emplace_front(Point(m_snake.front().getX() + 1, m_snake.front().getY()));
		break;
	default:
		break;
	}
	//新画蛇头
	this->setColor(6);
	m_snake.front().printCircle();
}


//正常移动
void Snake::moveSnake()
{
	this->addSnake();//先加一个蛇头，若是正常移动再将尾部删除
	m_snake.back().clearPrint();
	m_snake.pop_back();
}

//判断是否死亡，死亡为true
bool Snake::hitSomething()
{
	Point *head = new Point(m_snake.front().getX(),m_snake.front().getY());//得到蛇头坐标
	//若蛇头坐标等于自身坐标，则撞到自己
	for (deque<Point>::iterator it = ++m_snake.begin(); it != m_snake.end(); it++)
	{
		if (*head == *it)
		{
			return true;
		}
	}
	//若蛇头坐标等于墙坐标，则死亡
	if (head->getX() >= 30 || head->getX() <= 1 || head->getY() >= 30 || head->getY() <= 1)
		return true;
	delete head;
	return false;
}

//改变蛇方向
bool Snake::changeDirection()
{
	char ch;//获取按下键位
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			switch (ch)
			{
			case 72:
				if (m_direction != Direction::DOWN)//如果方向与当前运动方向相反，无效
					m_direction = Direction::UP;
				break;
			case 80:
				if (m_direction != Direction::UP)
					m_direction = Direction::DOWN;
				break;
			case 75:
				if (m_direction != Direction::RIGHT)
					m_direction = Direction::LEFT;
				break;
			case 77:
				if (m_direction != Direction::LEFT)
					m_direction = Direction::RIGHT;
				break;
			default:
				break;
			}
			return true;

		case 27://ESC
			return false;

		default:
			return true;

		}
	}
	return true;
}

//判断是否吃到食物
bool Snake::getFood(const Food & food)
{
	if (m_snake.front().getX() == food.m_x&&m_snake.front().getY() == food.m_y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

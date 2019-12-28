#include "snake.h"
#include <conio.h>

Snake::Snake()//Snake���캯������һ��ʼֻ�����ڣ��������
{
	m_snake.emplace_back(Point(14, 14));
	m_snake.emplace_back(Point(14, 15));
	int direction = rand() % 4;//�������
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

//�������������
void Snake::initSnake()
{
	this->setColor(6);
	for (auto &point : m_snake)
	{
		point.printCircle();
	}
}

//��ͷ�ӳ�
void Snake::addSnake()
{
	//��ͬ������ͷ�ӵ�λ�ò�ͬ
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
	//�»���ͷ
	this->setColor(6);
	m_snake.front().printCircle();
}


//�����ƶ�
void Snake::moveSnake()
{
	this->addSnake();//�ȼ�һ����ͷ�����������ƶ��ٽ�β��ɾ��
	m_snake.back().clearPrint();
	m_snake.pop_back();
}

//�ж��Ƿ�����������Ϊtrue
bool Snake::hitSomething()
{
	Point *head = new Point(m_snake.front().getX(),m_snake.front().getY());//�õ���ͷ����
	//����ͷ��������������꣬��ײ���Լ�
	for (deque<Point>::iterator it = ++m_snake.begin(); it != m_snake.end(); it++)
	{
		if (*head == *it)
		{
			return true;
		}
	}
	//����ͷ�������ǽ���꣬������
	if (head->getX() >= 30 || head->getX() <= 1 || head->getY() >= 30 || head->getY() <= 1)
		return true;
	delete head;
	return false;
}

//�ı��߷���
bool Snake::changeDirection()
{
	char ch;//��ȡ���¼�λ
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
				if (m_direction != Direction::DOWN)//��������뵱ǰ�˶������෴����Ч
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

//�ж��Ƿ�Ե�ʳ��
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

#include "controller.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

Controller::Controller()
{
	
}

//��Ϸ��ʼ
void Controller::startGame()
{
	Map::setWindowSize(41, 32);//���ô��ڴ�С
	//Map::setColor(1);//����������ɫ
	
}

//������Ϸ��ͼ
void Controller::drawMap()
{
	system("cls");//����

	this->Map::setColor(1);
	//���ƹ���
	Map *init_map = new Map();
	init_map->printInitMap();
	delete init_map;
	m_score = 0;
}

//ѡ��ģʽ
void Controller::selectMode()
{
	//ѡ�����
	this->Map::setColor(3);
	this->Map::setCursorPosition(8, 10);
	cout << "��ѡ���Ѷ�";
	this->Map::setCursorPosition(8, 12);
	cout << "(���¼�ѡ��";
	this->Map::setCursorPosition(8, 13);
	cout << "�س���ȷ��)";
	this->Map::setCursorPosition(18, 10);
	this->Map::setBackColor();//Ĭ��Ϊ��ģʽ��ѡ��ʱ�б���ɫ
	cout << "��ģʽ";
	this->Map::setColor(3);
	this->Map::setCursorPosition(18, 14);
	cout << "����ģʽ";
	this->Map::setCursorPosition(18, 18);
	cout << "����ģʽ";

	bool flag = false;//��¼�Ƿ񰴻س�ȷ��
	this->m_key = 1;//Ĭ��ѡ�м�ģʽ
	int ch;//������ȡ���¼���ASCII��
	//ѡ��ģʽ
	while (ch = _getch())
	{
		switch (ch)
		{
		case 72://�ϼ�
			if (m_key > 1)//����ǰѡ�еĲ��Ǽ�ģʽ�����޷�������
			{
				switch (m_key)
				{
				case 2:
					//��������ģʽ��Ϊ��ģʽʱ
					this->Map::setCursorPosition(18, 10);
					this->Map::setBackColor();
					cout << "��ģʽ";

					this->Map::setCursorPosition(18, 14);
					this->Map::setColor(3);
					cout << "����ģʽ";

					m_key = 1;

					break;
				case 3:
					//���ӵ���ģʽ��Ϊ����ģʽʱ
					this->Map::setCursorPosition(18, 14);
					this->Map::setBackColor();
					cout << "����ģʽ";

					this->Map::setCursorPosition(18, 18);
					this->Map::setColor(3);
					cout << "����ģʽ";

					m_key = 2;

					break;
				default:
					break;
				}
			}
			break;
		case 80://�¼�
			if (m_key < 3)//����ǰѡ�еĲ��ǵ���ģʽ�����޷�������
			{
				switch (m_key)
				{
				case 1:
					//���Ӽ�ģʽ������ģʽʱ
					this->Map::setCursorPosition(18, 14);
					this->Map::setBackColor();
					cout << "����ģʽ";

					this->Map::setCursorPosition(18, 10);
					this->Map::setColor(3);
					cout << "��ģʽ";

					m_key = 2;

					break;

				case 2:
					//��������ģʽ������ģʽʱ
					this->Map::setCursorPosition(18, 18);
					this->Map::setBackColor();
					cout << "����ģʽ";

					this->Map::setCursorPosition(18, 14);
					this->Map::setColor(3);
					cout << "����ģʽ";

					m_key = 3;

					break;
				default:
					break;
				}
			}
			break;
		case 13://�س���
			flag = true;//ȷ����flagΪ��
			break;
		default:
			break;
		}
		if (flag)//ȷ�����˳�whileѭ��
		{
			break;
		}
	}
	//����ģʽȷ��С���ٶ�
	switch (m_key)
	{
	case 1:
		m_speed = 150;
		break;
	case 2:
		m_speed = 125;
		break;
	case 3:
		m_speed = 100;
		break;
	default:
		break;
	}
}

//��Ϸ����
void Controller::gamePlayControl()
{
	startGame();
	while(true)
	{
		selectMode();
		drawMap();
		drawSocre();
		int tmp = beginPlay();
		if (tmp == 2)
		{
			system("cls");
			continue;
		}
	}
}

//��ʼ��Ϸ
int Controller::beginPlay()
{
	Snake *csnake = new Snake();
	Food *cfood = new Food();
	csnake->initSnake();//��ӡ��ʼ����
	srand((unsigned)time(NULL));
	cfood->drawFood(*csnake);

	while (!csnake->hitSomething())
	{
		if (!csnake->changeDirection())//ESC��ͣ
		{
			int tmp = this->pauseMenu();
			switch (tmp)
			{
			case 2:
				delete csnake;
				delete cfood;
				return 2;
			case 3:
				delete csnake;
				delete cfood;
				exit(0);
			default:
				break;
			}
		}
		if (csnake->getFood(*cfood))//�Ե�ʳ��
		{
			csnake->addSnake();
			this->upDateScore();
			this->drawSocre();
			m_speed--;
			cfood->drawFood(*csnake);
		}
		else//�Զ��ƶ�
		{
			csnake->moveSnake();
		}
		Sleep(m_speed);
	}

	delete csnake;
	delete cfood;
}

void Controller::upDateScore()//���·���
{
	m_score++;
}

void Controller::drawSocre()//���Ʒ���
{
	this->Map::setCursorPosition(32, 15);
	this->Map::setColor(3);
	cout << "���ķ���Ϊ��";
	this->Map::setCursorPosition(33, 17);
	cout << m_score;
}

int Controller::pauseMenu()
{
	this->Map::setCursorPosition(32, 19);
	this->Map::setColor(3);
	this->Map::setBackColor();
	cout << "������Ϸ";
	this->Map::setColor(3);
	this->Map::setCursorPosition(32, 21);
	cout << "���¿�ʼ";
	this->Map::setCursorPosition(32, 23);
	cout << "�˳���Ϸ";
	
	int key = 1;
	char ch;
	bool flag = false;
	while (true)
	{
		switch (ch = _getch())
		{
		case 72:
			if (key > 1)
			{
				switch (key)
				{
				case 2:
					this->Map::setCursorPosition(32, 19);
					this->Map::setColor(3);
					this->Map::setBackColor();
					cout << "������Ϸ";

					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "���¿�ʼ";

					key = 1;
					break;
				case 3:
					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					this->Map::setBackColor();
					cout << "���¿�ʼ";
					this->Map::setCursorPosition(32, 23);
					this->Map::setColor(3);
					cout << "�˳���Ϸ";

					key = 2;
					break;
				default:
					break;
				}
			}
			break;
		case 80:
			if (key < 3)
			{
				switch (key)
				{
				case 1:
					this->Map::setCursorPosition(32, 19);
					this->Map::setColor(3);
					cout << "������Ϸ";
					this->Map::setColor(3);
					this->Map::setBackColor();
					this->Map::setCursorPosition(32, 21);
					cout << "���¿�ʼ";

					key = 2;
					break;
				case 2:
					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "���¿�ʼ";
					this->Map::setCursorPosition(32, 23);
					this->Map::setColor(3);
					this->Map::setBackColor();
					cout << "�˳���Ϸ";

					key = 3;
					break;
				default:
					break;
				}
			}
			break;
		case 13:
			flag = true;
			break;
		default:
			break;
		}
		if(flag)
			break;

	}

	if (key == 1)
	{
		this->Map::setCursorPosition(32, 19);
		cout << "          ";
		this->Map::setCursorPosition(32, 21);
		cout << "          ";
		this->Map::setCursorPosition(32, 23);
		cout << "          ";
	}

	return key;
}

void Controller::gameOverMenu()
{
	
}

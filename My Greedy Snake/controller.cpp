#include "controller.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <algorithm>

Controller::Controller()
{
	
}

//��Ϸ��ʼ
void Controller::startGame()
{
	Map::setWindowSize(41, 32);//���ô��ڴ�С
	//Map::setColor(1);//����������ɫ
	m_save_score.clear();//����
	this->loadScore();//��Ϸ��ʼ��ȡ����
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

	this->Map::setCursorPosition(0, 31);

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
		this->Map::setCursorPosition(0, 31);
		if (flag)//ȷ�����˳�whileѭ��
		{
			break;
		}
	}
	//����ģʽȷ��С���ٶ�,ֵԽС�ٶ�Խ��
	switch (m_key)
	{
	case 1:
		m_speed = 150;
		break;
	case 2:
		m_speed = 120;
		break;
	case 3:
		m_speed = 90;
		break;
	default:
		break;
	}
}

//��Ϸ����
void Controller::gamePlayControl()
{
	startGame();//���ƴ���
	while(true)
	{
		selectMode();//ѡ���Ѷ�
		drawMap();//���Ƶ�ͼ
		drawSocre();//���Ʒ���
		beginPlay();//��ʼ��Ϸ

	}
}

//��ʼ��Ϸ
void Controller::beginPlay()
{
	srand((unsigned)time(NULL));//���ÿ�ʼ�����ʳ������ֵ
	Snake *csnake = new Snake();
	Food *cfood = new Food();
	csnake->initSnake();//��ӡ��ʼ����
	cfood->drawFood(*csnake);

	while (!csnake->hitSomething())
	{
		if (!csnake->changeDirection())//ESC��ͣ
		{
			this->pauseMenu();//��ͣ�˵�
			
		}
		if (csnake->getFood(*cfood))//�Ե�ʳ��
		{
			csnake->addSnake();//���ӱ䳤
			this->updateScore();//���·���
			this->drawSocre();//���Ƹ����˵ķ���
			if (m_speed != 0)
				m_speed--;//�ٶȼӿ�
			cfood->drawFood(*csnake);//�����µ�ʳ��
		}
		else//�Զ��ƶ�
		{
			csnake->moveSnake();
		}
		Sleep(m_speed);//speedԽС�ٶ�Խ��
	}
	if (csnake->hitSomething())//���ײ��
	{
		this->gameOverMenu();//��Ϸ�����˵�
	}

	delete csnake;
	delete cfood;
}

//���·���
void Controller::updateScore()
{
	m_score += m_key;
}

//���Ʒ���
void Controller::drawSocre()
{
	this->Map::setCursorPosition(32, 15);
	this->Map::setColor(3);
	cout << "���ķ���Ϊ��";
	this->Map::setCursorPosition(33, 17);
	cout << m_score;
}

//��ͣ�˵�
void Controller::pauseMenu()
{
	//��ͣ�˵�ѡ��
	this->Map::setCursorPosition(32, 19);
	this->Map::setColor(3);
	this->Map::setBackColor();
	cout << "������Ϸ";
	this->Map::setColor(3);
	this->Map::setCursorPosition(32, 21);
	cout << "���¿�ʼ";
	this->Map::setCursorPosition(32, 23);
	cout << "�˳���Ϸ";
	
	this->Map::setCursorPosition(0,31);

	int key = 1;
	char ch;
	bool flag = false;
	while (true)
	{
		switch (ch = _getch())
		{
		case 72://Up
			if (key > 1)
			{
				switch (key)
				{
				case 2:
					this->Map::setCursorPosition(32, 19);
					//this->Map::setColor(3);
					this->Map::setBackColor();
					cout << "������Ϸ";

					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "���¿�ʼ";

					key = 1;
					break;
				case 3:
					this->Map::setCursorPosition(32, 21);
					//this->Map::setColor(3);
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
		case 80://Down
			if (key < 3)
			{
				switch (key)
				{
				case 1:
					this->Map::setCursorPosition(32, 19);
					this->Map::setColor(3);
					cout << "������Ϸ";
					//this->Map::setColor(3);
					this->Map::setCursorPosition(32, 21);
					this->Map::setBackColor();
					cout << "���¿�ʼ";

					key = 2;
					break;
				case 2:
					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "���¿�ʼ";
					this->Map::setCursorPosition(32, 23);
					//this->Map::setColor(3);
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
		this->Map::setCursorPosition(0, 31);
		if(flag)
			break;

	}
	//������Ϸ���������ͣ�˵�������
	if (key == 1)
	{
		this->Map::setCursorPosition(32, 19);
		cout << "          ";
		this->Map::setCursorPosition(32, 21);
		cout << "          ";
		this->Map::setCursorPosition(32, 23);
		cout << "          ";
		Sleep(400);//�ӳ�0.4s��ʼ
	}
	//���¿�ʼ
	if (key == 2)
	{
		this->gamePlayControl();
	}
	//�˳�
	if (key == 3)
	{
		exit(0);
	}
	
}

//��Ϸ�����˵�
void Controller::gameOverMenu()
{
	Sleep(300);
	//������Ϸ�����˵�
	this->Map::setCursorPosition(8, 10);
	this->Map::setColor(7);
	cout << "Game Over !!! ";
	this->Map::setCursorPosition(8, 12);
	cout << "��ķ���Ϊ�� " << m_score;
	this->Map::setCursorPosition(8, 14);
	if(isRank())
	{
		cout << "��ϲ���ϰ�";
	}
	else
	{
		cout << "���ź�����δ�ϰ�";
	}
	this->Map::setCursorPosition(8, 16);
	cout << "�Ƿ�����һ�֣�";
	this->Map::setCursorPosition(8, 18);
	this->Map::setBackColor();
	cout << "ȷ��";
	this->Map::setCursorPosition(11, 18);
	this->Map::setColor(7);
	cout << "�˳�";

	this->showScoreRank();//��ʾ����

	this->Map::setCursorPosition(0, 31);

	int key = 1;
	int flag = false;
	char ch;
	while (ch=_getch())
	{
		switch (ch)
		{
		case 75://Left
			if (key == 2)
			{
				this->Map::setCursorPosition(8, 18);
				this->Map::setBackColor();
				cout << "ȷ��";
				this->Map::setCursorPosition(11, 18);
				this->Map::setColor(7);
				cout << "�˳�";

				key = 1;
			}
			break;
		case 77://Right
			if (key == 1)
			{
				this->Map::setCursorPosition(8, 18);
				cout << "ȷ��";
				this->Map::setCursorPosition(11, 18);
				this->Map::setBackColor();
				cout << "�˳�";

				key = 2;
			}
			break;
		case 13://Enter
			flag = true;
			break;
		default:
			break;
		}
		this->Map::setCursorPosition(0, 31);
		if (flag)
		{
			break;
		}

	}
	//���¿�ʼ
	if (key == 1)
	{
		this->gamePlayControl();
	}
	//�˳�
	else if (key == 2)
	{
		exit(0);
	}



}

//��������  
void Controller::saveScore()
{
	ofstream ofs;
	ofs.open("score.txt", ios::out);
	if (!ofs.is_open())
	{
		return;
	}
	if(m_save_score.size() <= 5)//��С��5����ȫ������
	{
		for (vector<int>::iterator it = m_save_score.begin(); it != m_save_score.end(); it++)
		{
			ofs << *it << endl;
		}
	}
	else//����ֻ����ǰ��5��
	{
		for (int i = 0; i < 5; i++)
		{
			ofs << m_save_score[i];
		}
	}
	ofs.close();
}

//���ط���
void Controller::loadScore()
{
	ifstream ifs;
	ifs.open("score.txt", ios::in);
	if (!ifs.is_open())
	{
		return;
	}
	int tmp_score;
	while (ifs >> tmp_score)
	{
		m_save_score.push_back(tmp_score);
	}
	sort(m_save_score.begin(), m_save_score.end(),greater<int>());//����
	ifs.close();
}

//չʾ��������
void Controller::showScoreRank()
{
	this->updateScoreRank();//ˢ�·���
	this->Map::setCursorPosition(17, 10);
	this->Map::setColor(7);
	cout << "����������";
	int pos = 12;//������ʾλ��
	for (int i = 0; i < m_save_score.size(); i++)
	{
		this->Map::setCursorPosition(17, pos);
		cout << "��" << i + 1 << "��";
		this->Map::setCursorPosition(21, pos);
		cout << m_save_score[i];
		pos += 2;
	}
}

//���·�������
void Controller::updateScoreRank()
{
	if (isRank() && !isSameRank())//�ϰ�����·���
	{
		if(m_save_score.size() >= 5)
		{
			m_save_score.back() = m_score;//����С�ķ�������
		}
		else
		{
			m_save_score.push_back(m_score);//������5�����������
		}
		this->saveScore();//���浽�ļ���
		sort(m_save_score.begin(), m_save_score.end(), greater<int>());//����
	}
	
}

//�ж��Ƿ��ϰ�
bool Controller::isRank()
{
	if (int(m_save_score.size()) < 5)//����¼����5�������Ϊ�ϰ�
	{
		return true;
	}
	else if (m_score >= m_save_score.back())//���������һ��������ҲΪ�ϰ�
	{
		return true;
	}
	return false;
}

//�ж��ϰ�����Ƿ��ظ����ظ��Ͳ���ʾ������Ϊ�ϰ��ظ�Ϊtrue
bool Controller::isSameRank()
{
	for (vector<int>::iterator it = m_save_score.begin(); it != m_save_score.end(); it++)
	{
		if (*it == m_score)
		{
			return true;
		}
	}
	return false;
}


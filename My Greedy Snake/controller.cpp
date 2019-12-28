#include "controller.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

Controller::Controller()
{
	
}

//游戏开始
void Controller::startGame()
{
	Map::setWindowSize(41, 32);//设置窗口大小
	//Map::setColor(1);//设置字体颜色
	
}

//绘制游戏地图
void Controller::drawMap()
{
	system("cls");//清屏

	this->Map::setColor(1);
	//绘制过程
	Map *init_map = new Map();
	init_map->printInitMap();
	delete init_map;
	m_score = 0;
}

//选择模式
void Controller::selectMode()
{
	//选择界面
	this->Map::setColor(3);
	this->Map::setCursorPosition(8, 10);
	cout << "请选择难度";
	this->Map::setCursorPosition(8, 12);
	cout << "(上下键选择";
	this->Map::setCursorPosition(8, 13);
	cout << "回车键确定)";
	this->Map::setCursorPosition(18, 10);
	this->Map::setBackColor();//默认为简单模式，选中时有背景色
	cout << "简单模式";
	this->Map::setColor(3);
	this->Map::setCursorPosition(18, 14);
	cout << "困难模式";
	this->Map::setCursorPosition(18, 18);
	cout << "地狱模式";

	bool flag = false;//记录是否按回车确定
	this->m_key = 1;//默认选中简单模式
	int ch;//用来获取上下键的ASCII码
	//选择模式
	while (ch = _getch())
	{
		switch (ch)
		{
		case 72://上键
			if (m_key > 1)//若当前选中的不是简单模式，则无法再往上
			{
				switch (m_key)
				{
				case 2:
					//当从困难模式变为简单模式时
					this->Map::setCursorPosition(18, 10);
					this->Map::setBackColor();
					cout << "简单模式";

					this->Map::setCursorPosition(18, 14);
					this->Map::setColor(3);
					cout << "困难模式";

					m_key = 1;

					break;
				case 3:
					//当从地狱模式变为困难模式时
					this->Map::setCursorPosition(18, 14);
					this->Map::setBackColor();
					cout << "困难模式";

					this->Map::setCursorPosition(18, 18);
					this->Map::setColor(3);
					cout << "地狱模式";

					m_key = 2;

					break;
				default:
					break;
				}
			}
			break;
		case 80://下键
			if (m_key < 3)//若当前选中的不是地狱模式，则无法再往下
			{
				switch (m_key)
				{
				case 1:
					//当从简单模式到困难模式时
					this->Map::setCursorPosition(18, 14);
					this->Map::setBackColor();
					cout << "困难模式";

					this->Map::setCursorPosition(18, 10);
					this->Map::setColor(3);
					cout << "简单模式";

					m_key = 2;

					break;

				case 2:
					//当从困难模式到地狱模式时
					this->Map::setCursorPosition(18, 18);
					this->Map::setBackColor();
					cout << "地狱模式";

					this->Map::setCursorPosition(18, 14);
					this->Map::setColor(3);
					cout << "困难模式";

					m_key = 3;

					break;
				default:
					break;
				}
			}
			break;
		case 13://回车键
			flag = true;//确定后flag为真
			break;
		default:
			break;
		}
		if (flag)//确定后退出while循环
		{
			break;
		}
	}
	//根据模式确定小蛇速度
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

//游戏控制
void Controller::gamePlayControl()
{
	startGame();
	while(true)
	{
		selectMode();
		drawMap();
		drawSocre();
		beginPlay();

	}
}

//开始游戏
void Controller::beginPlay()
{
	Snake *csnake = new Snake();
	Food *cfood = new Food();
	csnake->initSnake();//打印初始化蛇
	srand((unsigned)time(NULL));
	cfood->drawFood(*csnake);

	while (!csnake->hitSomething())
	{
		if (!csnake->changeDirection())//ESC暂停
		{
			this->pauseMenu();
			
		}
		if (csnake->getFood(*cfood))//吃到食物
		{
			csnake->addSnake();
			this->upDateScore();
			this->drawSocre();
			m_speed--;
			cfood->drawFood(*csnake);
		}
		else//自动移动
		{
			csnake->moveSnake();
		}
		Sleep(m_speed);
	}

	delete csnake;
	delete cfood;
}

void Controller::upDateScore()//更新分数
{
	m_score++;
}

void Controller::drawSocre()//绘制分数
{
	this->Map::setCursorPosition(32, 15);
	this->Map::setColor(3);
	cout << "您的分数为：";
	this->Map::setCursorPosition(33, 17);
	cout << m_score;
}

void Controller::pauseMenu()
{
	this->Map::setCursorPosition(32, 19);
	this->Map::setColor(3);
	this->Map::setBackColor();
	cout << "继续游戏";
	this->Map::setColor(3);
	this->Map::setCursorPosition(32, 21);
	cout << "重新开始";
	this->Map::setCursorPosition(32, 23);
	cout << "退出游戏";
	
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
					cout << "继续游戏";

					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "重新开始";

					key = 1;
					break;
				case 3:
					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					this->Map::setBackColor();
					cout << "重新开始";
					this->Map::setCursorPosition(32, 23);
					this->Map::setColor(3);
					cout << "退出游戏";

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
					cout << "继续游戏";
					//this->Map::setColor(3);
					this->Map::setBackColor();
					this->Map::setCursorPosition(32, 21);
					cout << "重新开始";

					key = 2;
					break;
				case 2:
					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "重新开始";
					this->Map::setCursorPosition(32, 23);
					this->Map::setColor(3);
					this->Map::setBackColor();
					cout << "退出游戏";

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
	if (key == 2)
	{
		this->gamePlayControl();
	}
	if (key == 3)
	{
		exit(0);
	}
	
}

void Controller::gameOverMenu()
{
	
}

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

//游戏开始
void Controller::startGame()
{
	Map::setWindowSize(41, 32);//设置窗口大小
	//Map::setColor(1);//设置字体颜色
	m_save_score.clear();//清理
	this->loadScore();//游戏开始读取分数
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

	this->Map::setCursorPosition(0, 31);

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
		this->Map::setCursorPosition(0, 31);
		if (flag)//确定后退出while循环
		{
			break;
		}
	}
	//根据模式确定小蛇速度,值越小速度越快
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

//游戏控制
void Controller::gamePlayControl()
{
	startGame();//绘制窗体
	while(true)
	{
		selectMode();//选择难度
		drawMap();//绘制地图
		drawSocre();//绘制分数
		beginPlay();//开始游戏

	}
}

//开始游戏
void Controller::beginPlay()
{
	srand((unsigned)time(NULL));//设置开始方向和食物的随机值
	Snake *csnake = new Snake();
	Food *cfood = new Food();
	csnake->initSnake();//打印初始化蛇
	cfood->drawFood(*csnake);

	while (!csnake->hitSomething())
	{
		if (!csnake->changeDirection())//ESC暂停
		{
			this->pauseMenu();//暂停菜单
			
		}
		if (csnake->getFood(*cfood))//吃到食物
		{
			csnake->addSnake();//身子变长
			this->updateScore();//更新分数
			this->drawSocre();//绘制更新了的分数
			if (m_speed != 0)
				m_speed--;//速度加快
			cfood->drawFood(*csnake);//绘制新的食物
		}
		else//自动移动
		{
			csnake->moveSnake();
		}
		Sleep(m_speed);//speed越小速度越快
	}
	if (csnake->hitSomething())//如果撞到
	{
		this->gameOverMenu();//游戏结束菜单
	}

	delete csnake;
	delete cfood;
}

//更新分数
void Controller::updateScore()
{
	m_score += m_key;
}

//绘制分数
void Controller::drawSocre()
{
	this->Map::setCursorPosition(32, 15);
	this->Map::setColor(3);
	cout << "您的分数为：";
	this->Map::setCursorPosition(33, 17);
	cout << m_score;
}

//暂停菜单
void Controller::pauseMenu()
{
	//暂停菜单选项
	this->Map::setCursorPosition(32, 19);
	this->Map::setColor(3);
	this->Map::setBackColor();
	cout << "继续游戏";
	this->Map::setColor(3);
	this->Map::setCursorPosition(32, 21);
	cout << "重新开始";
	this->Map::setCursorPosition(32, 23);
	cout << "退出游戏";
	
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
					cout << "继续游戏";

					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "重新开始";

					key = 1;
					break;
				case 3:
					this->Map::setCursorPosition(32, 21);
					//this->Map::setColor(3);
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
		case 80://Down
			if (key < 3)
			{
				switch (key)
				{
				case 1:
					this->Map::setCursorPosition(32, 19);
					this->Map::setColor(3);
					cout << "继续游戏";
					//this->Map::setColor(3);
					this->Map::setCursorPosition(32, 21);
					this->Map::setBackColor();
					cout << "重新开始";

					key = 2;
					break;
				case 2:
					this->Map::setCursorPosition(32, 21);
					this->Map::setColor(3);
					cout << "重新开始";
					this->Map::setCursorPosition(32, 23);
					//this->Map::setColor(3);
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
		this->Map::setCursorPosition(0, 31);
		if(flag)
			break;

	}
	//继续游戏，清除掉暂停菜单的内容
	if (key == 1)
	{
		this->Map::setCursorPosition(32, 19);
		cout << "          ";
		this->Map::setCursorPosition(32, 21);
		cout << "          ";
		this->Map::setCursorPosition(32, 23);
		cout << "          ";
		Sleep(400);//延迟0.4s后开始
	}
	//重新开始
	if (key == 2)
	{
		this->gamePlayControl();
	}
	//退出
	if (key == 3)
	{
		exit(0);
	}
	
}

//游戏结束菜单
void Controller::gameOverMenu()
{
	Sleep(300);
	//绘制游戏结束菜单
	this->Map::setCursorPosition(8, 10);
	this->Map::setColor(7);
	cout << "Game Over !!! ";
	this->Map::setCursorPosition(8, 12);
	cout << "你的分数为： " << m_score;
	this->Map::setCursorPosition(8, 14);
	if(isRank())
	{
		cout << "恭喜您上榜！";
	}
	else
	{
		cout << "很遗憾，您未上榜";
	}
	this->Map::setCursorPosition(8, 16);
	cout << "是否再来一局？";
	this->Map::setCursorPosition(8, 18);
	this->Map::setBackColor();
	cout << "确定";
	this->Map::setCursorPosition(11, 18);
	this->Map::setColor(7);
	cout << "退出";

	this->showScoreRank();//显示分数

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
				cout << "确定";
				this->Map::setCursorPosition(11, 18);
				this->Map::setColor(7);
				cout << "退出";

				key = 1;
			}
			break;
		case 77://Right
			if (key == 1)
			{
				this->Map::setCursorPosition(8, 18);
				cout << "确定";
				this->Map::setCursorPosition(11, 18);
				this->Map::setBackColor();
				cout << "退出";

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
	//重新开始
	if (key == 1)
	{
		this->gamePlayControl();
	}
	//退出
	else if (key == 2)
	{
		exit(0);
	}



}

//分数储存  
void Controller::saveScore()
{
	ofstream ofs;
	ofs.open("score.txt", ios::out);
	if (!ofs.is_open())
	{
		return;
	}
	if(m_save_score.size() <= 5)//若小于5个则全部储存
	{
		for (vector<int>::iterator it = m_save_score.begin(); it != m_save_score.end(); it++)
		{
			ofs << *it << endl;
		}
	}
	else//否则只储存前面5个
	{
		for (int i = 0; i < 5; i++)
		{
			ofs << m_save_score[i];
		}
	}
	ofs.close();
}

//加载分数
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
	sort(m_save_score.begin(), m_save_score.end(),greater<int>());//排序
	ifs.close();
}

//展示分数排名
void Controller::showScoreRank()
{
	this->updateScoreRank();//刷新分数
	this->Map::setCursorPosition(17, 10);
	this->Map::setColor(7);
	cout << "分数排名：";
	int pos = 12;//分数显示位置
	for (int i = 0; i < m_save_score.size(); i++)
	{
		this->Map::setCursorPosition(17, pos);
		cout << "第" << i + 1 << "名";
		this->Map::setCursorPosition(21, pos);
		cout << m_save_score[i];
		pos += 2;
	}
}

//更新分数排名
void Controller::updateScoreRank()
{
	if (isRank() && !isSameRank())//上榜则更新分数
	{
		if(m_save_score.size() >= 5)
		{
			m_save_score.back() = m_score;//将最小的分数更新
		}
		else
		{
			m_save_score.push_back(m_score);//若不足5个分数则添加
		}
		this->saveScore();//储存到文件中
		sort(m_save_score.begin(), m_save_score.end(), greater<int>());//排序
	}
	
}

//判断是否上榜
bool Controller::isRank()
{
	if (int(m_save_score.size()) < 5)//若记录不足5个，则称为上榜
	{
		return true;
	}
	else if (m_score >= m_save_score.back())//若大于最后一个分数，也为上榜
	{
		return true;
	}
	return false;
}

//判读上榜分数是否重复，重复就不显示，但是为上榜，重复为true
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


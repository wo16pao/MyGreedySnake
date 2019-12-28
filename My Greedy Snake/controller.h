#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "map.h"
#include "food.h"
#include "snake.h"

class Controller : public Map , public Food , public Snake
{
public:

	Controller();

	void startGame();//游戏开始

	void drawMap();//绘制地图

	void selectMode();//选择模式

	void gamePlayControl();//游戏控制

	int beginPlay();//开始游戏

	void upDateScore();//更新分数

	void drawSocre();//绘制分数

	int pauseMenu();//暂停菜单

	void gameOverMenu();//游戏结束菜单


private:

	int m_key;//记录当前模式选择
	int m_score;//记录当前分数
	int m_speed;//记录速度

};

#endif //CONTROLLER_H

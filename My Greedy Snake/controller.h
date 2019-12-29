#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "map.h"
#include "food.h"
#include "snake.h"
#include <vector>

class Controller : public Map , public Food , public Snake
{
public:

	Controller();

	void startGame();//游戏开始

	void drawMap();//绘制地图

	void selectMode();//选择模式

	void gamePlayControl();//游戏控制

	void beginPlay();//开始游戏

	void updateScore();//更新分数

	void drawSocre();//绘制分数

	void pauseMenu();//暂停菜单

	void gameOverMenu();//游戏结束菜单

	void saveScore();//分数储存

	void loadScore();//分数读取

	void showScoreRank();//展示分数排名

	void updateScoreRank();//更新分数排名

	bool isRank();//判断是否上榜

	bool isSameRank();//判断是否分数有重复

private:

	int m_key;//记录当前模式选择
	int m_score;//记录当前分数
	int m_speed;//记录速度
	vector<int> m_save_score;//储存分数
};

#endif //CONTROLLER_H

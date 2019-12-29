#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "map.h"
#include "food.h"
#include "snake.h"

class Controller : public Map , public Food , public Snake
{
public:

	Controller();

	void startGame();//��Ϸ��ʼ

	void drawMap();//���Ƶ�ͼ

	void selectMode();//ѡ��ģʽ

	void gamePlayControl();//��Ϸ����

	void beginPlay();//��ʼ��Ϸ

	void upDateScore();//���·���

	void drawSocre();//���Ʒ���

	void pauseMenu();//��ͣ�˵�

	void gameOverMenu();//��Ϸ�����˵�

	void saveScore();

private:

	int m_key;//��¼��ǰģʽѡ��
	int m_score;//��¼��ǰ����
	int m_speed;//��¼�ٶ�

};

#endif //CONTROLLER_H

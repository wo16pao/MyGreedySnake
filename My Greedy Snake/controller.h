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

	void startGame();//��Ϸ��ʼ

	void drawMap();//���Ƶ�ͼ

	void selectMode();//ѡ��ģʽ

	void gamePlayControl();//��Ϸ����

	void beginPlay();//��ʼ��Ϸ

	void updateScore();//���·���

	void drawSocre();//���Ʒ���

	void pauseMenu();//��ͣ�˵�

	void gameOverMenu();//��Ϸ�����˵�

	void saveScore();//��������

	void loadScore();//������ȡ

	void showScoreRank();//չʾ��������

	void updateScoreRank();//���·�������

	bool isRank();//�ж��Ƿ��ϰ�

	bool isSameRank();//�ж��Ƿ�������ظ�

private:

	int m_key;//��¼��ǰģʽѡ��
	int m_score;//��¼��ǰ����
	int m_speed;//��¼�ٶ�
	vector<int> m_save_score;//�������
};

#endif //CONTROLLER_H

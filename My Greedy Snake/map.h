#ifndef MAP_H
#define MAP_H

#include "point.h"
#include <vector>
using namespace std;

class Map : public Point
{
public:

	Map();

	void printInitMap();//���Ƶ�ͼ

private:

	vector<Point> m_init_map;//��¼ǽ��λ��

};

#endif // MAP_H

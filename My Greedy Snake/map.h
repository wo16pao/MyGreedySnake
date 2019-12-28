#ifndef MAP_H
#define MAP_H

#include "point.h"
#include <vector>
using namespace std;

class Map : public Point
{
public:

	Map();

	void printInitMap();//绘制地图

private:

	vector<Point> m_init_map;//记录墙的位置

};

#endif // MAP_H

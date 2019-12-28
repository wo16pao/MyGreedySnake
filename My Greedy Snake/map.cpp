#include "map.h"
#include <windows.h>

//���캯������ǽ��λ����ӽ�ȥ
Map::Map()
{
	for (int i = 1; i <= 30; i++)
	{
		m_init_map.emplace_back(Point(i, 1));
	}
	for (int i = 2; i <= 30; i++)
	{
		m_init_map.emplace_back(Point(30, i));
	}
	for (int i = 29; i >= 1; i--)
	{
		m_init_map.emplace_back(Point(i, 30));
	}
	for (int i = 29; i >= 1; i--)
	{
		m_init_map.emplace_back(Point(1, i));
	}
}

//����ǽ
void Map::printInitMap()
{
	for (auto &point : m_init_map)
	{
		point.printRect();
		Sleep(10);
	}
}

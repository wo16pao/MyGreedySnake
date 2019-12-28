#include "point.h"
#include <iostream>
using namespace std;


Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Point::printRect()
{
	this->setCursorPosition(m_x, m_y);
	cout << "¡ö";
}

void Point::printCircle()
{
	this->setCursorPosition(m_x, m_y);
	cout << "¡ñ";
}

void Point::clearPrint()
{
	this->setCursorPosition(m_x, m_y);
	cout << "  ";
}

void Point::changePosition(const int x, const int y)
{
	this->m_x = x;
	this->m_y = y;
}

bool Point::operator==(const Point & point)
{
	return (point.m_x == this->m_x) && (point.m_y == this->m_y);
}

int Point::getX()
{
	return this->m_x;
}

int Point::getY()
{
	return this->m_y;
}

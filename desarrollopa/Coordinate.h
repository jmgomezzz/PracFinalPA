#pragma once
#include <iostream>
using namespace std;
class Coordinate
{
private:
	float x;
	float y;
public:
	Coordinate(float xArgument=0.0, float yArgument=0.0):x(xArgument),y(yArgument){}
	friend ostream& operator<<(ostream&, const Coordinate& coord);
};


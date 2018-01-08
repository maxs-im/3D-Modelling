#include "Pyramid(R_4).h"

Pyramid::Pyramid(const Figure input) : Figure(input){};
Pyramid::Pyramid(double _height, double _length): Figure(), height(_height), length(_length)
{
	point.push_back(Coordinates(0, 0, 0));
	point.push_back(Coordinates(0, 0, length));
	point.push_back(Coordinates(length, 0, length));
	point.push_back(Coordinates(length, 0, 0));
	s_point.push_back(Coordinates(length/2, height, length/2));
	centre = find_Centre();
};
Pyramid::~Pyramid(){};
const char* Pyramid::getname()
{
	return "Pyramid(R_4)";
};
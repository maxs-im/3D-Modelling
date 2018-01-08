#include "Coordinates.h"

Coordinates::Coordinates (double _x, double _y, double _z) :
	x(_x), y(_y), z(_z) {};

Coordinates::Coordinates (const Coordinates &input) :
	x(input.x), y(input.y), z(input.z){};

Coordinates Coordinates::operator+(const Coordinates& val)
{
	return Coordinates( this->x + val.x, this->y + val.y, this->z + val.z);
};
Coordinates Coordinates::operator-(const Coordinates& val)
{
	return Coordinates( this->x - val.x, this->y - val.y, this->z - val.z);
};
Coordinates Coordinates::operator* (double val)
{
	return Coordinates( val*this->x, val*this->y, val*this->z);
};
void Coordinates::operator() (double _x, double _y, double _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
};
bool operator== (const Coordinates& a, const Coordinates& b)
{
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
};

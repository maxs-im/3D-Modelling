#ifndef PYRAMID(R_4)_H_
#define PYRAMID(R_4)_H_

#include "Figure.h"

class Pyramid : public Figure
{
public: 
	double height;
	double length;

	Pyramid(double, double);
	Pyramid(const Figure);

	virtual const char* getname();

	virtual ~Pyramid();
};

#endif //PYRAMID(R_4)_H_
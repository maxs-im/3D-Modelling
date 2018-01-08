#ifndef PRISM_H_
#define PRISM_H_

#include "Figure.h"

#include <algorithm>
#include <cmath>

class Prism : public Figure
{
public:
	Coordinates alpha;

	Prism(std::vector<Coordinates>, Coordinates);
	Prism(const Figure);

	virtual const char* getname();

	virtual ~Prism();
};

#endif //PRISM_H_
#ifndef FIGURE_H_
#define FIGURE_H_

#include <vector>

#include "Coordinates.h"

class Figure
{
public:
	bool selected;
	double d_angle, 
			d_step, 
			d_zoom;
	Coordinates color;
	Coordinates centre;
	std::vector<Coordinates> point,
							s_point;
	std::vector< std::vector<Coordinates> > projections;

	Figure();

	Coordinates find_Centre();
	virtual const char* getname();

	virtual ~Figure();

};

extern std::vector<Figure*> figures_to_paint;

#endif //FIGURE_H_
#ifndef FIGURE_CHANGE_H_
#define FIGURE_CHANGE_H_

#include "Figure.h"

namespace Change
{
	static double eps(0.1),
			box_size(1500);
	void change_Angle(Figure*, 
							 short, short, short);
	void change_Coordinates(Figure*, 
								   short, short, short);
	void change_Zoom(Figure*, bool);
	bool check_coordinates(const std::vector<Coordinates>&, Coordinates);
	bool check_zoom(const Figure*, bool);
};

#endif //FIGURE_CHANGE_H_
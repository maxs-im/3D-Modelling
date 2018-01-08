#include "Figure.h"

std::vector<Figure*> figures_to_paint;

Figure::Figure() : selected(false), 
		color(Coordinates(1.0, 1.0, 1.0)), 
		d_angle(2.0), d_step(2.0), d_zoom(0.1){};
Coordinates Figure::find_Centre()
{
	Coordinates average(point[0]);
	for(auto it : point)
		average = (average + it)*0.5;
	for(auto it : s_point)
		average = (average + it)*0.5;

	return average;
};
Figure::~Figure(){};
const char* Figure::getname()
{
	return "Unknown";
};
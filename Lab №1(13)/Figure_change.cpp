#include "Figure_change.h"

void Change::change_Angle(Figure* figure, 
							 short d_x, short d_y, short d_z)
{
	double _cos = std::cos(figure->d_angle* std::atan(1.0)*4/180),
			_sin = std::sin(figure->d_angle* std::atan(1.0)*4/180);
	for(auto &it : figure->point)
	{
		it = it - figure->centre;
		Coordinates old(it);
		double cos_val,
				sin_val;
		if (d_x) {
			cos_val = _cos * abs(d_x);
			sin_val = _sin * d_x;
			it.y = old.y*cos_val + old.z*sin_val;
			it.z = -old.y*sin_val + old.z*cos_val;
		}
		if(d_y) {
			cos_val = _cos * abs(d_y);
			sin_val = _sin * d_y;
			it.x = old.x*cos_val + old.z*sin_val;
			it.z = -old.x*sin_val + old.z*cos_val;
		}
		if(d_z) {
			cos_val = _cos * abs(d_z);
			sin_val = _sin * d_z;
			it.x = old.x*cos_val - old.y*sin_val;
			it.y = old.x*sin_val + old.y*cos_val;
		}
		it = it + figure->centre;
	}
	for(auto &it : figure->s_point)
	{
		it = it - figure->centre;
		Coordinates old(it);
		double cos_val,
				sin_val;
		if (d_x) {
			cos_val = _cos * abs(d_x);
			sin_val = _sin * d_x;
			it.y = old.y*cos_val + old.z*sin_val;
			it.z = -old.y*sin_val + old.z*cos_val;
		}
		if(d_y) {
			cos_val = _cos * abs(d_y);
			sin_val = _sin * d_y;
			it.x = old.x*cos_val + old.z*sin_val;
			it.z = -old.x*sin_val + old.z*cos_val;
		}
		if(d_z) {
			cos_val = _cos * abs(d_z);
			sin_val = _sin * d_z;
			it.x = old.x*cos_val - old.y*sin_val;
			it.y = old.x*sin_val + old.y*cos_val;
		}
		it = it + figure->centre;
	}
	
	figure->centre = figure->find_Centre();
};
void Change::change_Coordinates(Figure* figure, 
								   short d_x, short d_y, short d_z)
{ 
	Coordinates delta = Coordinates( d_x, d_y, d_z )*figure->d_step;

	if(!check_coordinates(figure->point, delta) || !check_coordinates(figure->s_point, delta))
		return;

	for(auto &it : figure->point)
		it = it + delta;
	for(auto &it : figure->s_point)
		it = it + delta;

	figure->centre = figure->centre + delta;
};
void Change::change_Zoom(Figure* figure, bool sign)
{
	double zoom(1.0);
	zoom += (2*sign - 1)*figure->d_zoom;

	if(!check_zoom(figure, sign))
		return;

	for(auto &it : figure->point)
		it = (it - figure->centre)*zoom + figure->centre;
	for(auto &it : figure->s_point)
		it = (it - figure->centre)*zoom + figure->centre;
	
	figure->centre = figure->find_Centre();
};
bool Change::check_zoom(const Figure* figure, bool sign)
{
	double zoom(1.0);
	zoom += (2*sign - 1)*figure->d_zoom;

	for(auto it : figure->point) {
		if (sign) {
			Coordinates delta_max = (it - figure->point[0])*zoom + figure->point[0];
			delta_max.x = abs(delta_max.x); delta_max.y = abs(delta_max.y);  delta_max.z = abs(delta_max.z);

			if(delta_max.x > box_size/zoom-1 || 
				delta_max.y > box_size/zoom-1 ||
				delta_max.z > box_size/zoom-1)
				return false;
		}
		else {
			Coordinates delta_min = (it - figure->point[0])*figure->d_zoom;
			delta_min.x = abs(delta_min.x); delta_min.y = abs(delta_min.y);  delta_min.z = abs(delta_min.z); 

			if((delta_min.x > 0 && delta_min.x < eps) ||
				(delta_min.y > 0 && delta_min.y < eps) ||
				(delta_min.z > 0 && delta_min.z < eps))
				return false;
		}
	}
	
	for(auto it : figure->s_point) {
		if (sign) {
			Coordinates delta_max = (it - figure->point[0])*zoom + figure->point[0];
			delta_max.x = abs(delta_max.x); delta_max.y = abs(delta_max.y);  delta_max.z = abs(delta_max.z);

			if(delta_max.x > box_size/zoom-1 || 
				delta_max.y > box_size/zoom-1 ||
				delta_max.z > box_size/zoom-1)
				return false;
		}
		else {
			Coordinates delta_min = (it - figure->point[0])*figure->d_zoom;
			delta_min.x = abs(delta_min.x); delta_min.y = abs(delta_min.y);  delta_min.z = abs(delta_min.z); 

			if((delta_min.x > 0 && delta_min.x < eps) ||
				(delta_min.y > 0 && delta_min.y < eps) ||
				(delta_min.z > 0 && delta_min.z < eps))
				return false;
		}
	}

	return true;
};
bool Change::check_coordinates(const std::vector<Coordinates>& mass, Coordinates delta)
{
	for(auto it : mass) {
		Coordinates temp = it + delta;
		temp.x = abs(temp.x); temp.y = abs(temp.y); temp.z = abs(temp.z);

		if(temp.x > box_size || temp.y > box_size || temp.z > box_size)
			return false;
	}

	return true;
};
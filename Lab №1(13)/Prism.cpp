#include "Prism.h"

Prism::Prism(const Figure input) : Figure(input){};
Prism::Prism(std::vector<Coordinates> _point, Coordinates _alpha) : Figure(), alpha(_alpha)
{
	bool zero_val(false);
	int count = _point.size();
	for(int i(count-1); i >= 0; i--) {
		_point[i].y = 0;
		if(_point[i] == Coordinates(0, 0, 0)) {
			if(!zero_val)
				zero_val = true;
			_point.erase(_point.begin()+i);
			count--;
		}
	}

	std::sort(_point.begin(), _point.end(), [](Coordinates a, Coordinates b){
		return atan2(a.x, a.z) < atan2(b.x, b.z);
	} );
	
	if(zero_val) {
		_point.push_back(Coordinates(0, 0, 0));
		count++;
	}

	for(int i(count-1); i > 0; i--) {
		if(_point[i] == _point[i-1]) {
			_point.erase(_point.begin()+i);
			count--;
		}
	}

	point = _point;
	for (int i(0); i < count; i++) 
		s_point.push_back(Coordinates(point[i] + alpha));
	centre = find_Centre();
};
Prism::~Prism(){};
const char* Prism::getname()
{
	return "Prism";
};

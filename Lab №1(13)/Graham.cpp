#include "Graham.h"

#include <algorithm>

double Graham_shell::triangle_area(const Point &a, const Point &b, const Point &c) 
{
	return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y);
};
void Graham_shell::build_Graham_shell(std::vector<Point> &mas) {
	if (mas.size() == 1)  
		return;
	std::sort(mas.begin(), mas.end(), [](Point a, Point b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);		
	} );

	Point left = mas[0], 
			right = mas.back();

	std::vector<Point> up, down;
	up.push_back (left);
	down.push_back (left);

	size_t number = mas.size();
	for (size_t i = 1; i < number; ++i) {

		if (i == number-1 || (triangle_area(left, mas[i], right)) < 0) {
			while (up.size() >= 2 && (triangle_area(up[up.size()-2], up[up.size()-1], mas[i]) >= 0))
				up.pop_back();
			up.push_back (mas[i]);
		}
		if (i == mas.size() - 1 || (triangle_area(left, mas[i], right) > 0)) {
			while (down.size() >= 2 && (triangle_area(down[down.size()-2], down[down.size()-1], mas[i]) <= 0))
				down.pop_back();
			down.push_back (mas[i]);
		}
	}

	mas.clear();
	for (size_t i = 0; i < up.size(); ++i)
		mas.push_back (up[i]);
	for (size_t i = down.size()-2; i > 0; --i)
		mas.push_back (down[i]);
};
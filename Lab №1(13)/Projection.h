#ifndef PROJECTION_H_
#define PROJECTION_H_

#include <algorithm>
#include <cmath>

#include "Figure.h"
#include "Graham.h"

namespace Projection
{
	struct Pr_struct{
		bool _x;
		bool _y;
		bool _z;
		Pr_struct(bool i_x, bool i_y, bool i_z) :
			_x(i_x), _y(i_y), _z(i_z) {};
	};

	void make_shell(std::vector<Coordinates>&);
	void convert_Forward(std::vector<Coordinates>&, std::vector<Graham_shell::Point>&);
	void convert_Back(std::vector<Coordinates>&, const std::vector<Graham_shell::Point>&);

	static Pr_struct make(0, 0, 0);

	void make_Projection(Figure*, const Pr_struct&);

};

#endif //PROJECTION_H_
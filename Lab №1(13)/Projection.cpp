#include "Projection.h"

void Projection::make_Projection (Figure* figure, 
						const Pr_struct& input)
															
{
	make = input;
	
	std::vector<Coordinates> mass;
	for(auto it : figure->point)
		mass.push_back(it);
	for(auto it : figure->s_point)
		mass.push_back(it);

	make_shell(mass);
	
	figure->projections.push_back(mass);
};
void Projection::make_shell(std::vector<Coordinates>& mass)
{
	std::vector<Graham_shell::Point> new_mass;

	convert_Forward(mass, new_mass);
	Graham_shell::build_Graham_shell(new_mass);
	convert_Back(mass, new_mass);
};
void Projection::convert_Forward(std::vector<Coordinates>& mass, std::vector<Graham_shell::Point>& new_mass)
{
	for(auto &it : mass) {
		if(!make._x) it.x = 0;
		if(!make._y) it.y = 0;
		if(!make._z) it.z = 0;
		if(!make._x) {
			new_mass.push_back(Graham_shell::Point(it.y, it.z));
			continue;
		}
		if(!make._y) {
			new_mass.push_back(Graham_shell::Point(it.x, it.z));
			continue;
		}
		if(!make._z) {
			new_mass.push_back(Graham_shell::Point(it.x, it.y));
			continue;
		}
	}
};
void Projection::convert_Back(std::vector<Coordinates>& mass, const std::vector<Graham_shell::Point>& new_mas)
{
	mass.clear();
	if(!make._x) {
		for(auto it : new_mas)
			mass.push_back( Coordinates(0, it.x, it.y) );
		return;
	}
	if(!make._y) {
		for(auto it : new_mas)
			mass.push_back( Coordinates(it.x, 0, it.y) );
		return;
	}
	if(!make._z) {
		for(auto it : new_mas)
			mass.push_back( Coordinates(it.x, it.y, 0) );
		return;
	}

	for(size_t i = mass.size()-1; i > 0; i--)
		if(mass[i] == mass[i-1])
			mass.erase(mass.begin()+i);
};
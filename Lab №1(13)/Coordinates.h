#ifndef COORDINATES_H_
#define COORDINATES_H_

struct Coordinates
{
	double x;
	double y;
	double z;

	Coordinates (double _x = 0, double _y = 0, double _z = 0);
	Coordinates (const Coordinates &);

	Coordinates operator+ (const Coordinates&);
	Coordinates operator- (const Coordinates&);
	Coordinates operator* (double);

	friend bool operator== (const Coordinates&, const Coordinates&);
	//Coordinates& operator= (const Coordinates&);
	void operator() (double, double, double);
};

#endif //COORDINATES_H_
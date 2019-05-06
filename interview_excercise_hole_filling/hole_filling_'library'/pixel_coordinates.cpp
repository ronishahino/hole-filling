#include "stdafx.h"
#include "pixel_coordinates.h"
#include <math.h>


namespace hole_filling
{
	pixel_coordinates::pixel_coordinates()
	{
		_x = 0;
		_y = 0;
		
	}

	pixel_coordinates::pixel_coordinates(int x, int y)
	{
		_x = x;
		_y = y;
		
	}

	pixel_coordinates::~pixel_coordinates()
	{
	}

	float pixel_coordinates::norm()
	{
		return sqrt(pow(_x,2) + pow(_y,2));
	}
	pixel_coordinates& pixel_coordinates::operator +(const pixel_coordinates& other)
	{
		return pixel_coordinates(_x + other._x, _y + other._y);
	}
	pixel_coordinates& pixel_coordinates::operator -(const pixel_coordinates& other)
	{
		return pixel_coordinates(_x - other._x, _y - other._y);
	}
	bool pixel_coordinates::operator==(const pixel_coordinates& p) const
	{
		return (p._x == _x) && (p._y == _y);
	}


	

}
#include "stdafx.h"
#include "euclidian_distance.h"
#include <math.h>

namespace hole_filling
{

	euclidian_distance::euclidian_distance(float z, float eps)
	{
		_z = z;
		_eps = eps;
	}


	euclidian_distance::~euclidian_distance()
	{
	}

	float euclidian_distance::calculate_weight(pixel_coordinates p1, pixel_coordinates p2)
	{
		pixel_coordinates p = p1 - p2;
		float eucl_dist = p.norm();
		
		return 1 / (pow(eucl_dist, _z) + _eps);
	}
}
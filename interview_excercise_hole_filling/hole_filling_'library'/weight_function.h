#pragma once
#include "pixel_coordinates.h"
namespace hole_filling {


	class weight_function
	{
	public:
		weight_function() {};
		~weight_function() {};
		virtual float calculate_weight(pixel_coordinates p1, pixel_coordinates p2) = 0;

	};

}
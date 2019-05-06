#pragma once
#include "pixel_conecctivity.h"
#include "pixel_coordinates.h"
#include "weight_function.h"
#include "filled_image.h"
#include <math.h>
#include <vector>
using namespace std;

namespace hole_filling {

	class hole_filler
	{
	private:
		filled_image _filled_image;
		pixel_conecctivity _conectivity;
		weight_function* _Weight_func;
		
		float evaluate_by_pixels(pixel_coordinates hole_pixel, vector<pixel_coordinates> non_hole_pixels);
		void add_hole_neighbors_to_next_boundary_level(const pixel_coordinates& boundary_pixel, unordered_set<pixel_coordinates, my_hash>& next_boundary);
		
	public:

		hole_filler(vector<vector<float>> im, conectivity_type conec_type, float z, float eps); // defualt wighting function
		
		~hole_filler();
		
		std::vector<std::vector<float>> accurate_algorithm_hole_filling();
		std::vector<std::vector<float>> approximate_algorithm_hole_filling();

	};
	

}
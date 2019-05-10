#pragma once
#include "pixel_conecctivity.h"
#include "pixel_coordinates.h"
#include "weight_function.h"
#include "filled_image.h"
#include <math.h>
#include <vector>
using namespace std;

namespace hole_filling {

	/// This class implement the different algorithms of hole filling
	
	class hole_filler
	{
	private:
		filled_image _filled_image;
		pixel_conecctivity _conectivity;
		weight_function* _Weight_func;
		
		float evaluate_by_pixels(pixel_coordinates hole_pixel, vector<pixel_coordinates> non_hole_pixels);
		void add_hole_neighbors_to_next_boundary_level(const pixel_coordinates& boundary_pixel, unordered_set<pixel_coordinates, my_hash>& next_boundary);
		
	public:
		// constructor for defualt wighting function
		hole_filler(vector<vector<float>> im, conectivity_type conec_type, float z, float eps); 
		// constructor for arbitrary wighting function. 
		hole_filler(vector<vector<float>> im, conectivity_type conec_type, weight_function* w_func);
		~hole_filler();
		

		// for every hole pixel -> estimate value by all boundery pixels
		std::vector<std::vector<float>> accurate_algorithm_hole_filling();


		// Approximate algorithm:
		//  1.	Go over the boundary pixels. And find the hole pixels that connect (neighbor) to them.
		//		Those hole pixels filled only by their neighbors(the boundary) 
		//      and added to the boundery of the next iteration .
		//	2. Now the hole is shrinking. And we update the new boundary - (all the pixels we just filled).
		//	We will repeat this process(1 + 2) until the entire hole is filled.
		std::vector<std::vector<float>> approximate_algorithm_hole_filling();

	};
	

}
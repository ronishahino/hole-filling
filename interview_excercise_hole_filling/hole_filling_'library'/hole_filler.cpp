#include "stdafx.h"
#include "hole_filler.h"

#include "euclidian_distance.h"
#include <iostream>
#include <stack>
#include <unordered_set>
using namespace std;

namespace hole_filling
{

	// constructor for defualt wighting function
	hole_filler::hole_filler(vector<vector<float>> im, conectivity_type conec_type, float z, float eps) 
	{
		_Weight_func = new euclidian_distance(z,eps);
		int N = im.size();
		int M = im[0].size();
		_conectivity.set_parameters(N, M, conec_type);

		_filled_image.initialize_parameters(im, _conectivity);
	}

	// constructor for arbitrary wighting function. 
	hole_filler::hole_filler(vector<vector<float>> im, conectivity_type conec_type, weight_function* w_func)
	{
		_Weight_func = w_func;
		int N = im.size();
		int M = im[0].size();
		_conectivity.set_parameters(N, M, conec_type);

		_filled_image.initialize_parameters(im, _conectivity);
	}
	
	hole_filler::~hole_filler()
	{
		
		if (_Weight_func != NULL)
		{
			delete _Weight_func;
			_Weight_func = NULL;
		}
			
	}

	// gets an pixel in the hole and set of other pixel .
	// -> estimate value to the hole pixel by weighted average.
	float hole_filler::evaluate_by_pixels(pixel_coordinates hole_pixel, vector<pixel_coordinates> non_hole_pixels)
	{
		float total_weights = 0;
		float weighted_sum = 0;

		for (auto p : non_hole_pixels)
		{
			if (_filled_image.is_hole(p)) continue;
			float w = _Weight_func->calculate_weight(p, hole_pixel);
			float val = _filled_image.value_at_pixel(p);
			weighted_sum += w * val;
			total_weights += w;

		}
		weighted_sum /= total_weights;

		return weighted_sum;
	}

	std::vector<std::vector<float>> hole_filler::accurate_algorithm_hole_filling()
	{
		_filled_image.reset_filled_image();

		for (auto hole_pixel : _filled_image.get_hole())
		{
			float val = evaluate_by_pixels(hole_pixel, _filled_image.get_boundary());
			_filled_image.set_value_at_pixel(hole_pixel, val);
		}

		return _filled_image.get_image();
	}

	std::vector<std::vector<float>> hole_filler::approximate_algorithm_hole_filling()
	{
		_filled_image.reset_filled_image();

		unordered_set<pixel_coordinates, my_hash> current_boundary(_filled_image.get_boundary().begin(), _filled_image.get_boundary().end());

		while (!current_boundary.empty())//if boundary is empty - there is no hole anymore.
		{
			unordered_set<pixel_coordinates, my_hash> next_boundary;			
			for (auto &boundary_pixel : current_boundary)
				add_hole_neighbors_to_next_boundary_level(boundary_pixel, next_boundary);
			
			current_boundary = std::move(next_boundary);
		}
		return _filled_image.get_image();
	}

	// Fill all hole pixels, neighbor to the boundery pixel. (by its neighbors)
	// and add them to the boundery of the next iteration
	void hole_filler::add_hole_neighbors_to_next_boundary_level(const pixel_coordinates& boundary_pixel, unordered_set<pixel_coordinates, my_hash>& next_boundary)
	{
		vector<pixel_coordinates> neighbors = _conectivity.get_all_neighbors(boundary_pixel);
		for (auto &neighbor_pixel : neighbors)
		{
			if (_filled_image.is_hole(neighbor_pixel))
			{
				// evaluate only by its adjucent neighbors
				float value = evaluate_by_pixels(neighbor_pixel, _conectivity.get_all_neighbors(neighbor_pixel));
				_filled_image.set_value_at_pixel(neighbor_pixel, value);
				next_boundary.insert(neighbor_pixel);
			}
		}
	}



}
#include "stdafx.h"
#include "filled_image.h"

namespace hole_filling
{

	filled_image::filled_image()
	{
		
	}

	filled_image::~filled_image()
	{
	}

	void filled_image::reset_filled_image()
	{
		_image = _original_image;
	}

	void filled_image::initialize_parameters(std::vector<std::vector<float>> image, pixel_conecctivity pixel_conect)
	{
		_original_image = image;
		_image = image;
		_conectivity = pixel_conect;
		_N = image.size();
		_M = image[0].size();

		fing_hole_and_boudary_pixels();
	}

	void filled_image::fing_hole_and_boudary_pixels()
	{
		for (int i = 0; i < _N; i++)
		{
			for (int j = 0; j < _M; j++)
			{
				pixel_coordinates current_p(i, j);

				if (is_hole(current_p))
					_hole.push_back(current_p);
				else if (is_boundary(current_p))
					_boundary.push_back(current_p);

			}
		}


	}
	
	float filled_image::value_at_pixel(pixel_coordinates p)
	{
		return _image[p.get_x()][p.get_y()];
	}

	void filled_image::set_value_at_pixel(pixel_coordinates p, float val)
	{
		_image[p.get_x()][p.get_y()] = val;
	}

	bool filled_image::is_hole(pixel_coordinates p)
	{
		return value_at_pixel(p) == -1;
	}

	bool filled_image::is_boundary(pixel_coordinates p)
	{
		//if p is not a hole pixel and has a hole neighbor.
		if (is_hole(p)) return false;
		for (auto p : _conectivity.get_all_neighbors(p))
		{
			if (is_hole(p))
				return true;
		}
		return false;
	}

	std::vector<pixel_coordinates>& filled_image::get_hole() { return _hole; }
	std::vector<pixel_coordinates>& filled_image::get_boundary() { return _boundary; }
	std::vector<std::vector<float>>& filled_image::get_image() { return _image; }

}
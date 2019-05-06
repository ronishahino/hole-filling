#pragma once
#include <vector>
#include "pixel_coordinates.h"
#include "pixel_conecctivity.h"

using namespace std;
namespace hole_filling 
{

	class filled_image
	{
		std::vector<std::vector<float>> _image; 
		std::vector<std::vector<float>> _original_image; // for reset filled image

		int _N;
		int _M;

		vector<pixel_coordinates> _hole;
		vector<pixel_coordinates> _boundary;

		pixel_conecctivity _conectivity;

	public:
		


		filled_image();
		~filled_image();

		void initialize_parameters(std::vector<std::vector<float>> image, pixel_conecctivity pixel_conect);
		void reset_filled_image();

		void fing_hole_and_boudary_pixels();

		bool is_hole(pixel_coordinates p);
		bool is_boundary(pixel_coordinates p);
		float value_at_pixel(pixel_coordinates p);
		void set_value_at_pixel(pixel_coordinates p, float val);

		std::vector<pixel_coordinates>& get_hole();
		std::vector<pixel_coordinates>& get_boundary();
		std::vector<std::vector<float>>& get_image();
	};


}

#pragma once
#include "pixel_coordinates.h"
#include <vector>

using namespace std;
namespace hole_filling
{
	enum conectivity_type
	{
		connected_4, connected_8
	};

	/// This class handle the conecctivity between pixels. with the different conectivity type.
	/// With input pixels its return all its neighbors.

	class pixel_conecctivity
	{
		int _N;// bounds
		int _M;
		conectivity_type _type;

	public:
		
		pixel_conecctivity();
		~pixel_conecctivity();
		
		void set_parameters(int N, int M, conectivity_type type);
		vector<pixel_coordinates> get_all_neighbors(pixel_coordinates p);
		
		bool in_bounds(pixel_coordinates p);

		
	};

}
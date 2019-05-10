#include "stdafx.h"
#include "pixel_conecctivity.h"
#include <math.h>

using namespace std;

namespace hole_filling
{

	pixel_conecctivity::pixel_conecctivity() {}

	pixel_conecctivity::~pixel_conecctivity()
	{

	}

	void pixel_conecctivity::set_parameters(int N, int M, conectivity_type type) 
	{
		_N = N;
		_M = M;
		_type = type;
	}

	vector<pixel_coordinates> pixel_conecctivity::get_all_neighbors(pixel_coordinates p)
	{
		vector<pixel_coordinates> neighbors;

		switch (_type)
		{
		case connected_4:
		{
			neighbors.push_back(pixel_coordinates (p.get_x(), p.get_y() + 1));
			neighbors.push_back(pixel_coordinates (p.get_x() + 1, p.get_y()));
			neighbors.push_back(pixel_coordinates (p.get_x(), p.get_y() - 1));
			neighbors.push_back(pixel_coordinates (p.get_x() - 1, p.get_y()));
			break;
		}
		case connected_8:
		{
			neighbors.push_back(pixel_coordinates (p.get_x(), p.get_y() + 1));
			neighbors.push_back(pixel_coordinates (p.get_x() + 1, p.get_y() + 1));
			neighbors.push_back(pixel_coordinates (p.get_x() + 1, p.get_y()));
			neighbors.push_back(pixel_coordinates (p.get_x() + 1, p.get_y() - 1));
			neighbors.push_back(pixel_coordinates (p.get_x(), p.get_y() - 1));
			neighbors.push_back(pixel_coordinates (p.get_x() - 1, p.get_y() - 1));
			neighbors.push_back(pixel_coordinates (p.get_x() - 1, p.get_y()));
			neighbors.push_back(pixel_coordinates (p.get_x() - 1, p.get_y() + 1));
			break;
		}
		default:
		{
			throw exception("conectivity type is only connected_4 or connected_8");
		}
		}
		
		//erase neighbors out of bounds
		for (int i = neighbors.size() - 1; i>=0;i--)
		{
			if (!in_bounds(neighbors[i]))
				neighbors.erase(neighbors.begin() + i);
		}

		return neighbors;
	}

	bool pixel_conecctivity::in_bounds(pixel_coordinates p)
	{
		if (p.get_x() >= 0 && p.get_x() < _N &&
			p.get_y() >= 0 && p.get_y() < _M)
			return true;
		return false;
	}

}
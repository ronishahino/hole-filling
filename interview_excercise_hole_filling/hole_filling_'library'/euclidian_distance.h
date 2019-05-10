
#include "weight_function.h"

namespace hole_filling
{

	/// Implement the interface weight_function:
	/// As Euclidian distance weight between coordinates pixels pair.

	class euclidian_distance :
		public weight_function
	{
		float _z;
		float _eps;

	public:
		euclidian_distance(float z, float eps);
		~euclidian_distance();
		float calculate_weight(pixel_coordinates p1, pixel_coordinates p2);
	};
}
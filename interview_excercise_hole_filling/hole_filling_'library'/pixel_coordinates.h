#pragma once
#include <unordered_set>

namespace hole_filling
{

	/// pixel_coordinates represent an pixel coordinates in image.
	/// struct my_hash immplement an hash function for pixel_coordinates hashing.

	class pixel_coordinates
	{
	private:
		
		int _x;
		int _y;
	public:
		pixel_coordinates();
		pixel_coordinates(int x, int y);
		~pixel_coordinates();
		int get_x() const { return _x; }
		int get_y() const { return _y; }

		float norm();
		pixel_coordinates& operator +(const pixel_coordinates& other);
		pixel_coordinates& operator -(const pixel_coordinates& other);

		bool operator==(const pixel_coordinates& p) const;
		
	};

	struct my_hash {
		size_t operator()( const pixel_coordinates& p) const
		{
			return (std::hash<int>()(p.get_x()) ^ std::hash<int>()(p.get_y()));
		}
	};

}
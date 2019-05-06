#pragma once

#include<opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;

class image_file_conversion
{
public:
	image_file_conversion();
	~image_file_conversion();

	cv::Mat read_image_file(std::string path, bool is_color = true);
	vector<vector<float>> image_and_mask_files_to_grayScale_hole_format(std::string img_file, std::string mask_file);
	cv::Mat grayScale_hole_format_to_image(vector<vector<float>> g_image, string name);
};

 
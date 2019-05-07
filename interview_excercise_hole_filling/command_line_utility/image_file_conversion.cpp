#include "stdafx.h"
#include "image_file_conversion.h"

using namespace std;
using namespace cv;


image_file_conversion::image_file_conversion()
{
}


image_file_conversion::~image_file_conversion()
{
}

Mat image_file_conversion::read_image_file(std::string path, bool is_color)
{
	Mat img;

	if (is_color)
		img = imread(path, cv::IMREAD_GRAYSCALE);
	else
		img = imread(path, cv::IMREAD_COLOR);

	if (!img.data)// Check for invalid input
	{
		cout << endl << "Could not open or find the image" << std::endl;
		return Mat();
	}

	return img;
}

Mat image_file_conversion::grayScale_hole_format_to_image(vector<vector<float>> g_image, string name)
{
	cv::Size s;
	s.height = g_image[0].size();
	s.width = g_image.size();

	Mat img(s, CV_8UC1);

	for (int i = 0; i < g_image.size(); i++)
	{
		for (int j = 0; j < g_image[0].size(); j++)
		{
			img.at<uchar>(j, i) = (int)(g_image[i][j] * 255);
		}
	}
	 
	imwrite(name, img);
	return img;


}

vector<vector<float>> image_file_conversion::image_and_mask_files_to_grayScale_hole_format(std::string img_file, std::string mask_file)
{
	//todo both read as RGB images

	Mat img = read_image_file(img_file);
	Mat mask = read_image_file(mask_file);

	if (img.cols != mask.cols || img.rows != mask.rows)
	{
		cout << endl << "image and mask size isn't match" << endl;
		return vector<vector<float>>();
	}

	int n = img.cols;
	int m = img.rows;
	vector<vector<float>> G_format_img; 
	G_format_img.resize(n, vector<float>(m));


	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			if ((int)mask.at<uchar>(j, i) > 200)
			{
				G_format_img[i][j] = -1;
				//img.at<uchar>(j, i) = 0; // to remove - for temporary visualization
			}
			else
			{
				G_format_img[i][j] = (float)((float)img.at<uchar>(j, i) / 255);
				
			}
		}
	}

	

	return G_format_img;
}

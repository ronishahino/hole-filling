// interview_excercise_hole_filling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "image_file_conversion.h"
#include "hole_filler.h"
#include <fstream>
#include <iostream>    
#include <stdio.h>



using namespace std;

bool is_file_exist(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}



bool validate_input_parameters(int argc, char *argv[], string &image_path, string &mask_path, float &z, float &eps, hole_filling::conectivity_type &conec_type)
{

	if (argc != 6)
	{
		cout << endl;
		cout << "expect to get 5 parameters as input: " << endl;
		cout << " image file name" << endl;
		cout << " mask file name" << endl;
		cout << " z (weight function parameter)" << endl;
		cout << " epsilon (weight function parameter)" << endl;
		cout << " conectivity type - 4 or 8" << endl;
		return 0;
	}


	image_path = argv[1];
	mask_path = argv[2];
	if (!is_file_exist(image_path))
	{
		cout << endl << "invalid first input: image file doesn't exist" << endl;
		return 0;
	}
	if (!is_file_exist(mask_path))
	{
		cout << endl << "invalid second input: mask file doesn't exist" << endl;
		return 0;
	}
	z = atof(argv[3]);
	eps = atof(argv[4]);
	if (atoi(argv[5]) == 4) conec_type = hole_filling::connected_4;
	else if (atoi(argv[5]) == 8) conec_type = hole_filling::connected_8;
	else
	{
		cout << endl << "invalid fifth input: expect to get only 4 or 8 as conectivuty type!" << endl;
		return 0;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	string image_path, mask_path;
	float z, eps;
	hole_filling::conectivity_type conec_type;

	if (!validate_input_parameters(argc, argv, image_path, mask_path, z, eps, conec_type))
		return -1;
	
	image_file_conversion IFC;
	vector<vector<float>> grayscale_hole_image = IFC.image_and_mask_files_to_grayScale_hole_format(image_path, mask_path);
	

	hole_filling::hole_filler GHF(grayscale_hole_image, conec_type ,z, eps);
	vector<vector<float>> fixed_image_grayscale = GHF.accurate_algorithm_hole_filling();
	string output_path = "output_accurate.jpg";
	IFC.grayScale_hole_format_to_image(fixed_image_grayscale, output_path);
	
	fixed_image_grayscale = GHF.approximate_algorithm_hole_filling();
	output_path = "output_approximate.jpg";
	IFC.grayScale_hole_format_to_image(fixed_image_grayscale, output_path);

	cout << endl << endl;
	cout << "Operation completed successfully" << endl;
	cout << "The output files (for accurate and approximate algorithms) saved to : " << endl;
	cout << "The same folder from which the command line was operated" << endl;
	cout << "Bye Bye!!" << endl << endl;

	return 0;
}


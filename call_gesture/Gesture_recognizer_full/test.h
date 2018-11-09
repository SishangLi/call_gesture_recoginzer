#pragma once
#include "iostream"

#include <dlib/image_processing.h>
#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/data_io.h>

using namespace dlib;
using namespace std;


void guster_test(
	const std::string _faces_directory,
	const std::string _modles_directory,
	string **models_name,
	const int _model_num = 1
	
);
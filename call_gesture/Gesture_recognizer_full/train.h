#pragma once
#include "iostream"

#include <dlib/image_processing.h>
#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/data_io.h>

using namespace dlib;
using namespace std;

// ÑµÁ·º¯Êý
void guster_train(
	const std::string _faces_directory,
	const std::string _file_name,
	int _scanner_wide = 80,
	int _scanner_high = 80,
	int _machine_core_num = 4,
	bool _verbose = TRUE,
	int _SVM_C = 3,
	double _loss_eps = 0.01
);

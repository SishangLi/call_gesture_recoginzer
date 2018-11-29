#pragma once
#include "train.h"
#include "test.h"
#include "iostream"

#include <dlib/image_processing.h>
#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/data_io.h>

#include <fstream>

using namespace std;
using namespace dlib;

//int main()
int main(int argc, char** argv)
{
	//接收训练集合测试集路径。
	if (argc < 3 )
	{
		//cout << "Give the path to the examples/faces directory as the argument to this" << endl;
		//cout << "program.  For example, if you are in the examples folder then execute " << endl;
		//cout << "this program by running: " << endl;
		//cout << "./fhog_object_detector_ex faces" << endl;
		cout << "传入参数：" << endl;
		cout << "训练模式依次为：模式，数据集路径，模型文件文件名" << endl;
		cout << "如：train ../samples face_detect.svm" << endl;
		cout << "测试模式依次为：模式，测试集路径，模型路径，联合使用的模型数量，文件名" << endl;
		cout << "如：train ../samples 2 face_detect_1.svm face_detect_2.svm" << endl;
		cout << endl;
		//system("pause");
		//return 0;
	}

	//判断模式，第一个参数
	const std::string mode = argv[1];
	//传入训练集路径，并调用训练函数，开始训练
	/*void guster_train(
		const std::string _faces_directory,
		int _scanner_wide = 80,
		int _scanner_high = 80,
		int _machine_core_num = 4,
		bool _verbose = TRUE,
		int _SVM_C = 3,
		double _loss_eps = 0.01
	)*/

	if (mode == "train")
	{
		//存储训练集和测试集路径
		//const std::string faces_directory = "F:\WorkStation\call_gesture\samples_left_two_classifier";
		const std::string faces_directory = argv[2];

		//模型文件名
		const std::string modle_name = argv[3];

		int scanner_wide = 80;
		int scanner_high = 80;
		int machine_core_num = 8;
		bool verbose = TRUE;
		int SVM_C = 6;
		double loss_eps = 0.005;

		cout << "已调用训练函数！" << endl;
		guster_train(faces_directory, modle_name, scanner_wide, scanner_high, machine_core_num, verbose, SVM_C, loss_eps);
	}

	if (mode == "test")
	{
		// 存储训练集和测试集路径
		// const std::string faces_directory = "F:\WorkStation\call_gesture\samples_left_two_classifier";
		const std::string faces_directory = argv[2];

		// 存储模型文件路径
		const std::string modles_directory = argv[3];

		// 提取模型个数  传入类型为字符型，与整型相差
		const int model_num = *(argv[4]) - 48;
		cout << "模型个数：" << model_num << endl;
		string *models_name = new string[model_num];
		// 存储模型文件名
		for (int i = 0; i < model_num; i++)
		{
			models_name[i] = argv[5 + i];
			cout << models_name[i] << endl;
		}
		cout << "已调用测试函数！" << endl;
		guster_test(faces_directory, modles_directory, models_name, model_num);
	}

}
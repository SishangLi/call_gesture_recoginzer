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
	//����ѵ�����ϲ��Լ�·����
	if (argc < 3 )
	{
		//cout << "Give the path to the examples/faces directory as the argument to this" << endl;
		//cout << "program.  For example, if you are in the examples folder then execute " << endl;
		//cout << "this program by running: " << endl;
		//cout << "./fhog_object_detector_ex faces" << endl;
		cout << "���������" << endl;
		cout << "ѵ��ģʽ����Ϊ��ģʽ�����ݼ�·����ģ���ļ��ļ���" << endl;
		cout << "�磺train ../samples face_detect.svm" << endl;
		cout << "����ģʽ����Ϊ��ģʽ�����Լ�·����ģ��·��������ʹ�õ�ģ���������ļ���" << endl;
		cout << "�磺train ../samples 2 face_detect_1.svm face_detect_2.svm" << endl;
		cout << endl;
		//system("pause");
		//return 0;
	}

	//�ж�ģʽ����һ������
	const std::string mode = argv[1];
	//����ѵ����·����������ѵ����������ʼѵ��
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
		//�洢ѵ�����Ͳ��Լ�·��
		//const std::string faces_directory = "F:\WorkStation\call_gesture\samples_left_two_classifier";
		const std::string faces_directory = argv[2];

		//ģ���ļ���
		const std::string modle_name = argv[3];

		int scanner_wide = 80;
		int scanner_high = 80;
		int machine_core_num = 8;
		bool verbose = TRUE;
		int SVM_C = 6;
		double loss_eps = 0.005;

		cout << "�ѵ���ѵ��������" << endl;
		guster_train(faces_directory, modle_name, scanner_wide, scanner_high, machine_core_num, verbose, SVM_C, loss_eps);
	}

	if (mode == "test")
	{
		// �洢ѵ�����Ͳ��Լ�·��
		// const std::string faces_directory = "F:\WorkStation\call_gesture\samples_left_two_classifier";
		const std::string faces_directory = argv[2];

		// �洢ģ���ļ�·��
		const std::string modles_directory = argv[3];

		// ��ȡģ�͸���  ��������Ϊ�ַ��ͣ����������
		const int model_num = *(argv[4]) - 48;
		cout << "ģ�͸�����" << model_num << endl;
		string *models_name = new string[model_num];
		// �洢ģ���ļ���
		for (int i = 0; i < model_num; i++)
		{
			models_name[i] = argv[5 + i];
			cout << models_name[i] << endl;
		}
		cout << "�ѵ��ò��Ժ�����" << endl;
		guster_test(faces_directory, modles_directory, models_name, model_num);
	}

}
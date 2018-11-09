#include "test.h"
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
	const int _model_num
	)
{
	//װ�ڲ��Լ���ѵ����
	dlib::array<array2d<unsigned char> > images_train, images_test;
	std::vector<std::vector<rectangle> > face_boxes_train, face_boxes_test;

	//��Ҫ��ѵ������������������������䣬��ָ����ȷ��xml�ļ�������������ѵ�����ϲ��Խ����������ȡ��ע��
	//load_image_dataset(images_train, face_boxes_train, _faces_directory + "/training.xml");
	load_image_dataset(images_test, face_boxes_test, _faces_directory + "/testing.xml");

	//������������
	typedef scan_fhog_pyramid<pyramid_down <12> > image_scanner_type;

	//װ��ѵ���õ�ģ��
	std::vector<object_detector<image_scanner_type>> detectors;
	for (int i = 0; i < _model_num; i++)
	{
		object_detector<image_scanner_type> detector_temp;
		deserialize(_modles_directory +  "/" + *models_name[i]) >> detector_temp;
		detectors.push_back(detector_temp);
	}

	//��ӡ���ȺͿ��ӻ�����ͼֻ���ڵ���svmģ����ʹ��

	//��ӡ��ѵ�����ϵĲ��Խ�����ֱ�Ϊprecision, recall, and then average precision.
	//cout << "training results: " << test_object_detection_function(detector, images_train, face_boxes_train) << endl;

	//��ӡ�ڲ��Լ��ϵĲ��Խ�����ֱ�Ϊprecision, recall, and then average precision.
	//cout << "testing results:  " << test_object_detection_function(detectors, images_test, face_boxes_test) << endl;

	//���ӻ�����ͼ
	//image_window hogwin(draw_fhog(detector), "Learned fHOG detector");

	//// ��ѵ��������Ԥ��
	//image_window win1;
	//for (unsigned long i = 0; i < images_train.size(); i++)
	//{
	//	// Run the detector and get the face detections.
	//	std::vector<rectangle> dets = detector(images_train[i]);
	//	win1.clear_overlay();
	//	win1.set_image(images_train[i]);
	//	win1.add_overlay(dets, rgb_pixel(255, 0, 0));
	//	cout << "Hit enter to process the next image..." << endl;
	//	cin.get();
	//}

	// �ڲ��Լ�����Ԥ��
	image_window win2;
	for (unsigned long i = 0; i < images_test.size(); ++i)
	{
		// Run the detector and get the face detections.
		std::vector<rectangle> dets = evaluate_detectors(detectors, images_test[i],0.1);
		//std::vector<rectangle> dets = detectors(images_test[i]);
		win2.clear_overlay();
		win2.set_image(images_test[i]);
		if (dets.size()>1)
		{
			win2.add_overlay(dets[0], rgb_pixel(255, 0, 0));
		}
		else
		{
			win2.add_overlay(dets, rgb_pixel(255, 0, 0));
		}
		// win2.add_overlay(dets, rgb_pixel(255, 0, 0));
		cout << "Hit enter to process the next image..." << endl;
		cin.get();
	}
}
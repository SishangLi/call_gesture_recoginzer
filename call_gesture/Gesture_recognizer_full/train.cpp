#include "train.h"
#include "iostream"

#include <dlib/image_processing.h>
#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/data_io.h>

using namespace dlib;
using namespace std;

void guster_train(
	const std::string _faces_directory,
	const std::string _file_name,
	int _scanner_wide,
	int _scanner_high,
	int _machine_core_num,
	bool _verbose,
	int _SVM_C,
	double _loss_eps
)
{
	try
	{
		//装载测试集和训练集
		dlib::array<array2d<unsigned char> > images_train, images_test;
		std::vector<std::vector<rectangle> > face_boxes_train, face_boxes_test;
		load_image_dataset(images_train, face_boxes_train, _faces_directory + "/training.xml");
		load_image_dataset(images_test, face_boxes_test, _faces_directory + "/testing.xml");

		// 图片上采样
		// upsample_image_dataset<pyramid_down<2> >(images_train, face_boxes_train);
		// upsample_image_dataset<pyramid_down<2> >(images_test,  face_boxes_test);

		//若是人脸检测可以使用如下语句，镜像处理图像，来数据增强
		// add_image_left_right_flips(images_train, face_boxes_train);

		//金字塔处理级数
		typedef scan_fhog_pyramid<pyramid_down < 12 > > image_scanner_type;

		// 定义一个扫面器
		image_scanner_type scanner;

		// 设置扫描器窗口大小
		scanner.set_detection_window_size(_scanner_wide, _scanner_high);

		// 定义一个训练器
		structural_object_detection_trainer<image_scanner_type> trainer(scanner);

		// 设置处理器核心
		trainer.set_num_threads(_machine_core_num);

		// 打印训练详情
		if (_verbose) trainer.be_verbose();

		// 设置训练集拟合率，增大这个数字可能会过拟合
		trainer.set_c(_SVM_C);

		// 停止迭代时的loss值，越小训练时间越长
		trainer.set_epsilon(_loss_eps);

		// 目标框不规范时要加上，能不加尽量不加，会有数据损失。
		remove_unobtainable_rectangles(trainer, images_train, face_boxes_train);

		// 正则化
		// scanner.set_nuclear_norm_regularization_strength(1.0);

		cout << "开始训练" << endl;
		object_detector<image_scanner_type> detector = trainer.train(images_train, face_boxes_train);

		cout << "存储模型中..." << endl;
		//存储训练好的模型
		serialize(_file_name) << detector;
		cout << "存储完成！" << endl;
	}
	catch (exception & e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
}

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
		//װ�ز��Լ���ѵ����
		dlib::array<array2d<unsigned char> > images_train, images_test;
		std::vector<std::vector<rectangle> > face_boxes_train, face_boxes_test;
		load_image_dataset(images_train, face_boxes_train, _faces_directory + "/training.xml");
		load_image_dataset(images_test, face_boxes_test, _faces_directory + "/testing.xml");

		// ͼƬ�ϲ���
		// upsample_image_dataset<pyramid_down<2> >(images_train, face_boxes_train);
		// upsample_image_dataset<pyramid_down<2> >(images_test,  face_boxes_test);

		//��������������ʹ��������䣬������ͼ����������ǿ
		// add_image_left_right_flips(images_train, face_boxes_train);

		//������������
		typedef scan_fhog_pyramid<pyramid_down < 12 > > image_scanner_type;

		// ����һ��ɨ����
		image_scanner_type scanner;

		// ����ɨ�������ڴ�С
		scanner.set_detection_window_size(_scanner_wide, _scanner_high);

		// ����һ��ѵ����
		structural_object_detection_trainer<image_scanner_type> trainer(scanner);

		// ���ô���������
		trainer.set_num_threads(_machine_core_num);

		// ��ӡѵ������
		if (_verbose) trainer.be_verbose();

		// ����ѵ��������ʣ�����������ֿ��ܻ�����
		trainer.set_c(_SVM_C);

		// ֹͣ����ʱ��lossֵ��ԽСѵ��ʱ��Խ��
		trainer.set_epsilon(_loss_eps);

		// Ŀ��򲻹淶ʱҪ���ϣ��ܲ��Ӿ������ӣ�����������ʧ��
		remove_unobtainable_rectangles(trainer, images_train, face_boxes_train);

		// ����
		// scanner.set_nuclear_norm_regularization_strength(1.0);

		cout << "��ʼѵ��" << endl;
		object_detector<image_scanner_type> detector = trainer.train(images_train, face_boxes_train);

		cout << "�洢ģ����..." << endl;
		//�洢ѵ���õ�ģ��
		serialize(_file_name) << detector;
		cout << "�洢��ɣ�" << endl;
	}
	catch (exception & e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
}

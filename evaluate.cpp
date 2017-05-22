//#include "opencv2/core/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <fstream>
//#include <time.h>
//#define board_row 12
//#define board_col 11
//#define square_long 6
//using namespace cv;
//using namespace std;
//Mat maplx;
//Mat maply;
//Mat maprx;
//Mat mapry;
//Mat Q;
//Mat xyz_bm;
//
//Rect validROIL;
//Rect validROIR;
//Mat bm_disp8;
//
//Mat  disp_bm;
//Mat view_gray_depth;
//void on_mouse(int event, int x, int y, int flags, void *ustc);
//int numDisparities =15;
//int main()
//{
//	cout << "��ȡӳ�����" << endl;
//	FileStorage fs(".\\map_mat.xml", FileStorage::READ);
//	fs["maplx"] >> maplx;
//	fs["maply"] >> maply;
//	fs["maprx"] >> maprx;
//	fs["mapry"] >> mapry;
//
//	fs["validROIL"] >> validROIL;
//	fs["validROIR"] >> validROIR;
//
//	fs["Q"] >> Q;
//	cout << "��ȡӳ�����" << endl;
//	cout << "��ȡͼƬ��ӳ����" << endl;
//	Mat image_left = imread("IR_left_sec1.png");
//	Mat image_right = imread("IR_right_sec1.png");
//	Mat image_left_map;
//	Mat image_right_map;
//    remap(image_left, image_left_map, maplx, maply, INTER_LINEAR);
//	remap(image_right, image_right_map, maprx, mapry, INTER_LINEAR);
//	
//	cout << "��ӳ�����" << endl;
//	Mat view_gray1;
//	Mat view_gray2;
//	cvtColor(image_left_map, view_gray1, CV_RGB2GRAY);
//	cvtColor(image_right_map, view_gray2, CV_RGB2GRAY);
//	cout << "��ʼƥ��" << endl;
//
//	cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create(16, 9);
//	/*bm->setPreFilterType(CV_STEREO_BM_NORMALIZED_RESPONSE);
//	bm->setPreFilterSize(9);
//	bm->setPreFilterCap(31);
//	bm->setBlockSize(21);
//	bm->setMinDisparity(0);
//	bm->setNumDisparities(64);
//	bm->setTextureThreshold(10);
//	bm->setUniquenessRatio(5);
//	bm->setSpeckleWindowSize(9);
//	bm->setSpeckleRange(4);
//	bm->setROI1(validROIL);
//	bm->setROI2(validROIR);*/
//
//	bm->setBlockSize(15);     //SAD���ڴ�С��5~21֮��Ϊ��
//	bm->setROI1(validROIL);
//	bm->setROI2(validROIR);
//	bm->setPreFilterCap(31);
//	bm->setMinDisparity(0);  //��С�ӲĬ��ֵΪ0, �����Ǹ�ֵ��int��
//	bm->setNumDisparities(numDisparities * 16 + 16);//�Ӳ�ڣ�������Ӳ�ֵ����С�Ӳ�ֵ֮��,���ڴ�С������16����������int��
//	bm->setTextureThreshold(10);
//	bm->setUniquenessRatio(10);//uniquenessRatio��Ҫ���Է�ֹ��ƥ��
//	bm->setSpeckleWindowSize(100);
//	bm->setSpeckleRange(32);
//	bm->setDisp12MaxDiff(1);
//
//	Mat gray_expandl;
//	Mat gray_expandr;
//
//	copyMakeBorder(view_gray1, gray_expandl, 0, 0, (numDisparities * 16 + 16), 0, IPL_BORDER_REPLICATE);
//	copyMakeBorder(view_gray2, gray_expandr, 0, 0, (numDisparities * 16 + 16), 0, IPL_BORDER_REPLICATE);
//
//	bm->compute(gray_expandl, gray_expandr, disp_bm);
//
//
//
//	disp_bm.convertTo(bm_disp8, CV_8U, 255 / ((numDisparities * 16 + 16)*16.));//��������Ӳ���CV_16S��ʽ
//	
//	
//	reprojectImageTo3D(disp_bm, xyz_bm, Q, true);
//	xyz_bm = xyz_bm * 16;
//
//	namedWindow("Disaparity_BM_SAD");
//	setMouseCallback("Disaparity_BM_SAD", on_mouse, 0);
//
//
//
//	while (true) {
//		imshow("Disaparity_BM_SAD", bm_disp8);
//	
//		waitKey(50);
//	}
//	getchar();
//	system("pause");
//	return 0;
//
//    
//
//}
//
//void on_mouse(int event, int x, int y, int flags, void *ustc)
//{
//	Point origin;
//	if (event == CV_EVENT_LBUTTONDOWN)
//	{
//		origin = Point(x, y);
//		cout << xyz_bm.at<Vec3f>(origin) << "mm" << endl;
//	}
//}
//
//

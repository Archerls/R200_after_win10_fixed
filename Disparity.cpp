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
//Mat xyz_sgbm;
//Rect validROIL;
//Rect validROIR;
//Mat bm_disp8;
//Mat sgbm_disp8;
//Mat  disp_bm;
//Mat disp_sgbm;
//Mat view_gray_depth;
//void on_mouse(int event, int x, int y, int flags, void *ustc);
//void on_mouse2(int event, int x, int y, int flags, void *ustc);
//int numDisparities = 5;
//int main()
//{
//	cout << "读取映射表中" << endl;
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
//	cout << "读取映射完成" << endl;
//	cout << "读取图片再映射中" << endl;
//	Mat image_left = imread("Disparity_IR_left.png");
//	Mat image_right = imread("Disparity_IR_right.png");
//	Mat image_left_map;
//	Mat image_right_map;
//    remap(image_left, image_left_map, maplx, maply, INTER_LINEAR);
//	remap(image_right, image_right_map, maprx, mapry, INTER_LINEAR);
//	cout << "再映射完成" << endl;
//	Mat view_gray1;
//	Mat view_gray2;
//	cvtColor(image_left_map, view_gray1, CV_RGB2GRAY);
//	cvtColor(image_right_map, view_gray2, CV_RGB2GRAY);
//	cout << "开始匹配" << endl;
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
//	bm->setBlockSize(15);     //SAD窗口大小，5~21之间为宜
//	bm->setROI1(validROIL);
//	bm->setROI2(validROIR);
//	bm->setPreFilterCap(31);
//	bm->setMinDisparity(0);  //最小视差，默认值为0, 可以是负值，int型
//	bm->setNumDisparities(numDisparities * 16 + 16);//视差窗口，即最大视差值与最小视差值之差,窗口大小必须是16的整数倍，int型
//	bm->setTextureThreshold(10);
//	bm->setUniquenessRatio(10);//uniquenessRatio主要可以防止误匹配
//	bm->setSpeckleWindowSize(100);
//	bm->setSpeckleRange(32);
//	bm->setDisp12MaxDiff(1);
//
//	clock_t start1 = clock();
//	bm->compute(view_gray1, view_gray2, disp_bm);
//	clock_t end1 = clock();
//	cout << "bm Running Time : " << (double)(end1 - start1) / CLOCKS_PER_SEC << endl;
//	int cn = 1;
//	int sgbmBlockSize = 9;
//	cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(
//		0,     //MinDisparity
//		(numDisparities * 16 + 16),      //NumDisparities
//		sgbmBlockSize,                    //blocksize
//		(8 * cn*sgbmBlockSize*sgbmBlockSize),  //P1
//		(32* cn*sgbmBlockSize*sgbmBlockSize),   //P2
//		1,        //Disp12MaxDiff
//		63,       //PreFilterCap
//		40,       //UniquenessRatio
//		100,   //SpeckleWindowSize
//		32,    //SpeckleRange
//		StereoSGBM::MODE_HH);      //Mode
//	/*sgbm->setBlockSize(21);
//	sgbm->setP1(8 * cn*sgbm->getBlockSize*sgbm->getBlockSize);
//	sgbm->setP2(32 * cn*sgbm->getBlockSize*sgbm->getBlockSize);
//	sgbm->setMinDisparity(0);
//	sgbm->setNumDisparities(numDisparities * 16 + 16);
//	bm->setUniquenessRatio(5);
//	sgbm->setSpeckleWindowSize(100);
//	sgbm->setSpeckleRange(32);
//	sgbm->setDisp12MaxDiff(1);*/
//	clock_t start2 = clock();
//	sgbm->compute(view_gray1, view_gray2, disp_sgbm);
//
//	clock_t end2 = clock();
//	cout << "sgbm Running Time : " << (double)(end2 - start2) / CLOCKS_PER_SEC << endl;
//
//
//	disp_bm.convertTo(bm_disp8, CV_8U, 255 / ((numDisparities * 16 + 16)*16.));//计算出的视差是CV_16S格式
//	disp_sgbm.convertTo(sgbm_disp8, CV_8U, 255 / ((numDisparities * 16 + 16)*16.));
//																			   //disp.convertTo(disp, CV_8U, 1.0 / 16);
//	
//	reprojectImageTo3D(disp_bm, xyz_bm, Q, true);
//	xyz_bm = xyz_bm * 16;
//
//	reprojectImageTo3D(disp_sgbm, xyz_sgbm, Q, true);
//	xyz_sgbm = xyz_sgbm * 16;
//
//	namedWindow("Disaparity_BM_SAD");
//	setMouseCallback("Disaparity_BM_SAD", on_mouse, 0);
//	namedWindow("Disaparity_SGBM");
//	setMouseCallback("Disaparity_SGBM", on_mouse2, 0);
//	ofstream fout_time("Disaparit_runtime.txt");
//	fout_time << "bm Running Time : " << (double)(end1 - start1) / CLOCKS_PER_SEC <<"s"<< endl;
//	fout_time<< "sgbm Running Time : " << (double)(end2 - start2) / CLOCKS_PER_SEC <<"s"<< endl;
//
//	imwrite("Disaparity_BM_SAD.png", bm_disp8);
//
//	imwrite("Disaparity_SGBM.png", sgbm_disp8);
//	while (true) {
//		imshow("Disaparity_BM_SAD", bm_disp8);
//		imshow("Disaparity_SGBM", sgbm_disp8);
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
//void on_mouse2(int event, int x, int y, int flags, void *ustc)
//{
//	Point origin;
//	if (event == CV_EVENT_LBUTTONDOWN)
//	{
//		origin = Point(x, y);
//		cout << xyz_sgbm.at<Vec3f>(origin) << "mm" << endl;
//	}
//}
//
//
//

//#include <opencv2\opencv.hpp>  
//#include <windows.h>
//#include "RealSense/SenseManager.h"
//#include "RealSense/SampleReader.h"
//#include "util_cmdline.h"
//#include "util_render.h"
////#include <conio.h>
//#include "pxcsensemanager.h"
//#include "pxcmetadata.h"
//
//#include "pxcsensemanager.h"
//#include <algorithm>
//#include "pxcmetadata.h"
//#include "util_cmdline.h"
//#include "util_render.h"
//#include <opencv2\opencv.hpp>
//
//using namespace Intel::RealSense;
//using namespace cv;
//using namespace std;
//
//Mat ir_left;
//Mat ir_right;
//#include "opencv2/core/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <fstream>
////#include <time.h>
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
//
//Mat view_gray_depth;
//void on_mouse(int event, int x, int y, int flags, void *ustc);
////void GenerateFalseMap(cv::Mat &src, cv::Mat &disp);
//int numDisparities = 5;
//
//
//
//int wmain(int argc, WCHAR* argv[])
//{
//
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
//	cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create(16, 9);
//	bm->setBlockSize(21);     //SAD窗口大小，5~21之间为宜
//	bm->setROI1(validROIL);
//	bm->setROI2(validROIR);
//	bm->setPreFilterCap(31);
//	bm->setMinDisparity(0);  //最小视差，默认值为0, 可以是负值，int型
//	bm->setNumDisparities(numDisparities * 16 + 16);//视差窗口，即最大视差值与最小视差值之差,窗口大小必须是16的整数倍，int型
//	bm->setTextureThreshold(20);
//	bm->setUniquenessRatio(5);//uniquenessRatio主要可以防止误匹配
//	bm->setSpeckleWindowSize(100);
//	bm->setSpeckleRange(32);
//	bm->setDisp12MaxDiff(1);
//	
//	namedWindow("Disaparity_BM_SAD");
//	setMouseCallback("Disaparity_BM_SAD", on_mouse, 0);
//
//	PXCSenseManager *psm = PXCSenseManager::CreateInstance();
//	if (!psm)
//	{
//		wprintf_s(L"Unabel to create the PXCSenseManager\n");
//		return 1;
//	}
//
//	psm->EnableStream(PXCCapture::STREAM_TYPE_COLOR);
//	psm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH);
//	psm->EnableStream(PXCCapture::STREAM_TYPE_LEFT);
//	psm->EnableStream(PXCCapture::STREAM_TYPE_RIGHT);
//
//
//	if (psm->Init() != PXC_STATUS_NO_ERROR)
//	{
//		wprintf_s(L"Unable to Init the PXCSenseManager\n");
//		return 2;
//	}
//
//	PXCImage *colorIm, *depthIm, *leftIm,*rightIm;
//	PXCImage::ImageData depth_data;
//	PXCImage::ImageData color_data;
//	PXCImage::ImageData left_data;
//	PXCImage::ImageData right_data;
//	PXCImage::ImageInfo depth_information;
//	PXCImage::ImageInfo color_information;
//	PXCImage::ImageInfo left_information;
//	PXCImage::ImageInfo right_information;
//
//	//namedWindow("depth");
//	//setMouseCallback("depth", on_mouse, 0);
//	while (1)
//	{
//		if (psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR) break;
//
//		PXCCapture::Sample *sample = psm->QuerySample();
//
//	//	colorIm = sample->color;
//	//	depthIm = sample->depth;
//		leftIm = sample->left;
//		rightIm = sample->right;
//
//		//获取深度和彩色帧
//	//	colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data);
//	//	depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data);
//		leftIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &left_data);
//		rightIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &right_data);
//
//	
//	//	depth_information = sample->depth->QueryInfo();
//	//	color_information = sample->color->QueryInfo();
//		left_information = sample->left->QueryInfo();
//		right_information = sample->right->QueryInfo();
//
//
//
//		//利用构造函数，载入数据。
//	//	depth = Mat(Size(depth_information.width, depth_information.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] / sizeof(uchar));
//	//	color = Mat(Size(color_information.width, color_information.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
//		ir_left = Mat(Size(left_information.width, left_information.height), CV_8UC1, (void*)left_data.planes[0], left_data.pitches[0] / sizeof(uchar));
//		ir_right = Mat(Size(right_information.width, right_information.height), CV_8UC1, (void*)right_data.planes[0], right_data.pitches[0] / sizeof(uchar));
//		
//		Mat image_left_map;
//		Mat image_right_map;
//		remap(ir_left, image_left_map, maplx, maply, INTER_LINEAR);
//		remap(ir_right, image_right_map, maprx, mapry, INTER_LINEAR);
//
//		Mat view_gray1= image_left_map;
//		Mat view_gray2= image_right_map;
//		//cvtColor(image_left_map, view_gray1, CV_RGB2GRAY);
//	//	cvtColor(image_right_map, view_gray2, CV_RGB2GRAY);
//
//		
//		bm->compute(view_gray1, view_gray2, disp_bm);
//		disp_bm.convertTo(bm_disp8, CV_8U, 255 / ((numDisparities * 16 + 16)*16.));//计算出的视差是CV_16S格式
//		reprojectImageTo3D(disp_bm, xyz_bm, Q, true);
//		xyz_bm = xyz_bm * 16;
//	//	Mat color_map(bm_disp8.rows, bm_disp8.cols, CV_8UC3);
//	//	GenerateFalseMap(bm_disp8, color_map);
//		imshow("Disaparity_BM_SAD", bm_disp8);
//		waitKey(1);
////		imshow("Disaparity_Color", color_map);
//		imshow("left", ir_left);
//		imshow("right", ir_right);
//	//	depthIm->ReleaseAccess(&depth_data);
//	//	colorIm->ReleaseAccess(&color_data);
//		leftIm->ReleaseAccess(&left_data); 
//		rightIm->ReleaseAccess(&right_data);
//
//
//
//		psm->ReleaseFrame();
//		 
//		waitKey(1);
//	}
//	psm->Release();
//}
//
//
//
//
//
//void on_mouse(int event, int x, int y, int flags, void *ustc)
//{
//	Point origin;
//	if (event == CV_EVENT_LBUTTONDOWN)
//	{
//		origin = Point(x, y);
//		cout << xyz_bm.at<Vec3f>(origin)[2] << "mm" << endl;
//	}
//}
//

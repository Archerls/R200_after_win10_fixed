//#include <opencv2\opencv.hpp>  
//#include <windows.h>
//#include "RealSense/SenseManager.h"
//#include "RealSense/SampleReader.h"
//#include "util_cmdline.h"
//#include "util_render.h"
//#include <conio.h>
//#include "pxcsensemanager.h"
//#include "pxcmetadata.h"
//
//#include "pxcsensemanager.h"
//
//#include "pxcmetadata.h"
//#include "util_cmdline.h"
//#include "util_render.h"
//#include <opencv2\opencv.hpp>
//
//using namespace Intel::RealSense;
//using namespace cv;
//using namespace std;
////Mat depth;
//Mat color;
////Mat ir_left;
////Mat ir_right;
//
// //鼠标点击回调函数
////void on_mouse(int event, int x, int y, int flags, void *ustc);
//
//
//int wmain(int argc, WCHAR* argv[])
//{
//
//
//
//
//	PXCSenseManager *psm = PXCSenseManager::CreateInstance();
//	if (!psm)
//	{
//		wprintf_s(L"Unabel to create the PXCSenseManager\n");
//		return 1;
//	}
//
//	psm->EnableStream(PXCCapture::STREAM_TYPE_COLOR);
//	//psm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH);
//	//psm->EnableStream(PXCCapture::STREAM_TYPE_LEFT);
// //psm->EnableStream(PXCCapture::STREAM_TYPE_RIGHT);
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
//		colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data);
//	//	depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data);
//	//	leftIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &left_data);
//	//	rightIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &right_data);
//
//	
//	//	depth_information = sample->depth->QueryInfo();
//		color_information = sample->color->QueryInfo();
//	//	left_information = sample->left->QueryInfo();
//	//	right_information = sample->right->QueryInfo();
//
//
//
//		//利用构造函数，载入深度数据和彩色数据。
//	//	depth = Mat(Size(depth_information.width, depth_information.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] / sizeof(uchar));
//		color = Mat(Size(color_information.width, color_information.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
//		ir_left = Mat(Size(left_information.width, left_information.height), CV_8UC1, (void*)left_data.planes[0], left_data.pitches[0] / sizeof(uchar));
//	//	ir_right = Mat(Size(right_information.width, right_information.height), CV_8UC1, (void*)right_data.planes[0], right_data.pitches[0] / sizeof(uchar));
//		
//
//
//	//	depthIm->ReleaseAccess(&depth_data);
//		colorIm->ReleaseAccess(&color_data);
//	//	leftIm->ReleaseAccess(&left_data); 
//	//	rightIm->ReleaseAccess(&right_data);
//
//
//
//		psm->ReleaseFrame();
//
//		imshow("color", color);
//		//CV_16UC1的图片在imshow时，原始数据将除以256，将最远探测距离设为z，那么imshow时可以乘以255*256/z
//	//	imshow("depth", depth * 25);
//	//	imshow("left", ir_left);
//	//	imshow("right", ir_right);
//		int key=0;
//		static int frame = 0;
//
//		key = waitKey(1);
//		stringstream ss;
//		string str;
//		switch (key)
//		{
//		case 'a':
//			  frame++; 
//			  ss << (frame);
//			  str = ss.str();
//			//  imwrite("Disparity_IR_left_block"+str + ".png", ir_left);
//			//  cout << "ir left img "+str+" saved" << endl;
//			//  imwrite("Disparity_IR_right_block"+str + ".png", ir_right);
//			//  cout << "ir right img " + str + " saved" << endl;
//			  imwrite("Color" + str + ".png", color);
//			  cout << "color img "+ str+" saved" << endl;
//			  break;
//		default:
//			break;
//		}
//		 
//		waitKey(1);
//	}
//	psm->Release();
//}
//
//
////void on_mouse(int event, int x, int y, int flags, void *ustc)
////{
////	if (event == CV_EVENT_LBUTTONDOWN)
////	{
////		cout << depth.at<ushort>(y, x) << "mm" << endl;
////	}
////}
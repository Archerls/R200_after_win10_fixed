#include <opencv2\opencv.hpp>  
#include <windows.h>
#include "RealSense/SenseManager.h"
#include "RealSense/SampleReader.h"
#include "util_cmdline.h"
#include "util_render.h"
//#include <conio.h>
#include "pxcsensemanager.h"
#include "pxcmetadata.h"

#include "pxcsensemanager.h"
#include <algorithm>
#include "pxcmetadata.h"
#include "util_cmdline.h"
#include "util_render.h"
#include <opencv2\opencv.hpp>

using namespace Intel::RealSense;
using namespace cv;
using namespace std;

Mat ir_left;
Mat ir_right;
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
//#include <time.h>
#define board_row 12
#define board_col 11
#define square_long 6
using namespace cv;
using namespace std;
Mat maplx;
Mat maply;
Mat maprx;
Mat mapry;
Mat Q;
Mat xyz_bm;

Rect validROIL;
Rect validROIR;
Mat gray_expandl;
Mat gray_expandr;
Mat bm_disp8;

Mat  disp_bm;

Mat view_gray_depth;
void on_mouse(int event, int x, int y, int flags, void *ustc);
//void GenerateFalseMap(cv::Mat &src, cv::Mat &disp);
int numDisparities = 12;



int wmain(int argc, WCHAR* argv[])
{

	FileStorage fs(".\\map_mat.xml", FileStorage::READ);
	fs["maplx"] >> maplx;
	fs["maply"] >> maply;
	fs["maprx"] >> maprx;
	fs["mapry"] >> mapry;

	fs["validROIL"] >> validROIL;
	fs["validROIR"] >> validROIR;

	fs["Q"] >> Q;
	cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create(16, 9);
	bm->setBlockSize(21);     //SAD���ڴ�С��5~21֮��Ϊ��
	bm->setROI1(validROIL);
	bm->setROI2(validROIR);
	bm->setPreFilterCap(31);
	bm->setMinDisparity(0);  //��С�ӲĬ��ֵΪ0, �����Ǹ�ֵ��int��
	bm->setNumDisparities(numDisparities * 16 + 16);//�Ӳ�ڣ�������Ӳ�ֵ����С�Ӳ�ֵ֮��,���ڴ�С������16����������int��
	bm->setTextureThreshold(20);
	bm->setUniquenessRatio(5);//uniquenessRatio��Ҫ���Է�ֹ��ƥ��
	bm->setSpeckleWindowSize(100);
	bm->setSpeckleRange(31);
	bm->setDisp12MaxDiff(1);
	
	namedWindow("left");
	setMouseCallback("left", on_mouse, 0);

	PXCSenseManager *psm = PXCSenseManager::CreateInstance();
	if (!psm)
	{
		wprintf_s(L"Unabel to create the PXCSenseManager\n");
		return 1;
	}

	psm->EnableStream(PXCCapture::STREAM_TYPE_COLOR);
	psm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH);
	psm->EnableStream(PXCCapture::STREAM_TYPE_LEFT);
	psm->EnableStream(PXCCapture::STREAM_TYPE_RIGHT);


	if (psm->Init() != PXC_STATUS_NO_ERROR)
	{
		wprintf_s(L"Unable to Init the PXCSenseManager\n");
		return 2;
	}

	PXCImage *colorIm, *depthIm, *leftIm,*rightIm;
	PXCImage::ImageData depth_data;
	PXCImage::ImageData color_data;
	PXCImage::ImageData left_data;
	PXCImage::ImageData right_data;
	PXCImage::ImageInfo depth_information;
	PXCImage::ImageInfo color_information;
	PXCImage::ImageInfo left_information;
	PXCImage::ImageInfo right_information;

	//namedWindow("depth");
	//setMouseCallback("depth", on_mouse, 0);
	while (1)
	{
		if (psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR) break;

		PXCCapture::Sample *sample = psm->QuerySample();

	//	colorIm = sample->color;
	//	depthIm = sample->depth;
		leftIm = sample->left;
		rightIm = sample->right;

		//��ȡ��ȺͲ�ɫ֡
	//	colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data);
	//	depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data);
		leftIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &left_data);
		rightIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &right_data);

	
	//	depth_information = sample->depth->QueryInfo();
	//	color_information = sample->color->QueryInfo();
		left_information = sample->left->QueryInfo();
		right_information = sample->right->QueryInfo();



		//���ù��캯�����������ݡ�
	//	depth = Mat(Size(depth_information.width, depth_information.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] / sizeof(uchar));
	//	color = Mat(Size(color_information.width, color_information.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
		ir_left = Mat(Size(left_information.width, left_information.height), CV_8UC1, (void*)left_data.planes[0], left_data.pitches[0] / sizeof(uchar));
		ir_right = Mat(Size(right_information.width, right_information.height), CV_8UC1, (void*)right_data.planes[0], right_data.pitches[0] / sizeof(uchar));
		
		Mat image_left_map;
		Mat image_right_map;
		remap(ir_left, image_left_map, maplx, maply, INTER_LINEAR);
		remap(ir_right, image_right_map, maprx, mapry, INTER_LINEAR);

		Mat view_gray1= image_left_map;
		Mat view_gray2= image_right_map;
		//cvtColor(image_left_map, view_gray1, CV_RGB2GRAY);
	//	cvtColor(image_right_map, view_gray2, CV_RGB2GRAY);

		copyMakeBorder(view_gray1, gray_expandl, 0, 0, (numDisparities * 16 + 16), 0, IPL_BORDER_REPLICATE);
		copyMakeBorder(view_gray2, gray_expandr, 0, 0, (numDisparities * 16 + 16), 0, IPL_BORDER_REPLICATE);
		bm->compute(gray_expandl, gray_expandr, disp_bm);
		disp_bm.convertTo(bm_disp8, CV_8U, 255 / ((numDisparities * 16 + 16)*16.));//��������Ӳ���CV_16S��ʽ
		reprojectImageTo3D(disp_bm, xyz_bm, Q, true);
		xyz_bm = xyz_bm * 16;
	//	Mat color_map(bm_disp8.rows, bm_disp8.cols, CV_8UC3);
	//	GenerateFalseMap(bm_disp8, color_map);
		namedWindow("Disaparity_BM_SAD");
		imshow("Disaparity_BM_SAD", bm_disp8);
		waitKey(1);
//		imshow("Disaparity_Color", color_map);
	//	namedWindow("left");
		imshow("left", view_gray1);
		imshow("right", view_gray2);

/*
		int frame=0;
		vector<Point2f> image_points_buf;
		int key = waitKey(1);
		Size board_size = Size(12, 11);
		stringstream ss;
				string str;
				switch (key)
				{
				case 'a':
					  frame++; 
					  ss << (frame);
					  str = ss.str();
					  if (0 == findChessboardCorners(view_gray1, board_size, image_points_buf, CV_CALIB_CB_ADAPTIVE_THRESH))
						  		{
						  		cout << "can not find chessboard corners in left image !\n"; //�Ҳ����ǵ�
						  			getchar();
						  			;
						  		}
					  else{
					  imwrite("value_IR_left"+str + ".png", view_gray1);
					  cout << "ir left img "+str+" saved" << endl;
					  imwrite("value_IR_right"+str + ".png", view_gray2);
					  cout << "ir right img " + str + " saved" << endl;
					//  imwrite("Color" + str + ".png", color);
					//  cout << "color img "+ str+" saved" << endl;
					  }
					  break;
				default:
					break;
				}
		*/
	//	depthIm->ReleaseAccess(&depth_data);
	//	colorIm->ReleaseAccess(&color_data);
		leftIm->ReleaseAccess(&left_data); 
		rightIm->ReleaseAccess(&right_data);



		psm->ReleaseFrame();
		 
		waitKey(1);
	}
	psm->Release();
}





void on_mouse(int event, int x, int y, int flags, void *ustc)
{
	Point origin;
	int circle_size = 30;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		int nx = x + (numDisparities * 16 + 16);
		
		origin = Point(nx, y);
	/*	cout << origin << endl;
		int xc = 0;
		int yc=0;
		int pix=0;

		Point p;
		for (int i = -circle_size / 2; i++; i < circle_size / 2)
		{
			for (int j = -circle_size / 2; j++; j < circle_size / 2)
			{
				p = Point(nx + i, y + j);
				xc += gray_expandl.at<uchar>(p) * (nx + i);
				yc += gray_expandl.at<uchar>(p) * (y + i);
				pix += gray_expandl.at<uchar>(p);
			}
		}
		origin = Point(xc/pix, yc/pix);*/
		cout << origin << endl;
		cout << xyz_bm.at<Vec3f>(origin) << " mm" << endl;
	}
}


//// R200.cpp : 定义控制台应用程序的入口点。
////
//
///*#include <windows.h>
//#include "RealSense/SenseManager.h"
//#include "RealSense/SampleReader.h"
//#include "util_cmdline.h"
//#include "util_render.h"
//#include <conio.h>
//#include <pxcsensemanager.h>
//#include <pxcsession.h>
//#include <iostream>
//#include <string>
//#include <opencv2\opencv.hpp>
//
//using namespace Intel::RealSense;
//using namespace cv;
//using namespace std;*/
////#include <stdafx.h>
//#include <pxcsensemanager.h>    
//#include <pxcsession.h>    
//#include <iostream>    
//#include <string>    
//#include <stdio.h>    
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
//Mat depth;
//Mat color;
//Mat ir_left;
//Mat ir_right;
// //鼠标点击回调函数
//void on_mouse(int event, int x, int y, int flags, void *ustc);
//
//
//int wmain(int argc, WCHAR* argv[])
//{
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
//	namedWindow("depth");
//	setMouseCallback("depth", on_mouse, 0);
//	while (1)
//	{
//		if (psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR) break;
//
//		PXCCapture::Sample *sample = psm->QuerySample();
//
//		colorIm = sample->color;
//		depthIm = sample->depth;
//		leftIm = sample->left;
//		rightIm = sample->right;
//
//		//获取深度和彩色帧
//		colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data);
//		depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data);
//		leftIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &left_data);
//		rightIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_Y8, &right_data);
//
//	
//		depth_information = sample->depth->QueryInfo();
//		color_information = sample->color->QueryInfo();
//		left_information = sample->left->QueryInfo();
//		right_information = sample->right->QueryInfo();
//
//
//
//		//利用构造函数，载入深度数据和彩色数据。
//		depth = Mat(Size(depth_information.width, depth_information.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] / sizeof(uchar));
//		color = Mat(Size(color_information.width, color_information.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
//		ir_left = Mat(Size(left_information.width, left_information.height), CV_8UC1, (void*)left_data.planes[0], left_data.pitches[0] / sizeof(uchar));
//		ir_right = Mat(Size(right_information.width, right_information.height), CV_8UC1, (void*)right_data.planes[0], right_data.pitches[0] / sizeof(uchar));
//		
//
//
//		depthIm->ReleaseAccess(&depth_data);
//		colorIm->ReleaseAccess(&color_data);
//		leftIm->ReleaseAccess(&left_data); 
//		rightIm->ReleaseAccess(&right_data);
//
//
//
//		psm->ReleaseFrame();
//
//		imshow("color", color);
//		//CV_16UC1的图片在imshow时，原始数据将除以256，将最远探测距离设为z，那么imshow时可以乘以255*256/z
//		imshow("depth", depth * 25);
//		imshow("left", ir_left);
//		imshow("right", ir_right);
//		int key=0;
//		static int frame = 0;
//
//		key = cvWaitKey(1);
//		stringstream ss;
//		string str;
//		switch (key)
//		{
//		case 'a':
//			  frame++; 
//			  ss << (frame);
//			  str = ss.str();
//			  imwrite("IR_left_sec"+str + ".png", ir_left);
//			  cout << "ir left img "+str+" saved" << endl;
//			  imwrite("IR_right_sec"+str + ".png", ir_right);
//			  cout << "ir right img " + str + " saved" << endl;
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
//void on_mouse(int event, int x, int y, int flags, void *ustc)
//{
//	if (event == CV_EVENT_LBUTTONDOWN)
//	{
//		cout << depth.at<ushort>(y, x) << "mm" << endl;
//	}
//}
//
//
//
///*******************************************************************************
//
//INTEL CORPORATION PROPRIETARY INFORMATION
//This software is supplied under the terms of a license agreement or nondisclosure
//agreement with Intel Corporation and may not be copied or disclosed except in
//accordance with the terms of that agreement
//Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.
//
//*******************************************************************************/
//
//
////R200 sample 
//
////int wmain(int argc, WCHAR* argv[]) {
////	/* Creates an instance of the SenseManager */
////	SenseManager *pp = SenseManager::CreateInstance();
////	if (!pp) {
////		wprintf_s(L"Unable to create the SenseManager\n");
////		return 3;
////	}
////
////	/* Collects command line arguments */
////	UtilCmdLine cmdl(pp->QuerySession());
////	if (!cmdl.Parse(L"-listio-nframes-sdname-csize-dsize-isize-lsize-rsize-file-record-noRender-mirror", argc, argv)) return 3;
////
////	/* Sets file recording or playback */
////	CaptureManager *cm = pp->QueryCaptureManager();
////	cm->SetFileName(cmdl.m_recordedFile, cmdl.m_bRecord);
////	if (cmdl.m_sdname) cm->FilterByDeviceInfo(cmdl.m_sdname, 0, 0);
////
////	// Create stream renders
////	UtilRender renderc(L"Color"), renderd(L"Depth"), renderi(L"IR"), renderr(L"Right"), renderl(L"Left");
////	Status sts;
////	do {
////		/* Apply command line arguments */
////		bool revert = false;
////		if (cmdl.m_csize.size() > 0) {
////			pp->EnableStream(Capture::STREAM_TYPE_COLOR, cmdl.m_csize.front().first.width, cmdl.m_csize.front().first.height, (pxcF32)cmdl.m_csize.front().second);
////		}
////		if (cmdl.m_dsize.size() > 0) {
////			pp->EnableStream(Capture::STREAM_TYPE_DEPTH, cmdl.m_dsize.front().first.width, cmdl.m_dsize.front().first.height, (pxcF32)cmdl.m_dsize.front().second);
////		}
////		if (cmdl.m_isize.size() > 0) {
////			pp->EnableStream(Capture::STREAM_TYPE_IR, cmdl.m_isize.front().first.width, cmdl.m_isize.front().first.height, (pxcF32)cmdl.m_isize.front().second);
////		}
////		if (cmdl.m_rsize.size() > 0) {
////			pp->EnableStream(Capture::STREAM_TYPE_RIGHT, cmdl.m_rsize.front().first.width, cmdl.m_rsize.front().first.height, (pxcF32)cmdl.m_rsize.front().second);
////		}
////		if (cmdl.m_lsize.size() > 0) {
////			pp->EnableStream(Capture::STREAM_TYPE_LEFT, cmdl.m_lsize.front().first.width, cmdl.m_lsize.front().first.height, (pxcF32)cmdl.m_lsize.front().second);
////		}
////		if (cmdl.m_csize.size() == 0 && cmdl.m_dsize.size() == 0 && cmdl.m_isize.size() == 0 && cmdl.m_rsize.size() == 0 && cmdl.m_lsize.size() == 0) {
////			DataDesc desc = {};
////			if (cm->QueryCapture()) {
////				cm->QueryCapture()->QueryDeviceInfo(0, &desc.deviceInfo);
////			}
////			else {
////				desc.deviceInfo.streams = Capture::STREAM_TYPE_LEFT | Capture::STREAM_TYPE_RIGHT;
////				revert = true;
////			}
////			pp->EnableStreams(&desc);
////		}
////
////		/* Initializes the pipeline */
////		sts = pp->Init();
////		if (sts < Status::STATUS_NO_ERROR) {
////			if (revert) {
////				/* Enable a single stream */
////				pp->Close();
////				pp->EnableStream(Capture::STREAM_TYPE_LEFT);
////				sts = pp->Init();
////				if (sts < Status::STATUS_NO_ERROR) {
////					pp->Close();
////					pp->EnableStream(Capture::STREAM_TYPE_RIGHT);
////					sts = pp->Init();
////				}
////			}
////			if (sts < Status::STATUS_NO_ERROR) {
////				wprintf_s(L"Failed to locate any video stream(s)\n");
////				pp->Release();
////				return sts;
////			}
////		}
////
////		/* Reset all properties */
////		Capture::Device *device = pp->QueryCaptureManager()->QueryDevice();
////		device->ResetProperties(Capture::STREAM_TYPE_ANY);
////
////		/* Set mirror mode */
////		if (cmdl.m_bMirror) {
////			device->SetMirrorMode(Capture::Device::MirrorMode::MIRROR_MODE_HORIZONTAL);
////		}
////		else {
////			device->SetMirrorMode(Capture::Device::MirrorMode::MIRROR_MODE_DISABLED);
////		}
////
////		/* Stream Data */
////		for (int nframes = 0; nframes < cmdl.m_nframes; nframes++) {
////			/* Waits until new frame is available and locks it for application processing */
////			sts = pp->AcquireFrame(false);
////
////			if (sts < Status::STATUS_NO_ERROR) {
////				if (sts == Status::STATUS_STREAM_CONFIG_CHANGED) {
////					wprintf_s(L"Stream configuration was changed, re-initilizing\n");
////					pp->Close();
////				}
////				break;
////			}
////
////			/* Render streams, unless -noRender is selected */
////			if (cmdl.m_bNoRender == false) {
////				const Capture::Sample *sample = pp->QuerySample();
////				if (sample) {
////					if (sample->depth && !renderd.RenderFrame(sample->depth)) break;
////					if (sample->color && !renderc.RenderFrame(sample->color)) break;
////					if (sample->ir && !renderi.RenderFrame(sample->ir))    break;
////					if (sample->right && !renderr.RenderFrame(sample->right)) break;
////					if (sample->left && !renderl.RenderFrame(sample->left))  break;
////				}
////			}
////
////			/* Releases lock so pipeline can process next frame */
////			pp->ReleaseFrame();
////
////			if (_kbhit()) { // Break loop
////				int c = _getch() & 255;
////				if (c == 27 || c == 'q' || c == 'Q') break; // ESC|q|Q for Exit
////			}
////		}
////	} while (sts == Status::STATUS_STREAM_CONFIG_CHANGED);
////
////	wprintf_s(L"Exiting\n");
////
////	// Clean Up
////	pp->Release();
////	return 0;
////}
//
//
//
////save 100
///*int main(int argc, char** argv)
//{
//UtilRender renderColor(L"COLOR_STREAM");
//UtilRender renderDepth(L"DEPTH_STREAM");
//
//PXCSenseManager *psm = 0;
//psm = PXCSenseManager::CreateInstance();
//if (!psm)
//{
//wprintf_s(L"Unabel to create the PXCSenseManager\n");
//return 1;
//}
//pxcStatus sts;
//
//psm->EnableStream(PXCCapture::STREAM_TYPE_COLOR, WIDTH, HEIGHT);
//
//psm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, WIDTH, HEIGHT);
//
//psm->Init();
//
//if (sts.isError)
//{
//wprintf_s(L"Unabel to Initializes the pipeline\n");
//return 2;
//}
//
//PXCImage *colorIm, *depthIm;
//PXCImage::ImageData depth_data, color_data;
//PXCImage::ImageInfo depth_info, color_info;
//
//for (int cframe = 0; cframe < 100; cframe++)
//{
//if (psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR) break;
//
//PXCCapture::Sample *sample = psm->QuerySample();
//
//colorIm = sample->color;
//depthIm = sample->depth;
//
//if (colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data) < PXC_STATUS_NO_ERROR)
//wprintf_s(L"未正常获取彩色图\n");
//if (depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data) < PXC_STATUS_NO_ERROR)
//wprintf_s(L"未正常获取深度图\n");
//
//depth_info = sample->depth->QueryInfo();
//color_info = sample->color->QueryInfo();
//
//Mat depth(Size(depth_info.width, depth_info.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] / sizeof(uchar));
//Mat color(Size(color_info.width, color_info.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
//
//if (!renderColor.RenderFrame(colorIm)) break;
//if (!renderDepth.RenderFrame(depthIm)) break;
//
//psm->ReleaseFrame();
//
//stringstream ss;
//string str;
//ss << (cframe);
//str = ss.str();
//
//vector<int> compressiong_params;
//compressiong_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
//compressiong_params.push_back(0);
//
//imwrite("E:\\programming tools\\VS_workspace\\Projects\\rs_capturepictures\\rs_capturepictures\\color\\color100" + str + ".png", color, compressiong_params);
//imwrite("E:\\programming tools\\VS_workspace\\Projects\\rs_capturepictures\\rs_capturepictures\\depth\\depth100" + str + ".png", depth * 15, compressiong_params);
//
//}
//psm->Release();
//getchar();
//
//}*/
//
//
//
///*int main(int argc, char** argv)
//{
//UtilRender *renderColor = new UtilRender(L"COLOR_STREAM");
//UtilRender *renderDepth = new UtilRender(L"DEPTH_STREAM");
//
//PXCSenseManager *psm = 0;
//psm = PXCSenseManager::CreateInstance();
//if (!psm)
//{
//wprintf_s(L"Unabel to create the PXCSenseManager\n");
//return 1;
//}
//pxcStatus sts;
//
//psm->EnableStream(PXCCapture::STREAM_TYPE_COLOR, WIDTH, HEIGHT);
//
//psm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, WIDTH, HEIGHT);
//
//sts = psm->Init();
//if (sts != PXC_STATUS_NO_ERROR)
//{
//wprintf_s(L"Unabel to Initializes the pipeline\n");
//return 2;
//}
//
//PXCImage *colorIm, *depthIm;
//PXCImage::ImageData depth_data, color_data;
//PXCImage::ImageInfo depth_info, color_info;
//while (psm->AcquireFrame(true) >= PXC_STATUS_NO_ERROR)
//
//{
//if (psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR) break;
//
//
//PXCCapture::Sample *sample = psm->QuerySample();
//
//colorIm = sample->color;
//depthIm = sample->depth;
//
//if (colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data) < PXC_STATUS_NO_ERROR)
//wprintf_s(L"未正常获取彩色图\n");
//if (depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data) < PXC_STATUS_NO_ERROR)
//wprintf_s(L"未正常获取深度图\n");
//
//depth_info = sample->depth->QueryInfo();
//color_info = sample->color->QueryInfo();
//
//Mat depth(Size(depth_info.width, depth_info.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] / sizeof(uchar));
//Mat color(Size(color_info.width, color_info.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
//
//depthIm->ReleaseAccess(&depth_data);
//colorIm->ReleaseAccess(&color_data);
//
//if (!renderColor->RenderFrame(colorIm)) break;
//if (!renderDepth->RenderFrame(depthIm)) break;
//
//psm->ReleaseFrame();
//
//imshow("color", color);
//waitKey(1);
////CV_16UC1的图片在imshow时会除以256，将最远探测距离设为z，那么imshow时可以乘以255*256/z,此处乘以15
//imshow("depth", depth * 15);
//waitKey(1);
//
//}
//psm->Release();
//system("pause");
//getchar();
//}*/
/////R200查询设备
//
///*int main()
//{
//
//pxcStatus retStatus;// 函数返回状态
//// Realsense会话
//PXCSession *Session = PXCSession::CreateInstance();
//PXCSession::ImplVersion ver = Session->QueryVersion();
//cout << "Realsense SDK 版本 " << ver.major << "." << ver.minor << endl;
//cout << "==================================================" << endl;
//// 收集信息-----------------------------------------------------------------------------\\
//cout << "Checking Cable..." << endl;
//cout << "-----------------" << endl;
//// 限定为RealSense DCM视频服务
//PXCSession::ImplDesc Qtemplat = {};
//Qtemplat.group = PXCSession::IMPL_GROUP_SENSOR;// 分组于传感器
//Qtemplat.subgroup = PXCSession::IMPL_SUBGROUP_VIDEO_CAPTURE;// 子分组于视频采集
//for (size_t DCMidx = 0; ; DCMidx += 1)
//{
//// 查询可用的DCM服务
//PXCSession::ImplDesc Impl;
//retStatus = Session->QueryImpl(&Qtemplat, DCMidx, &Impl);
//if (retStatus < PXC_STATUS_NO_ERROR)break;
//wcout << "Enum_Index[" << DCMidx << "]" << "@" << Impl.friendlyName << ":" << endl;
//
//// 尝试初始化信息采集
//PXCCapture *Capture = NULL;
//retStatus = Session->CreateImpl<PXCCapture>(&Impl, &Capture);
//if (retStatus<PXC_STATUS_NO_ERROR) continue;
//
//// 输出硬件信息
//for (size_t Didx = 0;; Didx += 1)
//{
//PXCCapture::DeviceInfo dinfo;
//retStatus = Capture->QueryDeviceInfo(Didx, &dinfo);
//if (retStatus < PXC_STATUS_NO_ERROR) break;
//// 硬件名称
//wcout << "  |___DEVICE[" << Didx << "]" << ":" << dinfo.name << endl;
//// 输出影像串流类型
//if (dinfo.streams&PXCCapture::STREAM_TYPE_COLOR)
//wprintf_s(L"             |___COLOR ----- STREAM\n");
//if (dinfo.streams&PXCCapture::STREAM_TYPE_DEPTH)
//wprintf_s(L"             |___DEPTH ----- STREAM\n");
//if (dinfo.streams&PXCCapture::STREAM_TYPE_IR)
//wprintf_s(L"             |___IRTOF ----- STREAM\n");
//if (dinfo.streams&PXCCapture::STREAM_TYPE_LEFT)
//wprintf_s(L"             |___STEIR L --- STREAM \n");
//if (dinfo.streams&PXCCapture::STREAM_TYPE_RIGHT)
//wprintf_s(L"             |___STEIR R --- STREAM\n");
//}
//Capture->Release();
//}
//// 接上面代码
//cout << "\n请输入需要查询的模组编号："; int Module_nIdx = cin.get() - 48;
//
//// 重新打开设备
//PXCSession::ImplDesc Impl;                                      // 会话
//PXCCapture *Capture = NULL;                                     // 采集
//PXCCapture::Device *RS_Device = NULL;                           // 设备
//retStatus = Session->QueryImpl(&Qtemplat, Module_nIdx, &Impl);  // 查询当前会话
//if (retStatus < PXC_STATUS_NO_ERROR) exit(0);                   //
//retStatus = Session->CreateImpl<PXCCapture>(&Impl, &Capture);   // 尝试打开采集器
//if (retStatus < PXC_STATUS_NO_ERROR) exit(0);                   //
//RS_Device = Capture->CreateDevice(Module_nIdx);                 // 连接到设备
//if (RS_Device == NULL) exit(0);
//
//// 查询可使用的影像串流类型
//cout << "Checking Streams..." << endl;
//cout << "--------------------" << endl;
//PXCCapture::StreamType flag_Streams = PXCCapture::STREAM_TYPE_COLOR | PXCCapture::STREAM_TYPE_DEPTH | PXCCapture::STREAM_TYPE_LEFT | PXCCapture::STREAM_TYPE_RIGHT;
//cout << "流类型" << "          分辨率" << "         帧速率" << "  像素格式" << "  RAW流传输" << endl;
//cout << "----------------------------------------------------------------------------------" << endl;
//for (size_t Profile_nIdx = 0;; Profile_nIdx += 1)
//{
//PXCCapture::Device::StreamProfileSet ProfileSet = {};
//retStatus = RS_Device->QueryStreamProfileSet(flag_Streams, Profile_nIdx, &ProfileSet);
//if (retStatus<PXC_STATUS_NO_ERROR) break;
//wprintf_s(L"Color[%d]:  |   %dx%d   | @%.1fFPS  |*%08X  |_%08X\n",
//Profile_nIdx, ProfileSet.color.imageInfo.width,
//ProfileSet.color.imageInfo.height, ProfileSet.color.frameRate.max, ProfileSet.color.imageInfo.format, ProfileSet.color.options);
//wprintf_s(L"Depth[%d]:  |   %dx%d   | @%.1fFPS  |*%08X  |_%08X\n",
//Profile_nIdx, ProfileSet.depth.imageInfo.width,
//ProfileSet.depth.imageInfo.height, ProfileSet.depth.frameRate.max, ProfileSet.depth.imageInfo.format, ProfileSet.depth.options);
//wprintf_s(L"DualL[%d]:  |   %dx%d   | @%.1fFPS  |*%08X  |_%08X\n",
//Profile_nIdx, ProfileSet.left.imageInfo.width,
//ProfileSet.left.imageInfo.height, ProfileSet.left.frameRate.max, ProfileSet.left.imageInfo.format, ProfileSet.left.options);
//wprintf_s(L"DualR[%d]:  |   %dx%d   | @%.1fFPS  |*%08X  |_%08X\n",
//Profile_nIdx, ProfileSet.right.imageInfo.width,
//ProfileSet.right.imageInfo.height, ProfileSet.right.frameRate.max, ProfileSet.right.imageInfo.format, ProfileSet.right.options);
//cout << "----------------------------------------------------------------------------------" << endl;
//}
//// 典型的流信息 彩色RGB24 1920 1080 双目IR int16 628 468 硬件帧同步 30FPS
//PXCCapture::Device::StreamProfileSet ProfileSet = {};
//ProfileSet.color.imageInfo.width = 1920; ProfileSet.color.imageInfo.height = 1080;
//ProfileSet.color.imageInfo.format = PXCImage::PIXEL_FORMAT_RGB32;
//ProfileSet.color.options = PXCCapture::Device::STREAM_OPTION_STRONG_STREAM_SYNC;
//ProfileSet.color.frameRate = { 30,30 };
//ProfileSet.depth.imageInfo.width = 628; ProfileSet.depth.imageInfo.height = 468;
//ProfileSet.depth.imageInfo.format = PXCImage::PIXEL_FORMAT_DEPTH;
//ProfileSet.depth.options = PXCCapture::Device::STREAM_OPTION_STRONG_STREAM_SYNC;
//ProfileSet.depth.frameRate = { 30,30 };
//ProfileSet.left.imageInfo.width = 628; ProfileSet.left.imageInfo.height = 468;
//ProfileSet.left.imageInfo.format = PXCImage::PIXEL_FORMAT_Y16;
//ProfileSet.left.options = PXCCapture::Device::STREAM_OPTION_STRONG_STREAM_SYNC;
//ProfileSet.left.frameRate = { 30,30 };
//ProfileSet.right.imageInfo.width = 628; ProfileSet.right.imageInfo.height = 468;
//ProfileSet.right.imageInfo.format = PXCImage::PIXEL_FORMAT_Y16;
//ProfileSet.right.options = PXCCapture::Device::STREAM_OPTION_STRONG_STREAM_SYNC;
//ProfileSet.right.frameRate = { 30,30 };
//
//cout << "配置影像串流...";
//if (RS_Device->IsStreamProfileSetValid(&ProfileSet))
//{
//RS_Device->SetStreamProfileSet(&ProfileSet);
//cout << "就绪" << endl;
//}
//else
//cout << "不支持的串流组合" << endl;
//system("pause");
//getchar();
//return 0;
//}*/
//

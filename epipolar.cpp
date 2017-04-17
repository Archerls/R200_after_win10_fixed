////#include "stdafx.h"  
//#include <opencv2/opencv.hpp>  
//#include <highgui.hpp>  
//#include "cv.h"  
//#include <cv.hpp>  
//#include <iostream> 
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat rectifyImageL;
//	Mat rectifyImageR;
//	rectifyImageL = imread("image_map1.png");
//	rectifyImageR = imread("image_map2.png");
//
//	Mat canvas;
//	Size image_size;
//	double sf;
//	int w, h;
//	image_size.width = rectifyImageL.cols;
//	image_size.height = rectifyImageL.rows;
//
//sf = 600. / MAX(imageSize.width, imageSize.height);
//w = cvRound(imageSize.width * sf);
//h = cvRound(imageSize.height * sf);
//canvas.create(h, w * 2, CV_8UC3);
//
///*��ͼ�񻭵�������*/
//Mat canvasPart = canvas(Rect(w * 0, 0, w, h));                                //�õ�������һ����  
//resize(rectifyImageL, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);     //��ͼ�����ŵ���canvasPartһ����С  
//Rect vroiL(cvRound(validROIL.x*sf), cvRound(validROIL.y*sf),                //��ñ���ȡ������    
//	cvRound(validROIL.width*sf), cvRound(validROIL.height*sf));
//rectangle(canvasPart, vroiL, Scalar(0, 0, 255), 3, 8);                      //����һ������  
//
//cout << "Painted ImageL" << endl;
//
///*��ͼ�񻭵�������*/
//canvasPart = canvas(Rect(w, 0, w, h));                                      //��û�������һ����  
//resize(rectifyImageR, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);
//Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y*sf),
//	cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
//rectangle(canvasPart, vroiR, Scalar(0, 255, 0), 3, 8);
//
//cout << "Painted ImageR" << endl;
//
///*���϶�Ӧ������*/
//for (int i = 0; i < canvas.rows; i += 16)
//	line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
//
//imshow("rectified", canvas);
//
//cout << "wait key" << endl;
//waitKey(0);
//system("pause");
//return 0;
//}
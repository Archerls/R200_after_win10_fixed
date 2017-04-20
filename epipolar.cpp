//#include "stdafx.h"  
//#include <opencv2/opencv.hpp>  
//#include <highgui.hpp>  
//#include "cv.h"  
//#include <cv.hpp>  
//#include <iostream> 
//#include<algorithm>
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Size image_size;
//	Mat image_map1;
//	Mat image_map2;
//	image_map1 = imread("IR_left1.png");
//	image_map2 = imread("IR_right1.png");
//	image_size.width = image_map1.cols;
//	image_size.height = image_map1.rows;
//
//
//	/*校正结果*/
//		Mat canvas;
//		double sf;
//		int w, h;
//		sf = 600. / MAX(image_size.width, image_size.height);
//		w = cvRound(image_size.width * sf);
//		h = cvRound(image_size.height * sf);
//		canvas.create(h, w * 2, CV_8UC1);
//	
//		
//		/*左图像画到画布上*/
//		Mat canvasPart1(canvas(Rect(w * 0, 0, w, h)));                                //得到画布的一部分  
//		resize(image_map1, canvasPart1, canvasPart1.size(), 0, 0, INTER_AREA);     //把图像缩放到跟canvasPart一样大小  
//		Rect vroiL(cvRound(validROIL.x*sf), cvRound(validROIL.y*sf),                //获得被截取的区域    
//		cvRound(validROIL.width*sf), cvRound(validROIL.height*sf));
//		imshow("canvasPart1", canvas);
//		waitKey(100);
//		imwrite("canvas.png", canvas);
//		
//		imwrite("canvasPart1.png", canvasPart1);
//		rectangle(canvasPart1, vroiL, Scalar(0, 0, 255), 3, 8);                      //画上一个矩形  
//		canvasPart1.copyTo(Mat(canvas, Rect(w * 0, 0, w, h)));
//		/*右图像画到画布上*/
//		Mat canvasPart2(canvas(Rect(w, 0, w, h)));                                      //获得画布的另一部分  
//		resize(image_map2, canvasPart2, canvasPart2.size(), 0, 0, INTER_LINEAR);
//		imshow("canvasPart2", canvasPart2);
//		imwrite("canvasPart2.png", canvasPart2);
//		Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y*sf),
//			cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
//		rectangle(canvasPart2, vroiR, Scalar(0, 0, 255), 3, 8);
//		canvasPart2.copyTo(Mat(canvas, Rect(w , 0, w, h)));
//	
//		cout << "Painted ImageR" << endl;
//	
//		/*画上对应的线条*/
//		for (int i = 0; i < canvas.rows; i += 16)
//		{
//			line(canvasPart1, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
//			line(canvasPart2, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
//		}
//			
//		imwrite("unrectified1.png", canvasPart1);
//	    imwrite("unrectified2.png", canvasPart2);
//		imshow("unrectified1", canvasPart1);
//		
//	     
//		waitKey(500);
//		imshow("unrectified2", canvasPart2);
//		waitKey(500);
//	
//		cout << "wait key" << endl;
//		waitKey(0);
//		
//	
//		imshow("image_map1.png", image_map1);
//		waitKey(300);
//		imshow("image_map2.png", image_map2);
//		waitKey(300);
//		imwrite("image_map1.png", image_map1);
//		imwrite("image_map2.png", image_map2);
//}
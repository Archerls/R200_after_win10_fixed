//#include "opencv2/highgui/highgui.hpp"    
//#include "opencv2/imgproc/imgproc.hpp"    
//#include "opencv2/core/core.hpp"  
//#include <opencv\ml.h>  
//#include <iostream>  
//#include "cv.h"  
//#include "highgui.h"  
//#include <vector>  
//#include <math.h>  
//#include <string.h>  
//#include <fstream>  
//using namespace std;
//using namespace cv;
//
//
//int bSums(Mat src)
//{
//
//	int counter = 0;
//	//�������������ص�  
//	Mat_<uchar>::iterator it = src.begin<uchar>();
//	Mat_<uchar>::iterator itend = src.end<uchar>();
//	for (; it != itend; ++it)
//	{
//		if ((*it)>0) counter += 1;//��ֵ�������ص���0����255  
//	}
//	return counter;
//}
//int main()
//{
//	ofstream fout("density.txt");
//	static string imgPath1 = "Disaparity_BM_SAD.png";//��ȡԴͼ  
//	static string imgPath2 = "Disaparity_SGBM.png";//��ȡԴͼ  
//
//	Mat a1 = imread(imgPath1);
//	Mat a2 = imread(imgPath2);
//	int row = a1.rows;
//	int col = a1.cols;
//	cvtColor(a1, a1, COLOR_BGR2GRAY);//ת�Ҷ�ͼ  
//	cvtColor(a2, a2, COLOR_BGR2GRAY);//ת�Ҷ�ͼ  
//	//threshold(a1, a1, 200, 255, THRESH_BINARY);//��ֵ��  
//	int a = bSums(a1);//���ú���bSums  
//	int b = bSums(a2);
//	
//	fout << "sad:" << a*100.0/(row*col-44928)<<"%" << endl;
//
//	fout << "sgm:" << b*100.0 /(row*col-44928)<<"%"  << endl;
//
//	waitKey();
//	return 0;
//}
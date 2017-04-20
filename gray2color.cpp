////[cpp] view plain copy
//#include <opencv2/opencv.hpp>  
//using namespace cv;
//using namespace std;
//
//Mat scaleGray(const Mat& inputGray)
//{
//	Mat outputGray(inputGray.size(), CV_8U);
//	unsigned char grayValue, maxValue = 1;
//	for (int y = 0; y < inputGray.rows; y++)
//		for (int x = 0; x < inputGray.cols; x++)
//		{
//			grayValue = inputGray.at<uchar>(y, x);
//			maxValue = max(maxValue, grayValue);
//		}
//
//	float scale = 255.0 / maxValue;
//	for (int y = 0; y < inputGray.rows; y++)
//		for (int x = 0; x < inputGray.cols; x++)
//		{
//			outputGray.at<uchar>(y, x) = static_cast<unsigned char>(inputGray.at<uchar>(y, x) * scale + 0.5);
//		}
//
//	return outputGray;
//}
//
//Mat gray2pseudocolor(const Mat& scaledGray)
//{
//	Mat outputPseudocolor(scaledGray.size(), CV_8UC3);
//	unsigned char grayValue;
//	for (int y = 0; y < scaledGray.rows; y++)
//		for (int x = 0; x < scaledGray.cols; x++)
//		{
//			grayValue = scaledGray.at<uchar>(y, x);
//			Vec3b& pixel = outputPseudocolor.at<Vec3b>(y, x);
//			pixel[0] = abs(255 - grayValue);
//			pixel[1] = abs(127 - grayValue);
//			pixel[2] = abs(0 - grayValue);
//		}
//
//	return outputPseudocolor;
//}
//
///*
//* color    R   G   B   gray
//* red      255 0   0   255
//* orange   255 127 0   204
//* yellow   255 255 0   153
//* green    0   255 0   102
//* cyan     0   255 255 51
//* blue     0   0   255 0
//*
//*/
//Mat gray2rainbow(const Mat& scaledGray)
//{
//	Mat outputRainbow(scaledGray.size(), CV_8UC3);
//	unsigned char grayValue;
//	for (int y = 0; y < scaledGray.rows; y++)
//		for (int x = 0; x < scaledGray.cols; x++)
//		{
//			grayValue = scaledGray.at<uchar>(y, x);
//			Vec3b& pixel = outputRainbow.at<Vec3b>(y, x);
//			if (grayValue <= 51)
//			{
//				pixel[0] = 255;
//				pixel[1] = grayValue * 5;
//				pixel[2] = 0;
//			}
//			else if (grayValue <= 102)
//			{
//				grayValue -= 51;
//				pixel[0] = 255 - grayValue * 5;
//				pixel[1] = 255;
//				pixel[2] = 0;
//			}
//			else if (grayValue <= 153)
//			{
//				grayValue -= 102;
//				pixel[0] = 0;
//				pixel[1] = 255;
//				pixel[2] = grayValue * 5;
//			}
//			else if (grayValue <= 204)
//			{
//				grayValue -= 153;
//				pixel[0] = 0;
//				pixel[1] = 255 - static_cast<unsigned char>(grayValue * 128.0 / 51 + 0.5);
//				pixel[2] = 255;
//			}
//			else if (grayValue <= 255)
//			{
//				grayValue -= 204;
//				pixel[0] = 0;
//				pixel[1] = 127 - static_cast<unsigned char>(grayValue * 127.0 / 51 + 0.5);
//				pixel[2] = 255;
//			}
//		}
//
//	return outputRainbow;
//}
//
//int main(int argc, char* argv[])
//{
//
//
//	Mat inputGray1 = imread("Disaparity_BM_SAD.png", 0);
//	Mat inputGray2 = imread("Disaparity_SGBM.png", 0);
////	Mat scaledGray = scaleGray(inputGray);
//	//Mat pseudocolor = gray2pseudocolor(inputGray1);
//	Mat rainbow1 = gray2rainbow(inputGray1);
//	Mat rainbow2 = gray2rainbow(inputGray2);
////	imwrite("scaledGray2.png", scaledGray);
//	//imwrite("pseudocolor1.png", pseudocolor);
//	imwrite("SADrainbow.png", rainbow1);
//	imwrite("SGBMrainbow.png", rainbow2);
//	return 0;
//}
////#include <stdafx.h>
//#include "opencv2/core/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <fstream>
//#define board_row 12
//#define board_col 11
//#define square_long 6
////#define image_try
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	ifstream fin1("calibdata.txt");   /* 标定所用LEFT图像文件的路径 */
//	ofstream fout1("caliberation_result.txt");  /* 保存标定结果的文件 */
//
//	ifstream fin2("calibdata2.txt"); /* 标定所用RIGHT图像文件的路径 */
//	ofstream fout2("caliberation_result2.txt");  /* 保存标定结果的文件 */
//
//												 //读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化	
//	cout << "开始提取角点………………";
//	int image_count = 0;  /* 图像数量 */
//	Size image_size;  /* 图像的尺寸 */
//	Size board_size = Size(board_row, board_col);    /* 标定板上每行、列的角点数 */
//	vector<Point2f> image_points_buf1;  /* 缓存每幅图像上检测到的角点 */
//	vector<vector<Point2f>> image_points_seq1; /* 保存检测到的所有角点 */
//	vector<Point2f> image_points_buf2;  /* 缓存每幅图像上检测到的角点 */
//	vector<vector<Point2f>> image_points_seq2; /* 保存检测到的所有角点 */
//	string filename1;
//	string filename2;
//	int count = -1;//用于存储角点个数。
//
//	while (getline(fin1, filename1) && getline(fin2, filename2))
//	{
//		image_count++;
//		// 用于观察检验输出
//		cout << "image_count = " << image_count << endl;
//		/* 输出检验*/
//		cout << "-->count = " << count;
//		Mat imageInput1 = imread(filename1);
//		Mat imageInput2 = imread(filename2);
//		if (image_count == 1)  //读入第一张图片时获取图像宽高信息
//		{
//			image_size.width = imageInput1.cols;
//			image_size.height = imageInput1.rows;
//			cout << "image_size.width = " << image_size.width << endl;
//			cout << "image_size.height = " << image_size.height << endl;
//		}
//
//		/* 提取左右图像的角点 */
//		if (0 == findChessboardCorners(imageInput1, board_size, image_points_buf1, CV_CALIB_CB_ADAPTIVE_THRESH))
//		{
//			cout << "can not find chessboard corners in left image !\n"; //找不到角点
//			getchar();
//			exit(1);
//		}
//		if (0 == findChessboardCorners(imageInput2, board_size, image_points_buf2, CV_CALIB_CB_ADAPTIVE_THRESH))
//		{
//			cout << "can not find chessboard corners in right image!\n"; //找不到角点
//			getchar();
//			exit(1);
//		}
//
//		else
//		{
//			/*如果输入的是彩色图像则需转换为灰色图像*/
//			Mat view_gray1;
//			Mat view_gray2;
//			cvtColor(imageInput1, view_gray1, CV_RGB2GRAY);
//			cvtColor(imageInput2, view_gray2, CV_RGB2GRAY);
//
//			/* 亚像素精确化 */
//			find4QuadCornerSubpix(view_gray1, image_points_buf1, Size(11, 11)); //对粗提取的角点进行精确化
//			find4QuadCornerSubpix(view_gray2, image_points_buf2, Size(11, 11)); //对粗提取的角点进行精确化
//			image_points_seq1.push_back(image_points_buf1);  //保存亚像素角点
//			image_points_seq2.push_back(image_points_buf2);  //保存亚像素角点
//
//															 /* 在图像上显示角点位置 */
//			drawChessboardCorners(view_gray1, board_size, image_points_buf1, true); //用于在图片中标记角点
//			drawChessboardCorners(view_gray2, board_size, image_points_buf2, true); //用于在图片中标记角点
//			imshow("LEFT Camera Calibration", view_gray1);//显示图片
//			imshow("RIGHT Camera Calibration", view_gray2);//显示图片
//			waitKey(500);//暂停0.5S		
//		}
//	}
//	cv::destroyWindow("LEFT Camera Calibration");
//	cv::destroyWindow("RIGHT Camera Calibration");
//	int total = image_points_seq1.size();
//	cout << "total = " << total << endl;
//	int CornerNum = board_size.width*board_size.height;  //每张图片上总的角点数
//	for (int ii = 0; ii<total; ii++)
//	{
//		if (0 == ii%CornerNum)
//		{
//			int i = -1;
//			i = ii / CornerNum;
//			int j = i + 1;
//			cout << "--> 第 " << j << "图片的数据 --> : " << endl;
//		}
//		if (0 == ii % 3)
//		{
//			cout << endl;
//		}
//		else
//		{
//			cout.width(10);
//		}
//		//输出所有的角点
//		cout << " left-->" << image_points_seq1[ii][0].x;
//		cout << " -->" << image_points_seq1[ii][0].y;
//		cout << " right-->" << image_points_seq2[ii][0].x;
//		cout << " -->" << image_points_seq2[ii][0].y;
//	}
//	cout << "角点提取完成！\n";
//
//	//以下是摄像机标定
//	cout << "开始标定………………";
//
//	/*棋盘三维信息*/
//	Size2f square_size = Size2f(square_long, square_long);  /* 实际测量得到的标定板上每个棋盘格的大小 */
//	vector<vector<Point3f>> object_points1;  /* 保存标定板上角点的三维坐标 */
//	vector<vector<Point3f>> object_points2; /* 保存标定板上角点的三维坐标 */
//
//	/*内外参数*/
//	Mat cameraMatrix1 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* LEFT摄像机内参数矩阵 */
//	Mat cameraMatrix2 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* RIGHT摄像机内参数矩阵 */
//	vector<int> point_counts;  // 每幅图像中角点的数量
//	Mat distCoeffs1 = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* LEFT摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
//	Mat distCoeffs2 = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* RIGHT摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
//	vector<Mat> tvecsMat1;  /* 每幅LEFT图像的旋转向量 */
//	vector<Mat> tvecsMat2;  /* 每幅RIGHT图像的旋转向量 */
//	vector<Mat> rvecsMat1; /* 每幅LEFT图像的平移向量 */
//	vector<Mat> rvecsMat2; /* 每幅RIGHT图像的平移向量 */
//
//						   /* 初始化标定板上角点的三维坐标 */
//	int i, j, t;
//	for (t = 0; t<image_count; t++)
//	{
//		vector<Point3f> tempPointSet;
//		for (i = 0; i<board_size.height; i++)
//		{
//			for (j = 0; j<board_size.width; j++)
//			{
//				Point3f realPoint;
//				/* 假设标定板放在世界坐标系中z=0的平面上 */
//				realPoint.x = i*square_size.width;
//				realPoint.y = j*square_size.height;
//				realPoint.z = 0;
//				tempPointSet.push_back(realPoint);
//			}
//		}
//		object_points1.push_back(tempPointSet);
//		object_points2.push_back(tempPointSet);
//	}
//	/* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
//	for (i = 0; i<image_count; i++)
//	{
//		point_counts.push_back(board_size.width*board_size.height);
//	}
//	/* 开始标定 */
//	calibrateCamera(object_points1, image_points_seq1, image_size, cameraMatrix1, distCoeffs1, rvecsMat1, tvecsMat1, 0);
//	calibrateCamera(object_points2, image_points_seq2, image_size, cameraMatrix2, distCoeffs2, rvecsMat2, tvecsMat2, 0);
//	cout << "标定完成！\n";
//	//对标定结果进行评价
//	cout << "开始评价标定结果………………\n";
//	double total_err1 = 0.0; /* 所有图像的平均误差的总和 */
//	double total_err2 = 0.0; /* 所有图像的平均误差的总和 */
//	double err1 = 0.0; /* 每幅图像的平均误差 */
//	double err2 = 0.0; /* 每幅图像的平均误差 */
//	vector<Point2f> image_points1_2; /* 保存重新计算得到的投影点 */
//	vector<Point2f> image_points2_2; /* 保存重新计算得到的投影点 */
//	cout << "\t每幅图像的标定误差：\n";
//	fout1 << "每幅图像的标定误差：\n";
//	fout2 << "每幅图像的标定误差：\n";
//	for (i = 0; i<image_count; i++)
//	{
//		vector<Point3f> tempPointSet1 = object_points1[i];
//		vector<Point3f> tempPointSet2 = object_points2[i];
//		/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
//		projectPoints(tempPointSet1, rvecsMat1[i], tvecsMat1[i], cameraMatrix1, distCoeffs1, image_points1_2);
//		projectPoints(tempPointSet2, rvecsMat2[i], tvecsMat2[i], cameraMatrix2, distCoeffs2, image_points2_2);
//		/* 计算新的投影点和旧的投影点之间的误差*/
//		vector<Point2f> tempImagePoint1 = image_points_seq1[i];
//		vector<Point2f> tempImagePoint2 = image_points_seq2[i];
//		Mat tempImagePointMat = Mat(1, tempImagePoint1.size(), CV_32FC2);
//		Mat tempImagePoint2Mat = Mat(1, tempImagePoint2.size(), CV_32FC2);
//		Mat image_points_2Mat = Mat(1, image_points1_2.size(), CV_32FC2);
//		Mat image_points2_2Mat = Mat(1, image_points2_2.size(), CV_32FC2);
//		for (int j = 0; j < tempImagePoint1.size(); j++)
//		{
//			image_points_2Mat.at<Vec2f>(0, j) = Vec2f(image_points1_2[j].x, image_points1_2[j].y);
//			image_points2_2Mat.at<Vec2f>(0, j) = Vec2f(image_points2_2[j].x, image_points2_2[j].y);
//			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint1[j].x, tempImagePoint1[j].y);
//			tempImagePoint2Mat.at<Vec2f>(0, j) = Vec2f(tempImagePoint2[j].x, tempImagePoint2[j].y);
//		}
//		err1 = norm(image_points_2Mat, tempImagePointMat, NORM_L2);
//		err2 = norm(image_points2_2Mat, tempImagePoint2Mat, NORM_L2);
//		total_err1 += err1 /= point_counts[i];
//		total_err2 += err2 /= point_counts[i];
//		std::cout << "left第" << i + 1 << "幅图像的平均误差：" << err1 << "像素" << endl;
//		std::cout << "right第" << i + 1 << "幅图像的平均误差：" << err2 << "像素" << endl;
//		fout1 << "第" << i + 1 << "幅图像的平均误差：" << err1 << "像素" << endl;
//		fout2 << "第" << i + 1 << "幅图像的平均误差：" << err2 << "像素" << endl;
//	}
//	std::cout << "left总体平均误差：" << total_err1 / image_count << "像素" << endl;
//	std::cout << "right总体平均误差：" << total_err2 / image_count << "像素" << endl;
//	fout1 << "总体平均误差：" << total_err1 / image_count << "像素" << endl << endl;
//	fout2 << "总体平均误差：" << total_err2 / image_count << "像素" << endl << endl;
//	std::cout << "评价完成！" << endl;
//	//保存定标结果  	
//	std::cout << "开始保存定标结果………………" << endl;
//	Mat rotation_matrix1 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
//	Mat rotation_matrix2 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
//	fout1 << "相机内参数矩阵：" << endl;
//	fout1 << cameraMatrix1 << endl << endl;
//	fout1 << "畸变系数：\n";
//	fout1 << distCoeffs1 << endl << endl << endl;
//
//	fout2 << "相机内参数矩阵：" << endl;
//	fout2 << cameraMatrix2 << endl << endl;
//	fout2 << "畸变系数：\n";
//	fout2 << distCoeffs2 << endl << endl << endl;
//
//	for (int i = 0; i<image_count; i++)
//	{
//		fout1 << "第" << i + 1 << "幅图像的旋转向量：" << endl;
//		fout1 << tvecsMat1[i] << endl;
//		/* 将旋转向量转换为相对应的旋转矩阵 */
//		Rodrigues(tvecsMat1[i], rotation_matrix1);
//		fout1 << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
//		fout1 << rotation_matrix1 << endl;
//		fout1 << "第" << i + 1 << "幅图像的平移向量：" << endl;
//		fout1 << rvecsMat1[i] << endl << endl;
//
//		fout2 << "第" << i + 1 << "幅图像的旋转向量：" << endl;
//		fout2 << tvecsMat2[i] << endl;
//		/* 将旋转向量转换为相对应的旋转矩阵 */
//		Rodrigues(tvecsMat2[i], rotation_matrix2);
//		fout2 << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
//		fout2 << rotation_matrix2 << endl;
//		fout2 << "第" << i + 1 << "幅图像的平移向量：" << endl;
//		fout2 << rvecsMat2[i] << endl << endl;
//	}
//	std::cout << "完成保存" << endl;
//	fout1 << endl;
//#ifndef image_try
//
//	/*单目标定各自完成,开始立体标定*/
//
//	/*	vector<Size> npoints;
//	for (int i = 0; i < image_count; i++)
//	{
//	npoints.push_back(board_size);
//	}*/
//	Mat R;  //旋转矩阵
//	Mat T;  //平移矩阵
//	Mat E;  //本征矩阵
//	Mat F;  //基础矩阵
//
//	stereoCalibrate(object_points1, image_points_seq1, image_points_seq2, cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2, image_size, R, T, E, F, CALIB_FIX_INTRINSIC, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 100, 1e-5));
//	ofstream fout_steroCali("sterocali_result.txt");
//	fout_steroCali << "旋转矩阵：" << endl;
//	fout_steroCali << R << endl;
//	fout_steroCali << "平移矩阵：" << endl;
//	//T = -1 * T;
//	fout_steroCali << T << endl;
//
//	/*立体校正*/
//	Mat Rl;   //左旋转矩阵
//	Mat Rr;   //右旋转矩阵
//	Mat Pl;   //左投影矩阵
//	Mat Pr;   //右投影矩阵
//	Mat Q;    //重投影矩阵
//	Rect validROIL, validROIR; 
//
//	stereoRectify(cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2,image_size,R,T,Rl,Rr,Pl,Pr,Q,CV_CALIB_ZERO_DISPARITY,0,image_size,&validROIL,&validROIR);
//	ofstream fout_steroRect("SteroRect_result.txt");
//	cout << "Rl:" << endl;
//	cout << Rl << endl;
//	cout << "Rr:" << endl;
//	cout << Rr << endl;
//	cout << "Pl:" << endl;
//	cout << Pl << endl;
//	cout << "Pr:" << endl;
//	cout << Pr << endl;
//	cout << "Q:" << endl;
//	cout << Q << endl;
//
//	fout_steroRect << "Rl:" << endl;
//	fout_steroRect << Rl << endl;
//	fout_steroRect << "Rr:" << endl;
//	fout_steroRect << Rr << endl;
//	fout_steroRect << "Pl:" << endl;
//	fout_steroRect << Pl << endl;
//	fout_steroRect << "Pr:" << endl;
//	fout_steroRect << Pr << endl;
//	fout_steroRect << "Q:" << endl;
//	fout_steroRect << Q << endl;
//
///*矫正映射*/
//	Mat maplx;
//	Mat maply;
//	Mat maprx;
//	Mat mapry;
//	initUndistortRectifyMap(cameraMatrix1, distCoeffs1, Rl, Pl, image_size, CV_32FC1, maplx, maply);
//	initUndistortRectifyMap(cameraMatrix2, distCoeffs2, Rr, Pr, image_size, CV_32FC1, maprx, mapry);
//
//	ofstream fout_steroRectMap("SteroRectMap_result.txt");
//
//	fout_steroRectMap << "maplx:" << endl;
//	fout_steroRectMap << maplx << endl;
//	fout_steroRectMap << "maply:" << endl;
//	fout_steroRectMap << maply << endl;
//	fout_steroRectMap << "maprx:" << endl;
//	fout_steroRectMap << maprx << endl;
//	fout_steroRectMap << "mapry:" << endl;
//	fout_steroRectMap << mapry << endl;
//	fout_steroRectMap << "validROIL:" << endl;
//	fout_steroRectMap << validROIL << endl;
//	fout_steroRectMap << "validROIR:" << endl;
//	fout_steroRectMap << validROIR << endl;
//
//
//	Mat image_source1 = imread("IR_left4.png");
//	Mat view_gray_source;
//	//imshow("image_source1", image_source1);
//	//cvtColor(image_source1, view_gray_source, CV_RGB2GRAY);
//	waitKey(300);
//	Mat image_source2 = imread("IR_right4.png");
//	//Mat view_gray_source;
//	//imshow("image_source2", image_source2);
//	waitKey(300);
//	Mat image_map1;
//	Mat image_map2;
//
//	FileStorage fs(".\\map_mat.xml", FileStorage::WRITE);
//	fs << "maplx" << maplx;
//	fs << "maply" << maply;
//	fs << "maprx" << maprx;
//	fs << "mapry" << mapry;
//	fs << "validROIL" << validROIL;
//	fs << "validROIR" << validROIR;
//	fs << "Q" << Q;
//	fs.release();
//	remap(image_source1, image_map1, maplx, maply, INTER_LINEAR);
//	remap(image_source2, image_map2, maprx, mapry, INTER_LINEAR);
//	imwrite("image_map3.png", image_map1);
//
//	imwrite("image_map4.png", image_map2);
//
//
//	/*校正结果*/
//	Mat canvas;
//	double sf;
//	int w, h;
//	sf = 600. / MAX(image_size.width, image_size.height);
//	w = cvRound(image_size.width * sf);
//	h = cvRound(image_size.height * sf);
//	canvas.create(h, w * 2, CV_8UC1);
//
//	/*左图像画到画布上*/
//	Mat canvasPart1(canvas(Rect(w * 0, 0, w, h)));                                //得到画布的一部分  
//	resize(image_map1, canvasPart1, canvasPart1.size(), 0, 0, INTER_AREA);     //把图像缩放到跟canvasPart一样大小  
//	Rect vroiL(cvRound(validROIL.x*sf), cvRound(validROIL.y*sf),                //获得被截取的区域    
//	cvRound(validROIL.width*sf), cvRound(validROIL.height*sf));
//	//imshow("canvasPart1", canvas);
//	//waitKey(100);
//	//imwrite("canvas.png", canvas);
//	
//	//imwrite("canvasPart1.png", canvasPart1);
//	//rectangle(canvasPart1, vroiL, Scalar(0, 0, 255), 3, 8);                      //画上一个矩形  
//	//canvasPart1.copyTo(Mat(canvas, Rect(w * 0, 0, w, h)));
//	/*右图像画到画布上*/
//	Mat canvasPart2(canvas(Rect(w, 0, w, h)));                                      //获得画布的另一部分  
//	resize(image_map2, canvasPart2, canvasPart2.size(), 0, 0, INTER_LINEAR);
//	//imshow("canvasPart2", canvasPart2);
//	//imwrite("canvasPart2.png", canvasPart2);
//	Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y*sf),
//		cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
//	//rectangle(canvasPart2, vroiR, Scalar(0, 0, 255), 3, 8);
//	//canvasPart2.copyTo(Mat(canvas, Rect(w , 0, w, h)));
//
//	//cout << "Painted ImageR" << endl;
//
//	/*画上对应的线条*/
//	for (int i = 0; i < canvas.rows; i += 16)
//	{
//		line(canvasPart1, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
//		line(canvasPart2, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
//	}
//		
//	imwrite("rectified3.png", canvasPart1);
//    imwrite("rectified4.png", canvasPart2);
//	imshow("rectified1", canvasPart1);
//	
//     
//	waitKey(500);
//	imshow("rectified2", canvasPart2);
//	waitKey(500);
//
//	cout << "wait key" << endl;
//	waitKey(0);
//	
//
//	//imshow("image_map1.png", image_map1);
//	//waitKey(300);
//	//imshow("image_map2.png", image_map2);
//	//waitKey(300);
//	//imwrite("image_map1.png", image_map1);
//	//imwrite("image_map2.png", image_map2);
//
//
//
//
//	
//#endif // image_try
//	//system("pause");
//     return 0;
//}
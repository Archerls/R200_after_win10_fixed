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
//	ifstream fin1("calibdata.txt");   /* �궨����LEFTͼ���ļ���·�� */
//	ofstream fout1("caliberation_result.txt");  /* ����궨������ļ� */
//
//	ifstream fin2("calibdata2.txt"); /* �궨����RIGHTͼ���ļ���·�� */
//	ofstream fout2("caliberation_result2.txt");  /* ����궨������ļ� */
//
//												 //��ȡÿһ��ͼ�񣬴�����ȡ���ǵ㣬Ȼ��Խǵ���������ؾ�ȷ��	
//	cout << "��ʼ��ȡ�ǵ㡭����������";
//	int image_count = 0;  /* ͼ������ */
//	Size image_size;  /* ͼ��ĳߴ� */
//	Size board_size = Size(board_row, board_col);    /* �궨����ÿ�С��еĽǵ��� */
//	vector<Point2f> image_points_buf1;  /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */
//	vector<vector<Point2f>> image_points_seq1; /* �����⵽�����нǵ� */
//	vector<Point2f> image_points_buf2;  /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */
//	vector<vector<Point2f>> image_points_seq2; /* �����⵽�����нǵ� */
//	string filename1;
//	string filename2;
//	int count = -1;//���ڴ洢�ǵ������
//
//	while (getline(fin1, filename1) && getline(fin2, filename2))
//	{
//		image_count++;
//		// ���ڹ۲�������
//		cout << "image_count = " << image_count << endl;
//		/* �������*/
//		cout << "-->count = " << count;
//		Mat imageInput1 = imread(filename1);
//		Mat imageInput2 = imread(filename2);
//		if (image_count == 1)  //�����һ��ͼƬʱ��ȡͼ������Ϣ
//		{
//			image_size.width = imageInput1.cols;
//			image_size.height = imageInput1.rows;
//			cout << "image_size.width = " << image_size.width << endl;
//			cout << "image_size.height = " << image_size.height << endl;
//		}
//
//		/* ��ȡ����ͼ��Ľǵ� */
//		if (0 == findChessboardCorners(imageInput1, board_size, image_points_buf1, CV_CALIB_CB_ADAPTIVE_THRESH))
//		{
//			cout << "can not find chessboard corners in left image !\n"; //�Ҳ����ǵ�
//			getchar();
//			exit(1);
//		}
//		if (0 == findChessboardCorners(imageInput2, board_size, image_points_buf2, CV_CALIB_CB_ADAPTIVE_THRESH))
//		{
//			cout << "can not find chessboard corners in right image!\n"; //�Ҳ����ǵ�
//			getchar();
//			exit(1);
//		}
//
//		else
//		{
//			/*���������ǲ�ɫͼ������ת��Ϊ��ɫͼ��*/
//			Mat view_gray1;
//			Mat view_gray2;
//			cvtColor(imageInput1, view_gray1, CV_RGB2GRAY);
//			cvtColor(imageInput2, view_gray2, CV_RGB2GRAY);
//
//			/* �����ؾ�ȷ�� */
//			find4QuadCornerSubpix(view_gray1, image_points_buf1, Size(11, 11)); //�Դ���ȡ�Ľǵ���о�ȷ��
//			find4QuadCornerSubpix(view_gray2, image_points_buf2, Size(11, 11)); //�Դ���ȡ�Ľǵ���о�ȷ��
//			image_points_seq1.push_back(image_points_buf1);  //���������ؽǵ�
//			image_points_seq2.push_back(image_points_buf2);  //���������ؽǵ�
//
//															 /* ��ͼ������ʾ�ǵ�λ�� */
//			drawChessboardCorners(view_gray1, board_size, image_points_buf1, true); //������ͼƬ�б�ǽǵ�
//			drawChessboardCorners(view_gray2, board_size, image_points_buf2, true); //������ͼƬ�б�ǽǵ�
//			imshow("LEFT Camera Calibration", view_gray1);//��ʾͼƬ
//			imshow("RIGHT Camera Calibration", view_gray2);//��ʾͼƬ
//			waitKey(500);//��ͣ0.5S		
//		}
//	}
//	cv::destroyWindow("LEFT Camera Calibration");
//	cv::destroyWindow("RIGHT Camera Calibration");
//	int total = image_points_seq1.size();
//	cout << "total = " << total << endl;
//	int CornerNum = board_size.width*board_size.height;  //ÿ��ͼƬ���ܵĽǵ���
//	for (int ii = 0; ii<total; ii++)
//	{
//		if (0 == ii%CornerNum)
//		{
//			int i = -1;
//			i = ii / CornerNum;
//			int j = i + 1;
//			cout << "--> �� " << j << "ͼƬ������ --> : " << endl;
//		}
//		if (0 == ii % 3)
//		{
//			cout << endl;
//		}
//		else
//		{
//			cout.width(10);
//		}
//		//������еĽǵ�
//		cout << " left-->" << image_points_seq1[ii][0].x;
//		cout << " -->" << image_points_seq1[ii][0].y;
//		cout << " right-->" << image_points_seq2[ii][0].x;
//		cout << " -->" << image_points_seq2[ii][0].y;
//	}
//	cout << "�ǵ���ȡ��ɣ�\n";
//
//	//������������궨
//	cout << "��ʼ�궨������������";
//
//	/*������ά��Ϣ*/
//	Size2f square_size = Size2f(square_long, square_long);  /* ʵ�ʲ����õ��ı궨����ÿ�����̸�Ĵ�С */
//	vector<vector<Point3f>> object_points1;  /* ����궨���Ͻǵ����ά���� */
//	vector<vector<Point3f>> object_points2; /* ����궨���Ͻǵ����ά���� */
//
//	/*�������*/
//	Mat cameraMatrix1 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* LEFT������ڲ������� */
//	Mat cameraMatrix2 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* RIGHT������ڲ������� */
//	vector<int> point_counts;  // ÿ��ͼ���нǵ������
//	Mat distCoeffs1 = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* LEFT�������5������ϵ����k1,k2,p1,p2,k3 */
//	Mat distCoeffs2 = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* RIGHT�������5������ϵ����k1,k2,p1,p2,k3 */
//	vector<Mat> tvecsMat1;  /* ÿ��LEFTͼ�����ת���� */
//	vector<Mat> tvecsMat2;  /* ÿ��RIGHTͼ�����ת���� */
//	vector<Mat> rvecsMat1; /* ÿ��LEFTͼ���ƽ������ */
//	vector<Mat> rvecsMat2; /* ÿ��RIGHTͼ���ƽ������ */
//
//						   /* ��ʼ���궨���Ͻǵ����ά���� */
//	int i, j, t;
//	for (t = 0; t<image_count; t++)
//	{
//		vector<Point3f> tempPointSet;
//		for (i = 0; i<board_size.height; i++)
//		{
//			for (j = 0; j<board_size.width; j++)
//			{
//				Point3f realPoint;
//				/* ����궨�������������ϵ��z=0��ƽ���� */
//				realPoint.x = i*square_size.width;
//				realPoint.y = j*square_size.height;
//				realPoint.z = 0;
//				tempPointSet.push_back(realPoint);
//			}
//		}
//		object_points1.push_back(tempPointSet);
//		object_points2.push_back(tempPointSet);
//	}
//	/* ��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨�� */
//	for (i = 0; i<image_count; i++)
//	{
//		point_counts.push_back(board_size.width*board_size.height);
//	}
//	/* ��ʼ�궨 */
//	calibrateCamera(object_points1, image_points_seq1, image_size, cameraMatrix1, distCoeffs1, rvecsMat1, tvecsMat1, 0);
//	calibrateCamera(object_points2, image_points_seq2, image_size, cameraMatrix2, distCoeffs2, rvecsMat2, tvecsMat2, 0);
//	cout << "�궨��ɣ�\n";
//	//�Ա궨�����������
//	cout << "��ʼ���۱궨���������������\n";
//	double total_err1 = 0.0; /* ����ͼ���ƽ�������ܺ� */
//	double total_err2 = 0.0; /* ����ͼ���ƽ�������ܺ� */
//	double err1 = 0.0; /* ÿ��ͼ���ƽ����� */
//	double err2 = 0.0; /* ÿ��ͼ���ƽ����� */
//	vector<Point2f> image_points1_2; /* �������¼���õ���ͶӰ�� */
//	vector<Point2f> image_points2_2; /* �������¼���õ���ͶӰ�� */
//	cout << "\tÿ��ͼ��ı궨��\n";
//	fout1 << "ÿ��ͼ��ı궨��\n";
//	fout2 << "ÿ��ͼ��ı궨��\n";
//	for (i = 0; i<image_count; i++)
//	{
//		vector<Point3f> tempPointSet1 = object_points1[i];
//		vector<Point3f> tempPointSet2 = object_points2[i];
//		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
//		projectPoints(tempPointSet1, rvecsMat1[i], tvecsMat1[i], cameraMatrix1, distCoeffs1, image_points1_2);
//		projectPoints(tempPointSet2, rvecsMat2[i], tvecsMat2[i], cameraMatrix2, distCoeffs2, image_points2_2);
//		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
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
//		std::cout << "left��" << i + 1 << "��ͼ���ƽ����" << err1 << "����" << endl;
//		std::cout << "right��" << i + 1 << "��ͼ���ƽ����" << err2 << "����" << endl;
//		fout1 << "��" << i + 1 << "��ͼ���ƽ����" << err1 << "����" << endl;
//		fout2 << "��" << i + 1 << "��ͼ���ƽ����" << err2 << "����" << endl;
//	}
//	std::cout << "left����ƽ����" << total_err1 / image_count << "����" << endl;
//	std::cout << "right����ƽ����" << total_err2 / image_count << "����" << endl;
//	fout1 << "����ƽ����" << total_err1 / image_count << "����" << endl << endl;
//	fout2 << "����ƽ����" << total_err2 / image_count << "����" << endl << endl;
//	std::cout << "������ɣ�" << endl;
//	//���涨����  	
//	std::cout << "��ʼ���涨����������������" << endl;
//	Mat rotation_matrix1 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
//	Mat rotation_matrix2 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
//	fout1 << "����ڲ�������" << endl;
//	fout1 << cameraMatrix1 << endl << endl;
//	fout1 << "����ϵ����\n";
//	fout1 << distCoeffs1 << endl << endl << endl;
//
//	fout2 << "����ڲ�������" << endl;
//	fout2 << cameraMatrix2 << endl << endl;
//	fout2 << "����ϵ����\n";
//	fout2 << distCoeffs2 << endl << endl << endl;
//
//	for (int i = 0; i<image_count; i++)
//	{
//		fout1 << "��" << i + 1 << "��ͼ�����ת������" << endl;
//		fout1 << tvecsMat1[i] << endl;
//		/* ����ת����ת��Ϊ���Ӧ����ת���� */
//		Rodrigues(tvecsMat1[i], rotation_matrix1);
//		fout1 << "��" << i + 1 << "��ͼ�����ת����" << endl;
//		fout1 << rotation_matrix1 << endl;
//		fout1 << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
//		fout1 << rvecsMat1[i] << endl << endl;
//
//		fout2 << "��" << i + 1 << "��ͼ�����ת������" << endl;
//		fout2 << tvecsMat2[i] << endl;
//		/* ����ת����ת��Ϊ���Ӧ����ת���� */
//		Rodrigues(tvecsMat2[i], rotation_matrix2);
//		fout2 << "��" << i + 1 << "��ͼ�����ת����" << endl;
//		fout2 << rotation_matrix2 << endl;
//		fout2 << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
//		fout2 << rvecsMat2[i] << endl << endl;
//	}
//	std::cout << "��ɱ���" << endl;
//	fout1 << endl;
//#ifndef image_try
//
//	/*��Ŀ�궨�������,��ʼ����궨*/
//
//	/*	vector<Size> npoints;
//	for (int i = 0; i < image_count; i++)
//	{
//	npoints.push_back(board_size);
//	}*/
//	Mat R;  //��ת����
//	Mat T;  //ƽ�ƾ���
//	Mat E;  //��������
//	Mat F;  //��������
//
//	stereoCalibrate(object_points1, image_points_seq1, image_points_seq2, cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2, image_size, R, T, E, F, CALIB_FIX_INTRINSIC, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 100, 1e-5));
//	ofstream fout_steroCali("sterocali_result.txt");
//	fout_steroCali << "��ת����" << endl;
//	fout_steroCali << R << endl;
//	fout_steroCali << "ƽ�ƾ���" << endl;
//	//T = -1 * T;
//	fout_steroCali << T << endl;
//
//	/*����У��*/
//	Mat Rl;   //����ת����
//	Mat Rr;   //����ת����
//	Mat Pl;   //��ͶӰ����
//	Mat Pr;   //��ͶӰ����
//	Mat Q;    //��ͶӰ����
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
///*����ӳ��*/
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
//	/*У�����*/
//	Mat canvas;
//	double sf;
//	int w, h;
//	sf = 600. / MAX(image_size.width, image_size.height);
//	w = cvRound(image_size.width * sf);
//	h = cvRound(image_size.height * sf);
//	canvas.create(h, w * 2, CV_8UC1);
//
//	/*��ͼ�񻭵�������*/
//	Mat canvasPart1(canvas(Rect(w * 0, 0, w, h)));                                //�õ�������һ����  
//	resize(image_map1, canvasPart1, canvasPart1.size(), 0, 0, INTER_AREA);     //��ͼ�����ŵ���canvasPartһ����С  
//	Rect vroiL(cvRound(validROIL.x*sf), cvRound(validROIL.y*sf),                //��ñ���ȡ������    
//	cvRound(validROIL.width*sf), cvRound(validROIL.height*sf));
//	//imshow("canvasPart1", canvas);
//	//waitKey(100);
//	//imwrite("canvas.png", canvas);
//	
//	//imwrite("canvasPart1.png", canvasPart1);
//	//rectangle(canvasPart1, vroiL, Scalar(0, 0, 255), 3, 8);                      //����һ������  
//	//canvasPart1.copyTo(Mat(canvas, Rect(w * 0, 0, w, h)));
//	/*��ͼ�񻭵�������*/
//	Mat canvasPart2(canvas(Rect(w, 0, w, h)));                                      //��û�������һ����  
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
//	/*���϶�Ӧ������*/
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
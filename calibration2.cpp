#include <stdafx.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#define board_row 12
#define board_col 11
//#define image_try
using namespace cv;
using namespace std;

void main()
{
	ifstream fin("calibdata.txt");   /* �궨����LEFTͼ���ļ���·�� */
	ofstream fout("caliberation_result.txt");  /* ����궨������ļ� */
											   
	ifstream fin2("calibdata2.txt"); /* �궨����RIGHTͼ���ļ���·�� */
	ofstream fout2("caliberation_result2.txt");  /* ����궨������ļ� */

    //��ȡÿһ��ͼ�񣬴�����ȡ���ǵ㣬Ȼ��Խǵ���������ؾ�ȷ��	
	cout << "��ʼ��ȡ�ǵ㡭����������";
	int image_count = 0;  /* ͼ������ */
	Size image_size;  /* ͼ��ĳߴ� */
	Size board_size = Size(board_row, board_col);    /* �궨����ÿ�С��еĽǵ��� */
	vector<Point2f> image_points_buf;  /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */
	vector<vector<Point2f>> image_points_seq; /* �����⵽�����нǵ� */
	vector<Point2f> image_points_buf2;  /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */
	vector<vector<Point2f>> image_points_seq2; /* �����⵽�����нǵ� */
	string filename;
	string filename2;
	int count = -1;//���ڴ洢�ǵ������

	while (getline(fin, filename)&& getline(fin2, filename2))
	{
		image_count++;
		// ���ڹ۲�������
		cout << "image_count = " << image_count << endl;
		/* �������*/
		cout << "-->count = " << count;
		Mat imageInput = imread(filename);
		Mat imageInput2 = imread(filename2);
		if (image_count == 1)  //�����һ��ͼƬʱ��ȡͼ������Ϣ
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			cout << "image_size.width = " << image_size.width << endl;
			cout << "image_size.height = " << image_size.height << endl;
		}

		/* ��ȡ����ͼ��Ľǵ� */
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf, CV_CALIB_CB_ADAPTIVE_THRESH))
		{
			cout << "can not find chessboard corners in left image !\n"; //�Ҳ����ǵ�
			getchar();
			exit(1);
		}
		if (0 == findChessboardCorners(imageInput2, board_size, image_points_buf2, CV_CALIB_CB_ADAPTIVE_THRESH))
		{
			cout << "can not find chessboard corners in right image!\n"; //�Ҳ����ǵ�
			getchar();
			exit(1);
		}
		
		else
		{
			/*���������ǲ�ɫͼ������ת��Ϊ��ɫͼ��*/
			Mat view_gray;
			Mat view_gray2;
			cvtColor(imageInput, view_gray, CV_RGB2GRAY);
			cvtColor(imageInput2, view_gray2, CV_RGB2GRAY);

			/* �����ؾ�ȷ�� */
			find4QuadCornerSubpix(view_gray, image_points_buf, Size(11, 11)); //�Դ���ȡ�Ľǵ���о�ȷ��
			find4QuadCornerSubpix(view_gray2, image_points_buf2, Size(11, 11)); //�Դ���ȡ�Ľǵ���о�ȷ��
			image_points_seq.push_back(image_points_buf);  //���������ؽǵ�
			image_points_seq2.push_back(image_points_buf2);  //���������ؽǵ�

			/* ��ͼ������ʾ�ǵ�λ�� */
			drawChessboardCorners(view_gray, board_size, image_points_buf, true); //������ͼƬ�б�ǽǵ�
			drawChessboardCorners(view_gray2, board_size, image_points_buf2, true); //������ͼƬ�б�ǽǵ�
			imshow("LEFT Camera Calibration", view_gray);//��ʾͼƬ
			imshow("RIGHT Camera Calibration", view_gray2);//��ʾͼƬ
			waitKey(500);//��ͣ0.5S		
		}
	}
	int total = image_points_seq.size();
	cout << "total = " << total << endl;
	int CornerNum = board_size.width*board_size.height;  //ÿ��ͼƬ���ܵĽǵ���
	for (int ii = 0; ii<total; ii++)
	{
		if (0 == ii%CornerNum)
		{
			int i = -1;
			i = ii / CornerNum;
			int j = i + 1;
			cout << "--> �� " << j << "ͼƬ������ --> : " << endl;
		}
		if (0 == ii % 3)
		{
			cout << endl;
		}
		else
		{
			cout.width(10);
		}
		//������еĽǵ�
		cout << " left-->" << image_points_seq[ii][0].x;
		cout << " -->" << image_points_seq[ii][0].y;
		cout << " right-->" << image_points_seq2[ii][0].x;
		cout << " -->" << image_points_seq2[ii][0].y;
	}
	cout << "�ǵ���ȡ��ɣ�\n";

	//������������궨
	cout << "��ʼ�궨������������";

	/*������ά��Ϣ*/
	Size2f square_size = Size2f(0.6, 0.6);  /* ʵ�ʲ����õ��ı궨����ÿ�����̸�Ĵ�С */
	vector<vector<Point3f>> object_points; /* ����궨���Ͻǵ����ά���� */
	vector<vector<Point3f>> object_points2; /* ����궨���Ͻǵ����ά���� */

	/*�������*/
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* LEFT������ڲ������� */
	Mat cameraMatrix2 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* RIGHT������ڲ������� */
	vector<int> point_counts;  // ÿ��ͼ���нǵ������
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* LEFT�������5������ϵ����k1,k2,p1,p2,k3 */
	Mat distCoeffs2 = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* RIGHT�������5������ϵ����k1,k2,p1,p2,k3 */
	vector<Mat> tvecsMat;  /* ÿ��LEFTͼ�����ת���� */
	vector<Mat> tvecsMat2;  /* ÿ��RIGHTͼ�����ת���� */
	vector<Mat> rvecsMat; /* ÿ��LEFTͼ���ƽ������ */
	vector<Mat> rvecsMat2; /* ÿ��RIGHTͼ���ƽ������ */

	/* ��ʼ���궨���Ͻǵ����ά���� */
	int i, j, t;
	for (t = 0; t<image_count; t++)
	{
		vector<Point3f> tempPointSet;
		for (i = 0; i<board_size.height; i++)
		{
			for (j = 0; j<board_size.width; j++)
			{
				Point3f realPoint;
				/* ����궨�������������ϵ��z=0��ƽ���� */
				realPoint.x = i*square_size.width;
				realPoint.y = j*square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
		object_points2.push_back(tempPointSet);
	}
	/* ��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨�� */
	for (i = 0; i<image_count; i++)
	{
		point_counts.push_back(board_size.width*board_size.height);
	}
	/* ��ʼ�궨 */
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);
	calibrateCamera(object_points2, image_points_seq2, image_size, cameraMatrix2, distCoeffs2, rvecsMat2, tvecsMat2, 0);
	cout << "�궨��ɣ�\n";
	//�Ա궨�����������
	cout << "��ʼ���۱궨���������������\n";
	double total_err = 0.0; /* ����ͼ���ƽ�������ܺ� */
	double total_err2 = 0.0; /* ����ͼ���ƽ�������ܺ� */
	double err = 0.0; /* ÿ��ͼ���ƽ����� */
	double err2 = 0.0; /* ÿ��ͼ���ƽ����� */
	vector<Point2f> image_points_2; /* �������¼���õ���ͶӰ�� */
	vector<Point2f> image_points2_2; /* �������¼���õ���ͶӰ�� */
	cout << "\tÿ��ͼ��ı궨��\n";
	fout << "ÿ��ͼ��ı궨��\n";
	fout2 << "ÿ��ͼ��ı궨��\n";
	for (i = 0; i<image_count; i++)
	{
		vector<Point3f> tempPointSet = object_points[i];
		vector<Point3f> tempPointSet2 = object_points[i];
		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points_2);
		projectPoints(tempPointSet2, rvecsMat2[i], tvecsMat2[i], cameraMatrix2, distCoeffs2, image_points2_2);
		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
		vector<Point2f> tempImagePoint = image_points_seq[i];
		vector<Point2f> tempImagePoint2 = image_points_seq2[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		Mat tempImagePoint2Mat = Mat(1, tempImagePoint2.size(), CV_32FC2);
		Mat image_points_2Mat = Mat(1, image_points_2.size(), CV_32FC2);
		Mat image_points2_2Mat = Mat(1, image_points2_2.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points_2Mat.at<Vec2f>(0, j) = Vec2f(image_points_2[j].x, image_points_2[j].y);
			image_points2_2Mat.at<Vec2f>(0, j) = Vec2f(image_points2_2[j].x, image_points2_2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
			tempImagePoint2Mat.at<Vec2f>(0, j) = Vec2f(tempImagePoint2[j].x, tempImagePoint2[j].y);
		}
		err = norm(image_points_2Mat, tempImagePointMat, NORM_L2);
		err2 = norm(image_points2_2Mat, tempImagePoint2Mat, NORM_L2);
		total_err += err /= point_counts[i];
		total_err2 += err2 /= point_counts[i];
		std::cout << "left��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
		std::cout << "right��" << i + 1 << "��ͼ���ƽ����" << err2 << "����" << endl;
		fout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
		fout2 << "��" << i + 1 << "��ͼ���ƽ����" << err2 << "����" << endl;
	}
	std::cout << "left����ƽ����" << total_err / image_count << "����" << endl;
	std::cout << "right����ƽ����" << total_err2 / image_count << "����" << endl;
	fout << "����ƽ����" << total_err / image_count << "����" << endl << endl;
	fout2 << "����ƽ����" << total_err2 / image_count << "����" << endl << endl;
	std::cout << "������ɣ�" << endl;
	//���涨����  	
	std::cout << "��ʼ���涨����������������" << endl;
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
	Mat rotation_matrix2 = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
	fout << "����ڲ�������" << endl;
	fout << cameraMatrix << endl << endl;
	fout << "����ϵ����\n";
	fout << distCoeffs << endl << endl << endl;

	fout2 << "����ڲ�������" << endl;
	fout2 << cameraMatrix2 << endl << endl;
	fout2 << "����ϵ����\n";
	fout2<< distCoeffs2 << endl << endl << endl;

	for (int i = 0; i<image_count; i++)
	{
		fout << "��" << i + 1 << "��ͼ�����ת������" << endl;
		fout << tvecsMat[i] << endl;
		/* ����ת����ת��Ϊ���Ӧ����ת���� */
		Rodrigues(tvecsMat[i], rotation_matrix);
		fout << "��" << i + 1 << "��ͼ�����ת����" << endl;
		fout << rotation_matrix << endl;
		fout << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
		fout << rvecsMat[i] << endl << endl;

		fout2 << "��" << i + 1 << "��ͼ�����ת������" << endl;
		fout2 << tvecsMat2[i] << endl;
		/* ����ת����ת��Ϊ���Ӧ����ת���� */
		Rodrigues(tvecsMat2[i], rotation_matrix2);
		fout2 << "��" << i + 1 << "��ͼ�����ת����" << endl;
		fout2 << rotation_matrix2 << endl;
		fout2 << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
		fout2 << rvecsMat2[i] << endl << endl;
	}
	std::cout << "��ɱ���" << endl;
	fout << endl;
#ifndef image_try

	/*��Ŀ�궨�������,��ʼ����궨*/

/*	vector<Size> npoints;
	for (int i = 0; i < image_count; i++)
	{
		npoints.push_back(board_size);
	}*/
	Mat R;
	Mat T;
	Mat E;
	Mat F;
	
	stereoCalibrate(object_points, image_points_seq, image_points_seq2, cameraMatrix, distCoeffs,cameraMatrix2,distCoeffs2,image_size,R,T,E,F);
	ofstream fout_steroCali("sterocali_result.txt");
	fout_steroCali << "��ת����" << endl;
	fout_steroCali << R << endl;
	fout_steroCali << "ƽ�ƾ���" << endl;
	fout_steroCali << T << endl;
#endif // image_try
	system("pause");
	return;
}
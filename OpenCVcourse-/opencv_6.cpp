#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//////////color Detection//////////////////

//Mat imgHSV, mask, imgColor;
//int hmin = 0, smin = 110, vmin = 153;
//int hmax = 19, smax = 240, vmax = 255;

//void main()
//{
//	string path = "Resources/lambo.png";//����ͼƬ·��
//	//string path = "Resources/shapes.png";//���������ͼ����Ѱ�Ҳ�ͬ��ɫ�ķ�Χ
//	Mat img = imread(path);//�������������ͼƬ
//
//	cvtColor(img, imgHSV, COLOR_BGR2HSV);//��BGRͼƬת��Ϊhsv,��ɫ�ռ���ڼ����ɫ��hɫ��,s���Ͷȣ�v����
//
//	namedWindow("Trackbars", (640, 200)); // ����window����
//	createTrackbar("Hue Min", "Trackbars", &hmin, 179);//������������������ֵ������������Ϊ��ʼֵ�����ĸ�Ϊ���ֵ
//	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
//	createTrackbar("Sat Min", "Trackbars", &smin, 255);
//	createTrackbar("Sat Max", "Trackbars", &smax, 255);
//	createTrackbar("Val Min", "Trackbars", &vmin, 255);
//	createTrackbar("Val Max", "Trackbars", &vmax, 255);
//
//	while (true)
//	{
//		Scalar lower(hmin, smin, vmin);//������ͨ��������ֵ�ķ�Χ����
//		Scalar upper(hmax, smax, vmax);
//
//		inRange(imgHSV, lower, upper, mask);//��ֵ�����ã�����Χ�ڵ���ɫ����Ϊ��ɫ��֮��Ϊ��ɫ
//
//
//		imshow("image", img);
//		imshow("image HSV", imgHSV);
//		imshow("Mask", mask);
//		waitKey(1);//����Ļ����ʱ���Ϊ1���룬�Ա�֤�������϶�ͼ��ˢ��
//	}
//}



	/// ///////////��������ͷͼ���ֵ��////////////////////////
	
	void main()
	{
		VideoCapture cap(1);//��������ͷ
		Mat img;
		Mat imgHSV, mask, imgColor;
		int hmin = 0, smin = 0, vmin = 0;
		int hmax = 25, smax = 255, vmax = 255;

		namedWindow("Trackbars", (640, 200)); // ����window����
		createTrackbar("Hue Min", "Trackbars", &hmin, 255);//������������������ֵ������������Ϊ��ʼֵ�����ĸ�Ϊ���ֵ
		createTrackbar("Hue Max", "Trackbars", &hmax, 255);
		createTrackbar("Sat Min", "Trackbars", &smin, 255);
		createTrackbar("Sat Max", "Trackbars", &smax, 255);
		createTrackbar("Val Min", "Trackbars", &vmin, 255);
		createTrackbar("Val Max", "Trackbars", &vmax, 255);

		while (true)
		{
			cap.read(img);
			cvtColor(img, imgHSV, COLOR_BGR2HSV);

			Scalar lower(hmin, smin, vmin);
			Scalar upper(hmax, smax, vmax);

			inRange(imgHSV, lower, upper, mask);
			// hmin, smin, vmin, hmax, smax, vmax;
			//cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
			imshow("Image", img);
			imshow("Mask", mask);
			waitKey(1);
		}
	
	}

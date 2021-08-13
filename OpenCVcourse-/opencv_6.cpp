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
//	string path = "Resources/lambo.png";//设置图片路径
//	//string path = "Resources/shapes.png";//可以用这个图尝试寻找不同颜色的范围
//	Mat img = imread(path);//定义变量并导入图片
//
//	cvtColor(img, imgHSV, COLOR_BGR2HSV);//将BGR图片转化为hsv,颜色空间便于检查颜色，h色调,s饱和度，v亮度
//
//	namedWindow("Trackbars", (640, 200)); // 创造window窗口
//	createTrackbar("Hue Min", "Trackbars", &hmin, 179);//创建滚动条，调节阈值，第三个参数为初始值，第四个为最大值
//	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
//	createTrackbar("Sat Min", "Trackbars", &smin, 255);
//	createTrackbar("Sat Max", "Trackbars", &smax, 255);
//	createTrackbar("Val Min", "Trackbars", &vmin, 255);
//	createTrackbar("Val Max", "Trackbars", &vmax, 255);
//
//	while (true)
//	{
//		Scalar lower(hmin, smin, vmin);//定义三通道的像素值的范围下限
//		Scalar upper(hmax, smax, vmax);
//
//		inRange(imgHSV, lower, upper, mask);//二值化作用，将范围内的颜色定义为白色，之外为灰色
//
//
//		imshow("image", img);
//		imshow("image HSV", imgHSV);
//		imshow("Mask", mask);
//		waitKey(1);//把屏幕出现时间调为1毫秒，以保证滚动条拖动图像刷新
//	}
//}



	/// ///////////网络摄像头图像二值化////////////////////////
	
	void main()
	{
		VideoCapture cap(1);//设置摄像头
		Mat img;
		Mat imgHSV, mask, imgColor;
		int hmin = 0, smin = 0, vmin = 0;
		int hmax = 25, smax = 255, vmax = 255;

		namedWindow("Trackbars", (640, 200)); // 创造window窗口
		createTrackbar("Hue Min", "Trackbars", &hmin, 255);//创建滚动条，调节阈值，第三个参数为初始值，第四个为最大值
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

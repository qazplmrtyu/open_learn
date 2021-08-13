#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////Basic function///////////////////灰度转化，模糊处理，边缘检测，膨胀，腐蚀，
void main()
{
	string path = "Resources/test.png";//设置图片路径
	Mat img = imread(path);//定义变量
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	cvtColor(img,imgGray, COLOR_BGR2GRAY);//灰度转化
	GaussianBlur(imgGray, imgBlur, Size(3,3), 3, 0);//size是高斯核大小，越小，模糊度越低
	Canny(imgBlur, imgCanny,50,100);//先模糊处理，再kanye边缘检测 。两个阈值越小，边缘线越多

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//使用结构成员定义膨胀内核的形状与大小
	dilate(imgCanny,imgDil,kernel);//用内核进行膨胀
	erode(imgDil, imgErode, kernel);//膨胀后腐蚀


	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny); 
	imshow("Image Dialation", imgDil);
	imshow("Image Erode", imgErode);

	waitKey(0);

}

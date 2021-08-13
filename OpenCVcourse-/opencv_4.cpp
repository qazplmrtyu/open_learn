#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////Draw Shapes and Text///////////////////
void main()
{
	//定义空白图片，大小，每点像素值八位无符号且颜色通道为三个，BGR值
	Mat img(512, 512,CV_8UC3,Scalar(255,255,255));
	
	//画圆，定义圆的位置，大小，颜色，厚度,填充时厚度改为FILLED
	circle(img, Point(256, 256),155, Scalar(0, 69, 255),FILLED);
	rectangle(img, Point(130,226), Point(382,286),Scalar(255,255,255));	//矩形
	line(img, Point(130, 296), Point(382, 450), Scalar(255, 255, 255));	//直线

	putText(img, "黄腾", Point(137, 262), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 69, 225));


	imshow("Image", img);
	
	waitKey(0);

}

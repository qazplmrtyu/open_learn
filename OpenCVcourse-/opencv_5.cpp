#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

float w = 250, h = 350;
Mat matrix, imgWrap;
////////Wrap image//////////////////
void main()
{
	
	string path = "Resources/cards.jpg";//设置图片路径
	Mat img = imread(path);//定义变量并导入图片

	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };//四个二维的浮点数坐标构成一个数组
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };//目标图像的四个坐标点
	
	matrix = getPerspectiveTransform(src, dst);//定义透视变化的矩阵
	warpPerspective (img, imgWrap,matrix,Point(w,h));//将图像扶正

	for(int i=0; i < 4;i++ )//循环画圆，标记四个点
	{
		circle(img, src[i],10, Scalar(0, 0, 255),FILLED); 
	}
	imshow("image", img);
	imshow("image Wrap", imgWrap);
	waitKey(0);//等待时间无限长

}

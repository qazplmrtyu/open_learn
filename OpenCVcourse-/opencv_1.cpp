#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////image///////////////////
//void main()
//{
//	string path = "Resources/test.png";//设置图片路径
//	Mat img = imread(path);//定义变量并导入图片
//	imshow("image", img);
//	waitKey(0);//等待时间无限长
//
//}

////////video///////////////////
//void main()
//{
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true)
//	{
//		cap.read(img);
//		imshow("image", img);
//		waitKey(100);
//
//	}
//}


////////webcam///////////////////
void main()
{
	
	VideoCapture cap(0);
	Mat img;

	while (true)
	{
		cap.read(img);
		imshow("image", img);
		waitKey(10);

	}
}
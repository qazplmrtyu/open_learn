#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////image///////////////////
//void main()
//{
//	string path = "Resources/test.png";//����ͼƬ·��
//	Mat img = imread(path);//�������������ͼƬ
//	imshow("image", img);
//	waitKey(0);//�ȴ�ʱ�����޳�
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
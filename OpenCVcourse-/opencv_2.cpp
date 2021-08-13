#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////Basic function///////////////////�Ҷ�ת����ģ��������Ե��⣬���ͣ���ʴ��
void main()
{
	string path = "Resources/test.png";//����ͼƬ·��
	Mat img = imread(path);//�������
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	cvtColor(img,imgGray, COLOR_BGR2GRAY);//�Ҷ�ת��
	GaussianBlur(imgGray, imgBlur, Size(3,3), 3, 0);//size�Ǹ�˹�˴�С��ԽС��ģ����Խ��
	Canny(imgBlur, imgCanny,50,100);//��ģ��������kanye��Ե��� ��������ֵԽС����Ե��Խ��

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//ʹ�ýṹ��Ա���������ں˵���״���С
	dilate(imgCanny,imgDil,kernel);//���ں˽�������
	erode(imgDil, imgErode, kernel);//���ͺ�ʴ


	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny); 
	imshow("Image Dialation", imgDil);
	imshow("Image Erode", imgErode);

	waitKey(0);

}

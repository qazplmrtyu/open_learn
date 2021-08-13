#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////Draw Shapes and Text///////////////////
void main()
{
	//����հ�ͼƬ����С��ÿ������ֵ��λ�޷�������ɫͨ��Ϊ������BGRֵ
	Mat img(512, 512,CV_8UC3,Scalar(255,255,255));
	
	//��Բ������Բ��λ�ã���С����ɫ�����,���ʱ��ȸ�ΪFILLED
	circle(img, Point(256, 256),155, Scalar(0, 69, 255),FILLED);
	rectangle(img, Point(130,226), Point(382,286),Scalar(255,255,255));	//����
	line(img, Point(130, 296), Point(382, 450), Scalar(255, 255, 255));	//ֱ��

	putText(img, "����", Point(137, 262), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 69, 225));


	imshow("Image", img);
	
	waitKey(0);

}

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
	
	string path = "Resources/cards.jpg";//����ͼƬ·��
	Mat img = imread(path);//�������������ͼƬ

	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };//�ĸ���ά�ĸ��������깹��һ������
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };//Ŀ��ͼ����ĸ������
	
	matrix = getPerspectiveTransform(src, dst);//����͸�ӱ仯�ľ���
	warpPerspective (img, imgWrap,matrix,Point(w,h));//��ͼ�����

	for(int i=0; i < 4;i++ )//ѭ����Բ������ĸ���
	{
		circle(img, src[i],10, Scalar(0, 0, 255),FILLED); 
	}
	imshow("image", img);
	imshow("image Wrap", imgWrap);
	waitKey(0);//�ȴ�ʱ�����޳�

}

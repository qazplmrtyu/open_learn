#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////Resize and Crop///////////////////
void main()
{
	string path = "Resources/test.png";//����ͼƬ·��
	Mat img = imread(path);//�������������ͼƬ
	Mat imgResize,imgCrop;
	
	//cout << img.size() << endl;//���ͼ���С
	//resize(img, imgResize, Size(640,480));//����������С
	resize(img, imgResize, Size(),0.5,0.5);//���ձ�����С
	
	Rect roi(200, 80, 300, 320);//����ü����ε����Ͻ�x,y����Ϳ�ȼ�����
	imgCrop = img(roi);


	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);

	waitKey(0);

}

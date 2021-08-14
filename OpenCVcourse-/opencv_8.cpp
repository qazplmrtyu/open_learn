#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////image///////////////////
void main()
{
	string path = "Resources/test.png";//����ͼƬ·��
	Mat img = imread(path);//�������������ͼƬ

	CascadeClassifier faceCascade;//����������
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");//xml�ļ�Ϊѵ���õ�ģ��

	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }//дΪ�գ�����Ƿ���ȷ����

	vector<Rect> faces;//�þ����������ṹ�壩�洢�����߽��
	faceCascade.detectMultiScale(img, faces, 1.1, 10);//���������������߶ȷ���

	for (int i = 0; i < faces.size(); i++)//������������
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	imshow("image", img);
	waitKey(0);//�ȴ�ʱ�����޳�

}

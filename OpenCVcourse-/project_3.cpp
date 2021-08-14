#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////// Project 3 ����ʶ�� //////////////////////

void main() 
{

	Mat img;
	VideoCapture cap(1);

	CascadeClassifier plateCascade;//����һ������������ 
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");//xml�ļ�Ϊѵ���õ�ģ��
	//·�������пո�
	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }//дΪ�գ�����Ƿ���ȷ����

	vector<Rect> plates;//�þ��������洢��ǳ���

	while (true)//ѭ��
	{

		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/Plates/ " + to_string(i) + ".png", imgCrop);//�洢���ļ��У�·��+�ļ����֣�д���ͼƬ
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);
		waitKey(1);
	}
}
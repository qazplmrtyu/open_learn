#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////// Project 3 车牌识别 //////////////////////

void main() 
{

	Mat img;
	VideoCapture cap(1);

	CascadeClassifier plateCascade;//定义一个级联分类器 
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");//xml文件为训练好的模型
	//路径不能有空格
	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }//写为空，检测是否正确加载

	vector<Rect> plates;//用矩形向量存储标记车牌

	while (true)//循环
	{

		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/Plates/ " + to_string(i) + ".png", imgCrop);//存储进文件夹，路径+文件名字，写入的图片
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);
		waitKey(1);
	}
}
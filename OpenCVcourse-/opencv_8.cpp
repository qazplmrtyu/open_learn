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
	string path = "Resources/test.png";//设置图片路径
	Mat img = imread(path);//定义变量并导入图片

	CascadeClassifier faceCascade;//级联分类器
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");//xml文件为训练好的模型

	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }//写为空，检测是否正确加载

	vector<Rect> faces;//用矩形向量（结构体）存储人脸边界框
	faceCascade.detectMultiScale(img, faces, 1.1, 10);//用人脸级联点检测多尺度方法

	for (int i = 0; i < faces.size(); i++)//遍历人脸画框
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	imshow("image", img);
	waitKey(0);//等待时间无限长

}

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int area;
int i;
string objectType;

//�������
void getContours(Mat imgDil, Mat img) 
{

	vector<vector<Point>> contours;//vector�����������ƶ���һ����֪����С�Ķ�̬����
	vector<Vec4i> hierarchy;//������ÿһ��Ԫ�ذ�����4��int�ͱ���

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//Ѱ��ͼ������
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//����ͼ������

	/*vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());*/

	///�鿴��������������ض�����
	for (int i = 0; i < contours.size(); i++)//������������
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//ȡ��ÿ��������������
	
		vector<vector<Point>> conPoly(contours.size());//���������ǵ����飬��С����������һ��
		vector<Rect> boundRect(contours.size());//�����������α߽�����

	
		if (area > 1000) ///�������С����������
		{
			float peri = arcLength(contours[i], true);//���������ĳ��ȣ������boolֵ�������������Ƿ�պ���Ϊtrue ���������߱պ�
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//ͨ���ǵ���������߽��н���
			

			cout << conPoly[i].size() << endl;//��ӡÿ�������ǵ���Ŀ
			//boundRect[i] = boundingRect(conPoly[i]);//���α߽�
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0),5);//ͨ���������µ���ƾ���
		}
		int objCor = (int)conPoly[i].size();

		if (objCor == 3) { objectType = "Tri"; }
		 if (objCor == 4) { objectType = "Rect"; }
		/*{
			float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
			cout << aspRatio << endl;
			if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
			else { objectType = "Rect"; }
		}*/
		 if (objCor > 4) { objectType = "Circle"; }

		drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//�����ǵ�����
		rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0),5);//ͨ���������µ���ƾ���
		putText(img, objectType, { boundRect[i].x,boundRect[i].y-5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
	}

	
}

//////��ͼ��Ԥ����Ѱ������///////////////////
void main()
{
	string path = "Resources/shapes.png";//����ͼƬ·��
	Mat img = imread(path);//�������������ͼƬ
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	
	//ͼ��Ԥ����
	cvtColor(img, imgGray, COLOR_BGR2GRAY);//�Ҷ�ת��
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);//size�Ǹ�˹�˴�С��ԽС��ģ����Խ��
	Canny(imgBlur, imgCanny, 50, 100);//��ģ��������kanye��Ե��� ��������ֵԽС����Ե��Խ��
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//ʹ�ýṹ��Ա���������ں˵���״���С
	dilate(imgCanny, imgDil, kernel);//���ں˽�������
	
	getContours(imgDil, img);
	 
	imshow("image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dialation", imgDil);*/
	

	waitKey(0);//�ȴ�ʱ�����޳�

}




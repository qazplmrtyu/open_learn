#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////project 1   ���⻭��///////////////////


Mat img;
vector<vector<int>> newPoints; // �洢������ݣ�ÿ�����к����꣬�����꣬��ɫ

//HSV��ɫ����ֵ
vector<vector<int>> myColors{ {124,48,117,143,170,255}, // Purple
                              {68,72,156,102,126,255},  // Green
                              {0,18,74,4,195,104} };    //red
//��ɫ��BGRֵ
vector<Scalar> myColorValues{ {255,0,255},  // Purple
							  {0,255,0},    // Green
	                          {0,0,255} };//red

Point getContours(Mat imgDil)//�õ�����,������һ����
{

	vector<vector<Point>> contours;//�������飬vector�����������ƶ���һ����֪����С�Ķ�̬����
	vector<Vec4i> hierarchy;//��ʾ��νṹ��������ÿһ��Ԫ�ذ�����4��int�ͱ���

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//Ѱ��ͼ������
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//����ͼ������

	vector<vector<Point>> conPoly(contours.size());//���������ǵ����飬��С����������һ��
	vector<Rect> boundRect(contours.size());//�����������α߽�����

	Point myPoint(0, 0);//����һ����
	///�鿴��������������ض�����
	for (int i = 0; i < contours.size(); i++)//������������
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//ȡ��ÿ��������������


		if (area > 1000) ///�������С����������
		{
			float peri = arcLength(contours[i], true);//���������ĳ��ȣ������boolֵ�������������Ƿ�պ���Ϊtrue ���������߱պ�
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//ͨ���ǵ���������߽��н���


			cout << conPoly[i].size() << endl;//��ӡÿ�������ǵ���Ŀ
			boundRect[i] = boundingRect(conPoly[i]);//���α߽�

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;//����������
			myPoint.y = boundRect[i].y;
			
		
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//�����ǵ�����
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);//ͨ���������µ���ƾ���

		}
	}

	return myPoint;
}

vector<vector<int>> findColor(Mat img)//�����ɫ,��Ҫ����һ��newpoint
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);//��BGRͼƬת��Ϊhsv,��ɫ�ռ���ڼ����ɫ��hɫ��,s���Ͷȣ�v����

	for (int i = 0; i < myColors.size(); i++)//����������ɫ
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);//ȡHSV��ֵɸѡ��ɫ
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);//������ֵ֮����ɰ�
		//imshow(to_string(i), mask);//չʾ��ͬ��ɫ���ɰ�
		Point myPoint = getContours(mask);//���ɰ��������صĵ�洢
		newPoints.push_back({ myPoint.x,myPoint.y,i });//��������꣬i��ʾ��ɫ��ȡֵ0,1,2���뵽�µ���
	}
	return newPoints;

}
//����newpoint
void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{

	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

void main()
{

	VideoCapture cap(0);
	

	while (true)
	{
		cap.read(img);
		newPoints=findColor(img);
		drawOnCanvas(newPoints, myColorValues);

		imshow("image", img);
		waitKey(10);

	}
}
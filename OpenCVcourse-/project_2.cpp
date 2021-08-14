#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////project 2  �ĵ�ɨ����///////////////////

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596;//A4ֽ�Ŀ�Ⱥͳ���

Mat preProcessing(Mat img)//Ԥ������
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil)//�õ�����,�������ĸ���
{

	vector<vector<Point>> contours;//�������飬vector�����������ƶ���һ����֪����С�Ķ�̬����
	vector<Vec4i> hierarchy;//��ʾ��νṹ��������ÿһ��Ԫ�ذ�����4��int�ͱ���

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//Ѱ��ͼ������
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//����ͼ������

	vector<vector<Point>> conPoly(contours.size());//���������ǵ����飬��С����������һ��
	vector<Rect> boundRect(contours.size());//�����������α߽�����

	vector<Point> biggest;//�����㣬����������������ĵ�����
	int maxArea = 0;

	///�鿴��������������������
	for (int i = 0; i < contours.size(); i++)//������������
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//ȡ��ÿ��������������


		if (area > 1000) ///�������С����������
		{
			float peri = arcLength(contours[i], true);//���������ĳ��ȣ������boolֵ�������������Ƿ�պ���Ϊtrue ���������߱պ�
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//ͨ���ǵ���������߽��н���


			if (area > maxArea && conPoly[i].size() == 4)//�����������������ֵͬʱ��֤�����Ǿ���
			{

				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };//�洢����������ĵ�����
				maxArea = area;
			}

			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);//�����ǵ�����
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);//ͨ���������µ���ƾ���

		}
	}

	return biggest;
}

void drawPoints(vector<Point> points, Scalar color)//������������ĵ�ĺ���
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);//�������������ı�����㣬���½�����
	}
}


vector<Point> reorder(vector<Point> points)//�ĵ���������ĺ���
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;//������������֮�ͣ�֮����µ�����

	for (int i = 0; i < 4; i++)//���嶨���ĸ����������֮�ͣ�֮����µ������ľ���Ԫ��
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	// ��ֵ���Ϊ���ĸ���,��ֵ��СΪ��һ���� ,�� 2 3 ������ͨ��y - x �����ж�
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end())- subPoints.begin()]); //1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
	Point2f src[4] = { points[0],points[1],points[2],points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}


void main()
{
	string path = "Resources/paper.jpg";//����ͼƬ·��
	imgOriginal = imread(path); //�������������ͼƬ
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// ��һ����Ԥ����
	imgThre = preProcessing(imgOriginal);

	//�ڶ������ҵ��������Ҳ����A4ֽ
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints, Scalar(0, 0, 255));

	docPoints = reorder(initialPoints);//�������������ĵ�λ��
	drawPoints(docPoints, Scalar(0, 255, 0));//�������յ��ĸ���

	//��������ͼ����ת����
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//���Ĳ����ü�
	int cropVal = 5;
	Rect roi(cropVal, cropVal, w -(2 * cropVal), h -(2 * cropVal));
	imgCrop = imgWarp(roi);

	imshow("image", imgOriginal);
	imshow("Image Dilation", imgThre);
	imshow("Image Warp", imgWarp);
	waitKey(0);//�ȴ�ʱ�����޳�

}
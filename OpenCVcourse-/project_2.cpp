#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////project 2  文档扫描仪///////////////////

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596;//A4纸的宽度和长度

Mat preProcessing(Mat img)//预处理函数
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil)//得到轮廓,并返回四个点
{

	vector<vector<Point>> contours;//轮廓数组，vector是向量，类似定义一个不知道大小的动态数组
	vector<Vec4i> hierarchy;//表示层次结构，向量内每一个元素包含了4个int型变量

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//寻找图像轮廓
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//绘制图像轮廓

	vector<vector<Point>> conPoly(contours.size());//声明轮廓角点数组，大小与轮廓数组一致
	vector<Rect> boundRect(contours.size());//声明轮廓矩形边界数组

	vector<Point> biggest;//声明点，里面有最大轮廓的四点坐标
	int maxArea = 0;

	///查看轮廓面积，绘制最大轮廓
	for (int i = 0; i < contours.size(); i++)//遍历所有轮廓
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//取得每个轮廓面积并输出


		if (area > 1000) ///过滤面积小的轮廓干扰
		{
			float peri = arcLength(contours[i], true);//计算轮廓的长度，后面的bool值表面轮廓曲线是否闭合若为true 则轮廓曲线闭合
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//通过角点对轮廓曲线进行近似


			if (area > maxArea && conPoly[i].size() == 4)//更新轮廓区域是最大值同时保证轮廓是矩形
			{

				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };//存储最大轮廓的四点坐标
				maxArea = area;
			}

			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);//画出角点曲线
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);//通过左上右下点绘制矩形

		}
	}

	return biggest;
}

void drawPoints(vector<Point> points, Scalar color)//绘制最大轮廓四点的函数
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);//第三个参数是文本框起点，左下角坐标
	}
}


vector<Point> reorder(vector<Point> points)//四点重新排序的函数
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;//声明横纵坐标之和，之差的新的向量

	for (int i = 0; i < 4; i++)//具体定义四个点横纵坐标之和，之差的新的向量的具体元素
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	// 和值最大为第四个点,和值最小为第一个点 ,而 2 3 点则是通过y - x 进行判断
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
	string path = "Resources/paper.jpg";//设置图片路径
	imgOriginal = imread(path); //定义变量并导入图片
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	// 第一步：预处理
	imgThre = preProcessing(imgOriginal);

	//第二步：找到最大轮廓也就是A4纸
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints, Scalar(0, 0, 255));

	docPoints = reorder(initialPoints);//重新排序轮廓四点位置
	drawPoints(docPoints, Scalar(0, 255, 0));//绘制最终的四个点

	//第三步：图像旋转扶正
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//第四步：裁剪
	int cropVal = 5;
	Rect roi(cropVal, cropVal, w -(2 * cropVal), h -(2 * cropVal));
	imgCrop = imgWarp(roi);

	imshow("image", imgOriginal);
	imshow("Image Dilation", imgThre);
	imshow("Image Warp", imgWarp);
	waitKey(0);//等待时间无限长

}
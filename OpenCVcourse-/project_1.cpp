#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////project 1   虚拟画笔///////////////////


Mat img;
vector<vector<int>> newPoints; // 存储点的数据，每个点有横坐标，纵坐标，颜色

//HSV颜色的阈值
vector<vector<int>> myColors{ {124,48,117,143,170,255}, // Purple
                              {68,72,156,102,126,255},  // Green
                              {0,18,74,4,195,104} };    //red
//颜色的BGR值
vector<Scalar> myColorValues{ {255,0,255},  // Purple
							  {0,255,0},    // Green
	                          {0,0,255} };//red

Point getContours(Mat imgDil)//得到轮廓,并返回一个点
{

	vector<vector<Point>> contours;//轮廓数组，vector是向量，类似定义一个不知道大小的动态数组
	vector<Vec4i> hierarchy;//表示层次结构，向量内每一个元素包含了4个int型变量

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//寻找图像轮廓
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//绘制图像轮廓

	vector<vector<Point>> conPoly(contours.size());//声明轮廓角点数组，大小与轮廓数组一致
	vector<Rect> boundRect(contours.size());//声明轮廓矩形边界数组

	Point myPoint(0, 0);//定义一个点
	///查看轮廓面积，绘制特定轮廓
	for (int i = 0; i < contours.size(); i++)//遍历所有轮廓
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//取得每个轮廓面积并输出


		if (area > 1000) ///过滤面积小的轮廓干扰
		{
			float peri = arcLength(contours[i], true);//计算轮廓的长度，后面的bool值表面轮廓曲线是否闭合若为true 则轮廓曲线闭合
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//通过角点对轮廓曲线进行近似


			cout << conPoly[i].size() << endl;//打印每个轮廓角点数目
			boundRect[i] = boundingRect(conPoly[i]);//矩形边界

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;//计算点的坐标
			myPoint.y = boundRect[i].y;
			
		
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//画出角点曲线
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);//通过左上右下点绘制矩形

		}
	}

	return myPoint;
}

vector<vector<int>> findColor(Mat img)//检测颜色,需要返回一个newpoint
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);//将BGR图片转化为hsv,颜色空间便于检查颜色，h色调,s饱和度，v亮度

	for (int i = 0; i < myColors.size(); i++)//遍历所有颜色
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);//取HSV阈值筛选颜色
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);//生成阈值之间的蒙版
		//imshow(to_string(i), mask);//展示不同颜色的蒙版
		Point myPoint = getContours(mask);//将蒙版轮廓返回的点存储
		newPoints.push_back({ myPoint.x,myPoint.y,i });//将点的坐标，i表示颜色，取值0,1,2插入到新点中
	}
	return newPoints;

}
//画出newpoint
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
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int area;
int i;
string objectType;

//获得轮廓
void getContours(Mat imgDil, Mat img) 
{

	vector<vector<Point>> contours;//vector是向量，类似定义一个不知道大小的动态数组
	vector<Vec4i> hierarchy;//向量内每一个元素包含了4个int型变量

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//寻找图像轮廓
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//绘制图像轮廓

	/*vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());*/

	///查看轮廓面积，绘制特定轮廓
	for (int i = 0; i < contours.size(); i++)//遍历所有轮廓
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//取得每个轮廓面积并输出
	
		vector<vector<Point>> conPoly(contours.size());//声明轮廓角点数组，大小与轮廓数组一致
		vector<Rect> boundRect(contours.size());//声明轮廓矩形边界数组

	
		if (area > 1000) ///过滤面积小的轮廓干扰
		{
			float peri = arcLength(contours[i], true);//计算轮廓的长度，后面的bool值表面轮廓曲线是否闭合若为true 则轮廓曲线闭合
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//通过角点对轮廓曲线进行近似
			

			cout << conPoly[i].size() << endl;//打印每个轮廓角点数目
			//boundRect[i] = boundingRect(conPoly[i]);//矩形边界
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0),5);//通过左上右下点绘制矩形
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

		drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//画出角点曲线
		rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0),5);//通过左上右下点绘制矩形
		putText(img, objectType, { boundRect[i].x,boundRect[i].y-5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
	}

	
}

//////用图像预处理寻找轮廓///////////////////
void main()
{
	string path = "Resources/shapes.png";//设置图片路径
	Mat img = imread(path);//定义变量并导入图片
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	
	//图像预处理
	cvtColor(img, imgGray, COLOR_BGR2GRAY);//灰度转化
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);//size是高斯核大小，越小，模糊度越低
	Canny(imgBlur, imgCanny, 50, 100);//先模糊处理，再kanye边缘检测 。两个阈值越小，边缘线越多
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//使用结构成员定义膨胀内核的形状与大小
	dilate(imgCanny, imgDil, kernel);//用内核进行膨胀
	
	getContours(imgDil, img);
	 
	imshow("image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dialation", imgDil);*/
	

	waitKey(0);//等待时间无限长

}




#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


////////Resize and Crop///////////////////
void main()
{
	string path = "Resources/test.png";//设置图片路径
	Mat img = imread(path);//定义变量并导入图片
	Mat imgResize,imgCrop;
	
	//cout << img.size() << endl;//获得图像大小
	//resize(img, imgResize, Size(640,480));//按照像素缩小
	resize(img, imgResize, Size(),0.5,0.5);//按照比例缩小
	
	Rect roi(200, 80, 300, 320);//定义裁剪矩形的左上角x,y坐标和宽度及长度
	imgCrop = img(roi);


	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);

	waitKey(0);

}

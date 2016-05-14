#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stitching.hpp>
#include "shape.h"

using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
vector<Mat> edge;
string result_name = "result.jpg";

int main()
{
	// 调用createDefault函数生成默认的参数
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);

	int mode;
	cout << "working mode:" << endl;
	cout << "1:include edges" << endl;
	cout << "2:not include edges" << endl;
	cout << "input:" << endl;
	cin >> mode;

	Mat img0, imgn;
	Mat img1 = imread("D:\\test\\01.jpg");
	Mat img2 = imread("D:\\test\\02.jpg");
	Mat img3 = imread("D:\\test\\03.jpg");
	Mat img4 = imread("D:\\test\\04.jpg");
	Mat img5 = imread("D:\\test\\05.jpg");
	Mat img6 = imread("D:\\test\\06.jpg");
	Mat img7 = imread("D:\\test\\07.jpg");
	Mat img8 = imread("D:\\test\\08.jpg");
	Mat img9 = imread("D:\\test\\09.jpg");


	//mode == 1时，先对边缘图像合成并且等分
	if (mode == 1)
	{
		Mat edge1 = imread("D:\\test\\0.jpg");
		Mat edge2 = imread("D:\\test\\n.jpg");

		edge.push_back(edge1);
		edge.push_back(edge2);

		Mat edge_pano;
		Rect edge_rect1, edge_rect2;
		Rect edge_rect = ROIRect(edge_pano);
		edge_rect1.x = edge_rect.x;
		edge_rect1.y = edge_rect.y;
		edge_rect1.width = edge_rect.width / 2;
		edge_rect1.height = edge_rect.height;

		edge_rect2.x = edge_rect.x + edge_rect.width / 2;
		edge_rect2.y = edge_rect.y;
		edge_rect2.width = edge_rect.width / 2;
		edge_rect2.height = edge_rect.height;

		img0 = edge_pano(edge_rect1);
		imgn = edge_pano(edge_rect2);
	}

	if(mode == 1)
		imgs.push_back(img0);
	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);
	imgs.push_back(img4);
	imgs.push_back(img5);
	imgs.push_back(img6);
	imgs.push_back(img7);
	imgs.push_back(img8);
	imgs.push_back(img9);
	if(mode == 1)
		imgs.push_back(imgn);

	// 使用stitch函数进行拼接
	Mat pano;
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	
	//图像裁剪
	Rect rect = ROIRect(pano);
	Mat roi = pano(rect);

	// 保存结果图像
	if (mode == 1)
	{
		imwrite("D:\\test\\edge1.jpg", img0);
		imwrite("D:\\test\\edge2.jpg", imgn);
	}
	imwrite("D:\\test\\result.jpg", pano);
	imwrite("D:\\test\\roi.jpg",roi);

	cout << "save successfully!" << endl;

	system("pause");
	return 0;
}
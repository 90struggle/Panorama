/****************************************************
** shape函数
**
*****************************************************/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stitching.hpp>

using namespace std;
using namespace cv;


Rect ROIRect(Mat src)
{
	Mat dst = src.clone();
	CvMat msrc = src;
	Scalar pixel1, pixel2, pixel3;
	Rect rect;
	Size size;

	int a, b, c, d;
	int flag_a = 1, flag_b = 1, flag_c = 1, flag_d = 1;

	size = cvGetSize(&msrc);
	a = 0;
	b = size.height - 1;
	c = 0;
	d = size.width - 1;
	/*cout << size.height << endl;
	cout << size.width << endl;*/
	/*a = 0;
	b = dst.rows;
	c = 0;
	d = dst.cols;
*/
	int p = 0;
	//每次对四边，都进行一行/一列的扫描。如果发现了背景色，则全部置（1,1,1）。
	//直到四边都没有背景色，扫描停止。
	//flag = 1,继续扫描。flag = 0.停止扫描。
	//最后得出的a,b,c,d就是裁剪的ROI区域。
	while (1)
	{
		//a行
		if (flag_a == 1)
			for (int i = 0; i < size.width - 2; i++)
			//for (int i = 0; i < dst.cols - 2; i++)
			{
				if(dst.at<Vec3b>(a, i)[0] == 0 && dst.at<Vec3b>(a, i)[1] == 0 && dst.at<Vec3b>(a, i)[2] == 0)
					if (dst.at<Vec3b>(a, i + 1)[0] == 0 && dst.at<Vec3b>(a, i + 1)[1] == 0 && dst.at<Vec3b>(a, i + 1)[2] == 0)
						if (dst.at<Vec3b>(a, i + 2)[0] == 0 && dst.at<Vec3b>(a, i + 2)[1] == 0 && dst.at<Vec3b>(a, i + 2)[2] == 0)
						{
							dst.row(a).setTo(Scalar(1, 1, 1));
							flag_a = 1;//扫描继续
							a++;
							break;
						}
				//如果if不成立，扫描标志置0.继续该行扫描。直到退出for循环为止。
				flag_a = 0;
			}

		//b行
		if (flag_b == 1)
			for (int i = 0; i < size.width - 2; i++)
			//for (int i = 0; i < dst.cols - 2; i++)
			{
				if (dst.at<Vec3b>(b, i)[0] == 0 && dst.at<Vec3b>(b, i)[1] == 0 && dst.at<Vec3b>(b, i)[2] == 0)
					if (dst.at<Vec3b>(b, i + 1)[0] == 0 && dst.at<Vec3b>(b, i + 1)[1] == 0 && dst.at<Vec3b>(b, i + 1)[2] == 0)
						if (dst.at<Vec3b>(b, i + 2)[0] == 0 && dst.at<Vec3b>(b, i + 2)[1] == 0 && dst.at<Vec3b>(b, i + 2)[2] == 0)
						{
							dst.row(b).setTo(Scalar(1, 1, 1));
							flag_b = 1;
							b--;
							break;
						}
				flag_b = 0;
			}

		//c列
		if (flag_c == 1)
			for (int j = 0; j < size.height - 2; j++)
			//for (int j = 0; j < dst.rows - 2; j++)
			{
				if (dst.at<Vec3b>(j, c)[0] == 0 && dst.at<Vec3b>(j, c)[1] == 0 && dst.at<Vec3b>(j, c)[2] == 0)
					if (dst.at<Vec3b>(j + 1, c)[0] == 0 && dst.at<Vec3b>(j + 1, c)[1] == 0 && dst.at<Vec3b>(j + 1, c)[2] == 0)
						if (dst.at<Vec3b>(j + 2, c)[0] == 0 && dst.at<Vec3b>(j + 2, c)[1] == 0 && dst.at<Vec3b>(j + 2, c)[2] == 0)
						{
							dst.col(c).setTo(Scalar(1, 1, 1));
							flag_c = 1;
							c++;
							break;
						}
				flag_c = 0;
			}

		//d列
		if (flag_d == 1)
			for (int j = 0; j < size.height - 2; j++)
			//for (int j = 0; j < dst.rows - 2; j++)
			{
				if (dst.at<Vec3b>(j, d)[0] == 0 && dst.at<Vec3b>(j, d)[1] == 0 && dst.at<Vec3b>(j, d)[2] == 0)
					if (dst.at<Vec3b>(j + 1, d)[0] == 0 && dst.at<Vec3b>(j + 1, d)[1] == 0 && dst.at<Vec3b>(j + 1, d)[2] == 0)
						if (dst.at<Vec3b>(j + 2, d)[0] == 0 && dst.at<Vec3b>(j + 2, d)[1] == 0 && dst.at<Vec3b>(j + 2, d)[2] == 0)
						{
							dst.col(d).setTo(Scalar(1, 1, 1));
							flag_d = 1;
							d--;
							break;
						}
				flag_d = 0;
			}

		if (flag_a == 0 && flag_b == 0 && flag_c == 0 && flag_d == 0)
			break;
	}

	rect.x = c;
	rect.y = a;
	rect.width = d - c;
	rect.height = b - a;

	return rect;
}


//int main()
//{
//	Mat img = imread("D:\\test\\1111.jpg");
//	Rect rect = ROIRect(img);
//	Mat roi = img(rect);
//
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	namedWindow("dst", CV_WINDOW_AUTOSIZE);
//	imshow("src", img);
//	imshow("dst", roi);
//	waitKey(0);
//
//	return 0;
//}
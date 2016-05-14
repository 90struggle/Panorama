#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stitching.hpp>

using namespace std;
using namespace cv;

int main()
{
	const int top = 3400, bottom = 3400;

	Mat src = imread("D:\\test\\45\\roi.bmp");

	Mat dst(src.rows + top + bottom, src.cols, src.type());


	for (int i = 0; i < dst.rows; i++) {
		uchar* dataD = dst.ptr<uchar>(0);
		for (int j = 0; j < dst.cols; j++) {
			*dataD++ = 255;
		}
	}


	for (int i = 0; i < src.rows; i++) {
		uchar* data = src.ptr<uchar>(i);
		uchar* dataD = dst.ptr<uchar>(i + top);
		for (int j = 0; j < src.cols; j++) {
			*dataD++ = *data++;
			*dataD++ = *data++;
			*dataD++ = *data++;
		}
	}

	imwrite("D:\\test\\45\\dst.bmp", dst);

	return 0;
}
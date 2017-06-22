#include "binarization.h"
#include "projection.h"
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char* srcURL="test3.png";

int main() {
	//load source image

	/*cout<< "please enter source URL" << endl;
	cin >> srcURL;*/

	Mat src = imread(srcURL);
	imshow("orginal image", src);

	Mat erodeIm;
	Mat erodeEl = getStructuringElement(MORPH_RECT, Size(11, 11));
	erode(src, erodeIm, erodeEl);
	imshow("erode image", erodeIm);

	//create a gray image
	Mat grayIm(src.cols, src.rows, CV_8UC1);
	creatGrayIm(erodeIm, grayIm);
	//cvShowImage("title",grayIm);
	
	//create a binary image with the same size of gray image
	Mat binIm(grayIm.cols, grayIm.rows, CV_8UC1);

	int threhold=127;

	creatBinaryIm(grayIm, binIm,threhold);
	imshow("binary image", binIm);

	vector<vector<Point>> contours;
	findContours(binIm, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	
	for (int i = 0; i < contours.size() - 1; i++) {
		Rect rect = boundingRect(contours[i]);

		if (rect.area() > 255) {
			rectangle(src, rect, Scalar(255, 0, 0));
		}
		
	}
	
	imshow("test", src);

	//do projection
	/*doProjection(binIm);
	showPro();
	showRect(src);*/
	
	cvWaitKey(0);


	return 0;
}

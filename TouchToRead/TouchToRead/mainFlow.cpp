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
	//create a gray image
	Mat grayIm(src.cols, src.rows, CV_8UC1);

	creatGrayIm(src, grayIm);
	//cvShowImage("title",grayIm);
	
	//create a binary image with the same size of gray image
	Mat binIm(grayIm.cols, grayIm.rows, CV_8UC1);

	int threhold=127;

	creatBinaryIm(grayIm, binIm,threhold);
	//imshow("binary image", binIm);

	//do projection
	doProjection(binIm);
	/*horizontalPro(binIm);
	verticalPro(binIm);*/
	showPro();
	showRect(src);
	cvWaitKey(0);


	return 0;
}

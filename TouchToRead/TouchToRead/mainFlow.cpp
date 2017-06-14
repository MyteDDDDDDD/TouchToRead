#include "binarization.h"
#include<opencv2\opencv.hpp>
using namespace std;


int main() {
	//load source image
	string srcURL;
	cout<< "please enter source URL" << endl;
	cin >> srcURL;
	IplImage *src = cvLoadImage("test2.png",CV_LOAD_IMAGE_UNCHANGED);
	//create a gray image
	IplImage *grayIm=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	creatGrayIm(src, grayIm);
	//cvShowImage("title",grayIm);
	
	IplImage* binIm = cvCreateImage(cvGetSize(grayIm), IPL_DEPTH_8U, 1);
	cvThreshold(grayIm, binIm, 1, 255, CV_THRESH_BINARY);
	cvShowImage("binary title", binIm);
	cvWaitKey(0);
	return 0;
}

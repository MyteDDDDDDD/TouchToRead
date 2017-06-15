#pragma once
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;


void creatGrayIm(Mat &srcP,Mat &dstP) {
	cvtColor(srcP, dstP, CV_BGR2GRAY);
}

void creatBinaryIm(Mat &srcP, Mat& dstP, int p) {
	if (p != 0) {
		threshold(srcP, dstP, p, 255, CV_THRESH_BINARY);
	}

}
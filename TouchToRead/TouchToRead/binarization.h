#pragma once
#include<opencv2\opencv.hpp>
#include<string>
using namespace std;


void creatGrayIm(IplImage* srcP, IplImage* dstP) {
	cvCvtColor(srcP, dstP, CV_BGR2GRAY);

}

void creatBinaryIm(string* srcP , string* dstP) {


}
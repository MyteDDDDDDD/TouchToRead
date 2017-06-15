#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
int r, c;
int *verPixel;
int *horPixel;

void showPor() {
	Mat horM(r, c, CV_8UC1);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			horM.at<uchar>(i, j) = 255;
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < horPixel[i]; j++) {
			horM.at<uchar>(i, j) = 0;
		}
	}

	imshow("horizaontalPro", horM);

	Mat verM(r, c, CV_8UC1);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			verM.at<uchar>(i, j) = 255;
		}
	}


	for (int i = 0; i < c; i++) {
		for (int j = 0; j <verPixel[i]; j++) {
			verM.at<uchar>(r - j - 1, i) = 0;
		}
	}

	imshow("verticalPro", verM);

	cvWaitKey(0);
}
void showVerPro() {

	Mat verM(r, c, CV_8UC1);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			verM.at<uchar>(i, j) = 255;
		}
	}
	
	
	for (int i = 0; i < c; i++) {
		for (int j = 0; j <verPixel[i]; j++) {
			verM.at<uchar>(r - j - 1, i) = 0;
		}
	}

	imshow("verticalPro", verM);
	cvWaitKey(0);
}

void showHorPro() {
	Mat horM(r, c, CV_8UC1);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			horM.at<uchar>(i, j) = 255;
		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < horPixel[i]; j++) {
			horM.at<uchar>(i, j) = 0;
		}
	}

	imshow("horizaontalPro", horM);
	cvWaitKey(0);
}

void verticalPro(Mat p) {
	r = p.rows;
	c = p.cols;
	int pixelVal=0;
	verPixel = new int[c];
	
	memset(verPixel, 0, c*4);
	
	

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (p.at<uchar>(i, j)==0)
				verPixel[j]++;
		}
		
	}
	
	//showVerPro(verPixel);
}

void horizontalPro(Mat p) {
	r = p.rows;
	c = p.cols;
	int pixelVal = 0;
	horPixel = new int[r];

	memset(horPixel, 0, r * 4);

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (p.at<uchar>(i, j) == 0)
				horPixel[i]++;
		}

	}

	//showHorPro(horPixel);
}


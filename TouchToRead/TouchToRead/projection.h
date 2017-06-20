#pragma once
#include<opencv2/opencv.hpp>
#include<vector>
using namespace cv;
int r, c;
int *verPixel;
int *horPixel;

vector<int> xU, xL, yL,yU;
void showRect(Mat p) {
	bool inLine = false;
	int startLine;
	int lastXU, lastXL, lastYU, lastYL;

	for (int i = 0; i < r; i++) {

		if (!inLine&&horPixel[i]>10) {
			inLine = true;
			startLine = i;
		}
		else if (inLine&&horPixel[i] <= 10 && (i - startLine) > 5) {
			inLine = false;

			if (!yL.empty()&&((startLine - 2) - yL.back() <5)) { //two line close
				yL.pop_back();
				yL.push_back(i+1);
			}
			else {
				yU.push_back(startLine - 2);
				yL.push_back(i + 2);
			}
		}
	}

	inLine = false;
	for (int i = 0; i < c; i++) {
		if (!inLine&&verPixel[i]>2) {
			inLine = true;
			startLine = i;
		}
		else if (inLine&&verPixel[i] <= 2 && (i - startLine) > 5) {
			inLine = false;
			xU.push_back(startLine - 1);
			xL.push_back(i + 1);
		}
	}

	
	for (int i = 0; i < xU.size(); i++) {
		for (int j = 0; j < yU.size(); j++) {
			rectangle(p, Point(xU.at(i), yU.at(j)), Point(xL.at(i), yL.at(j)), Scalar(255, 0, 0));
		}
	}
	xU.clear();
	xL.clear();
	yU.clear();
	yL.clear();
	imshow("rect", p);
	cvWaitKey(0);
}

void showPro() {
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

	//cvWaitKey(0);
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

void doProjection(Mat p) {
	r = p.rows;
	c = p.cols;
	int pixelVal = 0;
	horPixel = new int[r];
	verPixel = new int[c];

	memset(horPixel, 0, r * 4);
	memset(verPixel, 0, c * 4);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (p.at<uchar>(i, j) == 0) {
				horPixel[i]++;
				verPixel[j]++;
			}
		}

	}
}


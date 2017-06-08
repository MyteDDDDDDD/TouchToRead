#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("test1.jpg");
	namedWindow("testing"); 
	imshow("testing", img);
	waitKey(10000);
	return 0;
}
#include "binarization.h"
#include "projection.h"
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char* srcURL="test3.png";

class block{
private:
	int x, y, w, h;
public:
	
	void setX(int newX) {
		x = newX;
	};
	void setY(int newY) {
		y = newY;
	};
	void setW(int newW) {
		w = newW;
	};
	void setH(int newH) {
		h = newH;
	};
	int getX() {
		return x;
	};
	int getY() {
		return y;
	};
	int getW() {
		return w;
	};
	int getH(){
		return h;
	};
};

vector<block> blocks;
int textBlkNum = 0, imageBlkNum = 0;
int main() {
	//load source image

	/*cout<< "please enter source URL" << endl;
	cin >> srcURL;*/
	
	Mat src = imread(srcURL);
	imshow("source image", src);
	Mat erodeIm;
	Mat erodeEl = getStructuringElement(MORPH_RECT, Size(11, 11));
	erode(src, erodeIm, erodeEl);
	//imshow("erode image", erodeIm);

	//create a gray image
	Mat grayIm(src.cols, src.rows, CV_8UC1);
	creatGrayIm(erodeIm, grayIm);
	//imshow("gray image",grayIm);
	
	//create a binary image with the same size of gray image
	Mat binIm(grayIm.cols, grayIm.rows, CV_8UC1);

	int threhold=99;

	creatBinaryIm(grayIm, binIm,threhold);
	//imshow("binary image", binIm);

	vector<vector<Point>> contours;
	findContours(binIm, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);


	Mat noTextIm =src.clone();
	for (int i = 0; i < contours.size() - 1; i++) {
		Rect rect = boundingRect(contours[i]);
		//rectangle(src, rect, Scalar(255, 0, 0));
		if (rect.area() > 255) {
			//rectangle(src, rect, Scalar(255, 0, 0));

			block bl;
			bl.setX(rect.x);
			bl.setY(rect.y);
			bl.setW(rect.width);
			bl.setH(rect.height);
			blocks.push_back(bl);
			textBlkNum++;

			drawContours(noTextIm, contours, i, Scalar(255, 255, 255), CV_FILLED);
		}
		
	}


	//imshow("source image without text", noTextIm);

	
	Rect r(0, 0, src.cols-1, src.rows-1 );
	Mat cutIm; 
	Mat bgModel, fgModel; 
							
	
	grabCut(noTextIm, cutIm, r, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
	
	compare(cutIm, GC_PR_FGD, cutIm, CMP_EQ);

	//Mat foreground(src.size(), CV_8UC1);
	//src.copyTo(foreground, cutIm); 

	//imshow("images blocks", cutIm);
	for (int i = 0; i < cutIm.rows; i++) {
		for (int j = 0; j < cutIm.cols; j++) {
			cutIm.at<uchar>(i, j) = 255 - cutIm.at<uchar>(i, j);
		}
	}
	erode(cutIm, erodeIm, erodeEl);
	//imshow("images blocks", cutIm);

	findContours(erodeIm, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size()-1; i++) {
		Rect rect = boundingRect(contours[i]);
		//rectangle(src, rect, Scalar(255, 0, 0));
		if (rect.area() > 255) {
			block bl;
			bl.setX(rect.x);
			bl.setY(rect.y);
			bl.setW(rect.width);
			bl.setH(rect.height);
			blocks.push_back(bl);
			imageBlkNum++;
		}
	}

	for (int i = 0; i < textBlkNum; i++) {
		bool trig = false;
		int nxl, txr, nyu, tyd, txl, tyu, nxr, nyd;
		txl = blocks.at(i).getX();
		tyu = blocks.at(i).getY();
		txr = txl + blocks.at(i).getW();
		tyd = tyu + blocks.at(i).getH();

		if (i < textBlkNum - 1) {
			for (int j = i + 1; j < textBlkNum; j++) {
				nxl = blocks.at(j).getX();
				nyu = blocks.at(j).getY();
				nxr = nxl + blocks.at(j).getW();
				nyd = nyu + blocks.at(j).getH();

				if ((nxl > txl - 2 && nxl < txr + 2 && nyu > tyu - 2 && nyu < tyd + 2) ||
					(nxr > txl - 2 && nxr < txr + 2 && nyu > tyu - 2 && nyu < tyd + 2) ||
					(nxl > txl - 2 && nxl < txr + 2 && nyd > tyu - 2 && nyd < tyd + 2) ||
					(nxr > txl - 2 && nxr < txr + 2 && nyd > tyu - 2 && nyd < tyd + 2)) {
					int nx, ny, nw, nh;
					nx = min(txl, nxl);
					ny = min(tyu, nyu);
					nw = max(txr, nxr) - nx;
					nh = max(tyd, nyd) - ny;
			//		cout << "nx" << nx << "ny" << ny << "nw" << nw << "nh" << endl;
					blocks.at(j).setX(nx);
					blocks.at(j).setY(ny);
					blocks.at(j).setW(nw);
					blocks.at(j).setH(nh);
					trig = true;
					break;
				}

			}

		}
		if (!trig) {
			rectangle(src, Point(txl, tyu), Point(txr, tyd), Scalar(255, 0, 0));
		}
		cout << "blocks" << i << endl << " x:" << blocks.at(i).getX() << " y:" << blocks.at(i).getY() << " h:" << blocks.at(i).getH() << " w:" << blocks.at(i).getW() << endl;
		
	}

	for (int i = 0; i < imageBlkNum; i++) {
		bool trig = false;
		int nxl, txr, nyu, tyd, txl, tyu, nxr, nyd;
		txl = blocks.at(textBlkNum + i).getX();
		tyu = blocks.at(textBlkNum + i).getY();
		txr = txl + blocks.at(textBlkNum + i).getW();
		tyd = tyu + blocks.at(textBlkNum + i).getH();

		if (i < imageBlkNum - 1) {
			for (int j = i+1; j < imageBlkNum; j++) {
				nxl = blocks.at(textBlkNum + j).getX();
				nyu = blocks.at(textBlkNum + j).getY();
				nxr = nxl + blocks.at(textBlkNum + j).getW();
				nyd =nyu + blocks.at(textBlkNum + j).getH();

				if ((nxl > txl-5&&nxl < txr+5&&nyu > tyu-5&&nyu < tyd+5) ||
					(nxr > txl-5&&nxr < txr+5&&nyu > tyu-5&&nyu < tyd+5) ||
					(nxl > txl-5&&nxl < txr+5&&nyd > tyu-5&&nyd < tyd+5) ||
					(nxr > txl-5&&nxr < txr+5&&nyd > tyu-5&&nyd < tyd+5)) {
					int nx, ny,nw,nh;
					nx = min(txl, nxl);
					ny = min(tyu, nyu);
					nw = max(txr, nxr) - nx;
					nh = max(tyd, nyd) - ny;
				//	cout << "nx" << nx<<"ny"<<ny<<"nw"<<nw<<"nh"<<endl;
					blocks.at(textBlkNum + j).setX(nx);
					blocks.at(textBlkNum + j).setY(ny);
					blocks.at(textBlkNum + j).setW(nw);
					blocks.at(textBlkNum + j).setH(nh);
					trig = true;
					break;
				}

			}
			
		}
		if (!trig) {
			rectangle(src, Point(txl, tyu), Point(txr, tyd), Scalar(255, 0, 0));
		}
		cout << "blocks" << i+ textBlkNum << endl << " x:" << blocks.at(i+ textBlkNum).getX() << " y:" << blocks.at(i+ textBlkNum).getY() << " h:" << blocks.at(i+ textBlkNum).getH() << " w:" << blocks.at(i+ textBlkNum).getW() << endl;
		
	}
	

	imshow("final", src);

	
	cvWaitKey(0);


	return 0;
}

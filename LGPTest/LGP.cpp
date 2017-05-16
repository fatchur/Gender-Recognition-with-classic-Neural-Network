#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include "LGP.h"

using namespace cv;
using namespace std;

vector<Mat> LGP::regionalImage(Mat inputImage, int col, int row) {
	int regionWidth = (int)inputImage.cols / col;
	int regionHeight = (int)inputImage.rows / row;

	vector<Mat> cutImage;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			Rect region(j * regionWidth, i * regionHeight, regionWidth, regionHeight);
			cutImage.push_back(inputImage(region));
		}
	}

	return cutImage;
}
float LGP::regionalLGPValue(vector<Mat> inputImage, int size) {

	int center = 1 + (inputImage.size() - 1) / 2;
	float centerValue = 0;

	vector<float> lgpValue;

	for (int a = 0; a < inputImage.size(); a++) {
		int jumlah = 0;
		for (int k = 0; k < inputImage[a].rows; k++) {
			for (int l = 0; l < inputImage[a].cols; l++) {

				jumlah += inputImage[a].at<uchar>(k, l);
			}
		}

		lgpValue.push_back(jumlah);
		if (a == center) { centerValue = jumlah; }
	}

	//menghitung nilai LBP
	float result = 0;

	for (int i = 0; i < lgpValue.size(); i++) {
		lgpValue[i] = lgpValue[i]-centerValue;
	}

	///////////////////////////////////////////////
	// searching min and max value              ///
	///////////////////////////////////////////////
	float min = lgpValue[0];
	float max = lgpValue[0];
	for (int i = 0; i < lgpValue.size(); i++) {
		if (lgpValue[i] > max) { max = lgpValue[i]; }
		if (lgpValue[i] < min) { min = lgpValue[i]; }
	}

	///////////////////////////////////////////////
	// set min as zero, max as one              ///
	///////////////////////////////////////////////
	float interval = max - min;
	// normalize lgp value
	for (int i = 0; i < lgpValue.size(); i++) {
		if (interval != 0) {
			lgpValue[i] = (lgpValue[i] - min) / interval;
		}
	}

	//gving value
	for (int i = 0; i < lgpValue.size(); i++) {

		if (i == 0) {
			result += lgpValue[i] * pow(2, i);
		}
		else if (i == 1) {
			result += lgpValue[i] * pow(2, i);
		}
		else if (i == 2) {
			result += lgpValue[i] * pow(2, i);
		}
		else if (i == 3) {
			result += lgpValue[i] * pow(2, 7);
		}
		else if (i == 4) {
			continue;
		}
		else if (i == 5) {
			result += lgpValue[i] * pow(2, 3);
		}
		else if (i == 6) {
			result += lgpValue[i] * pow(2, 6);
		}
		else if (i == 7) {
			result += lgpValue[i] * pow(2, 5);
		}
		else { result += lgpValue[i] * pow(2, 4); }

		/*
		if (i < center) { result += lbpValue[i] * pow(2, i); }
		else { result += lbpValue[i] * pow(2, i-1); }
		*/
	}

	return result;
}
#ifndef  _LGP_H_
#define _LGP_H_

#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>

using namespace cv;
using namespace std;

class LGP	{
public:
	//method untuk membagi gambar menjadi beberapa region
	static vector<Mat> regionalImage(Mat inputImage, int col, int row);
	//method untuk menghitung nilai LBP (tiap region)
	static float regionalLGPValue(vector<Mat> inputImage, int size); // size merupakan jumlah sub region dari tiap region
};

#endif // ! -LGP_H_


#ifndef  _NEURALNET_H
#define _NEURALNET_H

#include <opencv2\highgui.hpp>

using namespace cv;
using namespace std;

class NeuralNet{
public:
	vector<double> offset;
	vector<double> gain;
	int min;
	vector<double> biasHidden1;
	vector<vector<double>> bobotHidden1;
	vector<double> bobotOutput;
	vector<vector<double>> bobotOutputSoftmax;
	double biasOutput;
	vector<double> biasOutputSoftmax;


	//methods
	static vector<double> normalisasiInput(vector<int> input, NeuralNet b);
	static vector<double> normalisasiInput(vector<float> input, NeuralNet b);
	static vector<double> normalisasiInput(vector<double> input, NeuralNet b);
	static vector<double> hitungHiddenNeuron(vector<double> normInput, int jumNeuronHidden, NeuralNet b);
	static float hitungOutput(vector<double> hiddenValue, NeuralNet b);
	static int hitungOutput(vector<double> hiddenValue, NeuralNet &b, int jumlahOutput);
};
#endif // ! _NEURALNET_


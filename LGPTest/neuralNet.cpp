#include "neuralNet.h"
#include <iostream>

using namespace cv;
using namespace std;

vector<double> NeuralNet::normalisasiInput(vector<int> input, NeuralNet b) {
	vector<double> normInput;

	for (int i = 0; i < input.size(); i++) {
		double y = input[i];
		y = y - b.offset[i];
		y = y * b.gain[i];
		y += b.min;
		normInput.push_back(y);
	}

	return normInput;
}
vector<double> NeuralNet::normalisasiInput(vector<float> input, NeuralNet b) {
	vector<double> normInput;

	for (int i = 0; i < input.size(); i++) {
		double y = input[i];
		y = y - b.offset[i];
		y = y * b.gain[i];
		y += b.min;
		normInput.push_back(y);
	}

	return normInput;
}
vector<double> NeuralNet::normalisasiInput(vector<double> input, NeuralNet b) {
	vector<double> normInput;

	for (int i = 0; i < input.size(); i++) {
		double y = input[i];
		y = y - b.offset[i];
		y = y * b.gain[i];
		y += b.min;
		normInput.push_back(y);
	}

	return normInput;
}
vector<double> NeuralNet::hitungHiddenNeuron(vector<double> normInput, int jumNeuronHidden, NeuralNet b) {
	vector<double> hiddenValue;

	for (int i = 0; i < jumNeuronHidden; i++) {
		double jumlah = 0;

		for (int j = 0; j < normInput.size(); j++) {
			jumlah += normInput[j] * b.bobotHidden1[i][j];
		}

		jumlah += b.biasHidden1[i];
		//aktivasi sigmoid
		jumlah = 2.0 / (1 + exp(-2 * jumlah)) - 1;
		hiddenValue.push_back(jumlah);
	}

	return hiddenValue;
}
float NeuralNet::hitungOutput(vector<double> hiddenValue, NeuralNet b) {
	float output ;

	double jumlah = 0;
	for (int i = 0; i < hiddenValue.size(); i++) {
		jumlah += hiddenValue[i] * b.bobotOutput[i];
	}

	jumlah = jumlah + b.biasOutput;
	output = 1.0 / (1.0 + exp(-jumlah));

	return output;
}
int NeuralNet::hitungOutput(vector<double> hiddenValue, NeuralNet &b, int macamOutput) {
	vector<double> output;

	for (int i = 0; i < macamOutput; i++) {
		double jumlah = 0;
		for (int j = 0; j < hiddenValue.size(); j++) {
			jumlah += hiddenValue[j] * b.bobotOutputSoftmax[i][j];
		}

		jumlah += b.biasOutputSoftmax[i];
		output.push_back(jumlah);
	}

	//mencari nilai terbesar 
	int kelas = 0;
	for (int i = 1; i < output.size(); i++) {
		if (output[i] > output[kelas]) {
			kelas = i;
		}
	}
	/*
	for (int i = 0; i < output.size(); i++) {
		output[i] = output[i] - output[kelas];
	}

	for (int i = 0; i < output.size(); i++) {
		output[i] = exp(output[i]);
	}

	double denom = 0;
	for (int i = 0; i < output.size(); i++) {
		denom += output[i];
	}

	if (denom == 0) { denom = 1; }

	for (int i = 0; i < output.size(); i++) {
		output[i] = output[i]/denom;
	}

	kelas = 0;
	for (int i = 1; i < output.size(); i++) {
		if (output[i] > output[kelas]) {
			kelas = i;
		}
	}
	*/

	return kelas;
}
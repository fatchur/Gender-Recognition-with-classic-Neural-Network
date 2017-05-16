#include "neuralNet.h"
#include "CSV.h"
#include "LGP.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include"CSV.h"
#include <opencv2\highgui.hpp>
#include <opencv2\objdetect.hpp>
#include <opencv2\imgcodecs.hpp>


using namespace std;

int main() {
	NeuralNet myNet;
	CSV a;
	myNet.min = -1;

	//membaca bobot hidden
	//------------------------------------------------------------------------------------------------------
	std::fstream fileBobotHidden("bobotHidden.csv", ios::in);
	if (!fileBobotHidden.is_open())
	{
		std::cout << "File 1 not found!\n";
		system("PAUSE");
		return 1;
	}

	a.readCSV(fileBobotHidden, myNet.bobotHidden1);
	cout << "   1 ok";
	//-------------------------------------------------------------------------------------------------------
	
	//membaca bias hidden
	std::fstream fileBiasHidden("biasHidden.csv", ios::in);
	if (!fileBiasHidden.is_open())
	{
		std::cout << "File 2 not found!\n";
		system("PAUSE");
		return 1;
	}
	a.readCSV(fileBiasHidden, myNet.biasHidden1);
	cout << "   2 ok";
	//membaca bobot output
	std::fstream fileBobotOutput("bobotOutput.csv", ios::in);
	if (!fileBobotOutput.is_open())
	{
		std::cout << "File 3 not found!\n";
		system("PAUSE");
		return 1;
	}
	a.readCSV(fileBobotOutput, myNet.bobotOutput);
	cout << " 3 ok  ";
	//membaca gain
	std::fstream fileGain("gain.csv", ios::in);
	if (!fileGain.is_open())
	{
		std::cout << "File 4 not found!\n";
		system("PAUSE");
		return 1;
	}
	a.readCSV(fileGain, myNet.gain);
	cout << "  4 ok  ";
	//membaca offset
	std::fstream fileOffset("offset.csv", ios::in);
	if (!fileOffset.is_open())
	{
		std::cout << "File 5 not found!\n";
		system("PAUSE");
		return 1;
	}
	a.readCSV(fileOffset, myNet.offset);
	cout << "   5 ok";

	std::fstream fileBiasOutput("biasOutput.csv", ios::in);
	if (!fileBiasOutput.is_open())
	{
		std::cout << "File 5 not found!\n";
		system("PAUSE");
		return 1;
	}
	a.readCSV(fileBiasOutput, myNet.biasOutput);
	cout << "bias output ok";

	//membaca input
	Mat myImage, frame;
	//membuka gambar dalam satu folder
	//string folder = "G:/sample/woman/*.pgm";
	string folder = "G:/sample/man_new/*.jpg";
	vector<String> fileNames;
	glob(folder, fileNames);

	//deklarasi haar cascade
	CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_alt.xml");

	VideoCapture capturedDevice;
	capturedDevice.open(CAP_ANY);

	float male = 0;
	float female = 0;

	for (size_t i = 0; i < fileNames.size(); i++)
	{
		//capturedDevice >> myImage;
		myImage = imread(fileNames[i]);
		frame = myImage;
		cvtColor(myImage, myImage, CV_BGR2GRAY);
		
		//deklarasi variabel dan fungsi untuk deteksi wajah
		vector<Rect> faces;
		vector<Mat> croppedImage;
		faceCascade.detectMultiScale(myImage, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, Size(60, 60));

		//mulai deteksi wajah
		for (int a = 0; a < faces.size(); a++)
		{
			Point pt1, pt2;
			pt1.x = faces[a].x + faces[a].width / 8;
			pt1.y = faces[a].y;
			pt2.x = faces[a].x + 7 * faces[a].width / 8;
			pt2.y = faces[a].y + faces[a].height;

			rectangle(myImage, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);
			//rectangle(frame, pt1, pt2, cvScalar(0, 255, 0, 0), 2, 8, 0);
			Rect myROI = Rect(pt1.x, pt1.y, pt2.x - pt1.x, pt2.y - pt1.y);
			//menyimpan potongan gambar wajah
			Mat gambar = myImage(myROI);
			equalizeHist(gambar, gambar);
			croppedImage.push_back(gambar);
		}
		
		//jika ada wajah yang terdeteksi
		if (faces.empty() == 0) {

			//ekstraksi fitur LBP untuk tiap potongan gambar
			for (int b = 0; b < croppedImage.size(); b++) {

				//deklarasi variabel penyimpan fitur LGP tiap wajah
				vector<float> lgpValues;
				int n = 5;
				for (int h = 1; h <= n; h++) {
					/*
					looping dari 0 - 2
					untuk:
					0. mengekstrak LBP jika 1 wajah ada 1 region dengan 9 sub  region
					1. mengekstrak LBP jika 1 wajah ada 9 region dengan 81 sub region
					2. mengekstrak LBP jika 1 wajah ada 81 region dengan 81 x 9 sub region
					*/
					if (h == 3) { continue; }
					if (h == 1) {
						for (int c = 0; c < 3; c++) {
							int jumlahLBP = pow(9, c);

							//jika jumlah LBP == 1, gambar langsung dibagi menjadi 9 SUBREGION dan diambil nilai LBP nya
							if (jumlahLBP == 1) {
								//gambar langsung dipecah menjadi 9 SUBREGION
								vector<Mat> subRegion = LGP::regionalImage(croppedImage[b], 3, 3);
								//menghitung nilai LBPnya
								lgpValues.push_back(LGP::regionalLGPValue(subRegion, 3));
							}

							//jika jumlah LBP > 1, gambar dipecah menjadi REGION dulu, kemudian SUBREGION
							else {
								//gambar dipecah menjadi 9^c REGION
								int akar = sqrt(jumlahLBP);
								vector<Mat> region = LGP::regionalImage(croppedImage[b], akar, akar);

								//tiap REGION dipecah menjadi 9 SUBREGION
								for (int d = 0; d < region.size(); d++) {
									//dipecah menjadi 9 SUBREGION
									vector <Mat> subRegion = LGP::regionalImage(region[d], 3, 3);
									lgpValues.push_back(LGP::regionalLGPValue(subRegion, 3));
								}
							}
						}
					}

					///////////////////////////////////////////
					//  ekstraksi LBP dengan pola 4 dan 36  ///
					//  total fitur terekstrak 40 fitur     ///
					///////////////////////////////////////////
					else {
						int init = h;
						//dua tahap
						for (int g = 0; g < 2; g++) {
							int jumlahLBP = pow(init, 2) * pow(9, g);
							int akar = sqrt(jumlahLBP);
							//memecah gambar menjadi sebanyak "jumlahLBP" REGION
							vector<Mat> region = LGP::regionalImage(croppedImage[b], akar, akar);
							//tiap REGION dipecah menjadi 9 SUBREGION
							for (int d = 0; d < region.size(); d++) {
								//dipecah menjadi 9 SUBREGION
								vector <Mat> subRegion = LGP::regionalImage(region[d], 3, 3);
								lgpValues.push_back(LGP::regionalLGPValue(subRegion, 3));
							}
						}
					}
				}
				
				//implementasi neural network
				// 1. normalisasi input (regionLBP)
				vector<double> normalisasi;
				normalisasi = NeuralNet::normalisasiInput(lgpValues, myNet);
				
				// 2. menghitung nilai hidden neuron
				vector<double> hiddVal;
				hiddVal = NeuralNet::hitungHiddenNeuron(normalisasi, 50, myNet); // jumlah hiiden neuron = 5
																 // 3. menghitung nilai output
				float output;
				output = NeuralNet::hitungOutput(hiddVal, myNet);
				string gender;
				
				if (output < 0.5) {
					gender = "male";
					male += 1.0;
					putText(frame, gender, Point(faces[b].x, faces[b].y - 2), FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 255, 0, 0), 1, 8);	
				}
				else {
					gender = "female";
					female += 1.0;
					putText(frame, gender, Point(faces[b].x, faces[b].y - 2), FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 0, 255, 0), 1, 8);
				}
				lgpValues.clear();
				
			}
		}
	
		//imshow("ckck", frame);
		cout << fileNames[i];
		cout << "\n";
		
		waitKey(3);
		//system("pause");
	}

	float akur = male / (male + female);
	cout << akur;
	cin.get();
}
#ifndef  _CSV_H_
#define _CSV_H_

using namespace std;
class CSV	{
	public:
		void CSV::readCSV(std::istream &input, std::vector< std::vector<int> > &output);
		void CSV::readCSV(std::istream &input, std::vector< std::vector<double> > &output);
		void CSV::readCSV(std::istream &input, std::vector< std::vector<float> > &output);
		void CSV::readCSV(std::istream &input, std::vector< std::vector<std::string> > &output);
		void CSV::readCSV(std::istream &input, std::vector< double> &output);
		void CSV::readCSV(std::istream &input, double &output);
		void CSV::writeCSV(std::string fileName, std::vector<float> inputChar, int kode);
		void CSV::writeCSV(std::string fileName, int code);
};
#endif // ! _CSV_H_


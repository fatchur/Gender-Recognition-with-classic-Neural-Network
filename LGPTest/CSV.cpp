#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "CSV.h"
using namespace std;

void CSV::readCSV(std::istream &input, std::vector< std::vector<int> > &output)
{
	std::string csvLine;
	// read every line from the stream
	while (std::getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::vector<int> csvColumn;
		std::string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (std::getline(csvStream, csvElement, ';'))
		{
			csvColumn.push_back(stoi(csvElement));
		}
		output.push_back(csvColumn);
	}
}
void CSV::readCSV(std::istream &input, std::vector< std::vector<double> > &output)
{
	std::string csvLine;
	// read every line from the stream
	while (std::getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::vector<double> csvColumn;
		std::string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (std::getline(csvStream, csvElement, ';'))
		{
			csvColumn.push_back(stod(csvElement));
		}
		output.push_back(csvColumn);
	}
}
void CSV::readCSV(std::istream &input, std::vector< std::vector<float> > &output)
{
	std::string csvLine;
	// read every line from the stream
	while (std::getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::vector<float> csvColumn;
		std::string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (std::getline(csvStream, csvElement, ';'))
		{
			csvColumn.push_back(stof(csvElement));
		}
		output.push_back(csvColumn);
	}
}
void CSV::readCSV(std::istream &input, std::vector< std::vector<std::string> > &output)
{
	std::string csvLine;
	// read every line from the stream
	while (std::getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::vector<std::string> csvColumn;
		std::string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (std::getline(csvStream, csvElement, ';'))
		{
			csvColumn.push_back(csvElement);
		}
		output.push_back(csvColumn);
	}
}
void CSV::readCSV(std::istream &input, std::vector<double> &output)
{
	std::string csvElement;
	while (std::getline(input, csvElement, ';'))
	{
		output.push_back(stod(csvElement));
	}
}
void CSV::readCSV(std::istream &input, double &output)
{
	std::string csvElement;
	while (std::getline(input, csvElement, ';'))
	{
		output = stod(csvElement);
	}
}
void CSV::writeCSV(std::string fileName, std::vector<float> inputChar, int code) {
	ofstream input;
	input.open(fileName, std::ios_base::app);
	for (int i = 0; i < inputChar.size(); i++) {

		input << inputChar[i];
		input << ";";
	}
	input << code;
	input << "\n";
}
void CSV::writeCSV(std::string fileName, int code) {
	ofstream input;
	input.open(fileName, std::ios_base::app);
	input << code;
	input << "\n";
}
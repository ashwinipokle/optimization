/*
 * textFileReader.h
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#ifndef TEXTFILEREADER_H_
#define TEXTFILEREADER_H_

#include "DataFeeder.h"
#include "Vector.h"
#include "TrainingInstance.h"
using namespace std;

#include<fstream>
#include<string>

class textFileReader: public DataFeeder {
public:
	textFileReader(const std::string& inputFilePath, int _featureNum,Vector::VectorType vtype);
	TrainingInstancePtr getNextInstance();
	void init();
private:
	std::shared_ptr<ifstream> fin;
	int featureNum;
	Vector::VectorType vectype;
};

#endif /* TEXTFILEREADER_H_ */

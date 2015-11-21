/*
 * textFileReader.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#include "textFileReader.h"
#include"TrainingInstance.h"
#include "VectoryFactory.h"

#include<fstream>
#include<iostream>
#include<sstream>

textFileReader::textFileReader(const std::string& inputFilePath, int _featureNum, Vector::VectorType vtype)
{
	this->fin = shared_ptr<ifstream>(new std::ifstream(inputFilePath));
	this->featureNum = _featureNum;
	this->vectype = vtype;
}

TrainingInstancePtr textFileReader::getNextInstance() {
	// TODO: check end of file and return null ptr
	
	std::string tempLine;
	while(!(*fin).eof()){
	getline((*fin), tempLine);
	std::cout<<"\n line : "<<tempLine;;
	istringstream iss(tempLine);
	
	int label;
	VectorPtr features;
	if(vectype == Vector::DENSE){

		features = createNewVector(Vector::DENSE, featureNum);

		for(int i=0;i<featureNum;i++) {
			iss >> (*features)[i];
		}
		iss >> label;
		std::cout<<"\nTrainingInstance : "; features->print();
	}
	else{
		double val;
		features = createNewVector(Vector::SPARSE, featureNum);

		for(int i=0;i<featureNum;i++) {
			iss >> val;
			if(val != 0)
				features->setValueAt(i,val);
		}
		iss >> label;
		std::cout<<"\nTrainingInstance : "; features->print();
	}
	return TrainingInstancePtr(new TrainingInstance(label, features));
	}
	return nullptr;
}

void textFileReader::init() {}

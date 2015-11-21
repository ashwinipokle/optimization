/*
 * Updater.h
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#ifndef UPDATER_H_
#define UPDATER_H_

#include "TrainingInstance.h"
#include "LossFunction.h"
#include<iostream>
#include<stdio.h>

class Updater {
public:
	Updater(LossFuncPtr _lossFunc, double _learningRate):
	  lossFunction(_lossFunc){
		learningRate = _learningRate;
	};
	virtual ~Updater(){}
public:
	virtual VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight) = 0;
	virtual void init() = 0;
	double getLearningRate() {return learningRate; }
	void setLearningRate(double value){ learningRate = value;}
public:
	std::shared_ptr<LossFunction> lossFunction;
	double learningRate;
};

typedef std::shared_ptr<Updater> UpdaterPtr;

#endif /* UPDATER_H_ */

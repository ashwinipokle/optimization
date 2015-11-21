/*
 * StochasticOptimizer.h
 *
 *  Created on: Jun 18, 2014
 *      Author: ashwini
 */

#ifndef STOCHASTICOPTIMIZER_H_
#define STOCHASTICOPTIMIZER_H_

#include<iostream>
#include<string>
#include<stdio.h>

#include "Vector.h"
#include "VectoryFactory.h"
#include "LossFunction.h"
#include "DataFeeder.h"
#include "Updater.h"



class StochasticOptimizer {
public:

	StochasticOptimizer(
		LossFuncPtr _myLoss,
		UpdaterPtr _myUpdater,
		DataFeederPtr _myFeeder,
		int _featureNum,
		Vector::VectorType _vecType,
		int _timestep,
		int _repetition
		):
		myLossFunc(_myLoss),
		myUpdater(_myUpdater),
		myDataFeeder(_myFeeder),
		featureNum(_featureNum),
		timestep(_timestep),
		repetition(_repetition),
		vecType(_vecType)
		{
			myUpdater->init();
			myDataFeeder->init();

			weight = createNewVector(vecType, featureNum);
		}
	virtual ~StochasticOptimizer(){}
	Vector& getWeight() { return *weight; }
	virtual void optimize() = 0;

protected:
		LossFuncPtr myLossFunc;
		UpdaterPtr myUpdater;
		DataFeederPtr myDataFeeder;

		int featureNum;
		int timestep;
		int repetition;
		Vector::VectorType vecType;
		VectorPtr weight;
};

#endif /* STOCHASTICOPTIMIZER_H_ */

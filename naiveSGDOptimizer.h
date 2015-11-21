/*
 * naiveSGDOptimizer.h
 *
 *  Created on: Jun 5, 2014
 *      Author: ashwini
 */

#ifndef NAIVESGDOPTIMIZER_H_
#define NAIVESGDOPTIMIZER_H_

#include "StochasticOptimizer.h"
#include "stocGradDescUpdater.h"

class naiveSGDOptimizer: public StochasticOptimizer {
public:
	naiveSGDOptimizer(
		LossFuncPtr _myLoss,
		DataFeederPtr _myFeeder,
		Vector::VectorType _vecType,
		int _featureNum,
		double learningrate, 
		double _epsilon,
		double _timestep,
		double _repeat
	):
		StochasticOptimizer(
			_myLoss,
			UpdaterPtr(new stocGradDescUpdater(_myLoss, learningrate)),
			_myFeeder,
			_featureNum,
			_vecType,
			_timestep,
			_repeat
		),
		epsilon(_epsilon) {};

	void optimize();
private:
	double epsilon;	// convergence bound
};
#endif /* NAIVESGDOPTIMIZER_H_ */

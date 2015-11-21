/*
 * PDL1RegOptimizer.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDL1REGOPTIMIZER_H_
#define PDL1REGOPTIMIZER_H_

#include "StochasticOptimizer.h"
#include"PDL1RegUpdater.h"

class PDL1RegOptimizer : public StochasticOptimizer {
public:
	PDL1RegOptimizer(
		LossFuncPtr _myLoss,
		DataFeederPtr _myFeeder,
		Vector::VectorType _vecType,
		int _featureNum,
		double learningrate,
		double delta,
		double lambda,
		double _epsilon,
		int _timestep,
		int _repeat
	):
		StochasticOptimizer(
			_myLoss,
			UpdaterPtr(new PDL1RegUpdater(_myLoss,_vecType,learningrate,delta,lambda,_timestep,_featureNum)),
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

#endif /* PDL1REGOPTIMIZER_H_ */

/*
 * PDL2RegOptimizer.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDL2REGOPTIMIZER_H_
#define PDL2REGOPTIMIZER_H_

#include "StochasticOptimizer.h"
#include "PDL2RegUpdater.h"


class PDL2RegOptimizer: public StochasticOptimizer {
public:
	PDL2RegOptimizer(
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
			UpdaterPtr(new PDL2RegUpdater(_myLoss,_vecType,learningrate,delta,lambda,_epsilon,_timestep,_featureNum)),
			_myFeeder,
			_featureNum,
			_vecType,
			_timestep,
			_repeat
		)
	{};

	void optimize();
};

#endif /* PDL2REGOPTIMIZER_H_ */

/*
 * PDL1BallOptimizer.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDL1BALLOPTIMIZER_H_
#define PDL1BALLOPTIMIZER_H_

#include"StochasticOptimizer.h"
#include"PDL1BallUpdater.h"

class PDL1BallOptimizer : public StochasticOptimizer {
public:
	PDL1BallOptimizer(
		LossFuncPtr _myLoss,
		DataFeederPtr _myFeeder,
		Vector::VectorType _vecType,
		int _featureNum,
		double learningrate,
		double delta,
		double c,
		double _epsilon,
		int _timestep,
		int _repeat
	):
		StochasticOptimizer(
			_myLoss,
			UpdaterPtr(new PDL1BallUpdater(_myLoss,_vecType,learningrate,delta,c,_timestep,_featureNum)),
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

#endif /* PDL1BALLOPTIMIZER_H_ */

/*
 * CML1BallOptimizer.h
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */

#ifndef CML1BALLOPTIMIZER_H_
#define CML1BALLOPTIMIZER_H_

#include "Updater.h"
#include "StochasticOptimizer.h"
#include "CML1BallUpdater.h"

class CML1BallOptimizer: public StochasticOptimizer {
public:
	CML1BallOptimizer(LossFuncPtr _myLoss,
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
			UpdaterPtr(new CML1BallUpdater(_myLoss,_vecType,learningrate,delta,c,_timestep,_featureNum)),
			_myFeeder,
			_featureNum,
			_vecType,
			_timestep,
			_repeat
		){};

	void optimize(){
		do{
			for(int i=1;i<timestep;i++) {
				std::cout<<"\nHere! : " << i;
				TrainingInstancePtr input = myDataFeeder->getNextInstance();
				double loss = myLossFunc->getValue(weight, input);
				std::cout<<"\nLoss before : "<<loss;
				weight = myUpdater->updateWeight(input, weight);
				std::cout<<"\n Weight Vector : "; weight->print();
				loss = myLossFunc->getValue(weight, input);
				std::cout<<"\nLoss after : "<<loss;
			}
			repetition--;
			}while(repetition > 0);
		}
};
#endif /* CML1BALLOPTIMIZER_H_ */

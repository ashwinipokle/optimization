/*
 * PDLinfOptimizer.h
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */

#ifndef PDLINFOPTIMIZER_H_
#define PDLINFOPTIMIZER_H_

#include "StochasticOptimizer.h"
#include "PDL2RegUpdater.h"


class PDLinfOptimizer: public StochasticOptimizer {
public:
	PDLinfOptimizer(
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
			UpdaterPtr(new PDLinfUpdater(_myLoss,_vecType,learningrate,delta,lambda,_epsilon,_timestep,_featureNum)),
			_myFeeder,
			_featureNum,
			_vecType,
			_timestep,
			_repeat
		)
	{};

	void optimize()
	{
		do{
			for(int i=1;i<timestep;i++) {
				TrainingInstancePtr input = myDataFeeder->getNextInstance();
				double loss = myLossFunc->getValue(weight, input);
				std::cout<<"\nLoss before : "<<loss;
				weight = myUpdater->updateWeight(input, weight);
				std::cout<<"\n Weight Vector : ";
				weight->print();
				loss = myLossFunc->getValue(weight, input);
				std::cout<<"\nLoss after : "<<loss;
			}
			repetition--;
			}while(repetition > 0);
	}
};

#endif /* PDLINFOPTIMIZER_H_ */

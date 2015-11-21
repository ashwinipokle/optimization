/*
 * CML2RegOptimizer.h
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */

#ifndef CML2REGOPTIMIZER_H_
#define CML2REGOPTIMIZER_H_

#include "StochasticOptimizer.h"
#include "CML2RegUpdater.h"

class CML2RegOptimizer: public StochasticOptimizer {
public:
	CML2RegOptimizer(LossFuncPtr _myLoss,
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
				UpdaterPtr(new CML2RegUpdater(_myLoss,_vecType,learningrate,delta,lambda,_epsilon,_timestep,_featureNum)),
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
				std::cout<<" Here! "<<i;
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
#endif /* CML2REGOPTIMIZER_H_ */

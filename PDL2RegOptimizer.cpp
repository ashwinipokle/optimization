/*
 * PDL2RegOptimizer.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#include "PDL2RegOptimizer.h"

void PDL2RegOptimizer::optimize()
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


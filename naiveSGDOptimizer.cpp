/*
 * naiveSGDOptimizer.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: ashwini
 */
#include "Vector.h"
#include "DenseVector.h"
#include "TrainingInstance.h"
#include "naiveSGDOptimizer.h"

void naiveSGDOptimizer::optimize()
{
	do{
	for(int i=1;i<timestep;i++) {
		TrainingInstancePtr input = myDataFeeder->getNextInstance();
		//std::cout<<"\n label : "<<input->label;
		//std::cout<<" features : ";input->features->print();
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

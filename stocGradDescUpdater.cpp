/*
 * stocGradDesc.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#include "stocGradDescUpdater.h"
#include "LossFunction.h"
#include "Vector.h"

VectorPtr stocGradDescUpdater::updateWeight(const TrainingInstancePtr input, VectorPtr weight) {
	VectorPtr subgradient = lossFunction->getSubgradient(weight, input);
	subgradient->multiply(this->getLearningRate());
	weight->minus(*subgradient);
	std::cout<<" weight : "; weight->print();
	return weight;
}

void stocGradDescUpdater::init(){}

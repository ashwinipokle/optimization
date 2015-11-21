/*
 * SquareLoss.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#include "SquareLoss.h"
#include "Vector.h"
#include "VectoryFactory.h"
#include "TrainingInstance.h"

double SquareLoss::getValue(const VectorPtr weight, const TrainingInstancePtr input) {
	double prod = weight->innerProduct(*(input->features));
	return 0.5*(prod - input->label)*(prod - input->label);
}

VectorPtr SquareLoss::getSubgradient(const VectorPtr weight, const TrainingInstancePtr input) {
	
	double prod = weight->innerProduct(*(input->features)) - input->label;
	VectorPtr subgradient = input->features->clone();
	subgradient->multiply(prod);
	return subgradient;
}




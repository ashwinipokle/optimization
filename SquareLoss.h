/*
 * SquareLoss.h
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#ifndef SQUARELOSS_H_
#define SQUARELOSS_H_

#include "LossFunction.h"

class SquareLoss: public LossFunction {
public:
	double getValue(const VectorPtr weight, const TrainingInstancePtr input);
	VectorPtr getSubgradient(const VectorPtr weight, const TrainingInstancePtr input);
};

#endif /* SQUARELOSS_H_ */


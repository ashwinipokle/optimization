/*
 * LossFunction.h
 *
 *  Created on: Jun 18, 2014
 *      Author: ashwini
 */

#ifndef LOSSFUNCTION_H_
#define LOSSFUNCTION_H_

#include"TrainingInstance.h"
#include"Vector.h"

#include <memory>

class LossFunction {
public:
	virtual ~LossFunction(){}

public:
	virtual double getValue(const VectorPtr weight,const TrainingInstancePtr input) = 0;
	virtual VectorPtr getSubgradient(const VectorPtr weight,const TrainingInstancePtr input) = 0;
};

typedef std::shared_ptr<LossFunction> LossFuncPtr;

#endif /* LOSSFUNCTION_H_ */

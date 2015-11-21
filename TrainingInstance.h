/*
 * TrainingInstance.h
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#ifndef TRAININGINSTANCE_H_
#define TRAININGINSTANCE_H_

#include"Vector.h"

class TrainingInstance {
public:
	TrainingInstance(int _label, VectorPtr _features):
	  label(_label), features(_features) {}
	TrainingInstance(int _label, Vector* _features):
	  label(_label), features(_features) {}
public:
	double label;
	VectorPtr features;
};

typedef std::shared_ptr<TrainingInstance> TrainingInstancePtr;

#endif /* TRAININGINSTANCE_H_ */

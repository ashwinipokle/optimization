/*
 * stocGradDesc.h
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#ifndef STOCGRADDESC_H_
#define STOCGRADDESC_H_

#include "Updater.h"

class stocGradDescUpdater: public Updater {
public:
	stocGradDescUpdater(LossFuncPtr _lossfunc, double _learningRate):
	  Updater(_lossfunc,_learningRate) {};
	~stocGradDescUpdater() {}
	VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
	void init();
};

#endif /* STOCGRADDESC_H_ */

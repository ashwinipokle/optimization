/*
 * PDL1RegUpdater.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDL1REGUPDATER_H_
#define PDL1REGUPDATER_H_

#include "Vector.h"
#include "DenseVector.h"
#include "Updater.h"
#include"SparseVector.h"
class PDL1RegUpdater: public Updater {
public:
	PDL1RegUpdater(LossFuncPtr _lossfunc, Vector::VectorType vecType, double _learningRate,double _delta,double _lambda,int _T,int _dimension):
	  Updater(_lossfunc,_learningRate),lambda(_lambda),delta(_delta),T(_T),dimension(_dimension)
	{
		timestep = 1;
		if(vecType == Vector::DENSE)
		{
			avgSubgrad = VectorPtr(new DenseVector(_dimension));
			sqrSubgrad = VectorPtr(new DenseVector(_dimension));
		}
		else
		{

			avgSubgrad = VectorPtr(new SparseVector());
			sqrSubgrad = VectorPtr(new SparseVector());
		}
	}
	~PDL1RegUpdater() {}
	VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
	void init();
private:
	double lambda;
	double delta;
	int T;	//total iterations required for gradient descent
	int dimension;
	int timestep; //variable to keep track of timsteps completed
	VectorPtr avgSubgrad;
	VectorPtr sqrSubgrad;
};

#endif /* PDL1REGUPDATER_H_ */

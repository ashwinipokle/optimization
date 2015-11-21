/*
 * PDLinfUpdater.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDLINFUPDATER_H_
#define PDLINFUPDATER_H_

#include "Vector.h"
#include "DenseVector.h"
#include "Updater.h"
#include"SparseVector.h"
class PDLinfUpdater: public Updater {
	public:
		PDLinfUpdater(LossFuncPtr _lossfunc, Vector::VectorType vecType, double _learningRate,double _delta,double _lambda,double _epsilon,int _T,int _dimension):
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
		~PDLinfUpdater() {}
		VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
		void init();
		VectorPtr generalL1Proj(VectorPtr v,VectorPtr a,double lambda,VectorPtr z);

	private:
		double lambda;
		double delta;
		int T;	//total iterations required for gradient descent
		int dimension;
		int timestep; //variable to keep track of timesteps completed
		VectorPtr avgSubgrad;
		VectorPtr sqrSubgrad;
};

#endif /* PDLINFUPDATER_H_ */

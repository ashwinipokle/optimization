/*
 * PDL1BallUpdater.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDL1BALLUPDATER_H_
#define PDL1BALLUPDATER_H_

#include"Updater.h"
#include"SparseVector.h"
#include"Vector.h"
#include"DenseVector.h"
class PDL1BallUpdater: public Updater {
public:
	PDL1BallUpdater(LossFuncPtr _lossfunc, Vector::VectorType vecType, double _learningRate,double _delta,double _c,int _T,int _dimension):
		  Updater(_lossfunc,_learningRate),delta(_delta),c(_c),T(_T),dimension(_dimension)
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
		~PDL1BallUpdater() {}
		VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
		void init();
		VectorPtr getOptParam(VectorPtr v,VectorPtr ht,double c,VectorPtr z);
private:
		double delta;
		double c;
		int T;	//total iterations required for gradient descent
		int dimension;
		int timestep; //variable to keep track of timsteps completed
		VectorPtr avgSubgrad;
		VectorPtr sqrSubgrad;
};

#endif /* PDL1BALLUPDATER_H_ */

/*
 * PDL2RegUpdater.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#ifndef PDL2REGUPDATER_H_
#define PDL2REGUPDATER_H_

#include"Vector.h"
#include"DenseVector.h"
#include"Updater.h"
#include"SparseVector.h"
class PDL2RegUpdater : public Updater{
public:
	PDL2RegUpdater(LossFuncPtr _lossfunc, Vector::VectorType vecType, double _learningRate,double _delta,double _lambda,double _epsilon,int _T,int _dimension):
		  Updater(_lossfunc,_learningRate),lambda(_lambda),delta(_delta),epsilon(_epsilon),T(_T),dimension(_dimension)
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
		~PDL2RegUpdater() {}
		VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
		void init();
		VectorPtr PDL2minimize(VectorPtr u, VectorPtr ht, double lambda,double epsilon,VectorPtr weight);
	private:
		double lambda;
		double delta;
		double epsilon;
		int T;	//total iterations required for gradient descent
		int dimension;
		int timestep; //variable to keep track of timsteps completed
		VectorPtr avgSubgrad;
		VectorPtr sqrSubgrad;
};

#endif /* PDL2REGUPDATER_H_ */


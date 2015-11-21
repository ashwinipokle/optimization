/*
 * CML1RegUpdater.h
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */

#ifndef CML1REGUPDATER_H_
#define CML1REGUPDATER_H_

#include "Updater.h"
#include "SparseVector.h"
#include "Vector.h"
#include "DenseVector.h"
class CML1RegUpdater:public Updater {
		public:
			CML1RegUpdater(LossFuncPtr _lossfunc, Vector::VectorType vecType, double _learningRate,double _delta,double _lambda,double _epsilon,int _T,int _dimension):
				  Updater(_lossfunc,_learningRate),lambda(_lambda),delta(_delta),T(_T),dimension(_dimension)
			{
				timestep = 1;
				if(vecType == Vector::DENSE)
				{
					sqrSubgrad = VectorPtr(new DenseVector(_dimension));
				}
				else
				{
					sqrSubgrad = VectorPtr(new SparseVector());
				}
			}
			~CML1RegUpdater() {}
			VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
			void init();

		private:
			double lambda;
			double delta;
			int T;	//total iterations required for gradient descent
			int dimension;
			int timestep; //variable to keep track of timesteps completed
			VectorPtr sqrSubgrad;
};
#endif /* CML1REGUPDATER_H_ */

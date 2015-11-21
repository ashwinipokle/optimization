/*
 * CML2RegUpdater.h
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */

#ifndef CML2REGUPDATER_H_
#define CML2REGUPDATER_H_

#include "Updater.h"

class CML2RegUpdater: public Updater {
public:
		CML2RegUpdater(LossFuncPtr _lossfunc, Vector::VectorType vecType, double _learningRate,double _delta,double _lambda,double _epsilon,int _T,int _dimension):
			Updater(_lossfunc,_learningRate),lambda(_lambda),delta(_delta),epsilon(_epsilon),T(_T),dimension(_dimension)
			{
				timestep = 1;
				if(vecType == Vector::DENSE)
				{
					sqrSubgrad = VectorPtr(new DenseVector(_dimension));
				}
			}
			~CML2RegUpdater() {}
			VectorPtr updateWeight(const TrainingInstancePtr input, VectorPtr weight);
			void init();
			VectorPtr CML2minimize(VectorPtr u, VectorPtr ht, double lambda,double epsilon,VectorPtr weight);
		private:
			double lambda;
			double delta;
			double epsilon;
			int T;	//total iterations required for gradient descent
			int dimension;
			int timestep; //variable to keep track of timsteps completed
			VectorPtr sqrSubgrad;
};
#endif /* CML2REGUPDATER_H_ */

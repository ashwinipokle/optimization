/*
 * PDL2RegUpdater.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#include "PDL2RegUpdater.h"
#include<cmath>
#include<iostream>
#include<stdio.h>

VectorPtr PDL2RegUpdater::updateWeight(const TrainingInstancePtr input, VectorPtr weight)
{
	VectorPtr subgradient = lossFunction->getSubgradient(weight, input);
	VectorPtr subgradClone = subgradient->clone();
	VectorPtr ht,u;
	if(weight->getType() == Vector::DENSE){
		ht = VectorPtr(new DenseVector(weight->size()));
		u = VectorPtr(new DenseVector(weight->size()));
	}
	else
	{
		//initialize for sparse Vector case
		ht = VectorPtr(new SparseVector());
		u = VectorPtr(new SparseVector());
	}
	std::cout<<"\n Sub Gradient vector : "; subgradient->print();

	if(timestep == 1){
		avgSubgrad = subgradient->clone();
		subgradient->multiply(*subgradient);
		sqrSubgrad = subgradient->clone();
	}
	else
	{
		//calculations for avgSubgrad
		avgSubgrad->multiply((double)(timestep-1)/timestep);
		//std::cout<<"\n timestep : "<<(double)(timestep-1)/timestep; avgSubgrad->print();
		subgradient->multiply(1.0/timestep);
		avgSubgrad->plus(*subgradient);
		//calculations for sqrSubGrad
		subgradClone->multiply(*subgradClone);
		sqrSubgrad->plus(*subgradClone);
		//sqrSubgrad[i] += subgradient[i]*subgradient[i];
	}

	int index;
	VectorPtr indices = avgSubgrad->getValidIndices();
	for(int i=0;i<indices->size();i++)
	{
		index = indices->getValueAt(i);
		u->setValueAt(index,learningRate*timestep*avgSubgrad->getValueAt(index)); // u will be non zero only when avgSbgrad is non-zero ; so valid
	}
	indices = sqrSubgrad->getValidIndices();
	for(int i=0;i<dimension;i++)
	{
		ht->setValueAt(i,delta + sqrt(sqrSubgrad->getValueAt(i)));	// getValueAt() should handle in-valid indices as well for sparse case ; better if it returns 0
	}

	timestep++;
	weight = PDL2minimize(u,ht,lambda,epsilon,weight);
	return weight;
}
void PDL2RegUpdater::init(){}

VectorPtr PDL2RegUpdater::PDL2minimize(VectorPtr u, VectorPtr ht, double lambda,double epsilon,VectorPtr weight)
{
	//assuming matrix H is diagonal H = delta*I + diag(Gt)

	int i,j;
	double sum =0;

	VectorPtr v,alpha;
	if(weight->getType() == Vector::DENSE){
		v = VectorPtr(new DenseVector(weight->size()));
		alpha = VectorPtr(new DenseVector(weight->size()));
	}else
	{
		v = VectorPtr(new SparseVector());
		alpha = VectorPtr(new SparseVector());
	}

	sum = u->innerProduct(*u);

	//for(i=0;i < u->size();i++) sum+=u[i] * u[i];

	if(sqrt(sum) < lambda) {
		std::cout<<"l2norm(u) : "<<sqrt(sum)<<" lambda : "<< lambda;
		weight->setValue(0); //set weight vector to all 0s according to algorithm
		return weight;
	}
	double l2norm = sqrt(v->innerProduct(*v));

	double minSigVal = ht->getValueAt(0);
	double maxSigVal = ht->getValueAt(0);
	double maxtheta,mintheta;
	double theta;

	VectorPtr htClone = ht->clone();

	//get inverse of diagonal matrix which is simply the inverse f each of the diagonal entries
	htClone->inverse();
	htClone->multiply(*u);
	v = htClone->clone();

	/*The above three lines basically perform following update */
	/*for(int i=0;i<v.size();i++)
	{	v[i] = (1/ht[i])*u[i];
	}
	*/

	//diag entries will be eigen values of ht matrix
	double htValue;
	VectorPtr indices = ht->getValidIndices();
	for(j=1;j<indices->size();j++)
	{
		i = indices->getValueAt(j);
		htValue = ht->getValueAt(i);
		if(htValue > maxSigVal) maxSigVal = htValue;
		if(htValue < minSigVal) minSigVal = htValue;
	}
	//singular values are square root of eigen values of diag matrix
	maxSigVal = sqrt(maxSigVal);
	minSigVal = sqrt(minSigVal);

	std::cout<<"maxSigval : "<<maxSigVal;
	std::cout<<"\t minSigVal : "<<minSigVal;

	maxtheta = l2norm/lambda - 1/minSigVal;
	mintheta = l2norm/lambda - 1/maxSigVal;

	VectorPtr htInv = ht->clone();
	htInv->inverse();

	while(maxtheta - mintheta > epsilon)
	{
		theta = (maxtheta + mintheta)/2;

		htInv->plus(theta);
		htInv->inverse();
		htInv->multiply(*v);
		htInv->multiply(-1);

		/*Above lines replicate the following update
		 *
		for(int i=0;i<weight.size();i++)
		{
			alpha[i] = -1*(1/((1/ht[i])+theta))*v[i];
		}
		*/
		l2norm = sqrt(alpha->innerProduct(*alpha));

		// Perform following update
		//for(int i=0;i<alpha->size();i++) l2norm+=alpha[i]*alpha[i];
		//l2norm = sqrt(l2norm);

		if(l2norm > lambda)	mintheta = theta;
		else maxtheta = theta;
	}

	std::cout<<"\n ht vector : ";
	ht->print();

	std::cout<<" \n Updating weight vectors! \n ";

	htInv = ht->clone();
	htInv->inverse();
	u->plus(*alpha);
	htInv->multiply(*u);
	htInv->multiply(-1);
	weight = htInv->clone();
	weight->print();
	/*
	for(i = 0;i<weight.size();i++)
		weight[i] = -1 * (1/ht[i])*(u[i] + alpha[i]);
	}
	*/
	return weight;
}

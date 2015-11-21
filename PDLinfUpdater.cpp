/*
 * PDLinfUpdater.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#include "PDLinfUpdater.h"
#include"Vector.h"
#include"DenseVector.h"
#include"PDLinfUpdater.h"
#include"SparseVector.h"
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>

VectorPtr PDLinfUpdater::updateWeight(const TrainingInstancePtr input, VectorPtr weight)
{
	VectorPtr subgradient = lossFunction->getSubgradient(weight, input);
	VectorPtr subgradClone = subgradient->clone();
	VectorPtr ht,v,z;
	VectorPtr temp;
	if(weight->getType() == Vector::DENSE){
		ht = VectorPtr(new DenseVector(weight->size()));
		v = VectorPtr(new DenseVector(weight->size()));
		temp = VectorPtr(new DenseVector(weight->size()));
		z = VectorPtr(new DenseVector(weight->size()));
	}
	else
	{
		//initialize for sparse Vector case
		ht = VectorPtr(new SparseVector());
		v = VectorPtr(new SparseVector());
		temp = VectorPtr(new SparseVector());
		z = VectorPtr(new SparseVector());

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
		subgradient->multiply(1.0/timestep);
		avgSubgrad->plus(*subgradient);
		//calculations for sqrSubGrad

		//square of subgradient
		subgradClone->multiply(*subgradClone);
		sqrSubgrad->plus(*subgradClone);
		//sqrSubgrad[i] += subgradient[i]*subgradient[i];

		//ht[i] = sqrt(1/(delta + sqrt(sqrSubgrad[i])));
		temp = sqrSubgrad->clone();
		temp->sqroot();
		temp->plus(delta);
		temp->inverse();
		ht = temp->clone();
		temp->sqroot();
		}

		for(int i=0;i<dimension;i++)
			v->setValueAt(i,-1*learningRate*timestep*ht->getValueAt(i)*avgSubgrad->getValueAt(i));

		z = generalL1Proj(v,temp,lambda,z);

		VectorPtr avgSubgradClone = avgSubgrad->clone();
		avgSubgradClone->multiply(-1*learningRate*timestep);
		avgSubgradClone->plus(*z);
		ht->multiply(-1);
		avgSubgradClone->multiply(*ht);
		weight = avgSubgradClone->clone();
		/*
		for(int i=0;i< weight.size();i++)
		{
			weight[i] = -1 * (1/(delta + sqrt(sqrSubgrad[i]))) * (-1 * learningrate*timestep*avgSubgrad[i] + z[i]);
		}
 	 	 */
		timestep++;
		return weight;
}
void PDLinfUpdater::init(){}

VectorPtr PDLinfUpdater::generalL1Proj(VectorPtr v,VectorPtr a,double lambda,VectorPtr z)
{
	std::vector<double> mu (0,v->size());

	VectorPtr vClone = v->clone();
	VectorPtr aClone = a->clone();

	double sum = v->innerProduct(*v);

	int i;
	double theta = 0;
	if(sum <= lambda){
		z = v->clone();
		std::cout<<" Here! "; return z;
	}

	//for(i=0;i<v.size();i++) mu[i] = v[i]/a[i];

	aClone->inverse();
	vClone->multiply(*aClone); //vClone holds v[i]/a[i]

	for(int i=0;i<dimension;i++)
		mu[i] = vClone->getValueAt(i); // mu = v/a

	//sort in descending order
	std::sort(mu.begin(),mu.end(),std::greater<int>());

	double max = 0; int index=-1;

	sum = 0;
	std::vector<double> prod_av (v->size());
	std::vector<double> sumSqr_a (v->size());

	prod_av[0] = a->getValueAt(0)*v->getValueAt(0);
	sumSqr_a[0] = a->getValueAt(0) * a->getValueAt(0);

	for(i=1;i<v->size(); i++)
	{
		prod_av[i] = prod_av[i-1] + a->getValueAt(i)*v->getValueAt(i);
		sumSqr_a[i] = sumSqr_a[i-1] + a->getValueAt(i)*a->getValueAt(i);
	}
	for(i=0;i<v->size();i++){
		sum += prod_av[i] - mu[i] * sumSqr_a[i];
		if(sum > max && sum < lambda)
		{
			max = sum;
			index = i;
		}
	}
	sum = 0;
	theta = (prod_av[index] - lambda)/sumSqr_a[index];

	std::cout<<"theta : "<<theta;

	a->multiply(theta);
	v->minus(*a);
	z->setValue(0);
	VectorPtr indices = v->getPositiveIndices();

	for(i=0;i<indices->size();i++)
	{
		index = indices->getValueAt(i);
		z->setValueAt(index,v->getValueAt(index));
	}
	return z;
}

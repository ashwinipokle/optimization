/*
 * CML1RegUpdater.cpp
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */
#include"Vector.h"
#include"DenseVector.h"
#include "SparseVector.h"
#include"CML1RegUpdater.h"
#include<cmath>
#include<iostream>
#include<stdio.h>
VectorPtr CML1RegUpdater::updateWeight(const TrainingInstancePtr input, VectorPtr weight)
{
	VectorPtr subgradient = lossFunction->getSubgradient(weight, input);
	VectorPtr subgradClone = subgradient->clone();
	std::cout<<"\n Sub Gradient vector : "; subgradient->print();
	VectorPtr ht,temp;
	if(weight->getType() == Vector::DENSE)
	{
		ht = VectorPtr(new DenseVector(weight->size()));
		temp = VectorPtr(new DenseVector(weight->size()));
	}
	else
	{
		ht = VectorPtr(new SparseVector());
		temp = VectorPtr(new SparseVector());
	}
	if(timestep == 1){
		subgradient->multiply(*subgradient);
		sqrSubgrad = subgradient->clone();
	}
	else
	{
		//calculations for sqrSubGrad
		subgradClone->multiply(*subgradClone);
		sqrSubgrad->plus(*subgradClone);
	}
	temp = sqrSubgrad->clone();
	temp->sqroot();
	temp->plus(delta);
	temp->inverse();
	ht = temp->clone();

	temp->multiply(learningRate);
	temp->multiply(*subgradient);

	timestep++; //increment the timestep

	double val;
	weight->setValue(0);
	for(int i=0;i<dimension;i++)
	{
		val = weight->getValueAt(i) - temp->getValueAt(i);
		if(std::abs(val) > lambda*learningRate*ht->getValueAt(i))
		{
			if(val > 0) weight->setValueAt(i,val - lambda*learningRate*ht->getValueAt(i));
			else weight->setValueAt(i,-1*val - lambda*learningRate*ht->getValueAt(i));
		}
	}
	/* Above loop replicates following loop updates for weight vector
	for(int i=0;i<dimension;i++)
	{
		val = weight[i] - (learningrate/(delta + sqrt(sqrSubgrad[i]))) * subgradient[i];
		if(abs(val) > lambda*learningrate/(delta + sqrt(sqrSubgrad[i])))
		{
			if(val > 0) weight[i] = val - lambda*learningrate/(delta + sqrt(sqrSubgrad[i]));
			else weight[i] = -1 * (val - lambda*learningrate/(delta + sqrt(sqrSubgrad[i])));
		}
		else weight[i] = 0;
	}*/
	return weight;
}
void CML1RegUpdater::init(){}

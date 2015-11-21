/*
 * PDL1RegUpdater.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: ashwini
 */

#include"PDL1RegUpdater.h"
#include<cmath>
#include<iostream>
#include<stdio.h>
VectorPtr PDL1RegUpdater::updateWeight(const TrainingInstancePtr input, VectorPtr weight)
{
	VectorPtr subgradient = lossFunction->getSubgradient(weight, input);
	VectorPtr subgradClone = subgradient->clone();
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
		subgradClone->multiply(*subgradClone);
		sqrSubgrad->plus(*subgradClone);
		//sqrSubgrad[i] += subgradient[i]*subgradient[i];
	}
	timestep++; //increment the timestep

	std::cout<<"avgSubgrad : "; avgSubgrad->print();
	std::cout<<"sqrSubgrad : "; sqrSubgrad->print();

	double val;
	int i;
	double weightVal = 0;
	VectorPtr indices = subgradient->getValidIndices();
	for(int j=0;j<indices->size();j++)
	{
		i = (int)indices->getValueAt(j);	//getValueAt returns double
		val = avgSubgrad->getValueAt(i);
		if(std::abs(val) > lambda){
			weightVal = (learningRate/(delta + sqrt(sqrSubgrad->getValueAt(i))))*(avgSubgrad->getValueAt(i) - lambda);
			std::cout<<"weightVal : "<<weightVal;
			if(avgSubgrad->getValueAt(i) > 0 ) weightVal*=-1;
		}else weightVal = 0;
		weight->setValueAt(i,weightVal);
	}
	return weight;
}
void PDL1RegUpdater::init(){}

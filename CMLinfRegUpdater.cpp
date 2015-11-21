/*
 * CMLinfRegUpdater.cpp
 *
 *  Created on: Jun 20, 2014
 *      Author: ashwini
 */

#include "CMLinfRegUpdater.h"

#include"Vector.h"
#include"DenseVector.h"
#include"SparseVector.h"
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>

VectorPtr CMLinfRegUpdater::updateWeight(const TrainingInstancePtr input, VectorPtr weight)
{
	VectorPtr subgradient = lossFunction->getSubgradient(weight, input);
	VectorPtr subgradClone = subgradient->clone();
	VectorPtr ht,u,a;
	VectorPtr temp;
	if(weight->getType() == Vector::DENSE){
		ht = VectorPtr(new DenseVector(weight->size()));
		u = VectorPtr(new DenseVector(weight->size()));
		temp = VectorPtr(new DenseVector(weight->size()));
		a = VectorPtr(new DenseVector(weight->size()));
	}
	else
	{
		//initialize for sparse Vector case
		ht = VectorPtr(new SparseVector());
		u = VectorPtr(new SparseVector());
		temp = VectorPtr(new SparseVector());
		a = VectorPtr(new SparseVector());
	}
	std::cout<<"\n Sub Gradient vector : "; subgradient->print();

	if(timestep == 1){
		subgradient->multiply(*subgradient);
		sqrSubgrad = subgradient->clone();
	}
	else
	{
		//square of subgradient
		subgradClone->multiply(*subgradClone);
		sqrSubgrad->plus(*subgradClone);
		//sqrSubgrad[i] += subgradient[i]*subgradient[i];
	}
		//ht[i] = sqrt(1/(delta + sqrt(sqrSubgrad[i])));
	temp = sqrSubgrad->clone();
	temp->sqroot();
	temp->plus(delta);
	ht = temp->clone();
	temp->sqroot();
	temp->inverse();

	for(int i=0;i<dimension;i++)
			u->setValueAt(i,learningRate*subgradient->getValueAt(i) - ht->getValueAt(i)*weight->getValueAt(i));

	a = generalL1Proj(u,temp,lambda,a);

	a->plus(*u);
	a->multiply(-1);
	ht->inverse();
	a->multiply(*ht);
	weight = a->clone();
	timestep++;
	return weight;
}
void CMLinfRegUpdater::init(){}

VectorPtr CMLinfRegUpdater::generalL1Proj(VectorPtr v,VectorPtr a,double lambda,VectorPtr z)
{

	std::vector<double> mu (v->size());

	VectorPtr vClone = v->clone();
	VectorPtr aClone = a->clone();

	double sum =0;

	for(int j=0;j<dimension;j++)
		sum+=v->getValueAt(j);

	std::cout<<"sum : "<<sum;
	int i;
	double theta = 0;
	if(sum <= lambda){
		z = v->clone();
		return z;
	}

	//for(i=0;i<v.size();i++) mu[i] = v[i]/a[i];

	aClone->inverse();
	vClone->multiply(*aClone); //vClone holds v[i]/a[i]

	for(int i=0;i<dimension;i++)
		mu[i] = vClone->getValueAt(i); // mu = v/a

	//sort in descending order
	std::sort(mu.begin(),mu.end(),std::greater<int>());

	double max = 0; int index=-1;

	std::vector<double> prod_av (v->size());
	std::vector<double> sumSqr_a (v->size());

	//cumuative sum of products and squares of products
	prod_av[0] = a->getValueAt(0)*v->getValueAt(0);
	sumSqr_a[0] = a->getValueAt(0) * a->getValueAt(0);

	for(i=1;i<v->size(); i++)
	{
		prod_av[i] = prod_av[i-1] + a->getValueAt(i)*v->getValueAt(i);
		sumSqr_a[i] = sumSqr_a[i-1] + a->getValueAt(i)*a->getValueAt(i);

		//std::cout<<" prod_av [ "<<i<<" ] : "<<prod_av[i];
		std::cout<<" sumSqr_a [ "<<i<<" ] : "<<sumSqr_a[i];
	}

	for(i=0;i<v->size();i++){
		sum += prod_av[i] - mu[i] * sumSqr_a[i];
		std::cout<<" sum [ "<<i<<" ] : "<<sum;
		if(sum > max && sumSqr_a[i] < lambda)
		{
			std::cout<<"Here ! max : "<<max<<" sum : "<<sum;
			max = sum;
			index = i;
		}
	}
	sum = 0;

	theta = (prod_av[index] - lambda)/sumSqr_a[index];

	std::cout<<" index : "<<index<<" theta : "<<theta;

	VectorPtr ptr (new DenseVector(dimension));
	a->multiply(theta);
	v->minus(*a);
	ptr = v->getPositiveIndices();
	z->setValue(0);//initialize to 0
	for(i=0;i<ptr->size();i++)
	{
		index = ptr->getValueAt(i);
		z->setValueAt(index,ptr->getValueAt(index));
	}
	return z;
}

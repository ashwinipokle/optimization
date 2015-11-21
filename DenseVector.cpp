/*
 * DenseVector.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashwini
 */

#include<vector>
#include"DenseVector.h"
#include<cmath>
#include<stdio.h>
#include<iostream>

DenseVector::DenseVector(int length){
		data.resize(length, 0);
}
double& DenseVector::operator[](int idx){
	return data[idx];
}
const double& DenseVector::operator[](int idx) const{
	return data[idx];
}
int DenseVector::size() const {
	return data.size();
}

double DenseVector::innerProduct(const Vector& otherVector) {
	double result = 0;
	for(int i=0;i<otherVector.size();i++)
	{
		result += data[i] * otherVector[i];
	}
	return result;
}
void DenseVector::print()
	{
		for(int i=0;i<size();i++) {
			std::cout << (*this)[i] << " ";
		}
		std::cout << std::endl;
	}
Vector& DenseVector::setValue(double scale) {
	for(int i=0;i<this->size();i++)
	{
		data[i] = scale;
	}
	return *this;
}
VectorPtr DenseVector::getValidIndices(){
	VectorPtr ptr = VectorPtr(new DenseVector(this->size()));
	for(int i=0;i<this->size();i++)
		(*ptr)[i] = i;
	return ptr;
}
VectorPtr DenseVector::getPositiveIndices(){
	std::vector<int> v (this->size());
	int index = 0;
	for(int i=0;i< this->size();i++)
	{
		if(data[i] > 0)
		{
			v[index] = i;
			index++;
		}
	}
	v.resize(index);
	VectorPtr ptr (new DenseVector(index));
	for(int i = 0;i< index;i++)
		(*ptr)[i] = v[i];
	return ptr;
}
// vector operations
Vector& DenseVector::plus(Vector& otherVector) {
	for(int i=0;i<otherVector.size();i++)
	{
		data[i] += otherVector[i];
	}
	return *this;
}

Vector& DenseVector::minus(Vector& otherVector) {
	for(int i=0;i<otherVector.size();i++)
	{
		data[i] -= otherVector[i];
	}
	return *this;
}

Vector& DenseVector::multiply(const Vector& otherVector) {
	for(int i=0;i<otherVector.size();i++)
	{
		data[i] *= otherVector[i];
	}
	return *this;
}

// scalar operations
Vector& DenseVector::plus(double scale) {
	for(int i=0;i<this->size();i++)
	{
		data[i] += scale;
	}
	return *this;
}

Vector& DenseVector::multiply(double scale) {
	for(int i=0;i<this->size();i++)
	{
		data[i] *= scale;
	}
	return *this;
}

Vector& DenseVector::sqroot(){
	for(int i=0;i<this->size();i++){
		data[i] = std::sqrt(data[i]);
	}
	return *this;
}

Vector& DenseVector::inverse(){
	for(int i=0;i<this->size();i++)
		data[i] = 1/data[i];
	return *this;
}

double DenseVector::getValueAt(int index){
	return data[index];
}

void DenseVector::setValueAt(int index, double value){
	data[index] = value;
}

VectorPtr DenseVector::clone() {
	VectorPtr tempVector(new DenseVector(this->size()));
	for(int i=0;i<this->size();i++) {
		(*tempVector)[i] = (*this)[i];
	}
	return tempVector;
}

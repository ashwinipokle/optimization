
#ifndef DENSEVECTOR_H_
#define DENSEVECTOR_H_

#include "Vector.h"
#include<vector>

class DenseVector: public Vector{
public:
	DenseVector(int length);
	double& operator[](int idx);
	const double& operator[](int idx) const;
	int size() const;
	VectorType getType() const{return DENSE;}

	Vector& plus(double scale);
	Vector& plus(Vector& otherVector);
	Vector& minus(Vector& otherVector);
	Vector& multiply(double scale);
	Vector& multiply(const Vector& otherVector);
	VectorPtr getValidIndices();
	VectorPtr getPositiveIndices();
	Vector& setValue(double scale);
	Vector& sqroot();
	Vector& inverse();
	VectorPtr clone();
	void print();
	double getValueAt(int index);
	void setValueAt(int index, double value);
	double innerProduct(const Vector& otherVector);

public:
	std::vector<double> data;
};

#endif /* DENSEVECTOR_H_ */

/*
 * Vector.h
 *
 *  Created on: Jun 4, 2014
 *      Author: ashwini
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>
#include <iostream>
#include <string>

class Vector {
public:
	virtual ~Vector(){}

	enum VectorType {DENSE=0, SPARSE=1};

	virtual double& operator[](int idx) = 0;
	virtual const double& operator[](int idx) const = 0;
	virtual int size() const = 0;
	virtual VectorType getType() const = 0;

	// operations
	virtual Vector& plus(double scale) = 0;
	virtual Vector& plus(Vector& otherVector) = 0;
	virtual Vector& minus(Vector& otherVector) = 0;
	virtual Vector& multiply(double scale) = 0;
	virtual Vector& multiply(const Vector& otherVector) =0;
	virtual Vector& sqroot() = 0;
	virtual Vector& inverse() = 0;
	virtual Vector& setValue(double scale) = 0;
	virtual std::shared_ptr<Vector> getValidIndices() = 0;
	virtual std::shared_ptr<Vector> getPositiveIndices() = 0;
	virtual double getValueAt(int index)=0;
	virtual void setValueAt(int index,double val)=0;
	virtual double innerProduct(const Vector& otherVector) =0;

	virtual std::shared_ptr<Vector> clone() = 0;

	virtual void print()=0;
};

typedef std::shared_ptr<Vector> VectorPtr;

#endif /* VECTOR_H_ */

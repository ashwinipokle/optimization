#include "VectoryFactory.h"
#include "SparseVector.h"
VectorPtr createNewVector(Vector::VectorType vecType, int length, double value) {
	if(vecType==Vector::DENSE) {
		VectorPtr newVector = VectorPtr(new DenseVector(length));
		newVector->setValue(value);
		return newVector;
	}
	else if(vecType == Vector::SPARSE){
		VectorPtr newVector = VectorPtr(new SparseVector());
		//zero length map ; no need to initialize anything
		return newVector;
	}
}

#ifndef VECTOR_FACTORY_H
#define VECTOR_FACTORY_H

#include "Vector.h"
#include "DenseVector.h"

VectorPtr createNewVector(Vector::VectorType vecType, int length, double value=0);

#endif
/*
 * Norm.h
 *
 *  Created on: Jun 25, 2014
 *      Author: ashwini
 */

#ifndef NORM_H_
#define NORM_H_

#include "Vector.h"

class Norm {
public:
	double getL1norm(VectorPtr v);
	double getL2norm(VectorPtr v);
	double getLpnorm(VectorPtr v,double p);
};

#endif /* NORM_H_ */

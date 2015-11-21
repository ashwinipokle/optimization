/*
 * DataFeeder.h
 *
 *  Created on: Jun 18, 2014
 *      Author: ashwini
 */

#ifndef DATAFEEDER_H_
#define DATAFEEDER_H_

#include"TrainingInstance.h"

#include <memory>

class DataFeeder{
public:
	virtual ~DataFeeder(){}
	virtual TrainingInstancePtr getNextInstance() = 0;
	virtual void init() = 0;
};

typedef std::shared_ptr<DataFeeder> DataFeederPtr;

#endif /* DATAFEEDER_H_ */

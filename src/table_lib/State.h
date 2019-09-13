/*
 * State.h
 *
 *  Created on: Feb 23, 2019
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_STATE_H_
#define TABLE_LIB_STATE_H_

#include "../StdAfx.h"

using namespace std;

class State {
public:
	State();
	virtual ~State();
protected:
	vector<unsigned int> interest;
};


#endif /* TABLE_LIB_STATE_H_ */

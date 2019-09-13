/*
 * TableTrain.h
 *
 *  Created on: Feb 17, 2019
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_TABLETRAIN_H_
#define TABLE_LIB_TABLETRAIN_H_


using namespace std;

#define DEBUG 0

#if DEBUG > 0
	#include "TableLogs.h"
	using ParentTableTrain = TableLogs;
#else
	#include "AbstractTable.h"
	using ParentTableTrain = AbstractTable;//TableLogs;
#endif

class TableTrain: public ParentTableTrain {
public:
	TableTrain(void);
	TableTrain(unsigned int n_players);
	TableTrain(vector<AbstractPlayer*> &);
	virtual ~TableTrain();


protected:
//	State state;
//	Tracker tracker;
};


#endif /* TABLE_LIB_TABLETRAIN_H_ */

/*
 * TableTrain.h
 *
 *  Created on: Feb 17, 2019
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_TABLETRAIN_H_
#define TABLE_LIB_TABLETRAIN_H_

#include "../player_lib/PlayerBot.h"


using namespace std;

#define DEBUG 1

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

	struct TableState{
			int interest;
			int initiative;
	};
	TableState get_state();
	void init_state();
	void init_hand();
	void update_state(PlayerBot::Action, unsigned int);
protected:
	TableState table_state;
};


#endif /* TABLE_LIB_TABLETRAIN_H_ */

/*
 * TableTrain.h
 *
 *  Created on: Feb 17, 2019
 *      Author: Michael Blot
 */

#ifndef TABLE_LIB_TABLETRAIN_H_
#define TABLE_LIB_TABLETRAIN_H_

#include "../player_lib/PlayerBot.h"
using namespace std;

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
			unsigned int total_action;
			unsigned int interest;
			unsigned int initiative;
	};
	TableState get_state();
	TableState init_state();
	static string state_to_str(TableState);
	void init_hand();
	void update_state(PlayerBot::Action, unsigned int);
	void update_state_when_raise();
	void update_state_when_bet();
	void update_state_when_check();
	void update_state_when_call();
	void update_state_when_fold();

	string to_str();
protected:
	TableState table_state;
};


#endif /* TABLE_LIB_TABLETRAIN_H_ */

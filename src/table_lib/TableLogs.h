/*
 * TableLog.h
 *
 *  Created on: Jun 16, 2019
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_TABLELOGS_H_
#define TABLE_LIB_TABLELOGS_H_

#include "AbstractTable.h"

using ParentTableLogs = AbstractTable;

class TableLogs : public ParentTableLogs{
public:
	TableLogs();
	TableLogs(unsigned int n_players);
	TableLogs(vector<AbstractPlayer*> &);
	virtual ~TableLogs();


	void display_table(unsigned int);

	void init_hand();

	void distribute_street(Street street);

	void play_hand();
	bool run_full_pre_flop();
	bool run_full_street(Street street, bool action);

	void player_gets_pot(AbstractPlayer* player, unsigned int pot);
	void distribute_pot_to_best_hands();
	void distribute_side_pots_to_best_hands();

	void close_hand();
};

#endif /* TABLE_LIB_TABLELOGS_H_ */

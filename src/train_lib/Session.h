/*
 * Session.h
 *
 *  Created on: Jan 5, 2019
 *      Author: michael Blot
 */

#ifndef TABLE_LIB_SESSION_H_
#define TABLE_LIB_SESSION_H_

#include "../table_lib/TableTrain.h"
#include "../player_lib/PlayerBot.h"

class Session {
public:
	Session();
	Session(vector<AbstractPlayer*>);
	virtual ~Session();
	void run(unsigned int n_hand);
	void checkpoint();

	vector<AbstractPlayer*> get_players();
protected:
	AbstractTable *table;
	unsigned int n_checkpoint;
	string log_folder;
};

#endif /* TABLE_LIB_SESSION_H_ */

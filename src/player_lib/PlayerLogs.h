/*
 * PlayerLogs.h
 *
 *  Created on: Mar 3, 2019
 *      Author: Michael Blot
 */

#ifndef PLAYER_LIB_PLAYERLOGS_H_
#define PLAYER_LIB_PLAYERLOGS_H_


#include "AbstractPlayer.h"

using namespace std;

class PlayerLogs : public AbstractPlayer {
public:
	PlayerLogs(void);
	PlayerLogs(string);
	PlayerLogs(string, float);
	PlayerLogs(AbstractTable * table);
	PlayerLogs(AbstractTable * table, unsigned int);
	~PlayerLogs();

	Action play_street(unsigned int);

	Action raise_pot(unsigned int);
	Action call_pot();
	Action bet_pot(unsigned int);
	Action check_pot();
	Action fold_pot();
};


#endif /* PLAYER_LIB_PLAYERLOGS_H_ */

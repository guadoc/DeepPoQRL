/*
 * PlayerStat.h
 *
 *  Created on: Jan 2, 2020
 *      Author: Michael Blot
 */

#ifndef PLAYER_LIB_PLAYERSTAT_H_
#define PLAYER_LIB_PLAYERSTAT_H_

#if DEBUG > 0
	#include "PlayerLogs.h"
	using ParentPlayerStat = PlayerLogs;
#else
	#include "AbstractPlayer.h"
	using ParentPlayerStat = AbstractPlayer;
#endif
#include "StatPlayer.h"

class PlayerStat: public ParentPlayerStat{
public:
	PlayerStat();
	PlayerStat(string id);
	PlayerStat(AbstractTable * table, unsigned int);
	virtual ~PlayerStat();

	AbstractPlayer::Action play_street(unsigned int street);
	StatPlayer* get_stats() const;
	virtual void update_stats();
protected:
	StatPlayer* player_stats;
	/*
	 * Contain the statistics about the player (evolution of the bankrooll, etc)
	 */
};

#endif /* PLAYER_LIB_PLAYERSTAT_H_ */

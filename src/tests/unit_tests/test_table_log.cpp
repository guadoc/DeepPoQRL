/*
 * test_table_log.cpp
 *
 *  Created on: Dec 20, 2019
 *      Author: Michael Blot
 */

#include "../../player_lib/PlayerLogs.h"
#include "../../player_lib/PlayerRandom.h"
#include "../../table_lib/TableLogs.h"

class test_table_log
{
public:
	test_table_log(){
	}

	int test_hand(){
		vector<AbstractPlayer*> players;
		players.push_back(new PlayerRandom());
		players.push_back(new PlayerRandom());
		players.push_back(new PlayerRandom());
		players.push_back(new PlayerRandom());
		players.push_back(new PlayerRandom());
		players.push_back(new PlayerRandom());
		TableLogs table = TableLogs(players);
		table.play_hand();
		return 0;
	}
};



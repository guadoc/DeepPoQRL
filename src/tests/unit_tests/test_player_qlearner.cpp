/*
 * test_PlayerQlearner.cpp
 *
 *  Created on: Jan 12, 2020
 *      Author: Michael Blot
 */

#include <player_lib/PlayerQlearner.h>

class MockingPlayerQlearner: public PlayerQlearner{

};

class test_player_qlearner
{
public:
	test_player_qlearner(){
	}

	unsigned int test_monitoring(){
		return 0;
	}

};

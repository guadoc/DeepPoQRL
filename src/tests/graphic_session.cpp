/*
 * graphic_session.cpp
 *
 *  Created on: Dec 20, 2019
 *      Author: Michael Blot
 */


#include "../table_lib/AbstractTable.h"
#include "../player_lib/AbstractPlayer.h"

#include "../table_lib/TableGUI.h"
#include "../player_lib/PlayerGUI.h"

#include "../player_lib/PlayerRandom.h"


static int only_gui_players(unsigned int n_hand){
	unsigned int n_player = 6;
	vector<AbstractPlayer*> players;
	for (unsigned int position=0; position < n_player; position++){
		AbstractPlayer * p = new PlayerGUI();
		players.push_back(p);
	}
	TableGUI* table = new TableGUI(players);
	for (unsigned int i =1; i<= n_hand; i++){
		table->play_hand();
	}
	return 0;
}

static int gui_vs_bots(unsigned int n_hand, bool hand_open){
	unsigned int n_player = 6;
	vector<AbstractPlayer*> players;
	for (unsigned int position=0; position < n_player-1; position++){
		AbstractPlayer * p = new PlayerRandom();
		p->set_open_hand(hand_open);
		p->set_auto_rebuy(false);
		players.push_back(p);
	}
	AbstractPlayer * p = new PlayerGUI();
	p->set_auto_rebuy(false);
	players.push_back(p);
	TableGUI* table = new TableGUI(players);
	for (unsigned int i =1; i<= n_hand; i++){
		table->play_hand();
	}
	return 0;
}

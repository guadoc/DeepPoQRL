/*
 * toolbox.cpp
 *
 *  Created on: Dec 14, 2019
 *      Author: Michael Blot
 */

#include "AbstractPlayer.h"

using namespace std;

template <class T>
static bool is_in_list(const list<T> &list_of_element,const T& value ){
	for (auto & element: list_of_element){
		if(element == value){
			return true;
		}
	}
	return false;
}

static bool are_players_in_list(list<AbstractPlayer*> players, list<string> ids){
	bool is_in = true;
	auto ids_it = ids.begin();
	for(auto & player: players){
		is_in = is_in and (*ids_it == player->get_id());
		ids_it++;
	}
	return is_in;
}

static bool are_players_in_lists(list<list<AbstractPlayer*>> player_lists, list<list<string>> expected_ids){
	bool is_in = true;
	auto ids_it = expected_ids.begin();
	for(auto & player_list: player_lists){
		is_in = is_in and are_players_in_list(player_list, *ids_it);
		ids_it++;
	}
	return is_in;
}


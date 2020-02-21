//============================================================================
// Name        : PQL.cpp
// Author      : Michael Blot
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#define DEBUG 1

#include "tests/unit_tests/test_abstract_player.cpp"
#include "tests/unit_tests/test_abstract_table.cpp"
#include "tests/unit_tests/test_table_train.cpp"
#include "tests/unit_tests/test_table_log.cpp"
#include "tests/unit_tests/test_deck.cpp"
#include "tests/unit_tests/test_hand.cpp"
#include "tests/unit_tests/test_stat_player.cpp"
#include "tests/unit_tests/test_player_v2.cpp"


#include "deck_lib/HandValueManager.h"
#include "tests/graphic_session.cpp"
#include "tests/training_session.cpp"

using namespace std;

#include "toolbox.cpp"


int main(){
//	bool verbose = true;
//	test_abstract_player().test_all();
//	test_abstract_table().test_all();
//	test_cards().test_all();
//	test_deck().test_all();
//	test_hand(verbose).test_all();
//	test_table_train().test_all();
//	test_player_v2().test_save_and_load();

//	test_stat_player().test_all();

//	test_table_train().test_performances();
//	test_stat_player().test_save_n_plot();

//	HandValueManager().fill_map_5_cards("./hand_value_maps/map5cards.p");

	unsigned int n_hand = 100;
//	only_gui_players(n_hand);
	gui_vs_bots(n_hand, false);
	string folder_bot_to_train = "./bots/v2";
	string folder_bot_against = "./bots/v2";
	Session sess = Session();
//	sess.train_individual(folder_bot_to_train, folder_bot_against, n_hand);
//	sess.test_trained_player(folder_bot, n_hand);
	return 0;
}

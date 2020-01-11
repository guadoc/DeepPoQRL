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


#include "deck_lib/HandValueManager.h"
#include "tests/graphic_session.cpp"
#include "tests/training_session.cpp"

//#include "tests/unit_tests/test_plot.cpp"
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

//	test_stat_player().test_all();

//	test_table_train().test_performances();
//	test_stat_player().test_save_n_plot();

//	HandValueManager().fill_map_5_cards("./hand_value_maps/map5cards.p");

	unsigned int n_hand = 10000;
//	only_gui_players(n_hand);
//	gui_vs_bots(n_hand, false);
	Session sess = Session();
	sess.train_individual("./bots/V2", n_hand);

	return 0;
}

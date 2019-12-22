//============================================================================
// Name        : PQL.cpp
// Author      : Michael Blot
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#define DEBUG 1


//#include "tests/test_table.cpp"
//#include "tests/runs.cpp"

#include "tests/unit_tests/test_abstract_player.cpp"
#include "tests/unit_tests/test_abstract_table.cpp"
#include "tests/unit_tests/test_table_log.cpp"
#include "tests/unit_tests/test_deck.cpp"
#include "tests/unit_tests/test_hand.cpp"

//#include "tests/unit_tests/test_optim_hand.cpp"

#include "deck_lib/HandValueManager.h"
#include "tests/graphic_session.cpp"


using namespace std;

int main() {
	bool verbose = true;
//	test_abstract_player().run_tests();
//	test_abstract_table().run_tests();
//	test_cards().run_tests();
//	test_deck().run_tests();
	test_hand(verbose).run_tests();

//	test_optim_hand(verbose).run_tests();


//	test_abstract_table().test_distribute_pot_with_fold();


//	HandValueManager().fill_map_5_cards("./hand_value_maps/map5cards.p");
//	HandValueManager().load_and_use_map();
//	HandValueManager().test_map_performances();


//	unsigned int n_hand = 100;
//	only_gui_players(n_hand);
//	gui_vs_bots(n_hand, false);


/******* TEST TABLE & GAME */
//	test_table test = test_table();
//	test.test_plot();
//	test.test_train_table();
//	test.test_torch();
//	test.test_session();
//	test.test_algo_g();
//	test.test_trained_player();
//	test.test_evolution();
//	test.test_train_individual();
//	test.test_save_and_load_playerV2();
//	test.save_n_load_net();
//	Runs run = Runs();
//	run.run_evolution();
//	run.run_train_individual();
	return 0;
}

//============================================================================
// Name        : PQL.cpp
// Author      : Michael Blot
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#define DEBUG 1

#include <iostream>
#include "tests/test_deck.cpp"
#include "tests/test_table.cpp"


using namespace std;


int main() {


/******* TEST HAND MANAGER */
	test_deck test_d = test_deck();
//	test_d.test_card();
//	test_d.test_deck_distribute();
//	test_d.test_hand_config_and_eval();
//	test_d.test_all_combos();
//	test_d.test_all_hands();
//	test_d.test_MC_hand_value();
//	test_d.test_two_cards_monte_carlo();
//	test_d.test_hash_function();
//	test_d.test_perf_map();
//	test_d.test_map();
//	test_d.test_save_map();
//	test_d.test_load_map();
//	test_d.test_hand_value_manager();

/******* TEST TABLE & GAME */
	test_table test = test_table();

//	test.test_plot();
//	test.test_save_and_load_player();
//	test.test_gui_player();
//	test.test_random_player();
//	test.test_train_table();
//	test.test_torch();
//	test.test_graphic_table();
//	test.test_session();
//	test.test_algo_g();
	test.test_trained_player();

//	test.test_player_serialization();


//	test.test_complete_average_value();





	return 0;
}

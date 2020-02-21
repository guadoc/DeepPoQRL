/*
 * test_PlayerV2.cpp
 *
 *  Created on: Jan 12, 2020
 *      Author: Michael Blot
 */

#include "../../player_lib/bots/PlayerBotV2.h"

class test_player_v2
{
public:
	test_player_v2(){
	}

	int test_all(){
		this->test_save_and_load();
		return 0;
	}

	int test_save_and_load(){
		PlayerBotV2 * player1 = new PlayerBotV2();
		string folder_to_save = "./src/tests/unit_tests/test_output_folder/test_player_v2";
		float value_learning_rate = 77;
		player1->init_train_params();
		player1->set_learning_rate(value_learning_rate);
		player1->save_to_folder(folder_to_save);
//		cout<<player1->training_params_to_str()<<endl;

		PlayerBotV2 * player2 = new PlayerBotV2();
		player2->init_train_params();
		player2->load_from_folder(folder_to_save);
//		cout<<player2->training_params_to_str()<<endl;
		assert(player2->get_learning_rate() == value_learning_rate);
		//TODO test load net
		return 0;
	}
};


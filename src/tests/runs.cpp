/*
 * runs.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: micha
 */

#include "../StdAfx.h"
#include "../deck_lib/Card.h"
#include "../deck_lib/Deck.h"
#include "../player_lib/PlayerBotV1.h"
#include "../player_lib/PlayerBotV2.h"
#include "../player_lib/bots/PlayerBotV21.h"
#include "../player_lib/PlayerGUI.h"
#include "../player_lib/PlayerLogs.h"
#include "../train_lib/Session.h"
#include "../table_lib/TableTrain.h"
#include "../table_lib/TableGUI.h"
#include "../utils/utils.h"

#include "../train_lib/Evolution.h"

#include <torch/torch.h>


using namespace std;

class Runs
{
public:
	Runs(void){

	}

	int run_evolution(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=0; position < n_player; position++){
			AbstractPlayer * p = new PlayerBotV2(to_string(position));
			players.push_back(p);
		}
		unsigned int n_generation = 1;
		unsigned int n_hand_generation = 10000;
		Evolution evolution = Evolution(players, n_generation, n_hand_generation);
		evolution.run_evolution();
		return 0;
	}


	int run_train_individual(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=1; position < n_player; position++){
			AbstractPlayer * p = new PlayerBotV2(to_string(position));
			((PlayerBot * )p)->init_train_params();
			((PlayerBot * )p)->set_train_mode(false);
			players.push_back(p);
		}
		AbstractPlayer * p = new PlayerBotV2(to_string(0));
		((PlayerBot * )p)->init_train_params();
//		p->load_from_model("./generation_bots/PlayerBotV2_2");
		((PlayerBot * )p)->set_train_mode(true);
		((PlayerBot * )p)->display_learning_params();
		players.push_back(p);

		Evolution evolution = Evolution(players);

		clock_t start = clock();
		evolution.run_selection(10000);
		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		p->save_to_folder("./bot");
		return 0;
	}
};



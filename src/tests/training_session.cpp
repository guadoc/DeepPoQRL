/*
 * runs.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: Michael Blot
 */

#include "../StdAfx.h"
//#include <player_lib/bots/PlayerBotV1.h>
#include "../player_lib/bots/PlayerBotV2.h"
#include "../player_lib/bots/PlayerBotV21.h"
#include "../train_lib/Evolution.h"

using namespace std;
class Session
{
private:
	string folder_expe;
public:
	Session(void){
		this->folder_expe = "\bots";
	}

	int evolution(){
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


	int train_individual(string folder_to_save, string folder_to_load, unsigned int n_hand){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=1; position < n_player; position++){
			PlayerBotV2 * p = new PlayerBotV2(to_string(position));
			p->init_train_params();
			p->load_from_folder(folder_to_load);
			p->set_train_mode(false);
			p->set_greedy_mode(false);
			p->set_monitoring_mode(false);
			players.push_back(p);
			cout<<p->training_params_to_str()<<endl;
		}
		PlayerBotV2 * p = new PlayerBotV2(to_string(0));
		p->init_train_params();
		p->set_train_mode(true);
		p->set_greedy_mode(true);
		p->set_monitoring_mode(true);
		players.push_back(p);
		cout<<p->training_params_to_str()<<endl;
		clock_t start = clock();
		Evolution evolution = Evolution(players);
		evolution.run_episodes(n_hand);



		for(const auto & player: players){
			((PlayerStat*)player)->get_stats()->reset_stats();
			cout<<((PlayerBotV2*)player)->training_params_to_str()<<endl;
		}
		p->plot_monitoring();
		p->set_train_mode(false);
		p->set_greedy_mode(false);
		p->set_monitoring_mode(false);
//		evolution.run_episodes(10000);



		for(const auto & player: players){
			cout<<((PlayerBotV2 *)player)->get_stats()->street_stat_to_str(AbstractTable::t_river)<<endl;
		}
		cout<<p->training_params_to_str()<<endl;
//		p->plot_monitoring();
//		p->save_to_folder(foalder_to_save);

		double elapsed = (double)(clock()- start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}




	int test_trained_player(string folder_bot, unsigned int n_hand){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=1; position < n_player; position++){
			PlayerBotV2 * p = new PlayerBotV2(to_string(position));
			p->init_train_params();
			p->set_train_mode(false);
			p->set_greedy_mode(true);
			p->set_monitoring_mode(false);
			players.push_back(p);
		}
		PlayerBotV2 * p = new PlayerBotV2(to_string(0));
		p->init_train_params();
		p->load_from_folder(folder_bot);
		p->set_train_mode(false);
		p->set_greedy_mode(false);
		p->set_monitoring_mode(false);
		cout<<p->training_params_to_str()<<endl;
		players.push_back(p);
		Evolution evolution = Evolution(players);

		clock_t start = clock();
//		evolution.run_episodes(n_hand);
		for(const auto & player: players){
			cout<<((PlayerBotV2 *)player)->get_stats()->street_stat_to_str(AbstractTable::t_river)<<endl;
		}
		double elapsed = (double)(clock()- start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}
};



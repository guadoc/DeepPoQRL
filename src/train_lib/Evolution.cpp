/*
 * Evolution.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: walnutalgo
 */

#include "Evolution.h"
#include "../player_lib/PlayerBotV1.h"
#include "../player_lib/PlayerBotV2.h"

#include <sys/stat.h>
#include <typeinfo>

namespace std {

Evolution::Evolution() {
	this->n_hand_selection = 10000;
	this->n_generation = 5;
	this->n_players = 6;
	this->generator = std::default_random_engine();
	for (unsigned int position=0; position < this->n_players; position++){
		AbstractPlayer * p = new PlayerBotV2(to_string(position));
		((PlayerBot*)p)->init_macro_params(this->generator);
//		((PlayerBot*)p)->set_train_mode(true);
		this->candidates.push_back(p);
	}
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./generation_bots/";
}

Evolution::Evolution(vector<AbstractPlayer*>& players) {
	this->n_hand_selection = 5000;
	this->n_generation = 5;
	this->n_players = 6;
	this->generator = std::default_random_engine();
	this->candidates = players;
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./generation_bots/";
}

Evolution::Evolution(vector<AbstractPlayer*>& players, unsigned int n_generation, unsigned int n_hand_selection) {
	this->n_hand_selection = n_hand_selection;
	this->n_generation = n_generation;
	this->n_players = 6;
	this->generator = std::default_random_engine();
	this->candidates = players;
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./generation_bots/";
}

Evolution::~Evolution() {
	// TODO Auto-generated destructor stub
}


list<AbstractPlayer*> Evolution::select_survivors(vector<AbstractPlayer *> & players){
	list<AbstractPlayer *> surviving_players;
	for (auto &player :players){
		if (this->survived(player)){
			surviving_players.push_back(player);
		}
	}
	return surviving_players;
}

bool Evolution::survived(AbstractPlayer *player){
	return player->get_bank_roll()  > player->get_initial_bank_roll();
}

void Evolution::run_selection(){
	this->run_selection(this->n_hand_selection);
}

void Evolution::run_selection(unsigned int n_hand){
	for (auto &p: this->candidates){
		p->init_bank_roll();
	}
	for (unsigned int i =1; i<= n_hand; i++){
		utils::progress_bar((float)i/(float)this->n_hand_selection);
		this->table->play_hand();
	}
}

static bool compare_players(AbstractPlayer * const & a, AbstractPlayer * const & b)
{
   return *a > *b;
}

string Evolution::save_best_genome(string saving_folder){
	//TODO create folder is doesn't exists
	const int dir_err = mkdir(saving_folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	std::sort(this->candidates.begin(), this->candidates.end(), compare_players);
	string folder = this->saving_folder;
	auto player_to_save = *this->candidates.begin();
//	cout<<typeid(player_to_save)<<endl;
	player_to_save->save_to_folder(saving_folder);
	return saving_folder;
}

string Evolution::save_best_genome(){
	return this->save_best_genome(this->saving_folder);
}


void Evolution::run_mutations(){
	list<AbstractPlayer*> survivors = this->select_survivors(this->candidates);
	for (auto & player: this->candidates){
		if(not this->survived(player)){
			((PlayerBot*)player)->mute_macro_params(survivors, this->generator);
		}
	}
}

void Evolution::init_players_params_for_evolution(){
	for(auto & p: this->candidates){
		((PlayerBot*)p)->init_train_params(this->generator);
		((PlayerBot*)p)->set_train_mode(true);
	}
}

void Evolution::run_evolution(string generation_folder){
	this->init_players_params_for_evolution();
	for(unsigned int j= 1; j<= this->n_generation; j++){
		this->run_selection();
		cout<<this->table->to_str()<<endl;
		this->run_mutations();
	}
	this->save_best_genome(generation_folder);
}

void Evolution::run_evolution(){
	this->run_evolution(this->saving_folder);
}


} /* namespace std */

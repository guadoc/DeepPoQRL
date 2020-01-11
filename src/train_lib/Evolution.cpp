/*
 * Evolution.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: Michael Blot
 */

#include "Evolution.h"
//#include "../player_lib/PlayerBotV1.h"
//#include "../player_lib/PlayerBotV2.h"
#include "../toolbox.cpp"
#include "../player_lib/PlayerBot.h"
#include "../player_lib/bots/PlayerBotV1.h"

//#include <sys/stat.h>
#include <boost/filesystem.hpp>
#include <typeinfo>

#define N_PLAYER_DEFAULT 6

namespace std {

Evolution::Evolution() {
	this->n_hand_selection = 10000;
	this->n_generation = 5;
	this->generator = std::default_random_engine();
	for (unsigned int position=0; position < N_PLAYER_DEFAULT; position++){
		AbstractPlayer * p = new PlayerBotV1(to_string(position));
		this->candidates.push_back(p);
	}
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./generation_bots/";
}

Evolution::Evolution(vector<AbstractPlayer*>& players) {
	this->n_hand_selection = 5000;
	this->n_generation = 5;
	this->generator = std::default_random_engine();
	this->candidates = players;
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./generation_bots/";
}

Evolution::Evolution(vector<AbstractPlayer*>& players, unsigned int n_generation, unsigned int n_hand_selection): Evolution(players) {
	this->n_hand_selection = n_hand_selection;
	this->n_generation = n_generation;
}

Evolution::Evolution(vector<AbstractPlayer*>& players, unsigned int n_generation, unsigned int n_hand_selection, string folder_to_save): Evolution(players, n_generation, n_hand_selection) {
	this->saving_folder = folder_to_save;
}

Evolution::~Evolution() {
	// TODO Auto-generated destructor stub
}


list<AbstractPlayer*> Evolution::select_survivors(vector<AbstractPlayer *> & players){
	list<AbstractPlayer *> surviving_players;
	for (auto &player :players){
		if (this->has_survived(player)){
			surviving_players.push_back(player);
		}
	}
	return surviving_players;
}

bool Evolution::has_survived(AbstractPlayer *player){
	return this->has_won_chips(player);
}

bool Evolution::has_won_chips(AbstractPlayer *player){
	return player->get_bank_roll()  > player->get_initial_bank_roll();
}

void Evolution::run_episodes(){
	this->run_episodes(this->n_hand_selection);
}

void Evolution::run_episodes(unsigned int n_hand){
	for (auto &p: this->candidates){
		p->init_bank_roll();
	}
//	cout<<this->table->to_str()<<endl;
	for (unsigned int i =1; i<= n_hand; i++){
		progress_bar(i, n_hand);
		this->table->play_hand();
//		cout<<this->table->to_str()<<endl;
	}
	cout<<this->table->to_str()<<endl;
}

static bool compare_players(AbstractPlayer * const & a, AbstractPlayer * const & b)
{
   return *a > *b;
}

string Evolution::save_best_genome(string saving_folder){
	//TODO check if folder properly created
	boost::filesystem::create_directory(saving_folder);
	std::sort(this->candidates.begin(), this->candidates.end(), compare_players);
	string folder = this->saving_folder;
	auto player_to_save = *this->candidates.begin();
	player_to_save->save_to_folder(saving_folder);
	return saving_folder;
}

string Evolution::save_best_genome(){
	return this->save_best_genome(this->saving_folder);
}


void Evolution::run_mutations(){
	list<AbstractPlayer*> survivors = this->select_survivors(this->candidates);
	for (auto & player: this->candidates){
		if(not this->has_survived(player)){
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
		progress_bar((float)j/(float)this->n_generation);
		this->run_episodes();
		cout<<this->table->to_str()<<endl;
		this->run_mutations();
	}
	this->save_best_genome(generation_folder);
}

void Evolution::run_evolution(){
	this->run_evolution(this->saving_folder);
}

string Evolution::state_to_str() const{
	string state_str = "";
	state_str += this->table->to_str();
	return state_str;
}


} /* namespace std */

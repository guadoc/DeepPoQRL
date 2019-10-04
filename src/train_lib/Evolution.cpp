/*
 * Evolution.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: walnutalgo
 */

#include "Evolution.h"
#include "../player_lib/PlayerBotV1.h"
#include "../player_lib/PlayerBotV2.h"


namespace std {

Evolution::Evolution() {
	this->n_hand_selection = 10;
	this->n_generation = 5;
	this->n_players = 6;
	this->generator = std::default_random_engine();
	for (unsigned int position=0; position < this->n_players; position++){
		AbstractPlayer * p = new PlayerBotV2(to_string(position));
		this->candidates.push_back(p);
		((PlayerBot*)p)->init_macro_params(generator);
		((PlayerBot*)p)->set_train_mode(true);
	}
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./bots/";
}

Evolution::Evolution(vector<AbstractPlayer*>& players) {
	this->n_hand_selection = 5000;
	this->n_generation = 20;
	this->n_players = 6;
	this->generator = std::default_random_engine();
	this->candidates = players;
	this->table = new TableTrain(this->candidates);
	this->saving_folder = "./bots/";
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
	return (player->get_bank_roll() + player->get_stake()) > (player->get_initial_bank_roll());
}

void Evolution::run_selection(){
	for (unsigned int i =1; i<= this->n_hand_selection; i++){
		utils::progress_bar((float)i/(float)this->n_hand_selection);
		this->table->play_hand();
	}
}

static bool compare_players(AbstractPlayer * const & a, AbstractPlayer * const & b)
{
   return *a > *b;
}

string Evolution::save_best_genome(){
	std::sort(this->candidates.begin(), this->candidates.end(), compare_players);
//	BOOST_SERIALIZATION_ASSUME_ABSTRACT( AbstractPlayer );
	string folder = this->saving_folder + (*this->candidates.begin())->get_id();
	(*this->candidates.begin())->save_to_folder(folder);
	return folder;
}

void Evolution::run_mutations(){
	list<AbstractPlayer*> survivors = this->select_survivors(this->candidates);
	for (auto & player: this->candidates){
		if(not this->survived(player)){
			((PlayerBot*)player)->mute_macro_params(survivors, this->generator);
		}
	}
}

void Evolution::run_evolution(){
	for(unsigned int j= 1; j<= this->n_generation; j++){
		this->run_selection();
		cout<<this->table->to_str()<<endl;
		this->run_mutations();
	}
	this->save_best_genome();
}



} /* namespace std */

/*
 * Evolution.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: walnutalgo
 */

#include "Evolution.h"


namespace std {

Evolution::Evolution() {
	this->generation = 0;
	this->n_hand_generation = 50000;
	this->n_sessions = 1;
}

Evolution::~Evolution() {
	// TODO Auto-generated destructor stub
}


bool Evolution::select_genome(AbstractPlayer * player){
	if(player->get_stake()> 3* player->get_base_stake()){
		return true;
	}
	else{return false;}
	return false;
}

void Evolution::selection(Session session){
	vector<AbstractPlayer*> players = session.get_players();
	for (auto player : players){
		if(this->select_genome(player)){
			player->save_to_folder(this->generation_folder);
		}
		else{
			// get new model (from mix or from former generation)
//			this->mix_genome();
			static_cast<PlayerBot*>(player)->mute_macro_params();
		}
		player->init_bank_roll();
	}
	//TODO set new vector of players
}

void Evolution::update_generation_folder(){
	this->generation_folder = this->base_folder + "/" + to_string(this->generation);
}

void Evolution::run_thread(unsigned int thread_session){
	while(true){
		sessions[thread_session].run(this->n_hand_generation);
		this->selection(sessions[thread_session]);
		this->generation++;
		this->update_generation_folder();
	}
}

} /* namespace std */

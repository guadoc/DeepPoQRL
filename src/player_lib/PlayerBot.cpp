/*
 * PlayerBot.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: Michael Blot
 */

#include "PlayerBot.h"
#include <table_lib/TableTrain.h>


PlayerBot::PlayerBot(void):ParentPlayerBot(){
	this->loss = 0;
	this->train_mode = true;
}

PlayerBot::PlayerBot(string id):ParentPlayerBot(id){
	this->loss = 0;
	this->train_mode = true;
	this->id = id;
}

PlayerBot::PlayerBot(AbstractTable * table, unsigned int position):ParentPlayerBot(table, position){
	this->loss = 0;
	this->train_mode = true;
}

PlayerBot::~PlayerBot() {
	// TODO Auto-generated destructor stub
}

string PlayerBot::training_params_to_str() const{
	return "";
}

void PlayerBot::commit_chips(unsigned int value){
	ParentPlayerBot::commit_chips(value);
	this->loss -= value;
}

void PlayerBot::add_to_stake(unsigned int value){
	ParentPlayerBot::add_to_stake(value);
	this->loss += value;
}

void PlayerBot::set_train_mode(bool train_mode){
	this->train_mode = train_mode;
}

void PlayerBot::init_train_params(){
	this->init_macro_params();
	this->init_learning_params();
//	cout<<this->training_params_to_str()<<endl;
}

void PlayerBot::init_train_params(std::default_random_engine& generator){
	this->init_macro_params(generator);
	this->init_learning_params();
}

void PlayerBot::close_hand(){
	ParentPlayerBot::close_hand();
	if (this->train_mode){
		this->train();
	}
}

void PlayerBot::init_hand(){
	ParentPlayerBot::init_hand();
	this->loss = 0;
}

PlayerBot::Action PlayerBot::raise_pot(unsigned int value){
	((TableTrain*)this->table)->update_state(PlayerBot::t_raise, value);
	return ParentPlayerBot::raise_pot(value);
}

PlayerBot::Action PlayerBot::call_pot(){
	((TableTrain*)this->table)->update_state(PlayerBot::t_call, 0);
	return ParentPlayerBot::call_pot();
}

PlayerBot::Action PlayerBot::bet_pot(unsigned int value){
	((TableTrain*)this->table)->update_state(PlayerBot::t_bet, value);
	return ParentPlayerBot::bet_pot(value);
}

PlayerBot::Action PlayerBot::check_pot(){
	((TableTrain*)this->table)->update_state(PlayerBot::t_check, 0);
	return ParentPlayerBot::check_pot();
}

PlayerBot::Action PlayerBot::fold_pot(){
	((TableTrain*)this->table)->update_state(PlayerBot::t_fold, 0);
	return ParentPlayerBot::fold_pot();
}


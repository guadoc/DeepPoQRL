
#include "PlayerBotV1.h"

//#include <algorithm>
#include <iostream>
#include <string>

#include <random>

#include "../deck_lib/Hand.h"

PlayerBotV1::PlayerBotV1(void):ParentPlayerBotV1(){
	this->lead = false;
	this->id = "PlayerBotV1";
//	this->learning_rate = 0.1;
//	this->param_reg = 0.1;
}


PlayerBotV1::PlayerBotV1(string id, float learning_rate):ParentPlayerBotV1(id){
	this->learning_rate = learning_rate;
//	this->param_reg = learning_rate;
	this->lead = false;
}


PlayerBotV1::PlayerBotV1(string id):ParentPlayerBotV1(id){
	this->lead = false;
}


void PlayerBotV1::init_learning_params(){
	this->param_lead = 0;
	this->param_foll = 0;
}


void PlayerBotV1::init_macro_params(){
	std::default_random_engine generator;
	std::normal_distribution<double> distribution_lr(1,0.01);
	this->learning_rate = (float)distribution_lr(generator);
	std::normal_distribution<double> distribution_reg(1,0.01);
	this->param_reg = (float)distribution_reg(generator);
//	cout<<"learning_rate "<<this->learning_rate <<" param_reg "<<this->param_reg<<endl;
}

void PlayerBotV1::set_learning_rate(float learning_rate){
	this->learning_rate = learning_rate;
}

void PlayerBotV1::init_macro_params(default_random_engine& generator){
	std::normal_distribution<double> distribution_lr(1,0.1);
	this->learning_rate = (float)distribution_lr(generator);
	std::normal_distribution<double> distribution_reg(1,0.1);
	this->param_reg = (float)distribution_reg(generator);
//	cout<<"Learning_rate "<<this->learning_rate <<" Param_reg "<<this->param_reg<<endl;
}

void PlayerBotV1::mute_macro_params(){
	this->init_macro_params();
}

void PlayerBotV1::mute_macro_params(default_random_engine& generator){
	this->init_macro_params(generator);
}

void PlayerBotV1::mute_macro_params(list<AbstractPlayer*> & winning_players, default_random_engine& generator){
	int rand_index = rand() % winning_players.size();
	auto it = winning_players.begin();
	std::advance(it, rand_index);
	std::normal_distribution<double> distribution_lr(static_cast<PlayerBotV1*>(*it)->get_learning_rate(), 0.1);
	this->learning_rate = (float)distribution_lr(generator);

	rand_index = rand() % winning_players.size();
	it = winning_players.begin();
	std::advance(it, rand_index);
	std::normal_distribution<double> distribution_reg(static_cast<PlayerBotV1*>(*it)->get_param_reg(), 0.1);
	this->param_reg = (float)distribution_lr(generator);
}


float PlayerBotV1::get_learning_rate(){
	return this->learning_rate;
}

float PlayerBotV1::get_param_reg(){
	return this->param_reg;
}

float PlayerBotV1::get_param_foll(){
	return this->param_foll;
}

float PlayerBotV1::get_param_lead(){
	return this->param_lead;
}


PlayerBotV1::~PlayerBotV1(void){}


AbstractPlayer::Action PlayerBotV1::play_preflop(){
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if(this->commitment < this->table->get_last_raise()){
			return this->call_pot();
		}
		else{
			return this->check_pot();
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		return this->check_pot();
	}
}

AbstractPlayer::Action PlayerBotV1::play_flop(){
	this->loss = 0;
	return this->check_pot();
}

AbstractPlayer::Action PlayerBotV1::play_turn(){
	return this->check_pot();
}

float sigmoid(float x){
	return 1 / (1 + std::exp(-x));
}

AbstractPlayer::Action PlayerBotV1::play_river(){
	float board_value = this->table->get_board_average_value();
	float hand_relative_value = this->hand.get_full_hand_average_value()/ board_value ;
//	cout<<"Player "<<this->pos_on_table<<" has hand value: "<<this->hand_relative_value<<endl;
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		this->lead = false;
		float proba = sigmoid(hand_relative_value - this->param_foll);
		int call_value = (int)this->table->get_last_raise() - (int)this->commitment;
		if (proba * (float)(this->table->get_pot() + 2*call_value) > call_value){//this->learning_rate > 0){
			this->invest = true;
			return this->call_pot();
		}
		else{
			if(this->commitment < this->table->get_last_raise()){
				this->invest = false;
				return this->fold_pot();
			}
			else{
				cout<<"never in this case or bug"<<endl;
			}
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		this->lead = true;
		unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
		float proba = sigmoid(hand_relative_value - this->param_lead);
		if (proba * (float)(this->table->get_pot() + 2*value_bet) > value_bet){//this->relative_value > 1 ){
			this->invest = true;
			return this->bet_pot(value_bet);
		}
		else{
			this->invest = false;
			return this->check_pot();
		}
	}
	return this->check_pot();
}


void PlayerBotV1::train(){
//	cout<<"Stack "<<this->stake<<endl;
//	cout<<"LOSS "<<this->loss<<endl;

	if (this->lead){
		if (this->loss < 0){
			this->param_lead += this->learning_rate;
		}
		else if (this->loss == 0){
			this->param_lead -= this->param_reg* this->learning_rate;
		}
	}
	else{
		if (this->loss < 0){
			this->param_foll += this->learning_rate;
		}
		else if (this->loss >= 0){
			this->param_foll -=  this->learning_rate;
		}
	}
//	cout<<" Sit "<<this->pos_on_table<< "(param lead): "<<this->param_lead<<endl;
//	cout<<" Sit "<<this->pos_on_table<< "(param foll): "<<this->param_foll<<endl;
	this->lead = false;
}








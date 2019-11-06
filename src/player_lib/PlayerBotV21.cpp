/*
 * PlayerBotV21.cpp
 *
 *  Created on: Oct 6, 2019
 *      Author: walnutalgo
 */

#include "PlayerBotV21.h"
#include "../table_lib/AbstractTable.h"

namespace std {

PlayerBotV2_1::PlayerBotV2_1(void):PlayerBotV2(){
	this->id = "PlayerBotV2_1";
}

PlayerBotV2_1::PlayerBotV2_1(string id):PlayerBotV2(id){
	this->id = "PlayerBotV2_1_" + id;
}

PlayerBotV2_1::PlayerBotV2_1(AbstractTable * table):PlayerBotV2(table){
	this->id = "PlayerBotV2_1";
}

PlayerBotV2_1::PlayerBotV2_1(AbstractTable * table, unsigned int position):PlayerBotV2(table, position){
	this->id = "PlayerBotV2_1";
}

PlayerBotV2_1::~PlayerBotV2_1() {
	// TODO Auto-generated destructor stub
}



void PlayerBotV2_1::zero_grad(){
	this->net->zero_grad();
}


void PlayerBotV2_1::init_learning_params() {
	this->dim_input = 1;
	this->dim_output = 1;
	NetV2_1* net_ = new NetV2_1(this->dim_input, this->dim_output);
//	this->net_initiate = new Net(this->dim_input, this->dim_output);
	this->net = nn::Sequential(*net_);
	this->optimizer = new torch::optim::SGD(this->net->parameters(), this->learning_rate);
}


AbstractPlayer::Action PlayerBotV2_1::play_river(){
	for (const auto& pair : this->net->named_parameters()) {
	  std::cout << pair.key() << ": " << pair.value() << endl;
	}
	this->loss = 0;
	torch::Tensor input_var = this->build_input();
	this->output = this->net->forward(input_var);//, this->table->get_last_raise() == 0);
	return this->compute_rewards_and_select_action(this->output);
}



} /* namespace std */

/*
 * PlayerBotV21.cpp
 *
 *  Created on: Oct 6, 2019
 *      Author: walnutalgo
 */

#include "PlayerBotV21.h"
#include "../table_lib/AbstractTable.h"

namespace std {


struct NetV2_1 : torch::nn::Module {
  NetV2_1(int64_t N, int64_t M) {
    W_initiative = register_parameter("W_initiative", torch::ones({N, M}));
    b_initiative = register_parameter("b_initiative", -torch::ones(M));
    W_opened = register_parameter("W_opened", torch::ones({N, M}));
	b_opened = register_parameter("b_opened", -torch::ones(M));
  }
//  torch::Tensor forward(torch::Tensor input, bool initiative) {
//	  if (initiative){
//		  return torch::addmm(b_initiative, input, W_initiative);
//	  }
//	  else{
//		  return torch::addmm(b_opened, input, W_opened);
//	  }
//  }
  torch::Tensor forward(torch::Tensor input) {
	  return torch::addmm(b_initiative, input, W_initiative);
  }

  torch::Tensor b_initiative, b_opened, W_initiative, W_opened;
};

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
	this->river_net->zero_grad();
}


void PlayerBotV2_1::init_learning_params() {
	this->dim_input = 1;
	this->dim_output = 1;
	NetV2_1* river_net_ = new NetV2_1(this->dim_input, this->dim_output);
//	this->river_net_initiate = new river_net(this->dim_input, this->dim_output);
	this->river_net = nn::Sequential(*river_net_);
	this->optimizer = new torch::optim::SGD(this->river_net->parameters(), this->learning_rate);
}


AbstractPlayer::Action PlayerBotV2_1::play_river(){
	for (const auto& pair : this->river_net->named_parameters()) {
	  std::cout << pair.key() << ": " << pair.value() << endl;
	}
	this->loss = 0;
	torch::Tensor input_var = this->build_input();
	this->output = this->river_net->forward(input_var);//, this->table->get_last_raise() == 0);
	return this->compute_rewards_and_select_action(this->output);
}



} /* namespace std */

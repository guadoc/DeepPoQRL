//
//#include "PlayerBotV2.h"
//#include "../table_lib/AbstractTable.h"
//
//#include <random>
//
////#include <torch/torch.h>
//
//PlayerBotV2::PlayerBotV2(void):ParentPlayerBotV2(){
//	this->init_params();
//	this->optimizer = new torch::optim::SGD(this->parameters, /*lr=*/this->learning_rate);
//}
//
//PlayerBotV2::PlayerBotV2(string id, float learning_rate):ParentPlayerBotV2(id){
//	this->init_params();
//	this->learning_rate = learning_rate;
//	this->optimizer = new torch::optim::SGD(this->parameters, /*lr=*/learning_rate);
//}
//
//PlayerBotV2::PlayerBotV2(AbstractTable * table):ParentPlayerBotV2(table){
//	this->init_params();
//	this->optimizer = new torch::optim::SGD(this->parameters, /*lr=*/this->learning_rate);
//}
//
//PlayerBotV2::PlayerBotV2(AbstractTable * table, unsigned int position):ParentPlayerBotV2(table, position){
//	this->init_params();
//	this->optimizer = new torch::optim::SGD(this->parameters, /*lr=*/this->learning_rate);
//}
//
//void PlayerBotV2::init_param(){
//	this->init_learning_params();
//	this->init_macro_params();
//}
//
//void PlayerBotV2::init_macro_params(){
//	this->learning_rate = 0.01;
//}
//
//void PlayerBotV2::mute_macro_params(){
//	//TODO
//}
//
//void PlayerBotV2::init_learning_params(){
////	float param_init_1[] = {0.};
////	float param_init_2[] = {0.};
//	this->parameters.clear();
//	this->parameters.push_back(torch::zeros(1, torch::requires_grad()));
//	this->parameters.push_back(torch::zeros(1, torch::requires_grad()));
//
//
//	this->decision_proba = torch::zeros({1});
//}
//
//
//PlayerBotV2::~PlayerBotV2(void){}
//
//
//AbstractPlayer::Action PlayerBotV2::play_preflop(){
//	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
//		if(this->commitment < this->table->get_last_raise()){
//			return this->call_pot();
//		}
//		else{
//			return this->check_pot();
//		}
//	}
//	else{//there is no raise from another player, choices: BET, check_pot (we remove the folding option: fold_pot)
//		return this->check_pot();
//	}
//}
//
//AbstractPlayer::Action PlayerBotV2::play_flop(){
//	return this->check_pot();
//}
//
//AbstractPlayer::Action PlayerBotV2::play_turn(){
//	return this->check_pot();
//}
//
//
//AbstractPlayer::Action PlayerBotV2::play_river(){
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	float board_value = this->table->get_board_average_value();
//	float relative_hand_value = this->hand.get_average_full_hand_value() / board_value;
//	cout<<"Player "<<this->pos_on_table<<" has hand value: "<<relative_hand_value<<endl;
//
//	auto value_bet = torch::ones({1});
//	value_bet = value_bet * 0.5* (float)std::min(this->stake, this->table->get_pot());
//
//	auto decision_proba  = torch::sigmoid(relative_hand_value * exp(this->parameters[0]) -2.52 + this->parameters[1] );
//	auto val = decision_proba *(3.5 * value_bet + (float)this->table->get_pot());
//	this->decision_proba = torch::sigmoid (2*(val - value_bet));
//	std::bernoulli_distribution decision(this->decision_proba[0].item<float>());
//	if(this->learning_rate >0){
//		cout<<"PROBA :"<<this->decision_proba<<endl;
//		cout<<"PROBA Decision:"<<decision_proba<<endl;
//	}
//
//	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
//		this->lead = false;
//		if (decision(gen)){
//			return this->call_pot();
//		}
//		else{
//			return this->fold_pot();
//		}
//	}
//	else{//there is no raise from another player, choices: BET, check_pot (we remove the folding option: fold_pot)
//		this->lead = true;
//		if (decision(gen)){
//			unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
//			return this->bet_pot(value_bet);
//		}
//		else{
//			return this->check_pot();
//		}
//	}
//	return this->check_pot();
//}
//
//void PlayerBotV2::train(){
//	cout<<"Stack "<<this->stake<<endl;
//	cout<<"LOSS "<<this->loss<<endl;
//	cout<<"parameter train 0: "<<this->parameters[0][0].item<float>()<<endl;
//	cout<<"parameter train 1: "<<this->parameters[1][0].item<float>()<<endl;
//	float param_reg = 0.1; //reg = 0.1n lr = 0.0001, factor = 1
//
//	if (this->loss > 0 or this->loss<-3){
//		auto neg_reward = - this->decision_proba * this->loss ;
//		neg_reward.backward();
//	}
//	else{
//		auto regul = - param_reg*(this->parameters[0] + this->parameters[1]);
//		regul.backward();
//	}
//	this->optimizer->step();
//			this->optimizer->zero_grad();
//
//	this->lead = false;
//	cout<<".parameter train 0: "<<this->parameters[0][0].item<float>()<<endl;
//	cout<<".parameter train 1: "<<this->parameters[1][0].item<float>()<<endl;
//}
//
//void PlayerBotV2::init_hand(){
//	ParentPlayerBotV2::init_hand();
//}
//
//
//
//

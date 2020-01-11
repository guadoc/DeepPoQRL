///*
// * PlayerBotV21.cpp
// *
// *  Created on: Oct 6, 2019
// *      Author: walnutalgo
// */
//
//#include "PlayerBotV21.h"
//#include "../../table_lib/TableTrain.h"
//
//namespace std {
//
//
//struct NetV2_1 : torch::nn::Module {
//  NetV2_1(int64_t N, int64_t M) {
//    W_initiative = register_parameter("W_initiative", torch::ones({N, M}));
//    b_initiative = register_parameter("b_initiative", -torch::ones(M));
//    W_opened = register_parameter("W_opened", torch::ones({N, M}));
//	b_opened = register_parameter("b_opened", -torch::ones(M));
//  }
//  torch::Tensor forward(torch::Tensor input) {
//	  auto out = torch::addmm(b_initiative, input, W_initiative);
//	  return out;
//  }
//
//  torch::Tensor b_initiative, b_opened, W_initiative, W_opened;
//};
//
//PlayerBotV2_1::PlayerBotV2_1(void):PlayerBotV2(){
//	this->id = "PlayerBotV2_1";
//	this->dim_input = 2;
//	this->dim_output = 1;
//}
//
//PlayerBotV2_1::PlayerBotV2_1(string id):PlayerBotV2(id){
//	this->id = "PlayerBotV2_1_" + id;
//	this->dim_input = 2;
//	this->dim_output = 1;
//}
//
////PlayerBotV2_1::PlayerBotV2_1(AbstractTable * table):PlayerBotV2(table){
////	this->id = "PlayerBotV2_1";
////	this->dim_input = 2;
////	this->dim_output = 1;
////}
//
//PlayerBotV2_1::PlayerBotV2_1(AbstractTable * table, unsigned int position):PlayerBotV2(table, position){
//	this->id = "PlayerBotV2_1";
//	this->dim_input = 2;
//	this->dim_output = 1;
//}
//
//PlayerBotV2_1::~PlayerBotV2_1() {
//	// TODO Auto-generated destructor stub
//}
//
////void PlayerBotV2_1::zero_grad()
//
//void PlayerBotV2_1::init_learning_params() {
//	NetV2_1* river_net_ = new NetV2_1(this->dim_input, this->dim_output);
//	this->river_net = nn::Sequential(*river_net_);
//	this->optimizer = new torch::optim::SGD(this->river_net->parameters(), this->learning_rate);
//}
//
//torch::Tensor PlayerBotV2_1::build_input(){
//	float board_value = this->table->get_board_average_value();
//	float hand_relative_value = this->hand.get_average_value() / board_value ;
//	TableTrain::TableState state = ((TableTrain*)this->table)->get_state();
//	float input[] = {hand_relative_value, state.initiative};//, (float)(this->table->count_in_hand())/6.};
//	auto input_var = torch::from_blob(input, {1, this->dim_input}).clone();
//	return input_var;
//}
//
//
//AbstractPlayer::Action PlayerBotV2_1::play_river(){
//	for (const auto& pair : this->river_net->named_parameters()) {
//	  std::cout << pair.key() << ": " << pair.value() << endl;
//	}
//	this->loss = 0;
//	torch::Tensor input_var = this->build_input();
//	this->output = this->river_net->forward(input_var);//, this->table->get_last_raise() == 0);
//	return this->compute_rewards_and_select_action(this->output);
//}
//
//
//
//} /* namespace std */

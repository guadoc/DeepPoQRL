
#include "PlayerBotV2.h"
#include "../table_lib/AbstractTable.h"

//#include <random>

struct Net : torch::nn::Module {
  Net(int64_t N, int64_t M) {
    W = register_parameter("W", torch::ones({N, M}));
    b = register_parameter("b", -torch::ones(M));
  }
  torch::Tensor forward(torch::Tensor input){
    return torch::addmm(b, input, W);
  }
  torch::Tensor W, b;
};

PlayerBotV2::PlayerBotV2(void):ParentPlayerBotV2(){
	this->id = "PlayerBotV2";
	this->dim_input = 1;
	this->dim_output = 1;
	this->init_macro_params();
}

PlayerBotV2::PlayerBotV2(string id):ParentPlayerBotV2(id){
	this->id = "PlayerBotV2_" + id;
	this->dim_input = 1;
	this->dim_output = 1;
	this->init_macro_params();
}

PlayerBotV2::PlayerBotV2(AbstractTable * table):ParentPlayerBotV2(table){
	this->id = "PlayerBotV2";
	this->dim_input = 1;
	this->dim_output = 1;
	this->init_macro_params();
}

PlayerBotV2::PlayerBotV2(AbstractTable * table, unsigned int position):ParentPlayerBotV2(table, position){
	this->id = "PlayerBotV2";
	this->dim_input = 1;
	this->dim_output = 1;
	this->init_macro_params();
}
void PlayerBotV2::display_learning_params(){
	ParentPlayerBotV2::display_learning_params();
	string str = "";
	str += "LR[" + to_string(this->learning_rate) +"]";
	str += ", Reg[" + to_string(this->coefficient_reg) +"]";
	str += ", Agg[" + to_string(this->bet_pot_percentage) +"]";
	cout<<str<<endl;
	for (const auto& pair : this->river_net->named_parameters()) {
	  std::cout << pair.key() << ": " << pair.value()<<endl;
	}
}


void PlayerBotV2::init_learning_params(){
	cout<<"INIT NET"<<endl;
	Net* net_ = new Net(this->dim_input, this->dim_output);
	this->river_net = nn::Sequential(
			*net_
	);
	this->optimizer = new torch::optim::SGD(this->river_net->parameters(), this->learning_rate);
}

void PlayerBotV2::init_macro_params(){
	/* init macro parameters with default values*/
	this->learning_rate = 0.001;
	this->bet_pot_percentage = 0.51;
	this->coefficient_reg = 0.1;
}


void PlayerBotV2::init_macro_params(default_random_engine& generator){
	std::normal_distribution<double> distribution_lr(0.001,0.1);
	this->learning_rate = (float)distribution_lr(generator);
	std::normal_distribution<double> distribution_reg(0.1,0.1);
	this->coefficient_reg = (float)distribution_reg(generator);
//	cout<<"Learning_rate "<<this->learning_rate <<" Param_reg "<<this->param_reg<<endl;
}


void PlayerBotV2::mute_macro_params(){
	//TODO
}

void PlayerBotV2::mute_macro_params(default_random_engine& generator){
	//TODO
	this->init_macro_params(generator);
}

void PlayerBotV2::mute_macro_params(list<AbstractPlayer*> & winning_players, default_random_engine& generator){
	int rand_index = rand() % winning_players.size();
	auto it = winning_players.begin();
	std::advance(it, rand_index);
	std::normal_distribution<double> distribution_lr(static_cast<PlayerBotV2*>(*it)->get_learning_rate(), 0.05);
	this->learning_rate = (float)distribution_lr(generator);

	rand_index = rand() % winning_players.size();
	it = winning_players.begin();
	std::advance(it, rand_index);
	std::normal_distribution<double> distribution_reg(static_cast<PlayerBotV2*>(*it)->get_coefficient_reg(), 0.05);
	this->coefficient_reg = (float)distribution_reg(generator);
}

string PlayerBotV2::save_to_folder(string folder)const{
	string folder_to_save = ParentPlayerBotV2::save_to_folder(folder);
	torch::save(this->river_net, folder_to_save + "/river_net_weights.q");
	return folder_to_save;
}

string PlayerBotV2::load_from_folder(string folder){
	string folder_to_load = ParentPlayerBotV2::load_from_folder(folder);
	torch::load(this->river_net, folder_to_load + "/river_net_weights.q");
	return folder_to_load;
}

string PlayerBotV2::load_from_model(string folder){
	string folder_to_load = ParentPlayerBotV2::load_from_model(folder);
	torch::load(this->river_net, folder_to_load + "/river_net_weights.q");
	return folder_to_load;
}


void PlayerBotV2::zero_grad(){
	this->river_net->zero_grad();
}

void PlayerBotV2::init_hand(){
	ParentPlayerBotV2::init_hand();
	this->zero_grad();
}

PlayerBotV2::~PlayerBotV2(void){}

AbstractPlayer::Action PlayerBotV2::play_preflop(){
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if(this->commitment < this->table->get_last_raise()){
			return this->call_pot();
		}
		else{
			return this->check_pot();
		}
	}
	else{//there is no raise from another player, choices: BET, check_pot (we remove the folding option: fold_pot)
		return this->check_pot();
	}
}

AbstractPlayer::Action PlayerBotV2::play_flop(){
	return this->check_pot();
}

AbstractPlayer::Action PlayerBotV2::play_turn(){
	return this->check_pot();
}

torch::Tensor PlayerBotV2::build_input(){
	float board_value = this->table->get_board_average_value();
	float hand_relative_value = this->hand.get_average_value() / board_value ;
	float input[] = {hand_relative_value};//, (float)(this->table->count_in_hand())/6.};
	auto input_var = torch::from_blob(input, {1, this->dim_input}).clone();
	return input_var;
}

AbstractPlayer::Action PlayerBotV2::play_river(){
	this->loss = 0;
	torch::Tensor input_var = this->build_input();
	this->output = this->river_net->forward(input_var);
	return this->compute_rewards_and_select_action(this->output);
}

void PlayerBotV2::train(){
	cout<<"Player "<<this->pos_on_table<<endl;
	Tensor error;
	if (this->loss != 0){
		cout<<"LOSS "<<this->loss<<endl;
		float lo[] = {(float)this->loss};
		auto q_value = log(this->action_value);
		auto loss_value = torch::from_blob(lo, {1});
		auto diff = q_value - loss_value;
		error = diff * diff;
	}
	else{//Regularization to make the player more aggressive
		cout<<"NO LOSS"<<endl;
		cout<<this->output<<endl;
		error = - this->coefficient_reg * this->output;
	}
	error.backward();
	this->optimizer->step();
	this->display_learning_params();
}

AbstractPlayer::Action PlayerBotV2::compute_rewards_and_select_action(Tensor & output_distrib){
//	auto uniform = torch::rand(1)[0].item<float>();
	Tensor one_tensor = torch::ones({1});
	float pot = (float) this->table->get_pot();
	float bet_value = (float)std::min(this->stake, (unsigned int)(this->bet_pot_percentage*this->table->get_pot()));
	auto proba_win = sigmoid(output_distrib[0]);
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		int call_value = (int)this->table->get_last_raise() - (int)this->commitment;
		auto eQ_call = exp(proba_win * (pot + 2 * call_value) - call_value);
		if(eQ_call.item<float>() > one_tensor[0].item<float>()){
			this->action_value = eQ_call;
			return this->call_pot();
		}
		else{
			this->action_value = one_tensor; //regularization
			return this->fold_pot();
		}
	}
	else{// no bet from previous players
//		unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
		auto eQ_bet = exp(proba_win * (pot + 2 * bet_value) - bet_value);
		auto eQ_check = exp(proba_win * pot);
		if(eQ_bet.item<float>() > eQ_check.item<float>()){
			this->action_value = eQ_bet;
			return this->bet_pot(bet_value);
		}
		else{
			this->action_value = eQ_check; //regularization
			return this->check_pot();
		}
	}
	return this->fold_pot();

}

//AbstractPlayer::Action PlayerBotV2::compute_reward_and_select_action(Tensor & output_distrib){
//	auto uniform = torch::rand(1)[0].item<float>();
//	float pot = (float) this->table->get_pot();
//	float bet_value = this->table->get_last_raise()*2;//std::min(this->bet_pot_percentage * pot, this->table->get_last_raise()*2);
//	auto proba_win = output_distrib[0];
//	auto proba_fold = output_distrib[1];
//	auto percentage_interested = output_distrib[2];
////	float proba_decision = 0.5;
//	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
//		auto eQ_raise_value = exp(proba_win * (pot + 3.5 * bet_value) - bet_value);
//		auto eQ_raise_bluff = exp(proba_fold * (pot + 2 * bet_value) - bet_value);
//		auto eQ_fold = exp(eQ_raise_bluff *0);
//		auto eQ_call = exp(proba_win * (pot + 2 * bet_value) - bet_value);
//		auto esum = eQ_raise_value + eQ_raise_bluff + eQ_fold + eQ_call;
//		if(uniform < (eQ_raise_value/esum).item<float>()){
//			this->action_value = eQ_raise_value/esum;
//			return this->bet_pot(bet_value);
//		}
//		else if(uniform < ((eQ_raise_value + eQ_raise_bluff)/esum).item<float>()){
//			this->action_value= eQ_raise_bluff/esum;
//			return this->bet_pot(bet_value);
//		}
//		else if(uniform < ((eQ_raise_value + eQ_raise_bluff + eQ_fold)/esum).item<float>()){
//			this->action_value = eQ_fold; //regularization
//			return this->fold_pot();
//		}
//		else{
//			this->action_value = eQ_call/esum;
//			return this->call_pot();
//		}
//	}
//	else{// no bet from previous players
//		auto eQ_bet_value = exp(proba_win * (pot + 3 * bet_value) - bet_value);
//		auto eQ_bet_bluff = exp(proba_fold * (pot + 2 * bet_value) - bet_value);
//		auto eQ_check = exp(proba_win * (pot ));
//		auto esum = eQ_bet_value + eQ_bet_bluff + eQ_check;
//		if(uniform < (eQ_bet_value/esum).item<float>()){
//			this->action_value = eQ_bet_value/esum;
//			return this->bet_pot(bet_value);
//		}
//		else if(uniform < ((eQ_bet_value + eQ_bet_bluff)/esum).item<float>()){
//			this->action_value = eQ_bet_bluff/esum;
//			return this->bet_pot(bet_value);
//		}
//		else{
//			this->action_value = eQ_check;
//			return this->check_pot();
//		}
//	}
//	return this->fold_pot();
//
//}








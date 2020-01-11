
#include "PlayerBotV2.h"
#include "table_lib/AbstractTable.h"

//#include "/home/micha/workspace/matplotlib-cpp-master/matplotlibcpp.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

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
	this->dim_output = 2;
	this->init_macro_params();
	this->is_monitoring_on = true;
	this->is_greedy = true;
}

PlayerBotV2::PlayerBotV2(string id):ParentPlayerBotV2(id){
	this->id = "PlayerBotV2_" + id;
	this->dim_input = 1;
	this->dim_output = 2;
	this->init_macro_params();
	this->is_monitoring_on = true;
	this->is_greedy = true;
}

PlayerBotV2::PlayerBotV2(AbstractTable * table, unsigned int position):ParentPlayerBotV2(table, position){
	this->id = "PlayerBotV2";
	this->dim_input = 1;
	this->dim_output = 2;
	this->init_macro_params();
	this->is_monitoring_on = true;
	this->is_greedy = true;
}

void PlayerBotV2::set_monitoring_mode(bool monitoring_mode){
	this->is_monitoring_on = monitoring_mode;
}

void PlayerBotV2::set_greedy_mode(bool greedy_mode){
	this->is_greedy = greedy_mode;
}

string PlayerBotV2::training_params_to_str() const{
	string str = ParentPlayerBotV2::training_params_to_str();
	str += "LR[" + to_string(this->learning_rate) +"]";
	str += ", Reg[" + to_string(this->coefficient_reg) +"]";
	str += ", Agg[" + to_string(this->bet_pot_percentage) +"]";
	str += "\n";
	for (const auto& pair : this->river_net->named_parameters()) {
	  cout<<pair.key() << ": " << pair.value() <<endl;
	}
	return str;
}

void PlayerBotV2::init_learning_params(){
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

void PlayerBotV2::zero_grad(){
	this->river_net->zero_grad();
}

void PlayerBotV2::init_hand(){
	ParentPlayerBotV2::init_hand();
	this->zero_grad();

	if(this->is_monitoring_on && ! this->is_greedy){
		this->player_stats->checkpoint(this->get_bank_roll());
		this->player_stats->plot_stats();
	}
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

AbstractPlayer::Action PlayerBotV2::play_river(){
	this->loss = 0;
	torch::Tensor input_var = this->build_input();
	vector<float> Qvalues = this->compute_Qvalues(input_var);
	auto action = this->select_action_from_Qvalues(Qvalues, AbstractTable::t_river);
	this->action_value = this->get_action_value(action);
	return action;
}

torch::Tensor PlayerBotV2::build_input(){
	float board_value = this->table->get_board_average_value();
	float hand_relative_value = this->hand.get_average_value() / board_value ;
	float input[] = {hand_relative_value};//(float)(this->table->count_in_hand())/6.};
	auto input_var = torch::from_blob(input, {1, this->dim_input}).clone();
	return input_var;
}

vector<float> PlayerBotV2::compute_Qvalues(torch::Tensor input){
	vector<float> Qvalues = vector<float>(2, 0);
	this->output = this->river_net->forward(input);
	return Qvalues;
}

AbstractPlayer::Action PlayerBotV2::select_action_from_Qvalues(vector<float> Qvalues, AbstractTable::Street street){
	if (this->is_greedy){
		return this->random_play(Qvalues, street);
	}
	return this->optimal_play_from_Qvalues(Qvalues, street);
}

torch::Tensor PlayerBotV2::get_action_value(AbstractPlayer::Action action){
	torch::Tensor Qvalue;
	float pot = (float) this->table->get_pot();
	switch(action){
	case AbstractPlayer::t_bet:
		Qvalue = this->output[0][0] * pot;
		break;
	case AbstractPlayer::t_raise:
		Qvalue = this->output[0][0] * pot;
		break;
	case AbstractPlayer::t_call:
		Qvalue = this->output[0][1] * pot;
		break;
	case AbstractPlayer::t_check:
		Qvalue = this->output[0][1] * pot;
		break;
	case AbstractPlayer::t_fold:
		Qvalue = this->output[0][1] * 0;
		break;
	}
	return Qvalue;
}

AbstractPlayer::Action PlayerBotV2::optimal_play_from_Qvalues(vector<float> Qvalues, AbstractTable::Street street){
	if (this->table->get_last_raise() != 0 ){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if((this->output[0][0].item<float>() >= this->output[0][1].item<float>()) && (this->output[0][0].item<float>() > 0)){
			if (this->table->get_last_raise() < this->stake + this->commitment){
				unsigned int value_raise = std::min(this->table->get_last_raise() +  1*this->table->get_diff_last_raises(),
													this->stake + this->commitment);
				return this->raise_pot(value_raise);
			}
		}
		/*FOR PREFLOP*/
//		if (this->table->get_last_raise() <= this->commitment){
//			return this->check_pot();
//		}
		if(this->output[0][1].item<float>() >= 0){
				return this->call_pot();
		}
		else{
			return this->fold_pot();
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		if(this->output[0][0].item<float>() > this->output[0][1].item<float>()){
			unsigned int value_bet = std::min(this->stake, (unsigned int)(0.3 * (float)this->table->get_total_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->fold_pot();
}

AbstractPlayer::Action PlayerBotV2::random_play(vector<float>, AbstractTable::Street street){
	if (this->table->get_last_raise() != 0 ){// there is a bet from another player: raise_pot, call_pot or fold_pot
		unsigned int choice = rand() % 7;
		if(choice == 0 or choice == 1 or choice == 2){
			if (this->table->get_last_raise() >= this->stake + this->commitment){
				return this->call_pot();
			}
			else{
				unsigned int value_raise = std::min(this->table->get_last_raise() +  1*this->table->get_diff_last_raises(),
													this->stake + this->commitment
													);
				return this->raise_pot(value_raise);
			}
		}
		else if(choice == 5 or choice == 6 or choice == 4){
			if (this->table->get_last_raise() > this->commitment){
				return this->call_pot();
			}
			else{
				return this->check_pot();
			}
		}
		else{
			if (this->commitment < this->table->get_last_raise()){
				return this->fold_pot();
			}
			else
			{
				return this->check_pot();
			}
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		unsigned int choice = rand() % 5;
		if(choice == 0 or choice == 1 or choice == 2 or choice == 3){
			unsigned int value_bet = std::min(this->stake, (unsigned int)(0.3 * (float)this->table->get_total_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->fold_pot();
}

void PlayerBotV2::train(){
	if (true){//this->action_value != NULL){
		float lo[1] = {(float)this->loss};
		Tensor loss_value = torch::from_blob(lo, {1});
		Tensor diff = this->action_value - loss_value;
//		Tensor error = diff * diff;
//		Tensor error = - this->action_value * tanh(loss_value);
		Tensor error = torch::abs(diff);
		error.backward();
		this->optimizer->step();
		if(this->is_monitoring_on){
			estimated_q_value.push_back(this->action_value.item<float>());
			observed_q_value.push_back((float)this->loss);
			observed_q_value_error.push_back(error.item<float>());
			if(this->is_monitoring_on){
				this->plot_monitoring();
			}
		}
	}
}

void PlayerBotV2::plot_monitoring(){
	plt::close();
	plt::figure();
	plt::subplot(3, 1, 1);
	vector<float> eqv = {std::begin(this->estimated_q_value), std::end(this->estimated_q_value)};
	plt::named_plot("estimated Q", eqv);
	vector<float> oqv = {std::begin(this->observed_q_value), std::end(this->observed_q_value)};
	plt::named_plot("observed Q", oqv);
	plt::legend();
	plt::subplot(3, 1, 2);
	plt::plot({std::begin(this->observed_q_value_error), std::end(this->observed_q_value_error)});
	plt::pause(0.05);
//	plt::legend();
//	plt::close();
	plt::show();
}



//	cout<<"Player "<<this->pos_on_table<<endl;
//	Tensor error;
//	if (this->loss != 0){
//		cout<<"LOSS "<<this->loss<<endl;
//		float lo[] = {(float)this->loss};
//		auto q_value = log(this->action_value);
//		auto loss_value = torch::from_blob(lo, {1});
//		auto diff = q_value - loss_value;
//		error = diff * diff;
//	}
//	else{//Regularization to make the player more aggressive
//		cout<<"NO LOSS"<<endl;
//		cout<<this->output<<endl;
//		error = - this->coefficient_reg * this->output;
//	}
//	error.backward();
//	this->optimizer->step();
//	if(this->is_monitoring_on){
//		this->player_stats->checkpoint(this->get_bank_roll());
//		this->player_stats->plot_stats();
//	}
//}

//AbstractPlayer::Action PlayerBotV2::compute_rewards_and_select_action(Tensor & output_distrib){
////	auto uniform = torch::rand(1)[0].item<float>();
//	Tensor one_tensor = torch::ones({1});
//	float pot = (float) this->table->get_pot();
//	float bet_value = (float)std::min(this->stake, (unsigned int)(this->bet_pot_percentage*this->table->get_pot()));
//	auto proba_win = sigmoid(output_distrib[0]);
//	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
//		int call_value = (int)this->table->get_last_raise() - (int)this->commitment;
//		auto eQ_call = exp(proba_win * (pot + 2 * call_value) - call_value);
//		if(eQ_call.item<float>() > one_tensor[0].item<float>()){
//			this->action_value = eQ_call;
//			return this->call_pot();
//		}
//		else{
//			this->action_value = one_tensor; //regularization
//			return this->fold_pot();
//		}
//	}
//	else{// no bet from previous players
////		unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
//		auto eQ_bet = exp(proba_win * (pot + 2 * bet_value) - bet_value);
//		auto eQ_check = exp(proba_win * pot);
//		if(eQ_bet.item<float>() > eQ_check.item<float>()){
//			this->action_value = eQ_bet;
//			return this->bet_pot(bet_value);
//		}
//		else{
//			this->action_value = eQ_check; //regularization
//			return this->check_pot();
//		}
//	}
//	return this->fold_pot();
//}

//string PlayerBotV2::save_to_folder(string folder)const{
//	string folder_to_save = ParentPlayerBotV2::save_to_folder(folder);
//	torch::save(this->river_net, folder_to_save + "/river_net_weights.q");
//	return folder_to_save;
//}
//
//string PlayerBotV2::load_from_folder(string folder){
//	string folder_to_load = ParentPlayerBotV2::load_from_folder(folder);
//	torch::load(this->river_net, folder_to_load + "/river_net_weights.q");
//	return folder_to_load;
//}
//
//string PlayerBotV2::load_from_model(string folder){
//	string folder_to_load = ParentPlayerBotV2::load_from_model(folder);
//	torch::load(this->river_net, folder_to_load + "/river_net_weights.q");
//	return folder_to_load;
//}


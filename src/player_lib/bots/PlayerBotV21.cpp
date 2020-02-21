#include "PlayerBotV21.h"

struct Net21 : torch::nn::Module {
  Net21(int64_t N, int64_t M) {
    W1 = register_parameter("W1", torch::randn({N, 4}));
    b1 = register_parameter("b1", -torch::zeros(4));
    W2 = register_parameter("W2", torch::randn({4, M})),
	b2 = register_parameter("b2", -torch::zeros(M));
  }
  torch::Tensor forward(torch::Tensor input){
	  auto inter = torch::addmm(b1, input, W1);
	  inter = torch::addmm(b2, inter, W2);
	  return inter;
  }
  torch::Tensor W1, b1, W2, b2;
};

PlayerBotV21::PlayerBotV21(void):ParentPlayerBotV21(){
	this->id = "PlayerBotV21";
	this->dim_input = 2;
	this->dim_output = 2;
	this->init_macro_params();
}

PlayerBotV21::PlayerBotV21(string id):ParentPlayerBotV21(id){
	this->id = "PlayerBotV21_" + id;
	this->dim_input = 2;
	this->dim_output = 2;
	this->init_macro_params();
}

PlayerBotV21::PlayerBotV21(AbstractTable * table, unsigned int position):ParentPlayerBotV21(table, position){
	this->id = "PlayerBotV21";
	this->dim_input = 2;
	this->dim_output = 2;
	this->init_macro_params();
}

PlayerBotV21::~PlayerBotV21() {
	delete this->optimizer;
}

void PlayerBotV21::set_learning_rate(float lr){
	this->learning_rate = lr;
}

string PlayerBotV21::training_params_to_str() const{
	string str = ParentPlayerBotV21::training_params_to_str();
	str += "LR[" + to_string(this->learning_rate) +"]";
	str += ", Reg[" + to_string(this->coefficient_reg) +"]";
	str += ", Agg[" + to_string(this->bet_pot_percentage) +"]";
	str += "\n";
	for (const auto& pair : this->river_net->named_parameters()) {
	  cout<<pair.key() << ": " << pair.value() <<endl;
	}
	return str;
}

void PlayerBotV21::init_learning_params(){
	Net21* net_ = new Net21(this->dim_input, this->dim_output);
	this->river_net = nn::Sequential(
			*net_
	);
	this->optimizer = new torch::optim::SGD(this->river_net->parameters(), this->learning_rate);
}

void PlayerBotV21::init_macro_params(){
	/* init macro parameters with default values*/
	this->learning_rate = 0.001;
	this->bet_pot_percentage = 0.51;
	this->coefficient_reg = 0.1;
}

void PlayerBotV21::init_macro_params(default_random_engine& generator){
	std::normal_distribution<double> distribution_lr(0.001,0.1);
	this->learning_rate = (float)distribution_lr(generator);
	std::normal_distribution<double> distribution_reg(0.1,0.1);
	this->coefficient_reg = (float)distribution_reg(generator);
}

void PlayerBotV21::mute_macro_params(){
}

void PlayerBotV21::mute_macro_params(default_random_engine& generator){
	this->init_macro_params(generator);
}

void PlayerBotV21::mute_macro_params(list<AbstractPlayer*> & winning_players, default_random_engine& generator){
	int rand_index = rand() % winning_players.size();
	auto it = winning_players.begin();
	std::advance(it, rand_index);
	std::normal_distribution<double> distribution_lr(static_cast<PlayerBotV21*>(*it)->get_learning_rate(), 0.05);
	this->learning_rate = (float)distribution_lr(generator);
	rand_index = rand() % winning_players.size();
	it = winning_players.begin();
	std::advance(it, rand_index);
	std::normal_distribution<double> distribution_reg(static_cast<PlayerBotV21*>(*it)->get_coefficient_reg(), 0.05);
	this->coefficient_reg = (float)distribution_reg(generator);
}

void PlayerBotV21::zero_grad(){
	this->river_net->zero_grad();
}

void PlayerBotV21::init_hand(){
	ParentPlayerBotV21::init_hand();
	this->zero_grad();
	if(this->is_monitoring_on && ! this->is_greedy){
		this->player_stats->checkpoint(this->get_bank_roll());
//		this->player_stats->plot_stats();
//		this->hand_estimated_q_value.clear();
	}
	this->hand_actions_Qvalue.clear();
}


vector<float> PlayerBotV21::build_input(){
	float board_value = this->table->get_board_average_value();
	float hand_relative_value = this->hand.get_average_value() / board_value ;
	vector<float> input{hand_relative_value, (float)(this->table->count_in_hand())/(float)6.};
	return input;
}

vector<float> PlayerBotV21::compute_Qvalues(vector<float> input){
	torch::Tensor input_tensor = torch::from_blob(input.data(), {1, 2}).clone();
	this->output.push_back(this->river_net->forward(input_tensor));
	std::vector<float> Qvalues(this->output.back().data_ptr<float>(), this->output.back().data_ptr<float>() + this->output.back().numel());
	return Qvalues;
}

float PlayerBotV21::credit_action_value(Action action){
	torch::Tensor Qvalue;
	float pot = (float) this->table->get_pot();
	switch(action){
	case AbstractPlayer::t_bet:
		Qvalue = this->output.back()[0][0] * pot;
		break;
	case AbstractPlayer::t_raise:
		Qvalue = this->output.back()[0][0] * pot;
		break;
	case AbstractPlayer::t_call:
		Qvalue = this->output.back()[0][1] * pot;
		break;
	case AbstractPlayer::t_check:
		Qvalue = this->output.back()[0][1] * pot;
		break;
	case AbstractPlayer::t_fold:
		Qvalue = this->output.back()[0][1] * 0;
		break;
	}
	this->hand_actions_Qvalue.push_back(Qvalue);
	return Qvalue.item<float>();
}

void PlayerBotV21::train(){
	//TODO: no use to backpropagate if action is fold
	Tensor loss = torch::zeros({1});
	for(auto action_value: this->hand_actions_Qvalue){
		float lo[1] = {(float)this->loss};
		Tensor loss_value = torch::from_blob(lo, {1});
		Tensor diff = loss_value - action_value;// this->hand_actions_Qvalue;
//		Tensor error = diff * diff;
//		Tensor error = - this->action_value * tanh(loss_value);
		Tensor error = torch::abs(diff);
		loss = loss + error;
	}
	loss.backward();
	this->optimizer->step();
}



template<class Archive>
void PlayerBotV21::serialize(Archive & ar, const unsigned int version) {
	ar & boost::serialization::base_object<AbstractPlayer>(*this);
	ar & this->learning_rate;
	ar & this->bet_pot_percentage;
	ar & this->coefficient_reg;
}

string PlayerBotV21::save_to_folder(string folder)const{
	string folder_to_save = ParentPlayerBotV21::save_to_folder(folder);
	torch::save(this->river_net, folder_to_save + "/river_net_weights.q");
	return folder_to_save;
}

string PlayerBotV21::load_from_folder(string folder){
	string folder_to_load = ParentPlayerBotV21::load_from_folder(folder);
	torch::load(this->river_net, folder_to_load + "/river_net_weights.q");
	return folder_to_load;
}



#ifndef PLAYER_LIB_PLAYERBOTV2_H_
#define PLAYER_LIB_PLAYERBOTV2_H_


#include "PlayerBot.h"

#include <torch/torch.h>
using namespace torch;

using ParentPlayerBotV2 = PlayerBot;

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

class PlayerBotV2 : public ParentPlayerBotV2{

public:
	PlayerBotV2(void);
	PlayerBotV2(string id);
	PlayerBotV2(AbstractTable * table);
	PlayerBotV2(AbstractTable * table, unsigned int);
	~PlayerBotV2();

	float get_coefficient_reg(){return this->coefficient_reg;}
	float get_learning_rate(){return this->learning_rate;}
	float get_bet_pot_percentage(){return this->bet_pot_percentage;}

//	void init_train_params();
	void train();

	virtual void init_learning_params() override;
	virtual void init_macro_params() override;
	void init_macro_params(std::default_random_engine& generator) override;

	void mute_macro_params();
	void mute_macro_params(std::default_random_engine& generator);
	void mute_macro_params(list<AbstractPlayer*> &, default_random_engine& generator) override;


	Action play_preflop();
	Action play_flop();
	Action play_turn();
	virtual Action play_river();


	void init_hand();
	virtual void zero_grad();
//	void close_hand();

	torch::Tensor build_input();
	Action select_action_from_distribution(Tensor&);
	virtual Action compute_rewards_and_select_action(Tensor&);


protected:
	torch::optim::SGD * optimizer;
	Net * net;
	unsigned int dim_input;
	unsigned int dim_output;
	torch::Tensor input;
	torch::Tensor output;
	torch::Tensor action_value;

	/* macro parameters */
	float learning_rate;
	float bet_pot_percentage;
	float coefficient_reg;

};

#endif /* PLAYER_LIB_PLAYERBOTV2_H_ */

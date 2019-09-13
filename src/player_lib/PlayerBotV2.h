

#ifndef PLAYER_LIB_PLAYERBOTV2_H_
#define PLAYER_LIB_PLAYERBOTV2_H_


#include "PlayerBot.h"

#include <torch/torch.h>

using ParentPlayerBotV2 = PlayerBot;

class PlayerBotV2 : public ParentPlayerBotV2{

public:
	PlayerBotV2(void);
	PlayerBotV2(string id, float);
	PlayerBotV2(AbstractTable * table);
	PlayerBotV2(AbstractTable * table, unsigned int);
	~PlayerBotV2();


	void train();
	void init_macro_params();
	void mute_macro_params();
	void init_learning_params();
	void init_param();


	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();


	void init_hand();
//	void close_hand();


protected:
	torch::optim::SGD* optimizer;
	vector<torch::Tensor> parameters;
	torch::Tensor decision_proba;
	bool lead;
	float param_stat;
	float learning_rate;

};

#endif /* PLAYER_LIB_PLAYERBOTV2_H_ */

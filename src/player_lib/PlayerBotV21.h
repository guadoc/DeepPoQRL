/*
 * PlayerBotV21.h
 *
 *  Created on: Oct 6, 2019
 *      Author: walnutalgo
 */

#ifndef PLAYER_LIB_PLAYERBOTV21_H_
#define PLAYER_LIB_PLAYERBOTV21_H_

#include "PlayerBotV2.h"

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

class PlayerBotV2_1: public PlayerBotV2 {
public:
	PlayerBotV2_1(void);
	PlayerBotV2_1(string id);
	PlayerBotV2_1(AbstractTable * table);
	PlayerBotV2_1(AbstractTable * table, unsigned int);
	~PlayerBotV2_1();

//	void init_hand();
	void zero_grad() override;
	void init_learning_params() override;
	AbstractPlayer::Action play_river();

protected:
//	NetV2_1* net;
//	Net* net_opened;
};

} /* namespace std */

#endif /* PLAYER_LIB_PLAYERBOTV21_H_ */

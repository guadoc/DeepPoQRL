/*
 * PlayerBotV21.h
 *
 *  Created on: Oct 6, 2019
 *      Author: Michael Blot
 */

#ifndef PLAYER_LIB_PLAYERBOTV21_H_
#define PLAYER_LIB_PLAYERBOTV21_H_

#include "PlayerBotV2.h"

namespace std {

class PlayerBotV2_1: public PlayerBotV2 {
public:
	PlayerBotV2_1(void);
	PlayerBotV2_1(string id);
//	PlayerBotV2_1(AbstractTable * table);
	PlayerBotV2_1(AbstractTable * table, unsigned int);
	~PlayerBotV2_1();

//	void init_hand();
//	void zero_grad() override;
	void init_learning_params() override;
	AbstractPlayer::Action play_river();

	torch::Tensor build_input();

protected:
};

} /* namespace std */

#endif /* PLAYER_LIB_PLAYERBOTV21_H_ */

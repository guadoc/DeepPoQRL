/*
 * PlayerBot.h
 *
 *  Created on: Jun 10, 2019
 *      Author: Michael Blot
 */

#ifndef PLAYER_LIB_PLAYERBOT_H_
#define PLAYER_LIB_PLAYERBOT_H_

#include <random>
#include "PlayerStat.h"

using ParentPlayerBot = PlayerStat;

class PlayerBot : public ParentPlayerBot{

public:
	PlayerBot(void);
	PlayerBot(string id);
	PlayerBot(AbstractTable * table, unsigned int);
	virtual ~PlayerBot();

	virtual string training_params_to_str() const;

	void init_hand();
	void close_hand();

	void commit_chips(unsigned int);
	void add_to_stake(unsigned int);
//	void update_stats();
	void set_train_mode(bool);


	void init_train_params();
	void init_train_params(std::default_random_engine& generator);
	virtual void init_learning_params()=0;
	virtual void init_macro_params()=0;
	virtual void init_macro_params(std::default_random_engine& generator)=0;
	virtual void mute_macro_params()=0;
	virtual void mute_macro_params(list<AbstractPlayer*> &, std::default_random_engine&) = 0;
	virtual void train() = 0;

	virtual Action play_preflop()=0;
	virtual Action play_flop()=0;
	virtual Action play_turn()=0;
	virtual Action play_river()=0;

	Action raise_pot(unsigned int);
	Action call_pot();
	Action bet_pot(unsigned int);
	Action check_pot();
	Action fold_pot();

protected:
	bool train_mode;
	int loss;
//	float param_stat; //can be a vector
};

#endif /* PLAYER_LIB_PLAYERBOT_H_ */

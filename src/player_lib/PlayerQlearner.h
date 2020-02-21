/*
 * PlayerQlearner.h
 *
 *  Created on: Jan 11, 2020
 *      Author: Michael Blot
 */

#ifndef PLAYER_LIB_PLAYERQLEARNER_H_
#define PLAYER_LIB_PLAYERQLEARNER_H_

#include "PlayerBot.h"

namespace std {

class PlayerQlearner: public PlayerBot {
public:
	PlayerQlearner(void);
	PlayerQlearner(string id);
	PlayerQlearner(AbstractTable* table, unsigned int);
	virtual ~PlayerQlearner();

	void close_hand();

	void set_monitoring_mode(bool);
	void plot_monitoring() const;

	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();

	virtual vector<float> build_input() = 0;
	virtual vector<float> compute_Qvalues(vector<float> input) = 0;
	virtual float credit_action_value(Action) = 0;

	void set_greedy_mode(bool);
	Action select_action_from_Qvalues(vector<float> Qvalues, AbstractTable::Street street);
	Action random_play(vector<float> Qvalues, AbstractTable::Street street);
	Action optimal_play_from_Qvalues(vector<float> Qvalues, AbstractTable::Street street);

protected:
	bool is_greedy;
	/*
	 * greedy is for train mode.
	 * It defines whether the decision mode
	 *  is random or optimal
	*/

	/* for monitoring */
	bool is_monitoring_on;
	list<float> hand_estimated_q_value;
	list<float> estimated_q_value;
	list<float> observed_q_value;
	list<float> observed_q_value_error;
};

} /* namespace PlayerQlearner */

#endif /* PLAYER_LIB_PLAYERQLEARNER_H_ */

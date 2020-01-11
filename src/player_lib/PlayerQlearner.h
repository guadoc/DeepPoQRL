/*
 * PlayerQlearner.h
 *
 *  Created on: Jan 11, 2020
 *      Author: micha
 */

#ifndef PLAYER_LIB_PLAYERQLEARNER_H_
#define PLAYER_LIB_PLAYERQLEARNER_H_

#include <player_lib/PlayerBot.h>

namespace std {

class PlayerQlearner: public PlayerBot {
public:
	PlayerQlearner();
	virtual ~PlayerQlearner();

	void plot_monitoring() const;
	void update_monitoring();
	void close_hand();
	void set_monitoring_mode(bool);

protected:
	/* for monitoring */
	bool is_monitoring_on;
	list<float> estimated_q_value;
	list<float> observed_q_value;
	list<float> observed_q_value_error;
};

} /* namespace PlayerQlearner */

#endif /* PLAYER_LIB_PLAYERQLEARNER_H_ */

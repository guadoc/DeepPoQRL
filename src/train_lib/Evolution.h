/*
 * Evolution.h
 *
 *  Created on: Jun 9, 2019
 *      Author: walnutalgo
 */

#ifndef TRAIN_LIB_EVOLUTION_H_
#define TRAIN_LIB_EVOLUTION_H_

#include "Session.h"
#include "../player_lib/PlayerBot.h"

namespace std {

class Evolution {
public:
	Evolution();
	virtual ~Evolution();

	void run_party();
	void selection(Session);
	void run_thread(unsigned int);
	bool select_genome(AbstractPlayer *);
	void save_genome();
//	void mix_genome();

	void update_generation_folder();
private:
	unsigned int n_hand_generation;
	vector<Session> sessions;
	string generation_folder;
	string base_folder;
	unsigned int n_sessions;
	unsigned int generation;
};

} /* namespace std */

#endif /* TRAIN_LIB_EVOLUTION_H_ */

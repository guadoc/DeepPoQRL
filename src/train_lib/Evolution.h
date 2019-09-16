/*
 * Evolution.h
 *
 *  Created on: Jun 9, 2019
 *      Author: walnutalgo
 */

#ifndef TRAIN_LIB_EVOLUTION_H_
#define TRAIN_LIB_EVOLUTION_H_

#include "Session.h"
#include "../player_lib/AbstractPlayer.h"

namespace std {

class Evolution {
public:
	Evolution();
	Evolution(vector<AbstractPlayer*>&);
	virtual ~Evolution();

	list<AbstractPlayer*> select_survivors(vector<AbstractPlayer *> &);
	bool survived(AbstractPlayer *);
	void run_selection();
	void run_evolution();
	void run_mutations();
	string save_best_genome();
//	void update_generation_folder();

private:
	unsigned int n_players;
	TableTrain * table;
	vector<AbstractPlayer*> candidates;
	unsigned int n_hand_selection;
	unsigned int n_generation;
	std::default_random_engine generator;

	string generation_folder;
	string base_folder;
};

} /* namespace std */

#endif /* TRAIN_LIB_EVOLUTION_H_ */

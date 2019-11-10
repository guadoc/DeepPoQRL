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
	Evolution(vector<AbstractPlayer*>& players, unsigned int n_generation, unsigned int n_hand_selection);
	virtual ~Evolution();

	void init_players_macro_params();

	list<AbstractPlayer*> select_survivors(vector<AbstractPlayer *> &);
	bool survived(AbstractPlayer *);
	void run_selection();
	void run_mutations();
	string save_best_genome();
	string save_best_genome(string folder);

	void run_evolution();
	void run_evolution(string folder);

	int train_player(AbstractPlayer *, vector<AbstractPlayer*>);

private:
	unsigned int n_players;
	TableTrain * table;
	vector<AbstractPlayer*> candidates;
	unsigned int n_hand_selection;
	unsigned int n_generation;
	std::default_random_engine generator;

	string saving_folder;

};

} /* namespace std */

#endif /* TRAIN_LIB_EVOLUTION_H_ */

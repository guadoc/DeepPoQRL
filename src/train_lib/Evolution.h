/*
 * Evolution.h
 *
 *  Created on: Jun 9, 2019
 *      Author: Michael Blot
 */

#ifndef TRAIN_LIB_EVOLUTION_H_
#define TRAIN_LIB_EVOLUTION_H_

#include "../player_lib/AbstractPlayer.h"
#include "../table_lib/TableTrain.h"

namespace std {

class Evolution {
public:
	Evolution();
	Evolution(vector<AbstractPlayer*>&);
	Evolution(vector<AbstractPlayer*>& players, unsigned int n_generation, unsigned int n_hand_selection);
	Evolution(vector<AbstractPlayer*>& players, unsigned int n_generation, unsigned int n_hand_selection, string folder_to_save);
	virtual ~Evolution();

	string state_to_str() const;

	void init_players_params_for_evolution();
	void run_evolution(string folder);
	void run_evolution();
	void run_episodes(unsigned int);
	void run_episodes();
	void run_mutations();
	list<AbstractPlayer*> select_survivors(vector<AbstractPlayer *> &);
	bool has_survived(AbstractPlayer *);
	string save_best_genome(string folder);
	string save_best_genome();

	bool has_won_chips(AbstractPlayer *player);

private:
	TableTrain * table;
	vector<AbstractPlayer*> candidates;
	unsigned int n_hand_selection;
	unsigned int n_generation;
	std::default_random_engine generator;
	string saving_folder;

};

} /* namespace std */

#endif /* TRAIN_LIB_EVOLUTION_H_ */

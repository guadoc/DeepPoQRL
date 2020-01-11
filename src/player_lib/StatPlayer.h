

#ifndef PLAYER_LIB_STATPLAYER_H_
#define PLAYER_LIB_STATPLAYER_H_
#include "../StdAfx.h"
#include "../table_lib/AbstractTable.h"
#include "AbstractPlayer.h"

using namespace std;

class StatPlayer {
public:
	StatPlayer();
	virtual ~StatPlayer();

	//TODO make a vector of unsigned int instead
	struct StreetStat{
		unsigned int played;
		unsigned int raise;
		unsigned int bet;
		unsigned int call;
		unsigned int check;
		unsigned int fold;
	};

	vector<StreetStat*> get_hand_stats()const;
	void init_hand_stats();
	StreetStat* street_stat_init() const;

	void reset_stats();


	void update_street_stat(AbstractTable::Street, AbstractPlayer::Action);
	void update_street_stat(StreetStat*, AbstractPlayer::Action);

	void checkpoint(unsigned int);
	void save_stats(string file_path) const;
	void plot_stats(void) const;
	string street_stat_to_str(StreetStat*) const;
	string street_stat_to_str(AbstractTable::Street) const;


protected:
	vector<StreetStat*> hand_stats;
	/*
	 * Stats to follow the player stats
	 */

	list<unsigned int> bankroll;
	list<float> river_aggression_proba;
	/*
	 * Lists to plots
	 */
};

#endif /* PLAYER_LIB_STATPLAYER_H_ */

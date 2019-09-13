

#ifndef PLAYER_LIB_STATPLAYER_H_
#define PLAYER_LIB_STATPLAYER_H_

#include "../StdAfx.h"
#include "../utils/utils.h"

using namespace std;

class StatPlayer {
public:
	StatPlayer();
	virtual ~StatPlayer();
	void update_stats(unsigned int, unsigned int, float);
	void update_stats(unsigned int, unsigned int);
	void plot_stats(string);
	void save_stats(string file_path);

protected:
	list<unsigned int> bank_roll_evolution;
	list<unsigned int> stake_evolution;
	list<float> param_stat_evolution;
};

#endif /* PLAYER_LIB_STATPLAYER_H_ */

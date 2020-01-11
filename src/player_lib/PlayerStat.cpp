
#include "StatPlayer.h"
#include "PlayerStat.h"

PlayerStat::PlayerStat():ParentPlayerStat() {
	this->player_stats = new StatPlayer();
}

PlayerStat::PlayerStat(string id):ParentPlayerStat(id){
	this->player_stats = new StatPlayer();
}
PlayerStat::PlayerStat(AbstractTable * table, unsigned int position): ParentPlayerStat(table, position){
	this->player_stats = new StatPlayer();
}

PlayerStat::~PlayerStat() {
	// TODO Auto-generated destructor stub
	delete this->player_stats;
}

StatPlayer* PlayerStat::get_stats() const {
	return this->player_stats;
}

void PlayerStat::update_stats(){
}

AbstractPlayer::Action PlayerStat::play_street(unsigned int street){
	AbstractPlayer::Action action = ParentPlayerStat::play_street(street);
	this->player_stats->update_street_stat((AbstractTable::Street)street, action);
	return action;
}

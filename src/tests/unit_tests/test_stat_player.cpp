/*
 * test_stat_player.cpp
 *
 *  Created on: Dec 27, 2019
 *      Author: Michael Blot
 */

#include "../../player_lib/StatPlayer.h"

class test_stat_player{
public:
	test_stat_player(){

	}

	int test_all(){
		this->test_create_and_reset_stats();
		this->test_update_stats();
		return 0;
	}

	bool is_street_stat_equal(StatPlayer::StreetStat* sst1, StatPlayer::StreetStat sst2){
		bool is_equal = true;
		is_equal = is_equal and sst1->played == sst2.played;
		is_equal = is_equal and sst1->bet == sst2.bet;
		is_equal = is_equal and sst1->raise == sst2.raise;
		is_equal = is_equal and sst1->call == sst2.call;
		is_equal = is_equal and sst1->check == sst2.check;
		is_equal = is_equal and sst1->fold == sst2.fold;
		return is_equal;
	}

	int test_create_and_reset_stats(){
		StatPlayer stat = StatPlayer();
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_preflop], StatPlayer::StreetStat({0,0,0,0,0,0})));
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_flop], StatPlayer::StreetStat({0,0,0,0,0,0})));
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_turn], StatPlayer::StreetStat({0,0,0,0,0,0})));
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_river], StatPlayer::StreetStat({0,0,0,0,0,0})));
		stat.update_street_stat(AbstractTable::t_turn, AbstractPlayer::t_check);
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_turn], StatPlayer::StreetStat({1,0,0,0,1,0})));
		stat.update_street_stat(AbstractTable::t_turn, AbstractPlayer::t_check);
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_turn], StatPlayer::StreetStat({2,0,0,0,2,0})));
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_call);
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_river], StatPlayer::StreetStat({1,0,0,1,0,0})));
		stat.reset_stats();
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_preflop], StatPlayer::StreetStat({0,0,0,0,0,0})));
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_flop], StatPlayer::StreetStat({0,0,0,0,0,0})));
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_turn], StatPlayer::StreetStat({0,0,0,0,0,0})));
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_river], StatPlayer::StreetStat({0,0,0,0,0,0})));
		return 0;
	}

	//TODO complete with more examples
	int test_update_stats(){
		StatPlayer stat = StatPlayer();
		stat.update_street_stat(AbstractTable::t_preflop, AbstractPlayer::t_bet);
//		cout<<stat.street_stat_to_str(stat.get_hand_stats().preflop)<<endl;
		assert(is_street_stat_equal(stat.get_hand_stats()[AbstractTable::t_preflop], StatPlayer::StreetStat({1,0,1,0,0,0})));
//		stat.update_street_stat(AbstractTable::t_preflop, AbstractPlayer::t_bet);
//		assert(is_street_stat_equal(stat.get_hand_stats().preflop, StatPlayer::StreetStat({1,1,0,0,0})));
		return 0;
	}

	int test_save_n_plot(){
		string foldername = "./test_folder";
		StatPlayer stat = StatPlayer();
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_bet);
		stat.checkpoint(0);
		stat.save_stats(foldername);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_fold);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_fold);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_fold);
		stat.checkpoint(3);
		stat.save_stats(foldername);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_bet);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_fold);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_fold);
		stat.checkpoint(4);
		stat.save_stats(foldername);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_bet);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_raise);
		stat.update_street_stat(AbstractTable::t_river, AbstractPlayer::t_raise);
		stat.checkpoint(7);
		stat.save_stats(foldername);
		cout<<"DONE"<<endl;
		return 0;
	}

};




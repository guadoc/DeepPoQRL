/*
 * table.h
 *
 *  Created on: Dec 8, 2018
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_AbstractTable_H_
#define TABLE_LIB_AbstractTable_H_



//#pragma once

#include "../StdAfx.h"
#include "../deck_lib/Deck.h"
#include "../deck_lib/Card.h"
#include "../deck_lib/Hand.h"
#include "../player_lib/PlayerRandom.h"
#include "../utils/utils.h"

using namespace std;

class AbstractTable {
public:
	AbstractTable(void);
	AbstractTable(unsigned int n_players);
	AbstractTable(vector<AbstractPlayer*> &);
	virtual ~AbstractTable(void);
	virtual void display_table(unsigned int);
	unsigned int get_before_last_raise(void) const;
	unsigned int get_diff_last_raises(void) const;
	unsigned int get_last_raise() const;
	unsigned int get_pot()const;
	unsigned int get_blend_value()const;
	vector<AbstractPlayer*> get_players() const;
	Hand get_board() const;
	unsigned int get_board_average_value();

	string to_str() const;

	enum Street
		{
			t_preflop= 0,
			t_flop,
			t_turn,
			t_river
		};


	void distribute_card_to_board();
	virtual void distribute_street(AbstractTable::Street);
	virtual void distribute_preflop();
//	void distribute_flop();
//	void distribute_turn();
//	void distribute_river();

	void update_current_raises(unsigned int);

	void set_blends();
	virtual void init_hand();
	virtual void play_hand();

	void run_pre_flop();
	void run_street(AbstractTable::Street);
	virtual bool run_full_pre_flop();
	virtual bool run_full_street(AbstractTable::Street, bool);
	bool gather_pots();
	void fill_side_pots(list<unsigned int> &);

	virtual void distribute_pot_to_best_hands();
	virtual void distribute_side_pot_to_best_hands(list<AbstractPlayer*> & players , unsigned int pot);
	virtual void distribute_side_pots_to_best_hands();
	virtual void player_gets_pot(AbstractPlayer* player, unsigned int pot);

	virtual void close_hand();


protected:
	unsigned int n_players;
	/*
	 * n_player indicates the number of player at the table.
	 * As a rule all sit should be filled with a player with a non zero stake value
	 */

	vector<AbstractPlayer*> players;
	/*
	 * Vector containing a pointer on each player.
	 * The index of the player in this vector indicates its position on the table
	 */

	Deck deck;
	/*
	 * The Deck is useful to provide the cards during a hand.
	 * The method random_card enables to create players' hand and to feed the board
	 */

	Hand board;
	/*
	 * The board is the list of distributed cards for the table board
	 * It is empty after every hand initializations
	 */

	unsigned int pot;
	/*
	 * pot is the central pot
	 */
	list<unsigned int > side_pots;
	list<list<AbstractPlayer*>> side_pots_player_list;
	/*
	 * side_pots and side_pot_player are useful whenever there is player all in
	 */


	unsigned int big_blend;
	unsigned int small_blend;
	/*
	 * big_blend and small_blend indicate the blends values
	 */

	unsigned int hand_played;
	/*
	 * hand_player is incremented to represent the number of player hand since the instantiation of the table
	 * Is not used yet
	 */

	unsigned int last_raise;
	unsigned int before_last_raise;
	/*
	 * last_raise and before_last raise are used to control that any raise is conform
	 */


	unsigned int dealer;
	/*
	 * dealer indicates the position of the dealer button
	 */


};



#endif /* TABLE_LIB_AbstractTable_H_ */



#ifndef PLAYER_LIB_ABSTRACTPLAYER_H_
#define PLAYER_LIB_ABSTRACTPLAYER_H_

#include "../deck_lib/Hand.h"
#include "../StdAfx.h"
//#include "StatPlayer.h"


#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>
#include <iostream>


using namespace std;
class AbstractTable;
//class StatPlayer;

class AbstractPlayer{
public:
	AbstractPlayer(void);
	AbstractPlayer(string);
	AbstractPlayer(AbstractTable *, unsigned int position);
	virtual ~AbstractPlayer();

	bool operator>=(const AbstractPlayer &player);
	bool operator>(const AbstractPlayer &player);
	bool operator<(const AbstractPlayer &player);
	bool operator<=(const AbstractPlayer &player);
	bool operator==(const AbstractPlayer &player);

	void init_bank_roll();
	void set_hand(const Hand &);
	void set_hand(list<Card> *);
	void clear_hand(void);
	void add_card_to_hand(Card);
	void add_cards_to_hand(list<Card>&);
	void set_commitment(int);
	void set_pos_on_table(unsigned int);
	void set_stake(unsigned int);
	void set_table(AbstractTable *, unsigned int );
	void set_is_in_hand(bool);
	void set_open_hand(bool);
	void set_auto_rebuy(bool);

	unsigned int get_hand_value();

	virtual void commit_chips(unsigned int);
	virtual void add_to_stake(unsigned int value);

	unsigned int get_commitment(void) const;
	Hand get_hand() const;
	unsigned int get_stake() const;
	unsigned int get_pos_on_table()const;
	unsigned int get_bank_roll()const;
	string get_id()const;
	unsigned int get_base_stake() const;
	unsigned int get_initial_bank_roll()const ;
	bool is_in_hand() const;
	bool is_auto_rebuy() const ;
	bool is_open_hand() const;
	Hand::HandCategory get_hand_category();

	string to_str();

	virtual void init_hand();
	virtual void close_hand();

	enum Action
	{
		t_fold = 1,
		t_call,
		t_raise,
		t_bet,
		t_check
	};

	virtual Action play_street(unsigned int);

	virtual Action raise_pot(unsigned int);
	virtual Action call_pot();
	virtual Action bet_pot(unsigned int);
	virtual Action check_pot();
	virtual Action fold_pot();

	virtual Action play_preflop(){cout<< "virtual function playPreflop not defined"<<endl; return t_fold;}
	virtual Action play_flop(){cout<< "virtual function playFlop not defined"<<endl;return t_fold;};
	virtual Action play_turn(){cout<< "virtual function playTurn not defined"<<endl;return t_fold;};
	virtual Action play_river(){cout<< "virtual function playRiver not defined"<<endl;return t_fold;};

	virtual void transfert_in(boost::archive::binary_iarchive & iarch);
	virtual void transfert_out(boost::archive::binary_oarchive &oa) const;
	virtual string save_to_folder(string) const;
	string save() const;
	virtual string load_from_folder(string);
	virtual string load_from_model(string);

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version);

protected:
	unsigned int stake;
	/*
	 * stake is the stake amount of the player.
	 * it should be > 0, otherwise the player is removed from the table
	 * or its stake is refilled
	 */

//	list<Card> hand;
	Hand hand;
	/*
	 * hand is a list of card that represents the two cards hand of the player
	 * Its size can be zero of two.
	 */

	AbstractTable * table;
	/*
	 * table is an object of type Table that represents the table
	 * where the player is playing
	 */

	unsigned int commitment;
	/*
	 * commitment indicates the money invested in the street.
	 * If commitment < 0 the player is not in the hand anymore
	 */

	bool _is_in_hand;
	/*
	 * boolean that indicates if the player is still implied in the hand.
	 * It has to be set to true at the beginning of every hands
	 * It is set to false only when the player fold
	 */

	string id;
	/*
	 * id represents the unique number of the player instance
	 * it can be reused if the player is reloaded from a file
	 */

	unsigned int pos_on_table;
	/*
	 * pos_on_table represents the relative position of the player on the table
	 * It is useful to get the playing order for the different streets
	 * Maybe it can be removed because the table already has the information
	 */

	unsigned int stock;
	/*
	 * Stock pile of the player over different games or re-buy.
	 * It is important to represent the player bank roll evolution in a learning purpose
	 */

	unsigned int initial_bank_roll;
	/*
	 * initial bank roll of the player. Default: 100000
	 */

	bool auto_rebuy;
	/*
	 * Decides if the stake is updated to minimum after every hands
	 */

	unsigned int base_stake;
	/*
	 * Represents the standard initial amount of chips a player has when sitting in a new table
	 * It is also the re-buy amount
	 */

	bool open_hand;
	/*
	 * Indicates if the hand of the player will be visible in the graphic mode
	 */

	string folder_to_save;
	/*
	 * Folder where the player is saved when no folder is given in argumentss
	 */
};



#endif /* PLAYER_LIB_ABSTRACTPLAYER_H_ */


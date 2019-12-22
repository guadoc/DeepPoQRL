/*
 * desck_m.h
 *
 *  Created on: Dec 8, 2018
 *      Author: Michael Blot
 */

#ifndef DECK_M_H_
#define DECK_M_H_

#pragma once
#include "../StdAfx.h"

#include "Card.h"
using namespace std;
class Deck
{
public:
	Deck(void);
	Deck(list<Card> &);
	Deck(vector<bool>&);
	Deck(const Deck &);
	list<Card> get_distributed_cards_list() const;
	vector<bool> get_distributed_cards() const;
	Card random_card(void);
	void shuffle(void);
	string distributed_cards_to_str(void) const;
private:
	vector<bool> is_distributed;
};



#endif /* DECK_M_H_ */

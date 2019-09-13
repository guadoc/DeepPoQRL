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
	Card random_card(void);
	void print_distributed_cards(void);
	void shuffle(void);
private:
	list<Card> distributed_cards;
};



#endif /* DECK_M_H_ */

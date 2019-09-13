/*
 * card_m.h
 *
 *  Created on: Dec 2, 2018
 *      Author: Michael Blot
 */

#ifndef DECK_LIB_CARD_H_
#define DECK_LIB_CARD_H_



#pragma once
#include "../StdAfx.h"
using namespace std;
class Card
{
public:
	enum Suit{
		_D	= 1,
		_C,
		_H,
		_S,
		_ERROR_SUIT
			};

	enum Rank{
		_2	= 1,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_10,
		_J,
		_Q,
		_K,
		_A,
		_ERROR_RANK
	};
	Card(void);
	Card(Rank, Suit);
	Card(const Card & C);
	Card(unsigned int Card_id);
	Card(const string);
	~Card(void);

	bool operator<(const Card &Ca);
	bool operator<=(const Card &Ca);
	bool operator==(const Card &Ca);
	bool operator>=(const Card &Ca);
	bool operator>(const Card &Ca);
	void set_rank(Rank);
	void set_suit(Suit);
	unsigned int get_id() const;
	Rank get_rank() const;
	Suit get_suit() const;
	string to_str() const;
//	void display_card(SDL_Renderer * renderer, int coordX,  int coordY, int sizeX, int sizeY) const;


private:
	Rank rank;
	Suit suit;
	unsigned int id;
};



#endif /* DECK_LIB_CARD_H_ */

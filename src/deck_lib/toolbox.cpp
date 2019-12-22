/*
 * toolbox.cpp
 *
 *  Created on: Dec 18, 2019
 *      Author: Michael Blot
 */

#include "Card.h"

static bool is_card_in_list(unsigned int card_id, list<Card>& card_list) {
	for (auto &card :card_list) {
		if (card_id == card.get_id()) {
			return true;
		}
	}
	return false;
}

static string card_list_to_str(const list<Card> &card_list) {
	list<Card>::const_iterator j;
	string hand_str = "";
	for (auto & card: card_list){
		hand_str += card.to_str() + " ";
	}
	return hand_str;
}

static unsigned int num_h_function(list<Card>* cards){
	unsigned int h_code = 0;
	cards->sort();
	cards->reverse(); //can be removed
	unsigned int power = 0;
	for (auto card : *cards){
		h_code += card.get_id() * std::pow((float)52, (int)power);
		power++;
	}
	return h_code;
}

static string str_h_function(list<Card>* cards){
	cards->sort();
	return card_list_to_str(*cards);
}

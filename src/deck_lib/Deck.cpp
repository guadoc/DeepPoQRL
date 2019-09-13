/*
 * deck_m.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: Michael Blot
 */



#include "../StdAfx.h"
#include "Deck.h"
using namespace std;

Deck::Deck(void){
	this->distributed_cards.clear();
}

Deck::Deck(list<Card> & cards){
	this->distributed_cards = cards;
}

Card Deck::random_card(void){
	unsigned int card_id;
	bool clear_from_distributed_cards = false;
	while(not clear_from_distributed_cards){
		clear_from_distributed_cards = true;
		card_id = rand() % 52;
		list<Card>::iterator j;
		for(j = this->distributed_cards.begin(); j != this->distributed_cards.end(); j++){
			if (card_id == j->get_id()){
				clear_from_distributed_cards = false;
				break;
			}
//			clear_from_distributed_cards = clear_from_distributed_cards and (card_id != j->get_id());
		}
	}
	Card new_card = Card(card_id);
	this->distributed_cards.push_back(new_card);
	return new_card;
}

void Deck::print_distributed_cards(void){
	list<Card>::iterator j;
	for(j = this->distributed_cards.begin(); j != this->distributed_cards.end(); j++){
		cout<<j->to_str()<<", ";
	}
	cout<<endl;
}

void Deck::shuffle(void){
	this->distributed_cards.clear();
}

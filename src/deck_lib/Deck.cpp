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
	this->is_distributed = vector<bool>(52, false);
}

Deck::Deck(list<Card> & distributed_cards_list):Deck(){
	for(auto &card: distributed_cards_list){
		this->is_distributed[card.get_id()] = true;
	}
}

Deck::Deck(vector<bool> & distributed_cards){
	this->is_distributed = distributed_cards;
}

Deck::Deck(const Deck & deck){
	this->is_distributed = deck.get_distributed_cards();
}

vector<bool> Deck::get_distributed_cards() const{
	return this->is_distributed;
}

list<Card> Deck::get_distributed_cards_list() const{
	list<Card> distributed_cards_list;
	for(unsigned int i=0; i < 52; i++){
		if(this->is_distributed[i]){
			distributed_cards_list.push_back(Card(i));
		}
	}
	return distributed_cards_list;
}

Card Deck::random_card(void){
	unsigned int card_id = rand() % 52;
	while(this->is_distributed[card_id]){
		card_id = rand() % 52;
	}
	this->is_distributed[card_id] = true;
	return Card(card_id);
}

void Deck::shuffle(){
	this->is_distributed = vector<bool>(52, false);
}

string Deck::distributed_cards_to_str(void) const{
	string distributed_cards_str = "";
	for(unsigned int i=0; i < 52; i++){
		if(this->is_distributed[i]){
			distributed_cards_str += Card(i).to_str() + ", ";
		}
	}
	return distributed_cards_str;
}

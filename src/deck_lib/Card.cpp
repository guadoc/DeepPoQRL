/*
 * card_m.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: Michael Blot
 */


#include "Card.h"

#include "../utils/utils.h"
using namespace std;

Card::Card(void):rank(Rank::_ERROR_RANK), suit(Suit::_ERROR_SUIT), id(0){}
Card::Card(Rank rank, Suit suit){
	if (rank > 13 || rank <= 0){
		cout<<"RANK ERROR"<<endl;
	}
	if (suit != Suit::_C && suit != Suit::_S && suit != Suit::_H && suit != Suit::_D  && suit != Suit::_ERROR_SUIT){
		cout<<"SUIT ERROR"<<endl;
	}
	this->suit = suit;
	this->rank = rank;
	this->id = 13 * (this->suit - 1) + this->rank - 1;
}

Card::Card(const Card & C){
	this->suit = C.suit;
	this->rank = C.rank;
	this->id = C.id;
}

Card::Card(unsigned int card_id){
	int rank = card_id % 13;
	this->suit = (Suit)((double)(card_id - rank) / 13 + 1);
	this->rank = (Rank)(rank + 1);
	this->id = card_id;
}


//TODO
Card::Card(const string cards){
	string suit_string;
	string rank_string;
	this->suit = Suit::_ERROR_SUIT;
	this->rank = Rank::_ERROR_RANK;
	this->id = 13 * (this->suit - 1) + this->rank - 1;
}

void Card::set_suit(Suit suit){
	this->suit = suit;
}

void Card::set_rank(Rank rank){
	this->rank= rank;
}

Card::Rank Card::get_rank() const {
	return this->rank;
}
Card::Suit Card::get_suit() const{
	return this->suit;
}
unsigned int Card::get_id()const{
	return 13 * (this->suit - 1) + this->rank - 1;
}
string Card::to_str() const {
	string suit;
	string rank;
	switch(this->suit){
	case Suit::_D : {
		suit = "d";
		break;
			 }
	case Suit::_S : {
		suit="s";
		break;
			 }
	case Suit::_H : {
		suit="h";
		break;
			 }
	case Suit::_C : {
		suit="c";
		break;
			 }
	case Suit::_ERROR_SUIT : {
		suit = " Card ERROR";
		break;
			}
	}
	switch(this->rank){
		case Rank::_2 : {
			rank = "2";
			break;
		 }
		case Rank::_3 : {
			rank = "3";
			break;
		 }
		case Rank::_4 : {
			rank = "4";
			break;
		 }
		case Rank::_5 : {
			rank = "5";
			break;
		 }
		case Rank::_6 : {
			rank = "6";
			break;
		 }
		case Rank::_7 : {
			rank = "7";
			break;
		 }
		case Rank::_8 : {
			rank = "8";
			break;
		 }
		case Rank::_9 : {
			rank = "9";
			break;
		 }
		case Rank::_10 : {
			rank = "T";
			break;
		 }
		case Rank::_J : {
			rank = "J";
			break;
		 }
		case Rank::_Q : {
			rank = "Q";
			break;
		 }
		case Rank::_K : {
			rank = "K";
			break;
		 }
		case Rank::_A : {
			rank = "A";
			break;
		 }
		case Rank::_ERROR_RANK : {
			rank = " Card ERROR";
			break;
				}
		}
	return rank + suit;
}


//void Card::display_card (SDL_Renderer * renderer, int coordX,  int coordY, int sizeX, int sizeY) const {
//	util_graphic::display_image(util_graphic::get_card_filename(this->to_str()), renderer, coordX, coordY, sizeX, sizeY);
//}

bool Card::operator < (const Card &Ca)
{
	if (this->rank < Ca.rank){
		return true;
	}
	else if(this->rank== Ca.rank){
		if(this->suit < Ca.suit){
			return true;
		}else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool Card::operator <= (const Card &Ca)
{
	if (this->rank < Ca.rank){
		return true;
	}
	else if(this->rank == Ca.rank){
		if(this->suit <= Ca.suit){
			return true;
		}else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool Card::operator >= (const Card &Ca)
{
	if (this->rank > Ca.rank){
		return true;
	}
	else if(this->rank == Ca.rank){
		if(this->suit >= Ca.suit){
			return true;
		}else{
			return false;
		}
	}
	else{
		return false;
	}
}
bool Card::operator > (const Card &Ca)
{
	if (this->rank > Ca.rank){
		return true;
	}
	else if(this->rank == Ca.rank){
		if(this->suit > Ca.suit){
			return true;
		}else{
			return false;
		}
	}
	else{
		return false;
	}
}
bool Card::operator == (const Card &Ca)
{
	if (this->id == Ca.id){//(this->rank == Ca.rank && this->suit == Ca.suit){
		return true;
	}
	else{
		return false;
	}
}



Card::~Card(void){}

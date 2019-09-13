

#include "PlayerRandom.h"

#include "../table_lib/TableGUI.h"

PlayerRandom::PlayerRandom(void):ParentPlayerRandom(){
}

PlayerRandom::PlayerRandom(string id):ParentPlayerRandom(id){
}

PlayerRandom::PlayerRandom(AbstractTable* table):ParentPlayerRandom(table){

}

PlayerRandom::PlayerRandom(AbstractTable * table, unsigned int position):ParentPlayerRandom(table, position){
}

PlayerRandom::~PlayerRandom(void){}


AbstractPlayer::Action PlayerRandom::play_preflop(){
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		unsigned int choice = rand() % 3;
		switch(choice){
		case 0:
			{
				if (this->table->get_last_raise() > this->stake + this->commitment){
					return this->call_pot();
				}
				else{
					unsigned int value_raise = std::min(this->table->get_last_raise() +  1*this->table->get_diff_last_raises()
														, this->stake + this->commitment
														);
					return this->raise_pot(value_raise);
				}
			break;}
		case 1:
			return this->call_pot();
			break;
		case 2:
			if (this->commitment < this->table->get_last_raise()){
				return this->fold_pot();
			}
			else
			{
				return this->check_pot();
			}

			break;
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		unsigned int choice = rand() % 2;
		switch(choice){
		case 0:
			{unsigned int value_bet = std::min(this->stake, this->table->get_pot());
			return this->bet_pot(value_bet);
			break;}
		case 1:
			return this->check_pot();
			break;
		}
	}
	return this->fold_pot();

}
AbstractPlayer::Action PlayerRandom::play_flop(){
	return this->play_preflop();
}
AbstractPlayer::Action PlayerRandom::play_turn(){
	return this->play_preflop();
}
AbstractPlayer::Action PlayerRandom::play_river(){
	return this->play_preflop();
}



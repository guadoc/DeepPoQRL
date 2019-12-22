

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

AbstractPlayer::Action PlayerRandom::random_play(){
	if (this->table->get_last_raise() != 0 ){// there is a bet from another player: raise_pot, call_pot or fold_pot
		unsigned int choice = rand() % 8;
		if(choice == 0){
			if (this->table->get_last_raise() >= this->stake + this->commitment){
				return this->call_pot();
			}
			else{
				unsigned int value_raise = std::min(this->table->get_last_raise() +  1*this->table->get_diff_last_raises()
													, this->stake + this->commitment
													);
				return this->raise_pot(value_raise);
			}
		}
		else if(choice == 1 or choice == 2 or choice == 3 or choice == 4 or choice == 5 or choice == 6){
			if (this->table->get_last_raise() > this->commitment){
				return this->call_pot();
			}
			else{
				return this->check_pot();
			}
		}
		else{
			if (this->commitment < this->table->get_last_raise()){
				return this->fold_pot();
			}
			else
			{
				return this->check_pot();
			}
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		unsigned int choice = rand() % 5;
		if(choice == 0){
			unsigned int value_bet = std::min(this->stake, (unsigned int)(0.3 * (float)this->table->get_total_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->fold_pot();
}


AbstractPlayer::Action PlayerRandom::play_preflop(){
	return this->random_play();

}
AbstractPlayer::Action PlayerRandom::play_flop(){
	return this->random_play();
}
AbstractPlayer::Action PlayerRandom::play_turn(){
	return this->random_play();
}
AbstractPlayer::Action PlayerRandom::play_river(){
	return this->random_play();
}



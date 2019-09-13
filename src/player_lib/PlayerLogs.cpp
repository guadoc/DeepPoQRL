/*
 * PlayerLogs.cpp
 *
 *  Created on: Mar 3, 2019
 *      Author: michael blot
 */

#include "PlayerLogs.h"
#include "../table_lib/AbstractTable.h"

PlayerLogs::PlayerLogs(void):AbstractPlayer(){

}

PlayerLogs::PlayerLogs(string id):AbstractPlayer(id){

}

PlayerLogs::PlayerLogs(string id, float lr):AbstractPlayer(id){

}


PlayerLogs::PlayerLogs(AbstractTable * table):AbstractPlayer(table){

}

PlayerLogs::PlayerLogs(AbstractTable * table, unsigned int position):AbstractPlayer(table, position){

}


PlayerLogs::~PlayerLogs(void){}

PlayerLogs::Action PlayerLogs::play_street(unsigned int street){
	this->table->display_table(this->pos_on_table);
	return AbstractPlayer::play_street(street);
}

PlayerLogs::Action PlayerLogs::raise_pot(unsigned int value){
	cout<<"==> Player " + to_string(this->pos_on_table)+" RAISE "+ std::to_string(value)<<"\n"<<endl;
	return AbstractPlayer::raise_pot(value);
}


PlayerLogs::Action PlayerLogs::bet_pot(unsigned int value){
	cout<<"==> Player " + to_string(this->pos_on_table)+" BET " + std::to_string(value)<<"\n"<<endl;
	return AbstractPlayer::bet_pot(value);
}

PlayerLogs::Action PlayerLogs::fold_pot(){
	cout<<"==> Player " + to_string(this->pos_on_table)+" FOLD"<<"\n"<<endl;
	return AbstractPlayer::fold_pot();
}

PlayerLogs::Action PlayerLogs::check_pot(){
	cout<<"==> Player " + to_string(this->pos_on_table)+" CHECK"<<"\n"<<endl;
	return AbstractPlayer::check_pot();
}


PlayerLogs::Action PlayerLogs::call_pot(){
	unsigned int value = (int)this->table->get_last_raise() - (int)this->commitment;
	unsigned int value_commited = min(value, this->stake);
	cout<<"==> Player " + to_string(this->pos_on_table)+" CALL "<<value_commited<<"\n"<<endl;
	return AbstractPlayer::call_pot();
}

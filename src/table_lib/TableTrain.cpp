/*
 * TableTrain.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Michael Blot
 */

#include "TableTrain.h"



TableTrain::TableTrain(): ParentTableTrain(){
	this->table_state = {0,0};
}


TableTrain::TableTrain(unsigned int n_players):ParentTableTrain(n_players){
	this->table_state = {0,0};
}

TableTrain::TableTrain(vector<AbstractPlayer*> & players):ParentTableTrain(players){
	this->table_state = {0,0};
}

TableTrain::~TableTrain(void){

}

TableTrain::TableState TableTrain::get_state(){
	return this->table_state;
}

void TableTrain::update_state(PlayerBot::Action action, unsigned int value){
//	switch(action){
//		case PlayerBot::t_raise:
//			this->table_state.initiative +=1;
//			this->table_state.interest +=1;
//			break;
//		case PlayerBot::t_fold:
//			break;
//		case PlayerBot::t_bet:
//			this->table_state.initiative +=1;
//			this->table_state.interest +=1;
//			break;
//		case PlayerBot::t_check:
//			break;
//		case PlayerBot::t_call:
//			this->table_state.interest +=1;
//			break;
//	}
}

void TableTrain::init_hand(){
	this->init_state();
	ParentTableTrain::init_hand();
}

void TableTrain::init_state(){
	this->table_state = {0,0};
}



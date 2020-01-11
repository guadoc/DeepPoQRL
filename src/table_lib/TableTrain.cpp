/*
 * TableTrain.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Michael Blot
 */

#include "TableTrain.h"



TableTrain::TableTrain(): ParentTableTrain(){
	this->table_state = this->init_state();
}


TableTrain::TableTrain(unsigned int n_players):ParentTableTrain(n_players){
	this->table_state = this->init_state();
}

TableTrain::TableTrain(vector<AbstractPlayer*> & players):ParentTableTrain(players){
	this->table_state = this->init_state();
}

TableTrain::~TableTrain(void){

}

TableTrain::TableState TableTrain::get_state(){
	return this->table_state;
}

string TableTrain::state_to_str(TableTrain::TableState state){
	string state_str = "Table State: ";
	state_str += "total action[" + to_string(state.total_action)+ "], ";
	state_str += "interest[" + to_string(state.interest)+ "], ";
	state_str += "initiative[" + to_string(state.initiative)+ "], ";
	return state_str;
}

void TableTrain::init_hand(){
	this->table_state = this->init_state();
	ParentTableTrain::init_hand();
}

TableTrain::TableState TableTrain::init_state(){
	return {0, 0, 0};
}

void TableTrain::update_state(PlayerBot::Action action, unsigned int value){
	this->table_state.total_action += 1;
	switch(action){
		case PlayerBot::t_raise:
			this->update_state_when_raise();
			break;
		case PlayerBot::t_fold:
			this->update_state_when_fold();
			break;
		case PlayerBot::t_bet:
			this->update_state_when_bet();
			break;
		case PlayerBot::t_check:
			update_state_when_check();
			break;
		case PlayerBot::t_call:
			this->update_state_when_call();
			break;
	}
}


void TableTrain::update_state_when_raise(){
	this->table_state.initiative +=1;
	this->table_state.interest +=1;
}

void TableTrain::update_state_when_bet(){
	this->table_state.initiative +=1;
	this->table_state.interest +=1;
}

void TableTrain::update_state_when_check(){
	this->table_state.interest +=1;
}

void TableTrain::update_state_when_call(){
	this->table_state.interest +=1;
}

void TableTrain::update_state_when_fold(){

}

string TableTrain::to_str(){
	string table_str = ParentTableTrain::to_str();
	table_str += "\n";
	table_str += TableTrain::state_to_str(this->table_state);
	return table_str;
}




/*
 * table.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: walnutalgo
 */

#include "TableLogs.h"

#include "../StdAfx.h"


TableLogs::TableLogs(): ParentTableLogs(){

}


TableLogs::TableLogs(unsigned int n_players):ParentTableLogs(n_players){

}

TableLogs::TableLogs(vector<AbstractPlayer*> & players):ParentTableLogs(players){

}

TableLogs::~TableLogs(){
//	~ParentTableLogs();
}


void TableLogs::display_table(unsigned int position_active_payer){
	cout<<this->to_str()<<endl;
}

void TableLogs::distribute_street(Street street){
	ParentTableLogs::distribute_street(street);
	this->display_table(-1);
}

bool TableLogs::run_full_pre_flop(void){
	cout<<"***********************************PRE FLOP*************************"<<endl;
	return ParentTableLogs::run_full_pre_flop();
}


void TableLogs::play_hand(){
	cout<<"###########################################################################################"<<endl;
	cout<<"###########################################################################################"<<endl;
	cout<<"Hand N°"<<this->hand_played<<endl;
	ParentTableLogs::play_hand();
}


void TableLogs::distribute_pot_to_best_hands(){
	cout<<"Pot to best hand"<<endl;
	ParentTableLogs::distribute_pot_to_best_hands();
}


void TableLogs::distribute_side_pots_to_best_hands(){
	cout<<"Side pots to best hands"<<endl;
	ParentTableLogs::distribute_side_pots_to_best_hands();
}

void TableLogs::init_hand(){
	ParentTableLogs::init_hand();
	this->display_table(-1);
}


void TableLogs::close_hand(){
	ParentTableLogs::close_hand();
	this->display_table(-1);
}

void TableLogs::player_gets_pot(AbstractPlayer* player, unsigned int pot){
	ParentTableLogs::player_gets_pot(player, pot);
	cout<<"Sit "<<player->get_pos_on_table()<<" gets "<<pot<<endl;
}


bool TableLogs::run_full_street(Street street, bool action){
	if(street == AbstractTable::t_flop){
		cout<<"***********************************FLOP*************************"<<endl;
	}
	else if(street == AbstractTable::t_turn){
		cout<<"***********************************TURN*************************"<<endl;
	}
	else if(street == AbstractTable::t_river){
		cout<<"***********************************RIVER************************"<<endl;
	}
	return ParentTableLogs::run_full_street(street, action);
}





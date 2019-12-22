

#include "TableGUI.h"
#include "../StdAfx.h"

#define TIME_LAPSE 4

TableGUI::TableGUI():ParentTableGUI(){
	this->gui = new GUI();
	this->showdown_time_lapse = TIME_LAPSE;
}


TableGUI::TableGUI(unsigned int n_players):ParentTableGUI(n_players){
	this->gui = new GUI(this->n_players);
	this->showdown_time_lapse = TIME_LAPSE;
}

TableGUI::TableGUI(vector<AbstractPlayer*> & players):ParentTableGUI(players){
	this->gui = new GUI(this->n_players);
	this->showdown_time_lapse = TIME_LAPSE;
}

TableGUI::~TableGUI(void){
	this->gui->~GUI();
	delete this->gui;
}

GUI * TableGUI::get_gui()const{
	return this->gui;
}


void TableGUI::display_table(unsigned int position_active_payer){
	float time_laps = 1.;//75;
	ParentTableGUI::display_table(position_active_payer);
	this->gui->display_table(this->get_total_pot(), this->board.get_cards(), this->players, this->dealer, position_active_payer);
	sleep(time_laps);
}





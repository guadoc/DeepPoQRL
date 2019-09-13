/*
 * Session.cpp
 *
 *  Created on: Jan 5, 2019
 *      Author: michael blot
 */

#include "Session.h"

Session::Session() {
	this->table = new AbstractTable(6);
	this->n_checkpoint = 1000;
	this->log_folder = "/home/walnutalgo/workspace/PQL/src/logs/";
}

Session::Session(vector<AbstractPlayer*> players){
	this->table = new TableTrain(players);
	this->n_checkpoint = 5000;
	this->log_folder = "/home/walnutalgo/workspace/PQL/src/logs/";
}

Session::~Session(){
	delete this->table;
}

void Session::run(unsigned int n_hand){
	for (unsigned int i = 1; i <= n_hand; i++){
		utils::progress_bar((float)i/(float)n_hand);
		this->table->play_hand();
		if (i%this->n_checkpoint == 0){
			this->checkpoint();
		}
	}
}

void Session::checkpoint(){
	for (auto player: this->table->get_players()){
		string folder_name = this->log_folder + player->get_id() + '/';
		cout<<folder_name<<endl;
		string command = "mkdir " + folder_name; 
		system(command.c_str());
		player->save_to_folder(folder_name);
		player->get_stats().save_stats(folder_name);
	}
}

vector<AbstractPlayer*> Session::get_players(){
	return this->table->get_players();
}


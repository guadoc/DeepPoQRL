
#include "StatPlayer.h"

StatPlayer::StatPlayer() {
	// TODO Auto-generated constructor stub

}

StatPlayer::~StatPlayer() {
	// TODO Auto-generated destructor stub
}


void StatPlayer::update_stats(unsigned int bankroll, unsigned int stake){
	this->bank_roll_evolution.push_back(bankroll + stake);
	this->stake_evolution.push_back(stake);
}

void StatPlayer::update_stats(unsigned int bankroll, unsigned int stake, float param){
	this->bank_roll_evolution.push_back(bankroll + stake);
	this->stake_evolution.push_back(stake);
	this->param_stat_evolution.push_back(param);
}

void StatPlayer::plot_stats(string id){		
	// command = "python src/script_python/plot_csv.py "+ file_to_save_log + "/bankroll.csv";
	// command = "python src/script_python/plot_csv.py "+ file_to_save_log + "/param.csv";
//	system(command.c_str());
}

void StatPlayer::save_stats(string folder_name){
	string file_to_save_log = folder_name + "/stats/";
	string command = "mkdir " + file_to_save_log;
	system(command.c_str());	
	utils::list_to_scv<list<unsigned int >>(file_to_save_log + "bankroll.csv", this->bank_roll_evolution);
	utils::list_to_scv<list<float >>(file_to_save_log + "param.csv", this->param_stat_evolution);
	cout<<"BankRoll"<<endl;
	cout<<this->bank_roll_evolution.size()<<endl;
}

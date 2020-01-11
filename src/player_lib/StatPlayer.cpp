
#include "StatPlayer.h"
#include "toolbox.cpp"

#include "/home/micha/workspace/matplotlib-cpp-master/matplotlibcpp.h"
namespace plt = matplotlibcpp;

StatPlayer::StatPlayer() {
	this->init_hand_stats();
}

StatPlayer::~StatPlayer() {
	for (auto & street_stat: this->hand_stats){
		delete street_stat;
	}
}

void StatPlayer::reset_stats(){
	for(auto & street_stat: this->hand_stats){
		street_stat->played = 0;
		street_stat->raise = 0;
		street_stat->bet = 0;
		street_stat->call = 0;
		street_stat->check = 0;
		street_stat->fold = 0;
	}
}

void StatPlayer::init_hand_stats(){
	this->hand_stats = vector<StreetStat*>(4, NULL);
	for (auto & street_stat: this->hand_stats){
		street_stat = this->street_stat_init();
	}
}

StatPlayer::StreetStat* StatPlayer::street_stat_init() const{
	StreetStat* street_stat= new StreetStat({0, 0, 0, 0, 0, 0});
	return street_stat;
}

vector<StatPlayer::StreetStat*> StatPlayer::get_hand_stats()const{
	return this->hand_stats;
}

void StatPlayer::update_street_stat(AbstractTable::Street street, AbstractPlayer::Action action){
	this->update_street_stat(this->hand_stats[street], action);
}

void StatPlayer::update_street_stat(StatPlayer::StreetStat* street_stat, AbstractPlayer::Action action){
	street_stat->played++;
	switch(action){
	case AbstractPlayer::t_bet:
		street_stat->bet++;
		break;
	case AbstractPlayer::t_raise:
		street_stat->raise++;
		break;
	case AbstractPlayer::t_call:
		street_stat->call++;
		break;
	case AbstractPlayer::t_fold:
		street_stat->fold++;
		break;
	case AbstractPlayer::t_check:
		street_stat->check++;
		break;
	}
}

void StatPlayer::checkpoint(unsigned int bankroll){
	float river_raise_proba = ((float)this->hand_stats[AbstractTable::t_river]->bet + (float)this->hand_stats[AbstractTable::t_river]->raise) / ((float)this->hand_stats[AbstractTable::t_river]->played);
	this->river_aggression_proba.push_back(river_raise_proba);
	this->bankroll.push_back(bankroll);
}

void StatPlayer::plot_stats(void) const{
	plt::close();
	plt::figure();
	plt::subplot(3, 1, 1);
	plt::plot({std::begin(this->bankroll), std::end(this->bankroll)});
	plt::subplot(3, 1, 2);
	plt::plot({std::begin(this->river_aggression_proba), std::end(this->river_aggression_proba)});
	plt::pause(0.05);
	plt::close();
	plt::show();
}

void StatPlayer::save_stats(string foldername) const{
	string file_to_save_log = foldername + "/stats/";
	list_to_scv<list<unsigned int >>(file_to_save_log + "bankroll.csv", this->bankroll);
	list_to_scv<list<float >>(file_to_save_log + "river_aggression_proba.csv", this->river_aggression_proba);
//	string command = "python3 src/script_python/plot_csv.py " + file_to_save_log + " &";
//	system(command.c_str());
}

string StatPlayer::street_stat_to_str(AbstractTable::Street street) const{
	return this->street_stat_to_str(this->hand_stats[street]);
}

string StatPlayer::street_stat_to_str(StreetStat* stats) const{
	string stat_str = "";
	stat_str += " total[" + to_string(stats->played) + "],";
	stat_str += " raise[" + to_string(stats->raise) + "],";
	stat_str += " bet[" + to_string(stats->bet) + "],";
	stat_str += " call[" + to_string(stats->call) + "],";
	stat_str += " check[" + to_string(stats->check) + "],";
	stat_str += " fold[" + to_string(stats->fold) + "]";
	return stat_str;
}

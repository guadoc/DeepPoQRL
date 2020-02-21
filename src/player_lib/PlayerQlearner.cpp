/*
 * PlayerQlearner.cpp
 *
 *  Created on: Jan 11, 2020
 *      Author: Michael Blot
 */

#include <player_lib/PlayerQlearner.h>
#include "matplotlibcpp.h"
#include <toolbox.cpp>
namespace plt = matplotlibcpp;
namespace std {

PlayerQlearner::PlayerQlearner(): PlayerBot() {
	this->is_greedy = false;
	this->is_monitoring_on = false;
}

PlayerQlearner::PlayerQlearner(string id): PlayerBot(id) {
	this->is_greedy = false;
	this->is_monitoring_on = false;
}

PlayerQlearner::PlayerQlearner(AbstractTable* table, unsigned int position): PlayerBot(table,  position) {
	this->is_greedy = false;
	this->is_monitoring_on = false;
}

PlayerQlearner::~PlayerQlearner() {
	// TODO Auto-generated destructor stub
}

void PlayerQlearner::set_monitoring_mode(bool monitoring_mode){
	this->is_monitoring_on = monitoring_mode;
}

void PlayerQlearner::set_greedy_mode(bool greedy_mode){
	this->is_greedy = greedy_mode;
}

AbstractPlayer::Action PlayerQlearner::play_preflop(){
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if(this->commitment < this->table->get_last_raise()){
			return this->call_pot();
		}
		else{
			return this->check_pot();
		}
	}
	else{//there is no raise from another player, choices: BET, check_pot (we remove the folding option: fold_pot)
		return this->check_pot();
	}
}

AbstractPlayer::Action PlayerQlearner::play_flop(){
	return this->check_pot();
}

AbstractPlayer::Action PlayerQlearner::play_turn(){
	return this->check_pot();
}

AbstractPlayer::Action PlayerQlearner::play_river(){
	this->loss = 0;
	vector<float> input_var = this->build_input();
	vector<float> Qvalues = this->compute_Qvalues(input_var);
	AbstractPlayer::Action action = this->select_action_from_Qvalues(Qvalues, AbstractTable::t_river);
	float qvalue = this->credit_action_value(action);
	if(this->is_monitoring_on){
		this->hand_estimated_q_value.push_back(qvalue);
	}
	return action;
}

AbstractPlayer::Action PlayerQlearner::select_action_from_Qvalues(vector<float> Qvalues, AbstractTable::Street street){
	AbstractPlayer::Action action;
	if (this->is_greedy){
		action = this->random_play(Qvalues, street);
	}
	else{
		action = this->optimal_play_from_Qvalues(Qvalues, street);
	}
	return action;
}

AbstractPlayer::Action PlayerQlearner::optimal_play_from_Qvalues(vector<float> Qvalues, AbstractTable::Street street){
	if (this->table->get_last_raise() != 0 ){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if((Qvalues[0] >= Qvalues[1]) && (Qvalues[0] > 0)){
			if (this->table->get_last_raise() < this->stake + this->commitment){
				unsigned int value_raise = std::min(this->table->get_last_raise() +  1*this->table->get_diff_last_raises(),
													this->stake + this->commitment);
				return this->raise_pot(value_raise);
			}
		}
		/*FOR PREFLOP*/
//		if (this->table->get_last_raise() <= this->commitment){
//			return this->check_pot();
//		}
		if(Qvalues[1] >= 0){
			return this->call_pot();
		}
		else{
			return this->fold_pot();
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		if(Qvalues[0] >= Qvalues[1]){
			unsigned int value_bet = std::min(this->stake, (unsigned int)(0.3 * (float)this->table->get_total_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->fold_pot();
}

AbstractPlayer::Action PlayerQlearner::random_play(vector<float> not_used, AbstractTable::Street street){
	if (this->table->get_last_raise() != 0 ){// there is a bet from another player: raise_pot, call_pot or fold_pot
		unsigned int choice = rand() % 7;
		if(choice == 0 or choice == 1 or choice == 2){
			if (this->table->get_last_raise() >= this->stake + this->commitment){
				return this->call_pot();
			}
			else{
				unsigned int value_raise = std::min(this->table->get_last_raise() +  1*this->table->get_diff_last_raises(),
													this->stake + this->commitment
													);
				return this->raise_pot(value_raise);
			}
		}
		else if(choice == 5 or choice == 6 or choice == 4){
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
		if(choice == 0 or choice == 1 or choice == 2 or choice == 3){
			unsigned int value_bet = std::min(this->stake, (unsigned int)(0.3 * (float)this->table->get_total_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->fold_pot();
}
static float sign(float value){
	if(value >= 0){
		return 1.;
	}
	return -1.;
}
static float QError(float estimatedQ, float observedQ){
	return estimatedQ*sign(observedQ);
}

void PlayerQlearner::close_hand(){
	if(this->is_monitoring_on){
		for(auto const & Qvalue : this->hand_estimated_q_value){
			if (Qvalue != this->loss){
				estimated_q_value.push_back(Qvalue);
				observed_q_value.push_back(this->loss);
				observed_q_value_error.push_back(QError(Qvalue, this->loss));
			}
		}
//		this->plot_monitoring();
	}
	this->hand_estimated_q_value.clear();
	PlayerBot::close_hand();
}

void PlayerQlearner::plot_monitoring() const{
	plt::close();
	plt::figure();
	plt::subplot(3, 1, 1);
	vector<float> eqv = {std::begin(this->estimated_q_value), std::end(this->estimated_q_value)};
	plt::named_plot("estimated Q", eqv);
	vector<float> oqv = {std::begin(this->observed_q_value), std::end(this->observed_q_value)};
	plt::named_plot("observed Q", oqv);
	plt::legend();
	plt::subplot(3, 1, 2);
	list<float> avg_list = average_list(this->observed_q_value_error, 200);
	vector<float> Q_error ={std::begin(avg_list), std::end(avg_list)};
	plt::named_plot("Averaged Q Error", Q_error);
//	plt::plot();
//	plt::pause(0.05);
	plt::legend();
//	plt::close();
	plt::show();
}

} /* namespace std */

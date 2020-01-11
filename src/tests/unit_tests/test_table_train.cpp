/*
 * test_table_train.cpp
 *
 *  Created on: Dec 23, 2019
 *      Author: Michael Blot
 */

#include "../../table_lib/TableTrain.h"
#include "../../toolbox.cpp"
//#include "/src/toolbox.cpp"

class PlayerBotTest: public PlayerBot{
	void init_learning_params(){};
	void init_macro_params(){};
	void init_macro_params(std::default_random_engine& generator){};
	void mute_macro_params(){};
	void mute_macro_params(list<AbstractPlayer*> &, std::default_random_engine&){};
	void train(){};
	Action play_loose(){
		if(this->table->get_last_raise() > this->commitment){
			return this->call_pot();
		}
		return this->check_pot();
	}
	Action play_preflop(){return this->play_loose();}
	Action play_flop(){return this->play_loose();}
	Action play_turn(){return this->play_loose();}
	Action play_river(){return this->play_loose();}
};

class test_table_train
{
public:
	test_table_train(){
	}

	int run_tests(){
		cout<<"Running TableTrain unit tests"<<endl;
		this->test_update_state();
		cout<<"----TableTrain unit test finished successfully"<<endl;
		return 0;
	}

	int test_performances(){
		/*
		 *  current is 3:42 for 1000000 hands
		 */
		PlayerBot* player1 = new PlayerBotTest();
		PlayerBot* player2 = new PlayerBotTest();
		PlayerBot* player3 = new PlayerBotTest();
		PlayerBot* player4 = new PlayerBotTest();
		PlayerBot* player5 = new PlayerBotTest();
		PlayerBot* player6 = new PlayerBotTest();
		vector<AbstractPlayer*> players = {player1, player2, player3, player4, player5, player6};
		TableTrain table = TableTrain(players);

		unsigned int n_hand_perf = 1000000;
		clock_t start = clock();
		for (unsigned int i = 0; i < n_hand_perf; i++){
			progress_bar((float)i/n_hand_perf);
			table.play_hand();
		}
		double elapsed = (double)(clock()- start) / CLOCKS_PER_SEC;
		cout<<table.to_str()<<endl;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}

	int test_update_state(){
		this->test_update_state_when_bet();
		this->test_update_state_when_call();
		this->test_update_state_when_check();
		this->test_update_state_when_fold();
		this->test_update_state_when_raise();
		return 0;
	}

	int test_update_state_when_raise(){
		PlayerBot* player1 = new PlayerBotTest();
		vector<AbstractPlayer*> players = {player1};
		TableTrain table = TableTrain(players);
		table.init_state();
		player1->raise_pot(10);
		TableTrain::TableState state = table.get_state();
		assert(state.total_action == 1);
		assert(state.initiative == 1);
		assert(state.interest == 1);

		player1->raise_pot(20);
		state = table.get_state();
		assert(state.total_action == 2);
		assert(state.initiative == 2);
		assert(state.interest == 2);

		table.init_hand();
		state = table.get_state();
		assert(state.total_action == 0);
		assert(state.initiative == 0);
		assert(state.interest == 0);
		return 0;
	}

	int test_update_state_when_bet(){
		PlayerBot* player1 = new PlayerBotTest();
		PlayerBot* player2 = new PlayerBotTest();
		vector<AbstractPlayer*> players = {player1, player2};
		TableTrain table = TableTrain(players);
		table.init_state();
		player1->bet_pot(10);
		TableTrain::TableState state = table.get_state();
		assert(state.total_action == 1);
		assert(state.initiative == 1);
		assert(state.interest == 1);

		player2->raise_pot(20);
		state = table.get_state();
		assert(state.total_action == 2);
		assert(state.initiative == 2);
		assert(state.interest == 2);
		return 0;
	}

	int test_update_state_when_fold(){
		PlayerBot* player1 = new PlayerBotTest();
		PlayerBot* player2 = new PlayerBotTest();
		vector<AbstractPlayer*> players = {player1, player2};
		TableTrain table = TableTrain(players);
		table.init_state();
		player1->bet_pot(10);
		TableTrain::TableState state = table.get_state();
		assert(state.total_action == 1);
		assert(state.initiative == 1);
		assert(state.interest == 1);

		player2->fold_pot();
		state = table.get_state();
		assert(state.total_action == 2);
		assert(state.initiative == 1);
		assert(state.interest == 1);
		return 0;
	}

	int test_update_state_when_check(){
		PlayerBot* player1 = new PlayerBotTest();
		vector<AbstractPlayer*> players = {player1};
		TableTrain table = TableTrain(players);
		table.init_state();
		player1->check_pot();
		TableTrain::TableState state = table.get_state();
		assert(state.total_action == 1);
		assert(state.initiative == 0);
		assert(state.interest == 1);
		return 0;
	}

	int test_update_state_when_call(){
		PlayerBot* player1 = new PlayerBotTest();
		PlayerBot* player2 = new PlayerBotTest();
		vector<AbstractPlayer*> players = {player1, player2};
		TableTrain table = TableTrain(players);
		table.init_state();
		player1->bet_pot(10);
		TableTrain::TableState state = table.get_state();
		assert(state.total_action == 1);
		assert(state.initiative == 1);
		assert(state.interest == 1);

		player2->call_pot();
		state = table.get_state();
		assert(state.total_action == 2);
		assert(state.initiative == 1);
		assert(state.interest == 2);
		return 0;
	}
};



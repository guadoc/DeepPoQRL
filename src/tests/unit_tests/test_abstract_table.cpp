/*
 * test_abstract_table.cpp
 *
 *  Created on: Dec 12, 2019
 *      Author: Michael Blot
 */

#include "../../player_lib/AbstractPlayer.h"
#include "../../player_lib/player_toolbox.cpp"
#include "../../table_lib/AbstractTable.h"

using namespace std;
using Rank = Card::Rank;
using Suit = Card::Suit;

class MockingPlayer: public AbstractPlayer{
public:
	MockingPlayer(vector<AbstractPlayer::Action> actions, AbstractTable *table, unsigned int pos): AbstractPlayer(table, pos){
		this->actions = actions;
		this->n_street = 0;
	}
	AbstractPlayer::Action play_preflop(){return this->play_street();}
	AbstractPlayer::Action play_flop(){return this->play_street();}
	AbstractPlayer::Action play_turn(){return this->play_street();}
	AbstractPlayer::Action play_river(){return this->play_street();}
	AbstractPlayer::Action play_street(){
		switch(this->actions[n_street]){
			case t_raise:
				this->raise_pot(2*this->table->get_pot());
				break;
			case t_bet:
				this->bet_pot(2*this->table->get_pot());
				break;
			case t_check:
				this->check_pot();
				break;
			case t_call:
				this->call_pot();
				break;
			case t_fold:
				this->fold_pot();
				break;
		}
		this->n_street++;
		return this->actions[n_street];
	}
protected:
	unsigned int n_street;
	vector<AbstractPlayer::Action> actions;
};

class test_abstract_table
{
public:
	test_abstract_table(){
	}

	int test_all(){
		cout<<"Running AbstractTable unit tests"<<endl;
		this->test_pot_updates();
		this->test_side_pots();
		this->test_distribute_pot();
		this->test_distribute_pot_with_fold();
		cout<<"----AbstractTable unit test finished successfully"<<endl;
		return 0;
	}

	//TODO test_fill_side_pots
	//TODO test_player_gets_pot
	//TODO test_gather_pots_output
	//TODO test_run_streets

	int test_distribute_pot_with_fold(){
		AbstractPlayer* player1 = new AbstractPlayer();
		AbstractPlayer* player2 = new AbstractPlayer();
		AbstractPlayer* player3 = new AbstractPlayer();
		AbstractPlayer* player4 = new AbstractPlayer();
		vector<AbstractPlayer*> players;
		players.push_back(player1);
		players.push_back(player2);
		players.push_back(player3);
		players.push_back(player4);
		AbstractTable table = AbstractTable(players);

		player1->add_card_to_hand(Card(Rank::_7, Suit::_D));
		player1->add_card_to_hand(Card(Rank::_7, Suit::_S));

		player2->add_card_to_hand(Card(Rank::_9, Suit::_D));
		player2->add_card_to_hand(Card(Rank::_9, Suit::_S));

		player3->add_card_to_hand(Card(Rank::_5, Suit::_D));
		player3->add_card_to_hand(Card(Rank::_5, Suit::_S));

		player4->add_card_to_hand(Card(Rank::_Q, Suit::_D));
		player4->add_card_to_hand(Card(Rank::_Q, Suit::_S));

		table.distribute_card_to_board(Card(Rank::_4, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_8, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_4, Suit::_D));
		table.distribute_card_to_board(Card(Rank::_Q, Suit::_C));
		table.distribute_card_to_board(Card(Rank::_5, Suit::_H));
		player1->set_stake(100);
		player2->set_stake(40);
		player3->set_stake(20);
		player4->set_stake(100);
		player1->raise_pot(30);
		player2->call_pot();
		player3->call_pot();
		player4->call_pot();
		table.gather_pots();
		table.init_raise_historic();
		player1->raise_pot(50);
		player2->call_pot();
		player4->fold_pot();
		table.gather_pots();
		table.distribute_pot_to_best_hands();
		table.distribute_side_pots_to_best_hands();

		assert(player1->get_bank_roll() == 99960);
		assert(player2->get_bank_roll() == 99950);
		assert(player3->get_bank_roll() == 99980);
		assert(player4->get_bank_roll() == 99970);

		return 0;
	}

	int test_distribute_pot(){
		AbstractPlayer* player1 = new AbstractPlayer();
		AbstractPlayer* player2 = new AbstractPlayer();
		AbstractPlayer* player3 = new AbstractPlayer();
		AbstractPlayer* player4 = new AbstractPlayer();
		AbstractPlayer* player5 = new AbstractPlayer();
		AbstractPlayer* player6 = new AbstractPlayer();
		vector<AbstractPlayer*> players;
		players.push_back(player1);
		players.push_back(player2);
		players.push_back(player3);
		players.push_back(player4);
		players.push_back(player5);
		players.push_back(player6);
		AbstractTable table = AbstractTable(players);
		player1->add_card_to_hand(Card(Rank::_9, Suit::_D));
		player1->add_card_to_hand(Card(Rank::_9, Suit::_S));
		player2->add_card_to_hand(Card(Rank::_T, Suit::_D));
		player2->add_card_to_hand(Card(Rank::_T, Suit::_S));

		table.distribute_card_to_board(Card(Rank::_4, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_7, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_4, Suit::_D));
		table.distribute_card_to_board(Card(Rank::_Q, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_5, Suit::_S));
		list<AbstractPlayer*> player_list;
		player_list.push_back(player1);
		player_list.push_back(player2);
		table.distribute_pot_to_best_hands(player_list, 10);
		assert(*player1 < *player2);
		assert(player1->get_bank_roll() == 100000);
		assert(player2->get_bank_roll() == 100010);

		table.clear_board();
		table.init_players_hand();
		player_list.push_back(player3);
		player1->add_card_to_hand(Card(Rank::_9, Suit::_D));
		player1->add_card_to_hand(Card(Rank::_9, Suit::_S));
		player2->add_card_to_hand(Card(Rank::_T, Suit::_D));
		player2->add_card_to_hand(Card(Rank::_T, Suit::_S));
		player3->add_card_to_hand(Card(Rank::_T, Suit::_H));
		player3->add_card_to_hand(Card(Rank::_T, Suit::_C));
		table.distribute_card_to_board(Card(Rank::_4, Suit::_C));
		table.distribute_card_to_board(Card(Rank::_7, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_4, Suit::_D));
		table.distribute_card_to_board(Card(Rank::_Q, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_5, Suit::_S));
		table.distribute_pot_to_best_hands(player_list, 10);
		assert(player1->get_bank_roll() == 100000);
		assert(player2->get_bank_roll() == 100015);
		assert(player3->get_bank_roll() == 100005);

		table.clear_board();
		table.init_players_hand();
		player_list.push_back(player3);
		player1->add_card_to_hand(Card(Rank::_9, Suit::_D));
		player1->add_card_to_hand(Card(Rank::_9, Suit::_S));
		player2->add_card_to_hand(Card(Rank::_T, Suit::_D));
		player2->add_card_to_hand(Card(Rank::_Q, Suit::_S));
		player3->add_card_to_hand(Card(Rank::_J, Suit::_H));
		player3->add_card_to_hand(Card(Rank::_Q, Suit::_C));
		player4->add_card_to_hand(Card(Rank::_3, Suit::_H));
		player4->add_card_to_hand(Card(Rank::_6, Suit::_C));
		table.distribute_card_to_board(Card(Rank::_A, Suit::_C));
		table.distribute_card_to_board(Card(Rank::_7, Suit::_S));
		table.distribute_card_to_board(Card(Rank::_4, Suit::_D));
		table.distribute_card_to_board(Card(Rank::_Q, Suit::_D));
		table.distribute_card_to_board(Card(Rank::_5, Suit::_S));

		player1->raise_pot(100);
		player2->raise_pot(115);
		player3->call_pot();
		player4->call_pot();
		player5->fold_pot();
		player6->fold_pot();
		table.gather_pots();
		table.distribute_pot_to_best_hands();
		table.distribute_side_pots_to_best_hands();

		assert(player1->get_bank_roll() == 99900);
		assert(player2->get_bank_roll() == 99910);
		assert(player3->get_bank_roll() == 99910);
		assert(player4->get_bank_roll() == 100300);
		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}
		return 0;
	}

	int test_pot_updates(){
		AbstractPlayer* player1 = new AbstractPlayer();
		AbstractPlayer* player2 = new AbstractPlayer();
		AbstractPlayer* player3 = new AbstractPlayer();
		AbstractPlayer* player4 = new AbstractPlayer();
		AbstractPlayer* player5 = new AbstractPlayer();
		AbstractPlayer* player6 = new AbstractPlayer();
		vector<AbstractPlayer*> players;
		players.push_back(player1);
		players.push_back(player2);
		players.push_back(player3);
		players.push_back(player4);
		players.push_back(player5);
		players.push_back(player6);
		AbstractTable table = AbstractTable(players);

		table.init_hand();
		table.gather_pots();
		assert(table.get_pot() == 4);
		assert(table.get_total_pot() == 4);
		assert(table.get_side_pots().size() == 0);
		assert(table.get_side_pots_player_list().size() == 0);
		assert(table.get_diff_last_raises() == 2);

		player2->raise_pot(6);
		assert(table.get_total_pot() == 10);
		table.gather_pots();
		assert(table.get_pot() == 10);
		assert(table.get_total_pot() == 10);
		assert(table.get_side_pots().size() == 0);
		assert(table.get_side_pots_player_list().size() == 0);
		assert(table.get_diff_last_raises() == 3);

		player2->raise_pot(9);
		assert(table.get_diff_last_raises() == 3);
		assert(table.get_total_pot() == 19);
		player3->call_pot();
		assert(table.get_total_pot() == 28);
		assert(table.get_pot() == 10);
		table.gather_pots();
		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}

		assert(table.get_pot() == 28);
		assert(table.get_side_pots().size() == 0);
		assert(table.get_side_pots_player_list().size() == 0);
		assert(table.get_diff_last_raises() == 3);

		table.init_raise_historic();
		player2->raise_pot(9);
		assert(table.get_diff_last_raises() == 9);
		assert(table.get_total_pot() == 37);
		player2->raise_pot(19);
		assert(table.get_diff_last_raises() == 10);
		assert(table.get_total_pot() == 47);
		table.gather_pots();
		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}
		assert(table.get_pot() == 47);
		assert(table.get_total_pot() == 47);
		assert(table.get_side_pots().size() == 0);
		assert(table.get_side_pots_player_list().size() == 0);
		assert(table.get_diff_last_raises() == 10);
		table.init_hand();
		assert(table.get_total_pot() == 4);
		player2->raise_pot(6);
		assert(table.get_total_pot() == 9);
		table.gather_pots();
		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}
		assert(table.get_pot() == 9);
		assert(table.get_total_pot() == 9);
		return 0;
	}

	int test_side_pots(){
		AbstractPlayer* player0 = new AbstractPlayer("player0");
		AbstractPlayer* player1 = new AbstractPlayer("player1");
		AbstractPlayer* player2 = new AbstractPlayer("player2");
		AbstractPlayer* player3 = new AbstractPlayer("player3");
		AbstractPlayer* player4 = new AbstractPlayer("player4");
		AbstractPlayer* player5 = new AbstractPlayer("player5");
		vector<AbstractPlayer*> players;
		players.push_back(player0);
		players.push_back(player1);
		players.push_back(player2);
		players.push_back(player3);
		players.push_back(player4);
		players.push_back(player5);
		AbstractTable table = AbstractTable(players);

		table.init_hand();
		player1->add_to_stake(20);
		player2->add_to_stake(20);
		player3->add_to_stake(40);
		player4->add_to_stake(40);
		player5->add_to_stake(60);

		player0->raise_pot(100);
		player1->raise_pot(120);
		player2->call_pot();
		player3->raise_pot(140);
		player4->call_pot();
		player5->call_pot();
		table.gather_pots();
		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}

		list<unsigned int > expected_side_pot = {600, 100, 60};
		assert(table.get_side_pots().size() == 3);
		assert(table.get_side_pots() == expected_side_pot);

		list<list<string>> expected_players_lists = {
				{"player0", "player1", "player2", "player3", "player4", "player5"},
				{"player1", "player2", "player3", "player4", "player5"},
				{"player3", "player4", "player5"}
		};
		assert(are_players_in_lists(table.get_side_pots_player_list(), expected_players_lists));

		player0->init_bank_roll();
		player1->init_bank_roll();
		player2->init_bank_roll();
		player3->init_bank_roll();
		player4->init_bank_roll();
		player5->init_bank_roll();
		table.init_hand();

		player5->add_to_stake(60);

		player0->raise_pot(100);
		player1->call_pot();
		player2->call_pot();
		player3->call_pot();
		player4->call_pot();
		player5->raise_pot(160);
		table.gather_pots();
		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}

		expected_side_pot = {600, 60};
		assert(table.get_side_pots().size() == 2);
		assert(table.get_side_pots() == expected_side_pot);
		expected_players_lists =
		{
			{"player0", "player1", "player2", "player3", "player4", "player5"},
			{"player5"}
		};
		assert(are_players_in_lists(table.get_side_pots_player_list(), expected_players_lists));

		player0->init_bank_roll();
		player1->init_bank_roll();
		player2->init_bank_roll();
		player3->init_bank_roll();
		player4->init_bank_roll();
		player5->init_bank_roll();
		table.init_hand();

		player0->raise_pot(100);
		player1->call_pot();
		player2->call_pot();
		player3->call_pot();
		player4->call_pot();
		player5->call_pot();
		table.gather_pots();

		for (auto &player : players){
			assert(player->get_commitment() == 0);
		}

		expected_side_pot = {600};
		assert(table.get_side_pots().size() == 1);
		assert(table.get_side_pots() == expected_side_pot);
		expected_players_lists =
		{
			{"player0", "player1", "player2", "player3", "player4", "player5"}
		};
		assert(are_players_in_lists(table.get_side_pots_player_list(), expected_players_lists));

		return 0;
	}
};



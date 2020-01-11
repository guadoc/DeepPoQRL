#include "../../player_lib/AbstractPlayer.h"
#include "../../table_lib/AbstractTable.h"

class test_abstract_player
{
public:
	test_abstract_player(){}

	int run_tests(void){
		cout<<"Running AbstractPlayer unit tests"<<endl;
		this->test_init();
		this->test_init_hand();

		/* TEST ACTIONS */
		this->test_action_check();
		this->test_action_bet();
		this->test_action_call();
		this->test_action_fold();
		this->test_action_raise();

		/* TEST SAVE AND LOAD*/
		this->test_save_and_load();
		cout<<"----AbstractPlayer unit test finished successfully"<<endl;
		return 0;
	}

	int test_init(){
		AbstractPlayer player = AbstractPlayer();
		assert(player.get_bank_roll()== 100000);
		assert(player.get_stake()== 100);
		return 0;
	}

	int test_init_hand(){
		AbstractPlayer player = AbstractPlayer();
		player.set_stake(90);
		player.add_to_stake(5);
		assert(player.get_stake() == 95);
		player.set_is_in_hand(false);
		player.init_hand();
		if (player.is_auto_rebuy()){
			assert(player.get_bank_roll() == 99995);
			assert(player.get_stake() == 100);
			assert(player.is_in_hand());
		}
		return 0;
	}

	int test_compare_players(){
		AbstractPlayer player1 = AbstractPlayer();
		AbstractPlayer player2 = AbstractPlayer();
		player1.add_to_stake(10);
		player2.set_stake(99);
		assert(player1 > player2);
		assert(player1 >= player2);
		assert(player2 <= player1);
		assert(player2 < player1);
		assert(player1 == player1);
		return 0;
	}

	int test_save_and_load(){
		AbstractPlayer player = AbstractPlayer("id_test");
		player.add_to_stake(77);
		assert(player.get_stake() == 177);
		string save_folder = player.save_to_folder("./src/tests/unit_test/test_output_folder");

		AbstractPlayer player2 = AbstractPlayer("autre_player");
		player2.load_from_model(save_folder);
		assert(player2.get_id() == "id_test");

		bool has_raised_error = false;
		try{
			player2.load_from_model("./not_existing_folder");
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);
		return 0;
	}

	int test_action_check(){
		AbstractTable* table = new AbstractTable();
		AbstractPlayer player = AbstractPlayer("id_test");
		player.set_table(table, 0);
		player.check_pot();
		assert(player.get_bank_roll()== 100000);
		assert(player.get_stake()== 100);
		assert(player.get_commitment()==0);

		table->update_current_raises(5);
		bool has_raised_error = false;
		try{
			player.check_pot();
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);
		return 0;
	}

	int test_action_bet(){
		AbstractTable* table = new AbstractTable();
		AbstractPlayer player = AbstractPlayer("id_test");
		player.set_table(table, 0);
		player.init_hand();
		unsigned int val_bet = 5;
		player.bet_pot(val_bet);
		assert(player.get_bank_roll()== 100000 - val_bet);
		assert(player.get_stake()== 100 - val_bet);
		assert(player.get_commitment() == val_bet);

		bool has_raised_error = false;
		try{
			player.bet_pot(val_bet);
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);

		has_raised_error = false;
		try{
			player.bet_pot(110);
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);
		return 0;
	}

	int test_action_raise(){
		AbstractTable* table = new AbstractTable();
		AbstractPlayer player = AbstractPlayer("id_test");
		player.set_table(table, 0);
		table->update_current_raises(5);
		table->update_current_raises(10);
		player.init_hand();
		unsigned int val_raise = 16;
		player.raise_pot(val_raise);
		assert(player.get_bank_roll()== 100000 - val_raise);
		assert(player.get_stake()== 100 - val_raise);
		assert(player.get_commitment() == val_raise);

		bool has_raised_error = false;
		try{
			player.raise_pot(val_raise + 1);
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);

		has_raised_error = false;
		try{
			player.raise_pot(120);
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);
		return 0;
	}

	int test_action_fold(){
		AbstractTable* table = new AbstractTable();
		AbstractPlayer player = AbstractPlayer("id_test");
		player.set_table(table, 0);
		table->update_current_raises(5);
		player.init_hand();
		player.fold_pot();
		assert(player.get_bank_roll()== 100000);
		assert(player.get_stake()== 100);
		assert(player.get_commitment() == 0);

		table->init_raise_historic();
		bool has_raised_error = false;
		try{
			player.fold_pot();
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);
		return 0;
	}

	int test_action_call(){
		AbstractTable* table = new AbstractTable();
		AbstractPlayer player = AbstractPlayer("id_test");
		player.set_table(table, 0);
		player.init_hand();
		unsigned int val_raise_1 = 5;
		table->update_current_raises(val_raise_1);
		player.call_pot();
		assert(player.get_bank_roll()== 100000 - val_raise_1);
		assert(player.get_stake()== 100 - val_raise_1);
		assert(player.get_commitment() == val_raise_1);

		unsigned int val_raise_2 = 12;
		table->update_current_raises(val_raise_2);
		player.call_pot();
		assert(player.get_bank_roll()== 100000 - val_raise_2);
		assert(player.get_stake()== 100 - val_raise_2);
		assert(player.get_commitment() == val_raise_2);

		table->update_current_raises(110);
		player.call_pot();
		assert(player.get_bank_roll()== 99900);
		assert(player.get_stake()== 0);
		assert(player.get_commitment() == 100);

		table->init_raise_historic();
		player.init_hand();
		bool has_raised_error = false;
		try{
			player.call_pot();
		}
		catch (const std::invalid_argument& ia) {
			has_raised_error = true;
		}
		assert(has_raised_error);
		return 0;
	}
};


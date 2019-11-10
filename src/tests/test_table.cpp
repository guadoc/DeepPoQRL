

#include "../StdAfx.h"
#include "../deck_lib/Card.h"
#include "../deck_lib/Deck.h"
#include "../player_lib/PlayerBotV1.h"
#include "../player_lib/PlayerBotV2.h"
#include "../player_lib/PlayerBotV21.h"
#include "../player_lib/PlayerGUI.h"
#include "../player_lib/PlayerLogs.h"
#include "../train_lib/Session.h"
#include "../table_lib/TableTrain.h"
#include "../table_lib/TableGUI.h"
#include "../utils/utils.h"

#include "../train_lib/Evolution.h"

#include <torch/torch.h>


using namespace std;

class test_table
{
public:
	test_table(void){

	}

	int test_evolution(){
		Evolution evolution = Evolution();
		evolution.run_evolution();
		return 0;
	}


	int test_train_individual(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=1; position < n_player; position++){
			AbstractPlayer * p = new PlayerBotV1(to_string(position));
			((PlayerBot * )p)->init_train_params();
			((PlayerBot * )p)->set_train_mode(true);
			players.push_back(p);
		}
		AbstractPlayer * p = new PlayerBotV2(to_string(0));
		((PlayerBot * )p)->init_train_params();
//		((PlayerBotV2*)p)->load_from_folder("./bot");
		((PlayerBot * )p)->set_train_mode(false);
		players.push_back(p);

		Evolution evolution = Evolution(players);

		clock_t start = clock();
		evolution.run_selection();
		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;

		//	((PlayerBotV2*)player)->save_to_folder("./bot");
		return 0;
	}


	int test_heritage(){
		AbstractPlayer *p1 = new AbstractPlayer();
		p1->save_to_folder("./bot");
		cout<<"other player"<<endl;
		AbstractPlayer *p2 = new PlayerBotV2();
//		((PlayerBotV2*)p2)->init_train_params();
		((PlayerBotV2*)p2)->init_train_params();
		p2->save_to_folder("./bot");
		return 0;
	}

	int test_player_serialization(){
//		AbstractPlayer player = AbstractPlayer();
//		player.add_to_stake(333);
//		cout<<player.get_stake()<<endl;
//		player.save_to_folder("./");
//
//		AbstractPlayer new_player = AbstractPlayer();
//		new_player.load_from_file("./AbstractPlayer");
//		cout<<new_player.get_stake()<<endl;

		PlayerBotV1 player = PlayerBotV1();
		player.add_to_stake(333);
		player.set_learning_rate(77);
		cout<<player.get_stake()<<endl;
		cout<<player.get_learning_rate()<<endl;
		player.save_to_folder(".");

		PlayerBotV1 new_player = PlayerBotV1();
		new_player.load_from_folder("./PlayerBotV1");
		cout<<new_player.get_stake()<<endl;
		cout<<new_player.get_learning_rate()<<endl;

		return 0;
	}

	int test_torch(){
		float param[] = {1.};
		float input[] = {0.5};

		torch::Tensor tensor_param = torch::from_blob(param, {1}, torch::requires_grad());
		torch::Tensor tensor_input = torch::from_blob(input, {1});

		cout<<"Param "<<tensor_param <<endl;

		vector<torch::Tensor> parameters;
		parameters.push_back(tensor_param);
		torch::optim::SGD optimizer(parameters, /*lr=*/0.01);
		optimizer.zero_grad();

		auto val = torch::sigmoid(tensor_param + tensor_input);
		cout << val[0]<<endl;
//		val.backward(torch::nullopt, /*keep_graph=*/ true, /*create_graph=*/ false);
		cout<<"Grad 1 "<<tensor_param.grad()<<endl;
		optimizer.step();
		cout<<"Grad 2 "<<tensor_param.grad()<<endl;
//		tensor_param = tensor_param - tensor_param.grad();
		cout<<"new param "<<tensor_param<<endl;
		auto val2 = torch::sigmoid(tensor_param + tensor_input);
//		val2.backward(torch::nullopt, /*keep_graph=*/ true, /*create_graph=*/ false);
		cout<<"Grad 3 "<<tensor_param.grad()<<endl;
		return 0;
	}


	int test_graphic_table(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=0; position < n_player; position++){
			AbstractPlayer * p = new PlayerRandom();
			players.push_back(p);
		}
		AbstractTable* table = new TableGUI(players);
		table->display_table(0);
		table->distribute_card_to_board();
		table->display_table(0);
		return 0;

	}


	int test_gui_player(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		for (unsigned int position=0; position < n_player; position++){
			AbstractPlayer * p = new PlayerGUI();
			players.push_back(p);
		}
		TableGUI* table = new TableGUI(players);
		unsigned int n_hands = 1000;
		for (unsigned int i =1; i<= n_hands; i++){
			table->play_hand();
		}
		return 0;
	}


	int test_random_player(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		cout<<"Players init"<<endl;
		for (unsigned int position=0; position < n_player; position++){
			AbstractPlayer * p = new PlayerRandom(to_string(position));
			players.push_back(p);
		}
		cout<<"Players ok"<<endl;
		TableGUI* table = new TableGUI(players);
		cout<<"Go play"<<endl;
		unsigned int n_hands = 10;
		for (unsigned int i =1; i<= n_hands; i++){
			table->play_hand();
		}
		return 0;
	}

	int test_train_table(){
		cout<<"TRAIN SESSION"<<endl;
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		AbstractPlayer * p = new PlayerBotV1(to_string(0), 0.1);
//		AbstractPlayer * p = new PlayerRandom();
		players.push_back(p);
		for (unsigned int position=1; position < n_player; position++){
//			AbstractPlayer * p = new PlayerRandom();
			AbstractPlayer * p = new PlayerBotV1(to_string(position), 0.1);
			players.push_back(p);
		}
		cout<<"Players initialized"<<endl;
		AbstractTable* table = new TableTrain(players);
		unsigned int n_hands = 100000;
		clock_t start = clock();
		for (unsigned int i =1; i<= n_hands; i++){
			utils::progress_bar((float)i/(float)n_hands);
			table->play_hand();
//			if(i%100==0){
//				for (auto player:players){//(unsigned int i = 0; i < n_player; i++){
//					player->get_stats().plot_stats(player->get_id());
//				}
//			}
		}
		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}

	static bool compare_players(AbstractPlayer * const & a, AbstractPlayer * const & b)
	{
	   return *a > *b;
	}

	int test_algo_g(){
		unsigned int n_generation = 20;
		unsigned int n_hand_generation = 5000;
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		std::default_random_engine generator;
		for (unsigned int position=0; position < n_player; position++){
			AbstractPlayer * p = new PlayerBotV1(to_string(position));
//			((PlayerBot*)p)->set_train_mode(true);
//			((PlayerBotV1*)p)->init_params();
			players.push_back(p);
			((PlayerBot*)p)->init_macro_params(generator);
		}
		cout<<"Players initialized"<<endl;
		AbstractTable* table = new TableTrain(players);
		clock_t start = clock();
		list<AbstractPlayer*> winning_players;
		for (unsigned int gen = 1; gen <= n_generation; gen++){
			cout<<"GENERATION "<<gen<<endl;
			cout<<table->to_str()<<endl;
			for (auto &player :players)player->init_bank_roll();

			for (unsigned int i =1; i<= n_hand_generation; i++){
//				utils::progress_bar((float)i/(float)n_hand_generation);
				table->play_hand();
			}
			cout<<table->to_str()<<endl;
			winning_players.clear();
			//Select models (natural selection)
			for (auto &player :players){
				if (player->get_bank_roll() + player->get_stake() > player->get_initial_bank_roll()){
					winning_players.push_back(player);
				}
			}
			for (auto &player :players){
				cout<<"Player "<<player->get_id()<<" Lr: "<<((PlayerBotV1*)player)->get_learning_rate()<<", Rp: "<<((PlayerBotV1*)player)->get_param_reg();
				cout<<"-------->Param lead: "<<((PlayerBotV1*)player)->get_param_lead()<<", param foll: "<< ((PlayerBotV1*)player)->get_param_foll()<<endl;
				if (player->get_bank_roll() + player->get_stake() < player->get_initial_bank_roll()){
					((PlayerBot*)player)->mute_macro_params(winning_players, generator);
					cout<<" mutes"<<endl;
				}
			}
		}

		std::sort(players.begin(), players.end(), compare_players);
		for(auto &player: players){
			cout<<"Player "<<player->get_id();
			cout<<" bankroll "<<player->get_bank_roll() + player->get_stake()<<endl;
		}

		BOOST_SERIALIZATION_ASSUME_ABSTRACT( AbstractPlayer );
		(*players.begin())->save_to_folder(".");

		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}


	int save_n_load_net(){
//		TORCH_MODULE(Net);
		struct Net : torch::nn::Module {
			Net() {
				W = register_parameter("W", torch::randn({1, 1}));
				b = register_parameter("b", -torch::randn(1));
			}
			torch::Tensor forward(torch::Tensor input) {
				return torch::addmm(b, input, W);
			}
			torch::Tensor W, b;
		};
		Net * net = new Net();
		nn::Sequential Net_2(
				*net
//				Net()
		);
	//	Net_2* net = new Net_2();
		float input_tab [] = {0.1};
		auto input = torch::from_blob(input_tab, {1, 1}).clone();
	//	auto input = torch::randn({1, 1});
		auto output = Net_2->forward(input);
		cout<<output<<endl;
		string path = "./net.q";
//		torch::save(Net_2, path);
		cout<<"LOADING"<<endl;
		nn::Sequential net2(
				*net
		);
		torch::load(net2, path);
		auto output_2 = net2->forward(input);
		cout<<output_2<<endl;
		return 0;
	}



	int test_trained_player(){
		unsigned int n_player = 6;
		vector<AbstractPlayer*> players;
		AbstractPlayer * p = new PlayerBotV1(to_string(0), 0.1);
		p->load_from_folder("./4");
		((PlayerBot*)p)->set_train_mode(false);
		players.push_back(p);

		cout<<"Lr: "<<((PlayerBotV1*)p)->get_learning_rate()<<", Rp: "<<((PlayerBotV1*)p)->get_param_reg();
		cout<<"-------->Param lead: "<<((PlayerBotV1*)p)->get_param_lead()<<", param foll: "<< ((PlayerBotV1*)p)->get_param_foll()<<endl;
		cout<<" bankroll "<<p->get_bank_roll() + p->get_stake()<<endl;
		p->init_bank_roll();
		for (unsigned int position=1; position < n_player; position++){
			AbstractPlayer * p = new PlayerBotV1(to_string(position), 0.1);
			((PlayerBot*)p)->set_train_mode(false);
			players.push_back(p);
		}
		cout<<"Players initialized"<<endl;
		AbstractTable* table = new TableTrain(players);
		unsigned int n_hands = 5000;
		clock_t start = clock();
		for (unsigned int i =1; i<= n_hands; i++){
//			utils::progress_bar((float)i/(float)n_hands);
			table->play_hand();
		}
		cout<<table->to_str()<<endl;
		cout<<"Lr: "<<((PlayerBotV1*)p)->get_learning_rate()<<", Rp: "<<((PlayerBotV1*)p)->get_param_reg();

		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;

	}



	int test_save_and_load_player(){
		string filename = "input.txt";
		AbstractPlayer player = AbstractPlayer();
		cout<<player.get_stake()<<endl;
		player.add_to_stake(777);
		cout<<player.get_stake()<<endl;
		player.save_to_folder(filename);
		AbstractPlayer new_player;
//		PlayerBotV1 new_player;
		new_player.load_from_folder(filename);
		cout<<"new player"<<endl;
		cout<<new_player.get_stake()<<endl;
		return 0;
	}

	int test_save_and_load_playerV2(){
		string folder = "./bot";
		AbstractPlayer* player = new PlayerBotV2();
		((PlayerBot *)player)->init_learning_params();
		cout<<player->get_stake()<<endl;
		player->add_to_stake(677);
		cout<<player->get_stake()<<endl;
		((PlayerBotV2 *)player)->save_to_folder(folder);
		cout<<player->get_stake()<<endl;

//		PlayerBotV2 new_player = PlayerBotV2();
//		cout<<new_player.get_stake()<<endl;
//		new_player.load_from_folder(folder);
//		cout<<"new player"<<endl;
//		cout<<new_player.get_stake()<<endl;
		return 0;
	}


	int test_plot(){
		unsigned int n_point = 1000;
		list<int> list;
		for(unsigned int i=0; i<n_point; i++){
			list.push_back(i*i);
		}
		cout<<list.size()<<endl;
		unsigned int max_value= 100;//n_point;
		unsigned int min_value= 0;
		unsigned int n_points_max = 1000;
		utils::plot(list, max_value, min_value, n_points_max);
		return 0;
	}

	int test_complete_average_value(){
		unsigned int n_monte_carlo = 1000;
		Deck deck = Deck();
		list<Card> card_list;
		card_list.push_back(deck.random_card());
		card_list.push_back(deck.random_card());
		card_list.push_back(deck.random_card());
		card_list.push_back(deck.random_card());
		card_list.push_back(deck.random_card());
		Hand hand = Hand(card_list);
		cout<<hand.to_str()<<endl;
		float complete_averaged_value = hand.combinatorial_average_value(7);
		cout<<"complete average "<<complete_averaged_value<<endl;
		float mc_average_value = hand.monte_carlo_average_value(7, n_monte_carlo );
		cout<<"monte carlo average "<<mc_average_value<<endl;
		cout<<hand.to_str()<<endl;
		return 0;
	}

};





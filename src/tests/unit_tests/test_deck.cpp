#include "../../player_lib/AbstractPlayer.h"
#include "../../deck_lib/Card.h"
#include "../../deck_lib/Deck.h"

class test_cards
{
public:
	test_cards(){}

	int run_tests(void){
		cout<<"Running Card unit tests"<<endl;
		this->test_card_to_string();
		cout<<"----Card unit test finished successfully"<<endl;
		return 0;
	}

	int test_card(void){
		cout<<"Test cards"<<endl;
		for( int i = 0; i < 53; i = i + 1 ){
			Card card = Card(i);
		}
		return 0;
	}

	int test_card_to_string(){
		list<string> expected_str = {
				"2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd", "Ad", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc", "Ac", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh", "Ah", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks", "As"
		};
		list<string> list_cards;
		for (unsigned int i=0; i< 52; i++){
			list_cards.push_back(Card(i).to_str());
		}
		bool is_equal = true;
		auto id_it = expected_str.begin();
		for (auto value_str: list_cards){
			is_equal = is_equal and (value_str == *id_it);
			id_it++;
		}
		assert(is_equal);
		return 0;
	}
};


class test_deck
{
public:
	test_deck(){}

	int run_tests(){
		cout<<"Running Deck unit tests"<<endl;
		this->test_init();
		this->test_distributed();
		this->test_shuffle();
		this->test_distribute_all();
		cout<<"----Deck unit test finished successfully"<<endl;
		return 0;
	}

	int test_all(){
		string deck_list_str = "";
		for(unsigned int i=0; i<52; i++){
			deck_list_str += Card(i).to_str();
		}
		assert(deck_list_str =="2d3d4d5d6d7d8d9dTdJdQdKdAd2c3c4c5c6c7c8c9cTcJcQcKcAc2h3h4h5h6h7h8h9hThJhQhKhAh2s3s4s5s6s7s8s9sTsJsQsKsAs");
		return 0;
	}

	int test_init(){
		Deck deck = Deck();
		assert(deck.get_distributed_cards_list().size() == 0);
		vector<bool> distributed_cards = vector<bool>(52, false);
		distributed_cards[12] = true;
		distributed_cards[45] = true;
		distributed_cards[50] = true;
		Deck deck2 = Deck(distributed_cards);
		assert(deck2.get_distributed_cards_list().size() == 3);
		assert(deck2.distributed_cards_to_str() == "Ad, 8s, Ks, ");
		return 0;
	}

	int test_distribute_all(){
		Deck deck = Deck();
		Card card;
		string deck_list_str = "";
		for(unsigned int i = 0; i < 52; i++){
			card = deck.random_card();
			deck_list_str += card.to_str();
		}
		assert(deck.get_distributed_cards_list().size() == 52);
		return 0;
	}

	int test_speed(){
		Deck deck = Deck();
		unsigned int n_sample = 10000000;
		unsigned int n_cards = 16;

		clock_t start= clock();
		for(unsigned int i=0; i < n_sample; i++){
			for(unsigned int i=0; i < n_cards; i++){
				deck.random_card();
			}
			deck.shuffle();
		}
		double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}

	int test_distributed(){
		list<Card> distributed_cards = {
			Card(2),
			Card(8)
		};
		Deck deck = Deck(distributed_cards);
		assert(deck.get_distributed_cards_list().size() == 2);
		assert(deck.distributed_cards_to_str() == "4d, Td, ");
		return 0;
	}

	int test_shuffle(){
		list<Card> distributed_cards = {
			Card(35),
			Card(51)
		};
		Deck deck = Deck(distributed_cards);
		assert(deck.get_distributed_cards_list().size() == 2);
		assert(deck.distributed_cards_to_str() == "Jh, As, ");
		deck.shuffle();
		assert(deck.get_distributed_cards_list().size() == 0);
		assert(deck.distributed_cards_to_str() == "");
		return 0;
	}

};


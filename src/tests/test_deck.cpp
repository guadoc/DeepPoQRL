/*
 * test_deck.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: Michael Blot
 */
#include <unordered_map>

#include "../StdAfx.h"


#include "../deck_lib/Card.h"
#include "../deck_lib/Deck.h"
#include "../deck_lib/Hand.h"

#include "../utils/utils.h"

#include <chrono>
#include <time.h>


#include <boost/version.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <fstream>
#include <iostream>

#include "../deck_lib/HandValueManager.h"

using namespace std;

class test_deck
{
public:
	test_deck(void){

	}

	int test_hand_value_manager(){
		unordered_map<string, float> * map = HandValueManager::fill_value_map_5among7_and_save(".");
		for (auto& it: *map) {
		    cout << "key "<<it.first<<", value "<<it.second<<endl;
		}
		return 0;
	}




	int test_card(void){
		cout<<"Test cards"<<endl;
		for( int i = 0; i < 53; i = i + 1 ){
			Card card = Card(i);
			cout<<card.to_str()<<endl;
		}
		return 0;
	}

	int test_deck_distribute(void){
		Deck deck = Deck();
		cout<<"Test deck distribution"<<endl;
		for(int i=0; i<= 10; i++){
			for(int i=0; i<= 10; i++){
				Card card = deck.random_card();
				cout<<card.to_str()<<endl;
				deck.print_distributed_cards();
			}
			deck.shuffle();
		}
		cout<<"END of test deck distribution"<<endl;
		return 0;
	}


	int test_hand_config_and_eval(){
		list<Card> hand_cards;
		hand_cards.push_back(Card(Card::Rank::_9, Card::Suit::_D));
		hand_cards.push_back(Card(Card::Rank::_5, Card::Suit::_S));
		hand_cards.push_back(Card(Card::Rank::_9, Card::Suit::_C));
		hand_cards.push_back(Card(Card::Rank::_6, Card::Suit::_C));
		hand_cards.push_back(Card(Card::Rank::_9, Card::Suit::_C));
		hand_cards.push_back(Card(Card::Rank::_7, Card::Suit::_S));
		hand_cards.push_back(Card(Card::Rank::_8, Card::Suit::_C));
//		hand_cards.push_back(Card(Card::Rank::_7, Card::Suit::_C));
//		hand_cards.push_back(Card(Card::Rank::_A, Card::Suit::_C));

//		hand_cards.push_back(Card(15));
//		hand_cards.push_back(Card(2));
//		hand_cards.push_back(Card(3));
//		hand_cards.push_back(Card(4));
//		hand_cards.push_back(Card(50));
//		hand_cards.push_back(Card(5));
//		hand_cards.push_back(Card(51));
		Hand hand = Hand(hand_cards);



		cout<< "Hand: "+ hand.to_str()<<endl;
		hand.scan();

		cout<<"********************VALUE************"<<endl;
		cout << "Evaluation :" <<hand.evaluate()<<endl;
//		cout << "Final hand : " << Hand(hand.get_final_hand()).to_str()<<endl;
		return 0;

	}

	int test_hand_comparator(void){
		unsigned int hand_size = 7;
		Deck deck = Deck();
		Hand hand1 = Hand(deck, hand_size);
		Hand hand2 = Hand(deck, hand_size);
		unsigned int val1 = hand1.evaluate();
		unsigned int val2 = hand2.evaluate();
		if (val1 > val2){
			cout<< hand1.to_str() + " > " + hand2.to_str();
		}
		else{
			cout<< hand1.to_str() + " <= " + hand2.to_str();
		}
		return 0;
	}


//	void progress_bar(float percentage){
//		unsigned int N_char_to_print = 100;
//		unsigned int n_done = (unsigned int) N_char_to_print * percentage;
//		unsigned int n_todo = (unsigned int) N_char_to_print * (1 -percentage);
//		string bar = "";
//		for (unsigned int i = 0; i<n_done; i++){
//			bar+="#";
//		}
//		for (unsigned int i = 0; i<n_todo; i++){
//			bar+=".";
//		}
//		cout<<bar<<endl;
//	}



	int test_all_combos(){
		cout<<"Test all combos"<<endl;
		list<Card> hand_card_list;
		int n_hand = 0;
		int n_high_card = 0;
		int n_paire = 0;
		int n_double_paire = 0;
		int n_set = 0;
		int n_full_house = 0;
		int n_square = 0;
		int n_straight = 0;
		int n_flush = 0;
		int n_straight_flush = 0;
		clock_t start = clock();
		for (unsigned int i1 = 0; i1<52; i1++){
			utils::progress_bar((float)i1/(float)52);
			hand_card_list.push_back(Card(i1));
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
				hand_card_list.push_back(Card(i2));
				for (unsigned int i3 = i2 + 1; i3 < 52; i3++){
					hand_card_list.push_back(Card(i3));
					for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
						hand_card_list.push_back(Card(i4));
						for (unsigned int i5 = i4 + 1; i5 < 52; i5++){
							hand_card_list.push_back(Card(i5));

							for (unsigned int i6 = i5 + 1; i6 < 52; i6++){
							hand_card_list.push_back(Card(i6));
							for (unsigned int i7 = i6 + 1; i7 < 52; i7++){
							hand_card_list.push_back(Card(i7));

							n_hand++;
							Hand hand = Hand(hand_card_list);

							hand.scan();
							if(hand.is_flush() and hand.is_straight()){
								if(hand.is_straight_flush()){
									n_straight_flush++;
//									hand.value_straight_flush();
								}
								else if(hand.is_square()){
									n_square++;
//									hand.value_square();
								}
								else if(hand.is_full_house()){
									n_full_house++;
//									hand.value_full_house();
								}
								else{
									n_flush++;
//									hand.value_flush();
								}
							}
							else{
								if(hand.is_square()){
									n_square++;
//									hand.value_square();
								}
								else if(hand.is_full_house()){
									n_full_house++;
//									hand.value_full_house();
								}
								else if(hand.is_flush()){
									n_flush++;
//									hand.value_flush();
								}
								else if(hand.is_straight()){
									n_straight++;
//									hand.value_straight();
								}
								else if(hand.is_set()){
									n_set++;
//									hand.value_set();
								}
								else if(hand.is_double_paire()){
									n_double_paire++;
//									hand.value_double_paire();
								}
								else if(hand.is_paire()){
									n_paire++;
//									hand.value_paire();
								}
								else{
									n_high_card++;
//									hand.value_high_card();
								}
							}
								hand_card_list.pop_back();}
								hand_card_list.pop_back();}
//							cout<<Hand::card_list_to_str(hand_card_list)<<endl;

							hand_card_list.pop_back();
						}
						hand_card_list.pop_back();
					}
					hand_card_list.pop_back();
				}
				hand_card_list.pop_back();
			}
			hand_card_list.pop_back();
		}
//		cout<<"Total hands: "+ to_string(n_hand)<< "    diff : "<< n_hand - 133784560 <<endl;
//		cout<<" nb HAUTEUR : "<<n_high_card<< "    diff : "<< n_high_card - 23294460<<endl;
//		cout<<" nb PAIRE : "<<n_paire<< "    diff : "<<n_paire -  58627800 <<endl;
//		cout<<" nb DOUBLE PAIRE : "<<n_double_paire<< "    diff : "<< n_double_paire - 31433400 <<endl;
//		cout<<" nb BRELAN : "<<n_set<< "    diff : "<<n_set - 6461620 <<endl;
//		cout<<" nb QUINTE : "<<n_straight<< "    diff : "<<n_straight - 6180020  <<endl;
//		cout<<" nb FLUSH : "<<n_flush<< "    diff : "<< n_flush -  4047644<<endl;
//		cout<<" nb FULL : "<<n_full_house<< "    diff : "<<n_full_house - 3473184 <<endl;
//		cout<<" nb CARRE : "<<n_square<< "    diff : "<< n_square - 224848<<endl;
//		cout<<" nb QUINTE FLUSH : "<<n_straight_flush<< "    diff : "<<n_straight_flush -  41584<<endl;

		cout<<"Total hands      : "+ to_string(n_hand)                 << "    diff : " << n_hand - 2598960 <<endl;
		cout<<" nb HAUTEUR      : "<<n_high_card                      << "    diff : "<< n_high_card - 1302540  <<endl;
		cout<<" nb PAIRE        : "<<n_paire                            << "    diff : "<<n_paire -  1098240<<endl;
		cout<<" nb DOUBLE PAIRE : "<<n_double_paire              << "    diff : "<< n_double_paire - 123552 <<endl;
		cout<<" nb BRELAN       : "<<n_set                             << "    diff : "<<n_set - 54912<<endl;
		cout<<" nb QUINTE       : "<<n_straight                        << "    diff : "<<n_straight - 10200<<endl;
		cout<<" nb FLUSH        : "<<n_flush                            << "    diff : "<< n_flush -  5108 <<endl;
		cout<<" nb FULL         : "<<n_full_house                        << "    diff : "<<n_full_house - 3744<<endl;
		cout<<" nb CARRE        : "<<n_square                           << "    diff : "<< n_square - 624<<endl;
		cout<<" nb QUINTE FLUSH : "<<n_straight_flush            << "    diff : "<<n_straight_flush -   40 <<endl;


		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;

	}


	int test_all_hands(){
		cout<<"Test all hands"<<endl;
		Hand hand = Hand();
		unsigned int n_hand = 0;
		for (unsigned int i1 = 0; i1<52; i1++){
			utils::progress_bar((float)i1/(float)52);
			hand.push_back(Card(i1));
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
				hand.push_back(Card(i2));
				for (unsigned int i3 = i2 + 1; i3 < 52; i3++){
					hand.push_back(Card(i3));
					for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
						hand.push_back(Card(i4));
						for (unsigned int i5 = i4 + 1; i5 < 52; i5++){
							hand.push_back(Card(i5));
							n_hand++;
							hand.pop_back();
						}
						hand.pop_back();
					}
					hand.pop_back();
				}
				hand.pop_back();
			}
			hand.pop_back();
		}
		cout<<"Total hands: "+ to_string(n_hand)<<endl;
		return 0;
	}



	int test_MC_hand_value(){
		unsigned int n_total_cards =7;
		unsigned int n_mc_sample = 1000;
		Deck deck = Deck();
		Hand hand = Hand();
		hand.push_back(deck.random_card());
		hand.push_back(deck.random_card());
		cout<<hand.monte_carlo_average_value(n_total_cards, n_mc_sample)<<endl;

		return 0;
	}



	int test_two_cards_monte_carlo(){
		list<Hand> hand_list;
		list<Card> card_list;
		for (unsigned int i1 = 0; i1<52; i1++){
			card_list.push_back(Card(i1));
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
				card_list.push_back(Card(i2));
				Hand * hand = new Hand(card_list);
				hand_list.push_back(*hand);
				card_list.pop_back();
			}
			card_list.clear();
		}

		cout<<"Hand list, size: "<<hand_list.size()<<endl;
		for(auto iter_hand = hand_list.begin(); iter_hand != hand_list.end(); iter_hand++){
			cout<<iter_hand->to_str()<<endl;
		}
		cout<<"Sorted hand list"<<endl;
		hand_list.sort();
		unsigned int i = 0;
		for(auto iter_hand = hand_list.begin(); iter_hand != hand_list.end(); iter_hand++){
			cout<<iter_hand->to_str()<<" top "<<(1326 -i) * 100 /1326<<"%"<<endl;
			i++;
		}
		return 0;
	}




	int test_hash_function(){
		Deck deck = Deck();
		Hand hand = Hand();

		hand.push_back(Card(51));
		hand.push_back(Card(50));
		hand.push_back(Card(49));
		hand.push_back(Card(48));
		hand.push_back(Card(47));
		cout<<"h code :"<<hand.h_function()<<endl;
		cout<<hand.to_str()<<endl;

		std::unordered_map<string, float> * valueMap = new std::unordered_map<string, float>;
		hand.set_map(valueMap);

		clock_t tStart = clock();
		cout<<"value "<<hand.get_value()<<endl;
		clock_t tInter = clock();
		cout<<"Time taken: "<< (double)(tInter - tStart)/CLOCKS_PER_SEC<<endl;
		cout<<"value "<<hand.get_value()<<endl;
		clock_t tEnd = clock();
		cout<<"Time taken: "<< (double)(tEnd - tInter)/CLOCKS_PER_SEC<<endl;
		return 0;
	}





};





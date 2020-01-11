/*
 * HandValueManager.h
 *
 *  Created on: Aug 25, 2019
 *      Author: Michael Blot
 */

#include <boost/version.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <fstream>
#include <iostream>
#include "../StdAfx.h"

#include "../toolbox.cpp"

#include "Card.h"
#include "Hand.h"

using namespace std;

class HandValueManager{

public:
	static unordered_map<string, float> * load_map(string filename){
		unordered_map<string, float> *valueMap;
		ifstream ifs(filename);
		boost::archive::binary_iarchive iarch(ifs);
		iarch >> valueMap;
		return valueMap;
	}

	static void fill_n_save_map(string filename){
		unordered_map<string, float> * map = fill_map_7_cards();
//		unordered_map<string, float> * map = fill_map_5_cards();
		save_map(map, filename);
	}

	static void save_map(unordered_map<string, float> * map, string filename){
		std::ofstream ofs(filename);
		boost::archive::binary_oarchive oa(ofs);
		oa << map;
	}

	static int load_and_use_map(){
		unordered_map<string, float> *map;
		map = load_map("./hand_value_maps/map5cards.p");
		cout<<map->size()<<endl;
		unsigned int max = 0;
		string argmax = "";
		for (auto& it: *map) {
//			cout << "key "<<it.first<<", value "<<it.second<<endl;
			if(it.second > max){
				argmax = it.first;
				max = it.second;
			}
		}
		cout << "key "<<argmax<<", value "<<max<<endl;
		return 0;
	}

	static unordered_map<string, float> * fill_map_5_cards(){
		list<Card> hand_card_list;
		unordered_map<string, float> * map = new unordered_map<string, float>;
		clock_t start = clock();
		unsigned int n_hand = 0;
		for (unsigned int i1 = 0; i1<52; i1++){
			progress_bar((float)i1/(float)52);
			Card card1 = Card(i1);
			hand_card_list.push_back(card1);
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
//				utils::progress_bar((float)i2/(float)52);
				Card card2 = Card(i2);
				hand_card_list.push_back(card2);
				for (unsigned int i3 = i2 + 1; i3 < 52; i3++){
					Card card3 = Card(i3);
					hand_card_list.push_back(card3);
					for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
						Card card4 = Card(i4);
						hand_card_list.push_back(card4);
						for (unsigned int i5 = i4 + 1; i5 < 52; i5++){
							Card card5 = Card(i5);
							hand_card_list.push_back(card5);

							Hand hand = Hand(&hand_card_list);
//							cout<<hand.to_str()<<endl;
//							cout<<hand.h_value()<<endl;
							n_hand++;
							map->emplace(hand.h_value(), hand.evaluate());

							hand_card_list.remove(card5);
						}
						hand_card_list.remove(card4);
					}
					hand_card_list.remove(card3);
				}
				hand_card_list.remove(card2);
			}
			hand_card_list.remove(card1);
		}

		cout<<"Map of size "<<map->size()<<" filled for "<<n_hand<<" hands"<<endl;
		double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return map;
	}

	static unordered_map<string, float> * fill_map_7_cards(){
			list<Card> hand_card_list;
			unordered_map<string, float> * map = new unordered_map<string, float>;
			clock_t start = clock();
			Hand hand = Hand(&hand_card_list);
			unsigned int n_hand = 0;
			for (unsigned int i1 = 0; i1<52; i1++){
				progress_bar((float)i1/(float)52);
				Card card1 = Card(i1);
				hand_card_list.push_back(card1);
				for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
	//				utils::progress_bar((float)i2/(float)52);
					Card card2 = Card(i2);
					hand_card_list.push_back(card2);
					for (unsigned int i3 = i2 + 1; i3 < 52; i3++){
						Card card3 = Card(i3);
						hand_card_list.push_back(card3);
						for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
							Card card4 = Card(i4);
							hand_card_list.push_back(card4);
							for (unsigned int i5 = i4 + 1; i5 < 52; i5++){
								Card card5 = Card(i5);
								hand_card_list.push_back(card5);
								for (unsigned int i6 = i5 + 1; i6 < 52; i6++){
									Card card6 = Card(i6);
									hand_card_list.push_back(card6);
									for (unsigned int i7 = i6 + 1; i7 < 52; i7++){
										Card card7 = Card(i7);
										hand_card_list.push_back(card7);

//										Hand hand = Hand(&hand_card_list);
//										cout<<hand.to_str()<<endl;
			//							cout<<hand.h_value()<<endl;
										n_hand++;
										map->emplace(hand.h_value(), 1222222);//hand.evaluate());
										hand_card_list.remove(card7);
									}
									hand_card_list.remove(card6);
								}
								hand_card_list.remove(card5);
							}
							hand_card_list.remove(card4);
						}
						hand_card_list.remove(card3);
					}
					hand_card_list.remove(card2);
				}
				hand_card_list.remove(card1);
			}

			cout<<"Map of size "<<map->size()<<" filled for "<<n_hand<<" hands"<<endl;
			double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
			cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
			return map;
		}


	static int test_map_performances(){
		list<Card> hand_card_list;
		unordered_map<string, float> *map;
		map = load_map("./hand_value_maps/map5among7cards.p");
		clock_t start = clock();

		for (unsigned int i1 = 0; i1<52; i1++){
			progress_bar((float)i1/(float)52);
			Card card1 = Card(i1);
			hand_card_list.push_back(card1);
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
				Card card2 = Card(i2);
				hand_card_list.push_back(card2);
				for (unsigned int i3 = i2 + 1; i3 < 52; i3++){
					Card card3 = Card(i3);
					hand_card_list.push_back(card3);
					for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
						Card card4 = Card(i4);
						hand_card_list.push_back(card4);
						for (unsigned int i5 = i4 + 1; i5 < 52; i5++){
							Card card5 = Card(i5);
							hand_card_list.push_back(card5);
							Hand hand = Hand(&hand_card_list);
//							unsigned int value = hand.evaluate();
							unsigned int value = map->at(hand.h_value());
//							if(value != map->at(hand.h_value())){
//								cout<<hand.to_str()<<": "<<value<<" - "<<map->at(hand.h_value())<<endl;
//							}
							hand_card_list.remove(card5);
						}
						hand_card_list.remove(card4);
					}
					hand_card_list.remove(card3);
				}
				hand_card_list.remove(card2);
			}
			hand_card_list.remove(card1);
		}
		double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
		cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		return 0;
	}
};


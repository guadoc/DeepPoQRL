/*
 * HandValueManager.h
 *
 *  Created on: Aug 25, 2019
 *      Author: micha
 */

#include <boost/version.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <fstream>
#include <iostream>
#include "../StdAfx.h"
#include "../utils/utils.h"

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


	static void save_map(unordered_map<string, float> * map, string filename){
		std::ofstream ofs(filename);
		boost::archive::binary_oarchive oa(ofs);
		oa << map;
	}

	static bool is_in_list(unsigned int card_id, list<Card> card_list) {
		for (auto card = card_list.begin(); card != card_list.end(); card++) {
			if (card_id == card->get_id()) {
				return true;
			}
		}
		return false;
	}


	static unordered_map<string, float> * fill_value_map_5among7_and_save(string folder){
//		unordered_map<string, float> * map_2among7;
		unordered_map<string, float> * map_5among7;

		unsigned int avg_2 = 0;
		unsigned int n_avg_2;

		unsigned int avg_5 = 0;
		unsigned int n_avg_5;

		list<Card> card_list;

		for (unsigned int i1 = 0; i1 < 52; i1++){
			utils::progress_bar((float)i1/(float)52);
			card_list.push_back(Card(i1));
			for (unsigned int i2 = i1  + 1; i2 < 52; i2++){
				utils::progress_bar((float)i2/(float)52);
				card_list.push_back(Card(i2));

//				avg_2 = 0;
//				n_avg_2 = 0;
				for(unsigned int i3 = i2 + 1; i3 < 52; i3++){
					card_list.push_back(Card(i3));
					for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
						card_list.push_back(Card(i4));
						for(unsigned int i5 = i4 + 1; i5 < 52; i5++){
							card_list.push_back(Card(i5));
							avg_5 = 0;
							n_avg_5 = 0;
							for(unsigned int i6 = 0; i6 < 52; i6++){
								if (!is_in_list(i6, card_list)) {
									card_list.push_back(Card(i6));
									for(unsigned int i7 = i6 + 1; i7 < 52; i7++){
	//									cout<<i7<<endl;
										if (!is_in_list(i7, card_list)) {
											card_list.push_back(Card(i7));

											unsigned int value =  Hand(card_list).evaluate();
		//									cout<<value<<endl;
											/*****************/
											n_avg_2++;
											avg_5 = avg_2*((float)n_avg_2 - 1)/(float)n_avg_2 +  (float)value/ (float)n_avg_2;
											//-----------------
											n_avg_5++;
											avg_5 = avg_5*((float)n_avg_5 - 1)/(float)n_avg_5 +  (float)value/ (float)n_avg_5;
											/*****************/
											card_list.pop_back();
										}
									}
									card_list.pop_back();
								}
							}
//							map_5among7->emplace(Hand(card_list).h_value(), avg_5);
							card_list.pop_back();
						}
						card_list.pop_back();
					}
					card_list.pop_back();
				}
//				map_2among7->emplace(Hand(card_list).h_value(), avg_2);
				card_list.pop_back();
			}
			card_list.pop_back();
		}
		save_map(map_5among7, folder + "/" + "5among7");
		return map_5among7;
	}

//	static void create_and_save_maps(string folder){
//		unordered_map<string, float> * map_5among7 = fill_value_map_5among7();
//		save_map(map_5among7, folder + "/" + "5among7");
//	}


};










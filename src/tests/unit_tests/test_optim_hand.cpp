/*
 * test_hand.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: Michael Blot
 */
#include "../../player_lib/AbstractPlayer.h"
#include "../../deck_lib/Card.h"
#include "../../toolbox.cpp"

using Rank = Card::Rank;
using Suit = Card::Suit;

#include "../../deck_lib/HandTest.h"

class test_optim_hand
{
public:
	bool verbose = false;
	test_optim_hand(bool verbose){this->verbose = verbose;}

	int run_tests(void){
		this->test_hand_init();
		this->test_high();
		this->test_pair();
		this->test_2pairs();
		this->test_set();
		this->test_straight();
		this->test_flush();
		this->test_fullhouse();
		this->test_square();
		this->test_quintflush();
		this->test_all_combos_5_cards();
		return 0;
	}

	int test_hand_init(){
		return 0;
	}


	int test_high(){
		list<Card*> hand_cards = {
			new Card(Rank::_2, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_6, Suit::_D),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_7, Suit::_S),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_high);
		return 0;
	}

	int test_pair(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_6, Suit::_D),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_7, Suit::_S),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_pair);
		return 0;
	}

	int test_set(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_6, Suit::_D),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_9, Suit::_S),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_set);
		return 0;
	}

	int test_2pairs(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_6, Suit::_D),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_5, Suit::_C),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_2pairs);
		return 0;
	}

	int test_straight(){
		list<Card*> hand_cards = {
			new Card(Rank::_3, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_4, Suit::_C),
			new Card(Rank::_6, Suit::_D),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_7, Suit::_S),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_straight);
		return 0;
	}

	int test_flush(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_9, Suit::_S),
			new Card(Rank::_6, Suit::_C),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_7, Suit::_C),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_flush);
		return 0;
	}

	int test_fullhouse(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_6, Suit::_D),
			new Card(Rank::_7, Suit::_C),
			new Card(Rank::_7, Suit::_S),
			new Card(Rank::_9, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_fullhouse);
		return 0;
	}

	int test_square(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_D),
			new Card(Rank::_Q, Suit::_H),
			new Card(Rank::_9, Suit::_C),
			new Card(Rank::_Q, Suit::_D),
			new Card(Rank::_Q, Suit::_C),
			new Card(Rank::_Q, Suit::_S),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_square);
		return 0;
	}

	int test_quintflush(){
		list<Card*> hand_cards = {
			new Card(Rank::_9, Suit::_D),
			new Card(Rank::_5, Suit::_S),
			new Card(Rank::_4, Suit::_S),
			new Card(Rank::_6, Suit::_S),
			new Card(Rank::_8, Suit::_S),
			new Card(Rank::_7, Suit::_S),
			new Card(Rank::_K, Suit::_C)
		};
		HandTest hand = HandTest(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == HandTest::t_quintflush);
		return 0;
	}


	int test_all_combos_5_cards(){
		list<Card*> hand_card_list;
		vector<unsigned int> combos = vector<unsigned int>(10, 0);
		clock_t start = clock();
		for (unsigned int i1 = 0; i1<52; i1++){
			if(verbose){
				progress_bar((float)i1/(float)52);
			}
			Card *card1 = new Card(i1);
			hand_card_list.push_back(card1);
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
				Card *card2 = new Card(i2);
				hand_card_list.push_back(card2);
				for (unsigned int i3 = i2 + 1; i3 < 52; i3++){
					Card *card3 = new Card(i3);
					hand_card_list.push_back(card3);
					for (unsigned int i4 = i3 + 1; i4 < 52; i4++){
						Card *card4 = new Card(i4);
						hand_card_list.push_back(card4);
						for (unsigned int i5 = i4 + 1; i5 < 52; i5++){
							Card *card5 = new Card(i5);
							hand_card_list.push_back(card5);
							/*TREATMENT OF CARD LIST */
							HandTest hand = HandTest(&hand_card_list);
							hand.scan();
							combos[0]++;
							combos[hand.get_category_from_scanned_hand()]++;
							/*END OF TREATMENT OF CARD LIST */
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
		vector<unsigned int> expected_combos = {
			2598960,
			1302540,
			1098240,
			123552,
			54912,
			10200,
			5108,
			3744,
			624,
			40
		};
		if(this->verbose){
			cout<<endl;
			cout<<"Total: "<<combos[0]<<", expected "<<expected_combos[0]<<". Diff["<<expected_combos[0] - combos[0]<<"]"<<endl;
			for (unsigned int i=1; i<10; i++){
				cout<<HandTest::hand_category_to_str(static_cast<HandTest::HandTestCategory>(i))<<": "<<combos[i]<<", expected "<<expected_combos[i]<<". Diff["<<expected_combos[i] - combos[i]<<"]"<<endl;
			}
			double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
			cout << "Duration: " + to_string((int) elapsed/60) +":"+ to_string((int)elapsed%60)<< endl;
		}
		assert(combos[0] == expected_combos[0]);
		for (unsigned int i=1; i<10; i++){
			assert(combos[i] == expected_combos[i]);
		}
		return 0;
	}
};






/*
 * test_hand.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: Michael Blot
 */
#include "../../player_lib/AbstractPlayer.h"
#include "../../deck_lib/Hand.h"
#include "../../deck_lib/Card.h"

#define LEVEL_MIN 0
#define LEVEL_PAIR 1302540
#define LEVEL_2PAIRS 2400780
#define LEVEL_SET 2524332
#define LEVEL_STRAIGHT 2579244
#define LEVEL_FLUSH 2589444
#define LEVEL_FULLHOUSE 2594552
#define LEVEL_SQUARE 2598296
#define LEVEL_QUINTFLUSH 2598920
#define LEVEL_MAX 2598960

using Rank = Card::Rank;
using Suit = Card::Suit;

#include "../../deck_lib/HandTest.h"

class test_hand
{
public:
	bool verbose = false;
	test_hand(bool verbose){this->verbose = verbose;}

	int run_tests(void){
		cout<<"Running Hand unit tests"<<endl;
		this->test_hand_init();
		this->test_adversarial();
		this->test_categories();
		this->test_all_combos_5_cards();
		cout<<"----Hand unit test finished successfully"<<endl;
		return 0;
	}

	//TODO
	int test_hand_init(){
		return 0;
	}

	//TODO
	int test_scan(){
		//Seems to work well so far
		return 0;
	}

	//TODO
	int test_values(){
		return 0;
	}

	int test_add_card(){
		string card_list = "";
		Hand hand = Hand();
		list<Card> cards;
		Card card = Card(47);
		card_list += card.to_str() + " ";
		cards.push_back(card);
		card = Card(32);
		card_list += card.to_str() + " ";
		cards.push_back(card);
		card = Card(12);
		card_list += card.to_str() + " ";
		cards.push_back(card);
		hand.add_cards(cards);
		assert(hand.to_str() == card_list);
		return 0;
	}

	//TODO
	int test_adversarial(){
		list<Card> hand1_cards = {
			Card(Rank::_4, Suit::_D),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_Q, Suit::_S),
			Card(Rank::_T, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		list<Card> hand2_cards = {
			Card(Rank::_4, Suit::_D),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_Q, Suit::_S),
			Card(Rank::_9, Suit::_S),
			Card(Rank::_9, Suit::_D)
		};
		Hand hand1 = Hand(&hand1_cards);
		Hand hand2 = Hand(&hand2_cards);
		assert(hand1.evaluate() > hand2.evaluate());
		return 0;
	}

	int test_categories(){
		this->test_high();
		this->test_pair();
		this->test_2pairs();
		this->test_set();
		this->test_straight();
		this->test_flush();
		this->test_fullhouse();
		this->test_square();
		this->test_quintflush();
		this->test_high_();
		this->test_pair_();
		this->test_2pairs_();
		this->test_set_();
		this->test_straight_();
		this->test_flush_();
		this->test_fullhouse_();
		this->test_square_();
		this->test_quintflush_();
		return 0;
	}

	int test_high(){
		list<Card> cards = {
			Card(Rank::_Q, Suit::_H),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_J, Suit::_C),
			Card(Rank::_2, Suit::_D),
			Card(Rank::_A, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_high,
					LEVEL_MIN,
					LEVEL_PAIR));
		return 0;
	}

	int test_pair(){
		list<Card> cards = {
			Card(Rank::_3, Suit::_H),
			Card(Rank::_J, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_2, Suit::_D),
			Card(Rank::_T, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_pair,
					LEVEL_PAIR,
					LEVEL_2PAIRS));
		return 0;
	}

	int test_2pairs(){
		list<Card> cards = {
			Card(Rank::_4, Suit::_H),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_6, Suit::_C),
			Card(Rank::_A, Suit::_D),
			Card(Rank::_A, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_2pairs,
					LEVEL_2PAIRS,
					LEVEL_SET));
		return 0;
	}

	int test_set(){
		list<Card> cards = {
			Card(Rank::_3, Suit::_H),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_3, Suit::_H),
			Card(Rank::_3, Suit::_C),
			Card(Rank::_2, Suit::_D),
			Card(Rank::_A, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_set,
					LEVEL_SET,
					LEVEL_STRAIGHT));
		return 0;
	}

	int test_straight(){
		list<Card> cards = {
			Card(Rank::_3, Suit::_H),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_2, Suit::_D),
			Card(Rank::_A, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_straight,
					LEVEL_STRAIGHT,
					LEVEL_FLUSH));
		cards = {
			Card(Rank::_J, Suit::_H),
			Card(Rank::_Q, Suit::_S),
			Card(Rank::_K, Suit::_H),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_Q, Suit::_D),
			Card(Rank::_A, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_straight,
					LEVEL_STRAIGHT,
					LEVEL_FLUSH));
		cards = {
			Card(Rank::_7, Suit::_H),
			Card(Rank::_T, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_8, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_A, Suit::_S),
			Card(Rank::_9, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_straight,
					LEVEL_STRAIGHT,
					LEVEL_FLUSH));
		return 0;
	}

	int test_flush(){
		list<Card> cards = {
			Card(Rank::_6, Suit::_S),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_3, Suit::_D),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_2, Suit::_S)
		};
		assert(this->test_hand_cat(
							cards,
							Hand::HandCategory::t_flush,
							LEVEL_FLUSH,
							LEVEL_FULLHOUSE));
		return 0;
	}

	int test_fullhouse(){
		list<Card> cards = {
			Card(Rank::_T, Suit::_H),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_4, Suit::_D),
			Card(Rank::_T, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_fullhouse,
					LEVEL_FULLHOUSE,
					LEVEL_SQUARE));
		cards = {
			Card(Rank::_2, Suit::_H),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_H),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_4, Suit::_D),
			Card(Rank::_T, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
					cards,
					Hand::HandCategory::t_fullhouse,
					LEVEL_FULLHOUSE,
					LEVEL_SQUARE));
		return 0;
	}

	int test_square(){
		list<Card> cards = {
			Card(Rank::_4, Suit::_D),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_4, Suit::_D),
			Card(Rank::_T, Suit::_S),
			Card(Rank::_T, Suit::_D)
		};
		assert(this->test_hand_cat(
							cards,
							Hand::HandCategory::t_square,
							LEVEL_SQUARE,
							LEVEL_QUINTFLUSH));
		return 0;
	}

	int test_quintflush(){
		list<Card> cards = {
			Card(Rank::_4, Suit::_D),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_4, Suit::_D),
			Card(Rank::_6, Suit::_S),
			Card(Rank::_3, Suit::_S)
		};
		assert(this->test_hand_cat(cards, Hand::HandCategory::t_quintflush, LEVEL_QUINTFLUSH, LEVEL_MAX));
		return 0;
	}

	bool test_hand_cat(list<Card> cards, Hand::HandCategory expected_category, unsigned int level_down, unsigned int level_up){
		Hand hand = Hand(&cards);
		hand.scan();
		unsigned int hand_value = hand.evaluate();
		return hand_value < level_up and hand_value >= level_down and hand.get_category_from_scanned_hand() == expected_category;
	}

	int test_high_(){
		list<Card> hand_cards = {
			Card(Rank::_2, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_9, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_high);
		return 0;
	}

	int test_pair_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_9, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_pair);
		return 0;
	}

	int test_set_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_9, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_9, Suit::_S),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_set);
		return 0;
	}

	int test_2pairs_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_9, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_5, Suit::_C),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_2pairs);
		return 0;
	}

	int test_straight_(){
		list<Card> hand_cards = {
			Card(Rank::_3, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_4, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_straight);
		return 0;
	}

	int test_flush_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_C),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_9, Suit::_S),
			Card(Rank::_6, Suit::_C),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_7, Suit::_C),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_flush);
		return 0;
	}

	int test_fullhouse_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_9, Suit::_C),
			Card(Rank::_6, Suit::_D),
			Card(Rank::_7, Suit::_C),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_9, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_fullhouse);
		return 0;
	}

	int test_square_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_D),
			Card(Rank::_Q, Suit::_H),
			Card(Rank::_9, Suit::_C),
			Card(Rank::_Q, Suit::_D),
			Card(Rank::_Q, Suit::_C),
			Card(Rank::_Q, Suit::_S),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_square);
		return 0;
	}

	int test_quintflush_(){
		list<Card> hand_cards = {
			Card(Rank::_9, Suit::_D),
			Card(Rank::_5, Suit::_S),
			Card(Rank::_4, Suit::_S),
			Card(Rank::_6, Suit::_S),
			Card(Rank::_8, Suit::_S),
			Card(Rank::_7, Suit::_S),
			Card(Rank::_K, Suit::_C)
		};
		Hand hand = Hand(&hand_cards);
		hand.scan();
		assert(hand.get_category_from_scanned_hand() == Hand::t_quintflush);
		return 0;
	}

	int test_all_combos_5_cards(){
		list<Card> hand_card_list;
		vector<unsigned int> combos = vector<unsigned int>(10, 0);
		clock_t start = clock();
		for (unsigned int i1 = 0; i1<52; i1++){
			if(verbose){
				utils::progress_bar((float)i1/(float)52);
			}
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
							/*TREATMENT OF CARD LIST */
							Hand hand = Hand(&hand_card_list);
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
				cout<<Hand::hand_category_to_str(static_cast<Hand::HandCategory>(i))<<": "<<combos[i]<<", expected "<<expected_combos[i]<<". Diff["<<expected_combos[i] - combos[i]<<"]"<<endl;
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

	int test_all_combos_7_cards(){
		list<Card> hand_card_list;
		vector<unsigned int> combos = vector<unsigned int>(10, 0);
		clock_t start = clock();
		for (unsigned int i1 = 0; i1<52; i1++){
			if(verbose){
				utils::progress_bar((float)i1/(float)52);
			}
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
							for (unsigned int i6 = i5 + 1; i6 < 52; i6++){
								Card card6 = Card(i6);
								hand_card_list.push_back(card6);
								for (unsigned int i7 = i6 + 1; i7 < 52; i7++){
									Card card7 = Card(i7);
									hand_card_list.push_back(card7);
									/*TREATMENT OF CARD LIST */
									Hand hand = Hand(&hand_card_list);
									hand.scan();
									combos[0]++;
									combos[hand.get_category_from_scanned_hand()]++;
									/*END OF TREATMENT OF CARD LIST */
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
		vector<unsigned int> expected_combos = {
			133784560,
			23294460,
			58627800,
			31433400,
			6461620,
			6180020,
			4047644,
			3473184,
			224848,
			37260 + 4324
		};
		if(this->verbose){
			cout<<endl;
			cout<<"Total: "<<combos[0]<<", expected "<<expected_combos[0]<<". Diff["<<expected_combos[0] - combos[0]<<"]"<<endl;
			for (unsigned int i=1; i<10; i++){
				cout<<Hand::hand_category_to_str(static_cast<Hand::HandCategory>(i))<<": "<<combos[i]<<", expected "<<expected_combos[i]<<". Diff["<<expected_combos[i] - combos[i]<<"]"<<endl;
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


	int test_all_combos_5_cards_TEST(){
		list<Card*> hand_card_list;
		vector<unsigned int> combos = vector<unsigned int>(10, 0);
		clock_t start = clock();
		for (unsigned int i1 = 0; i1<52; i1++){
			if(verbose){
				utils::progress_bar((float)i1/(float)52);
			}
			Card *card1 = new Card(i1);
			hand_card_list.push_back(card1);
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++){
//				utils::progress_bar((float)i2/(float)52);
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
				cout<<Hand::hand_category_to_str(static_cast<Hand::HandCategory>(i))<<": "<<combos[i]<<", expected "<<expected_combos[i]<<". Diff["<<expected_combos[i] - combos[i]<<"]"<<endl;
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







#ifndef PLAYER_LIB_HAND_T_H_
#define PLAYER_LIB_HAND_T_H_

#include "Card.h"
#include "Deck.h"

class HandTest{
public:
	HandTest();
	HandTest(list<Card*> *);
	void set_cards(list<Card*> *);
	void push_back(Card * Ca);
	void pop_back();
	void clear();
	void add_cards(list<Card*>&);
	list<Card*> get_cards() const;
	vector<list<Card*>> get_config() const;
	void init_config();
	void display_config(); // const;
	list<Card*> get_final_hand() const;
	unordered_map<string, float> * get_map();
	void set_map(unordered_map<string, float> *);
//	static string card_list_to_str(const list<Card*> &);
	string to_str() const;
	virtual ~HandTest();

	enum HandTestCategory
	{
		t_high = 1,
		t_pair,
		t_2pairs,
		t_set,
		t_straight,
		t_flush,
		t_fullhouse,
		t_square,
		t_quintflush
	};

	void scan();
	HandTestCategory get_category_from_scanned_hand();
	static string hand_category_to_str(HandTestCategory);
//	unsigned int get_value_from_category_and_scanned_hand(HandTestCategory);

//	bool operator<(HandTest &Ha);

//	unsigned int evaluate();

	bool is_full_house();
	bool is_square();
	bool is_flush();
	bool is_straight();
	bool is_pair();
	bool is_2pairs();
	bool is_high_card();
	bool is_set();
	bool is_straight_flush();

//	unsigned int value_fullhouse();
//	unsigned int value_square();
//	unsigned int value_straight();
//	unsigned int value_high_card();
//	unsigned int value_pair();
//	unsigned int value_2pairs();
//	unsigned int value_set();
//	unsigned int value_flush();
//	unsigned int value_quintflush();


protected:
	list<Card*>* cards;
	vector<list<Card*>> config;
	list<Card*> final_hand;

	float evaluated_average_value;
	bool is_evaluated;
	unsigned int n_cards_eval;
	unsigned int n_monte_carlo_sampling;

	std::unordered_map<string, float> * value_map;


};

#endif /* PLAYER_LIB_HAND_H_ */


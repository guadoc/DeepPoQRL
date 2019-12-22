
#ifndef PLAYER_LIB_HAND_H_
#define PLAYER_LIB_HAND_H_

#include "Card.h"
#include "Deck.h"

class Hand {
public:
	Hand();
	Hand(list<Card> *);
	void set_cards(list<Card> *);
	void push_back(const Card & Ca);
	void pop_back();
	void clear();
	void add_cards(list<Card>&);
	list<Card> get_cards() const;
	vector<list<Card>> get_config() const;
	void init_config();
	void display_config() const;
	list<Card> get_final_hand() const;
	string to_str() const;
	virtual ~Hand();

//	unordered_map<string, float> * get_map() const;
	void set_map(unordered_map<string, float> *);

	enum HandCategory
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
	unsigned int h_function() const;
	string h_value() const;

	float average_value_from_MC(unsigned int total_cards, unsigned int n_samples);
	float average_value_combinatorial(unsigned int total_cards);
	float average_value_from_map(std::unordered_map<string, float> * value_map);
	float get_average_value();

	unsigned int evaluate();
	void scan();
	HandCategory get_category_from_scanned_hand();
	static string hand_category_to_str(HandCategory);
	unsigned int get_value_from_category_and_scanned_hand(HandCategory);


	bool operator<(Hand &Ha);

	bool is_full_house() const ;
	bool is_square() const;
	bool is_flush() const;
	bool is_straight() const;
	bool is_pair() const;
	bool is_2pairs() const;
	bool is_high_card() const;
	bool is_set() const;
	bool is_quintflush();

	unsigned int value_fullhouse() const;
	unsigned int value_square() const;
	unsigned int value_straight() const;
	unsigned int value_high_card() const;
	unsigned int value_pair() const;
	unsigned int value_2pairs() const;
	unsigned int value_set() const;
	unsigned int value_flush() const;
	unsigned int value_quintflush() const;


protected:
	list<Card>* cards;
	vector<list<Card>> config;
	list<Card> final_hand;

	bool is_evaluated;
	unsigned int value;

	bool is_averaged;
	float average_value;

	/* setup for averaged hand value*/
	unsigned int n_total_hand;
	unsigned int n_monte_carlo_sampling;

	std::unordered_map<string, float> * value_map;
};

#endif /* PLAYER_LIB_HAND_H_ */


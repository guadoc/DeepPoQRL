
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

	float average_value_from_MC(unsigned int total_cards, unsigned int n_samples) const;
	float average_value_combinatorial(unsigned int total_cards) const;
	float average_value_from_map(std::unordered_map<string, float> * value_map) const;
	float get_average_value();

	unsigned int evaluate();
	vector<list<Card>> scan() const;
	HandCategory get_category_from_config(vector<list<Card>> &config) const;
	static string category_to_str(HandCategory);
	unsigned int get_value_from_category_and_config(HandCategory, vector<list<Card>> &config) const;


	bool operator<(Hand &Ha);

	bool is_full_house(vector<list<Card>> &config) const ;
	bool is_square(vector<list<Card>> &config) const;
	bool is_flush(vector<list<Card>> &config) const;
	bool is_straight(vector<list<Card>> &config) const;
	bool is_pair(vector<list<Card>> &config) const;
	bool is_2pairs(vector<list<Card>> &config) const;
	bool is_high_card(vector<list<Card>> &config) const;
	bool is_set(vector<list<Card>> &config) const;
	bool is_quintflush(vector<list<Card>> &config) const;

	unsigned int value_fullhouse(vector<list<Card>> &config) const;
	unsigned int value_square(vector<list<Card>> &config) const;
	unsigned int value_straight(vector<list<Card>> &config) const;
	unsigned int value_high_card(vector<list<Card>> &config) const;
	unsigned int value_pair(vector<list<Card>> &config) const;
	unsigned int value_2pairs(vector<list<Card>> &config) const;
	unsigned int value_set(vector<list<Card>> &config) const;
	unsigned int value_flush(vector<list<Card>> &config) const;
	unsigned int value_quintflush(vector<list<Card>> &config) const;


protected:
	list<Card>* cards;
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


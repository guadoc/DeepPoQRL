
#ifndef PLAYER_LIB_HAND_H_
#define PLAYER_LIB_HAND_H_

#include "Card.h"
#include "Deck.h"

class Hand {
public:
	Hand();
	Hand(const list<Card>&);
	Hand(Deck &, unsigned int);
	void set_cards(const list<Card> &);
	void set_map(unordered_map<string, float> *);
	void push_back(const Card & Ca);
	void clear();
	void pop_back();
	list<Card> get_cards() const;
	unordered_map<string, float> * get_map();
	void add_cards(list<Card>&);


	bool operator<(Hand &Ha);

	static string card_list_to_str(const list<Card> &);
	string to_str() const;
	virtual ~Hand();

	vector<list<Card>> get_config() const;
	list<Card> get_final_hand() const;

	void scan();
	unsigned int evaluate();
	float get_value();
	float get_full_hand_average_value_from_map(std::unordered_map<string, float> *);
	float get_full_hand_average_value();
	float monte_carlo_average_value(unsigned int n_total_cards, unsigned int);
	float combinatorial_average_value(unsigned int n_total_cards);

	unsigned int h_function();
	string h_value();

	void init_config();
	void display_config(); // const;

	bool is_full_house();
	bool is_square();
	bool is_flush();
	bool is_straight();
	bool is_paire();
	bool is_double_paire();
	bool is_high_card();
	bool is_set();
	bool is_straight_flush();

	unsigned int value_full_house();
	unsigned int value_square();
	unsigned int value_straight();
	unsigned int value_high_card();
	unsigned int value_paire();
	unsigned int value_double_paire();
	unsigned int value_set();
	unsigned int value_flush();
	unsigned int value_straight_flush();

protected:
	list<Card> cards;
	vector<list<Card>> config;
	list<Card> final_hand;

	float evaluated_average_value;
	bool is_evaluated;
	unsigned int n_cards_eval;
	unsigned int n_monte_carlo_sampling;

	std::unordered_map<string, float> * value_map;

};

#endif /* PLAYER_LIB_HAND_H_ */


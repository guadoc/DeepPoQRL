//
//#ifndef PLAYER_LIB_HAND_H_
//#define PLAYER_LIB_HAND_H_
//
//#include "Card.h"
//#include "Deck.h"
//
//class Hand {
//public:
//	Hand();
//	Hand(const list<Card>&);
//	Hand(Deck &, unsigned int);
//	void set_cards(const list<Card> &);
//	void push_back(const Card & Ca);
//	void clear();
//	void remove_end();
//	list<Card> get_cards() const;
//	void add_cards(list<Card>&);
//
//	bool operator<(Hand &Ha);
//
//	static string card_list_to_str(const list<Card> &);
//	string to_str() const;
//	virtual ~Hand();
//
//	vector<list<Card>> get_config() const;
//	list<Card> get_final_hand() const;
//
//	void scan();
//	unsigned int evaluate();
//	unsigned int get_average_full_hand_value();
//	float monte_carlo_average_value(unsigned int n_total_cards, unsigned int);
//	unsigned int combinatorial_average_value(unsigned int n_total_cards);
//
//	void init_config();
//	void display_config(); // const;
//
//	bool is_full_house();
//	bool is_square();
//	bool is_flush();
//	bool is_straight();
//	bool is_paire();
//	bool is_double_paire();
//	bool is_high_card();
//	bool is_set();
//	bool is_straight_flush();
//
//	unsigned int value_full_house();
//	unsigned int value_square();
//	unsigned int value_straight();
//	unsigned int value_high_card();
//	unsigned int value_paire();
//	unsigned int value_double_paire();
//	unsigned int value_set();
//	unsigned int value_flush();
//	unsigned int value_straight_flush();
//
//protected:
//	list<Card> cards;
//	vector<list<Card>> config;
//	list<Card> final_hand;
//
//	unsigned int evaluated_average_value;
//	bool is_evaluated;
////	unsigned int value;
//	unsigned int n_cards_eval;
//	unsigned int n_monte_carlo_sampling;
//
//};
//
//namespace std {
//
//class Hand_ {
//public:
//	Hand_();
//	virtual ~Hand_();
//};
//
//} /* namespace std */
//#endif /* PLAYER_LIB_HAND_H_ */
//

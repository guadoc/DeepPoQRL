#include "Hand.h"
#include <cmath>

#define ID_STRAIGHT 0
#define ID_SINGLE 1
#define ID_PAIR 2
#define ID_TRIPPLE 3
#define ID_SQUARE 4
#define ID_FLUSH 5

#include "../utils/utils.h"
#include "toolbox.cpp"

Hand::Hand(){
	this->n_total_hand = 7;
	list<Card> empty_list;
	for (unsigned int i = 0; i < 9; i++) {
		this->config.push_back(empty_list);
	}
	this->n_monte_carlo_sampling = 10000;
	this->is_evaluated = false;
	this->is_averaged= false;
	this->average_value = 0;
	this->value = 0;
	this->cards = new list<Card>;

	//TODO
	this->value_map = NULL;
}

Hand::Hand(list<Card> *cards):Hand(){
	this->cards = cards;
}

Hand::~Hand() {
}

void Hand::init_config() {
	for(auto& config_list : this->config){
		config_list.clear();
	}
}

list<Card> Hand::get_cards() const {
	return *this->cards;
}

void Hand::clear() {
	this->cards->clear();
	this->is_evaluated = false;
	this->is_averaged= false;
}

void Hand::set_cards(list<Card> *cards) {
	this->cards = cards;
	this->is_evaluated = false;
	this->is_averaged= false;
}

void Hand::push_back(const Card &card) {
	this->cards->push_back(card);
	this->is_evaluated = false;
	this->is_averaged= false;
}

void Hand::pop_back() {
	this->cards->pop_back();
	this->is_evaluated = false;
	this->is_averaged= false;
}

void Hand::add_cards(list<Card> &cards){
	this->cards->insert(this->cards->end(), cards.begin(), cards.end());
	this->is_evaluated = false;
	this->is_averaged= false;
}

void Hand::set_map(std::unordered_map<string, float> * map){
	this->value_map = map;
}

bool Hand::operator <(Hand& Ha) {
	bool ret = false;
	float val1 = this->get_average_value();
	float val2 = Ha.get_average_value();
	if (val1 < val2) {
		ret = true;
	} else {
		ret = false;
	}
	return ret;
}

string Hand::to_str() const {
	return card_list_to_str(*this->cards);
}

string Hand::h_value() const{
	return str_h_function(this->cards);
}

list<Card> Hand::get_final_hand() const {
	return this->final_hand;
}

float Hand::get_average_value(){
	if(!this->is_averaged){
//		this->average_value = this->average_value_combinatorial(this->n_total_hand);
		this->average_value = this->average_value_from_MC(this->n_total_hand, this->n_monte_carlo_sampling);
//		this->average_value = this->average_value_from_map(map);
		this->is_averaged = true;
	}
	return this->average_value;
}

float Hand::average_value_from_MC(unsigned int n_total_cards, unsigned int n_samples){
	float average_value = 0;
	unsigned int n_card_to_add = n_total_cards - this->cards->size();
	for (unsigned int i = 0; i < n_samples; i++) {
		list<Card> temp_card_list = *this->cards;
		Deck deck = Deck(temp_card_list);
		this->init_config();
		for (unsigned int jj = 0; jj < n_card_to_add; jj++) {
			temp_card_list.push_back(deck.random_card());
		}
		Hand hand = Hand(&temp_card_list);
		unsigned int value = hand.evaluate();
		average_value += (float) value / (float) n_samples;
	}
	return average_value;
}

//TODO to generalize to any number of card
float Hand::average_value_combinatorial(unsigned int total_cards){
	float average_value = 0;
	unsigned int n_hand = 0;
	list<Card> card_list = *this->cards;
	for (unsigned int i1 = 0; i1 < 52; i1++) {
		if (!is_card_in_list(i1, card_list)) {
			Card card1 = Card(i1);
			card_list.push_back(card1);
			for (unsigned int i2 = i1 + 1; i2 < 52; i2++) {
				if (!is_card_in_list(i2, card_list)) {
					Card card2 = Card(i2);
					card_list.push_back(card2);
					n_hand++;
					Hand hand = Hand(&card_list);
					average_value = average_value*((float)n_hand - 1)/(float)n_hand
									+ (float)hand.evaluate() / (float)n_hand;
					card_list.remove(card2);
				}
			}
			card_list.remove(card1);
		}
	}
	return (unsigned int) average_value;
}

float Hand::average_value_from_map(std::unordered_map<string, float> * value_map){
	//get the right map
	//return the value
	return 0;
}

void Hand::scan() {
	this->init_config();
	this->cards->sort();
	list<Card> list_successive;
	list<Card> list_similar;
	list<Card>::iterator card = this->cards->begin();
	while (card != this->cards->end()) {
		list_similar.clear();
		unsigned int rank = card->get_rank();
		list_successive.push_back(*card);
		while (rank == card->get_rank() and card != this->cards->end()) {
			this->config[card->get_suit() -1 + ID_FLUSH].push_back(*card);
			list_similar.push_back(*card);
			card++;
		}
		this->config[list_similar.size()].merge(list_similar);
		if (card->get_rank() != rank + 1 or card == this->cards->end()) {
			if (list_successive.size() >= 5) {
				this->config[ID_STRAIGHT].merge(list_successive);
			} else if (list_successive.size() == 4
					and list_successive.back().get_rank() == Card::Rank::_5
					and this->cards->back().get_rank() == Card::Rank::_A) {
				list_successive.push_front(this->cards->back());
				this->config[ID_STRAIGHT].merge(list_successive);
			}
			list_successive.clear();
		}
	}

}

void Hand::display_config()const { //const {
	cout<<"Straight      : "<<card_list_to_str(this->config[ID_STRAIGHT])<<endl;
	cout<<"Single        : "<<card_list_to_str(this->config[ID_SINGLE])<<endl;
	cout<<"Paired        : "<<card_list_to_str(this->config[ID_PAIR])<<endl;
	cout<<"Tripple       : "<<card_list_to_str(this->config[ID_TRIPPLE])<<endl;
	cout<<"Squared       : "<<card_list_to_str(this->config[ID_SQUARE])<<endl;
	cout<<"Flush 1       : "<<card_list_to_str(this->config[ID_FLUSH])<<endl;
	cout<<"Flush 2       : "<<card_list_to_str(this->config[ID_FLUSH+1])<<endl;
	cout<<"Flush 3       : "<<card_list_to_str(this->config[ID_FLUSH+2])<<endl;
	cout<<"Flush 4       : "<<card_list_to_str(this->config[ID_FLUSH+3])<<endl;
}

unsigned int Hand::evaluate() {
	if(!this->is_evaluated){
		this->scan();
		if (this->is_square()) {
			this->value = this->value_square();
		} else if (this->is_full_house()) {
			this->value = this->value_fullhouse();
		} else if (this->is_flush()) {
			if (this->is_straight()) {//to fasten the execution
				if (this->is_quintflush()) {
					this->value = this->value_quintflush();
					this->is_evaluated = true;
					return this->value;
				}
			}
			this->value = this->value_flush();
		} else if (this->is_straight()) {
			this->value = this->value_straight();
		} else if (this->is_set()) {
			this->value = this->value_set();
		} else if (this->is_2pairs()) {
			this->value = this->value_2pairs();
		} else if (this->is_pair()) {
			this->value = this->value_pair();
		} else {
			this->value = this->value_high_card();
		}
		this->is_evaluated = true;
	}
	return this->value;
}


string Hand::hand_category_to_str(HandCategory category) {
	switch(category){
	case t_high:
		return "high";
	case t_pair:
		return "pair";
	case t_2pairs:
		return "2 pairs";
	case t_set:
		return "set";
	case t_straight:
		return "straight";
	case t_flush:
		return "flush";
	case t_fullhouse:
		return "hull house";
	case t_square:
		return "square";
	case t_quintflush:
		return "quinte flush";
	default:
		return "Error: category does not exist";
	}
}

Hand::HandCategory Hand::get_category_from_scanned_hand() {
	if (this->is_square()) {
		return t_square;
	} else if (this->is_full_house()) {
		return t_fullhouse;
	} else if (this->is_flush()) {
		if (this->is_straight()) {
			if (this->is_quintflush()) {
				return t_quintflush;
			}
		}
		return t_flush;
	} else if (this->is_straight()) {
		return t_straight;
	} else if (this->is_set()) {
		return t_set;
	} else if (this->is_2pairs()) {
		return t_2pairs;
	} else if (this->is_pair()) {
		return t_pair;
	} else {
		return t_high;
	}
}


bool Hand::is_high_card() const {
	return (this->config[ID_SINGLE].size() > 0);
}
bool Hand::is_pair() const {
	return (this->config[ID_PAIR].size() > 0);
}
bool Hand::is_2pairs() const {
	return (this->config[ID_PAIR].size() > 2);
}
bool Hand::is_set() const {
	return (this->config[ID_TRIPPLE].size() > 0);
}
bool Hand::is_straight() const {
	return (this->config[ID_STRAIGHT].size() >= 5);
}
bool Hand::is_flush() const {
	return (this->config[ID_FLUSH].size() >= 5 or this->config[ID_FLUSH+1].size() >= 5
			or this->config[ID_FLUSH+2].size() >= 5 or this->config[ID_FLUSH+3].size() >= 5);
}
bool Hand::is_full_house() const{
	bool full = (this->config[ID_TRIPPLE].size() > 0 and this->config[ID_PAIR].size() > 0);
	full = full or (this->config[ID_TRIPPLE].size() > 3);
	return full;
}
bool Hand::is_square() const {
	return (this->config[ID_SQUARE].size() > 0);
}
bool Hand::is_quintflush() {
	list<Card> list_straight;
	for (unsigned int suit = 0; suit < 4; suit++) {
		if (this->config[suit + ID_FLUSH].size() >= 5){
			//check if there is a straight within the flush
			list<Card>::const_iterator card = this->config[suit + ID_FLUSH].begin();
			unsigned int rank = card->get_rank() - 1;
			while (card != this->config[suit + ID_FLUSH].end()) {
				if (rank + 1 == card->get_rank()) {
					list_straight.push_back(*card);
				}
				else {
					if (list_straight.size() >= 5) {
						this->final_hand.clear();
						this->final_hand = list_straight;
						return true;
					} else if (list_straight.size() == 4
							and list_straight.back().get_rank()
									== Card::Rank::_5
							and this->config[suit + ID_FLUSH].back().get_rank()
									== Card::Rank::_A) {
						this->final_hand.clear();
						this->final_hand = list_straight;
						return true;
					}
					list_straight.clear();
					list_straight.push_back(*card);
				}
				rank = card->get_rank();
				card++;
			}
			if (list_straight.size() >= 5) {
				this->final_hand = list_straight;
				return true;
			}
			list_straight.clear();
		}
	}
	return false;
}

// factorial N
unsigned int facto(unsigned int N) {
	if (N <= 1) {
		return 1;
	} else {
		unsigned int a = 1;
		for (unsigned int i = 1; i <= N; i++) {
			a *= i;
		}
		return a;
	}
}

//compute k among n
unsigned int C_nk(unsigned int n, unsigned int k) {
	if (k > n) {
		return 0;
	} else {
		double a = (double) facto(n) / (double) (facto(n - k) * facto(k));
		return (unsigned int) a;
	}
}

unsigned int Hand::get_value_from_category_and_scanned_hand(Hand::HandCategory category){
	switch(category){
		case t_high:
			return this->value_high_card();
		case t_pair:
			return this->value_pair();
		case t_2pairs:
			return this->value_2pairs();
		case t_set:
			return this->value_set();
		case t_straight:
			return this->value_straight();
		case t_flush:
			return this->value_flush();
		case t_fullhouse:
			return this->value_fullhouse();
		case t_square:
			return this->value_square();
		case t_quintflush:
			return this->value_quintflush();
		default:
			return -1;
		}
}

unsigned int Hand::value_high_card() const {
	unsigned int n_base = 0;
	list<Card>::const_iterator card_iter = this->config[ID_SINGLE].end();
	for (unsigned int i = 0; i < 5; i++) {
		card_iter--;
//		this->final_hand.push_back(*card_iter);
		n_base += C_nk(card_iter->get_rank() - 1, 5 - i) * 1020;
		;
	}
	n_base = n_base - (this->config[ID_SINGLE].back().get_rank() - 5) * 1020; //subtility if biggest card is As
	return n_base;
}

unsigned int Hand::value_pair() const {
	unsigned int n_base = 1302540;
	unsigned int rank_paire = this->config[ID_PAIR].back().get_rank();
//	this->final_hand = *this->config[2];
	n_base += (rank_paire - 1) * 84480; // = (rank_paire - 1)* C_nk(4, 2) * C_nk(12, 3) * (4*4*4);
	list<Card>::const_iterator card_iter = this->config[ID_SINGLE].end();
	for (unsigned int i = 0; i < 3; i++) {
		card_iter--;
		n_base += C_nk(card_iter->get_rank() - 1, 3 - i) * pow(4, 3 - i);
		//		this->final_hand.push_back(*card_iter);
	}
	return n_base;
}

unsigned int Hand::value_2pairs() const {
	unsigned int n_base = 2400780; // =1302540 + 1098240;
	list<Card>::const_iterator iter_paire = this->config[ID_PAIR].end();

	iter_paire--;
//	this->final_hand.push_back(*iter_paire);
	iter_paire--;
//	this->final_hand.push_back(*iter_paire);
	iter_paire--;
//	this->final_hand.push_back(*iter_paire);
	iter_paire--;
//	this->final_hand.push_back(*iter_paire);
	unsigned int val_smallpaire = iter_paire->get_rank();
	unsigned int val_bigpaire = this->config[ID_PAIR].back().get_rank(); //bigger paire
	unsigned int val_simple_card = this->config[ID_SINGLE].back().get_rank();
//	this->final_hand.push_back(this->config[1].back());

	n_base += C_nk(val_bigpaire - 1, 2) * 1584; // = C_nk(val_bigpaire - 1, 2) * C_nk(4, 2) * C_nk(4, 2) * (13 -2)*4
	n_base += (val_smallpaire - 1) * 264; // = (val_smallpaire - 1) * C_nk(4,2) * (13 -2)*4

	if (val_simple_card > val_bigpaire) {
		n_base += (val_simple_card - 3) * 4;
	} else if (val_simple_card < val_smallpaire) {
		n_base += (val_simple_card - 1) * 4;
	} else {
		n_base += (val_simple_card - 3) * 4;
	}
	return n_base;
}

unsigned int Hand::value_set() const {
	unsigned int n_base = 2524332; //=1302540 + 1098240 + 123552;
	unsigned int val_triple = this->config[ID_TRIPPLE].back().get_rank();

	list<Card>::const_iterator iter_simple = this->config[ID_SINGLE].end();
	iter_simple--;
	unsigned int val_big_simple_card = iter_simple->get_rank();
	//	this->final_hand.push_back(*iter_simple);

	iter_simple--;
	unsigned int val_small_simple_card = iter_simple->get_rank();
	//	this->final_hand.push_back(*iter_simple);

	n_base += (val_triple - 1) * 4224; // = (val_triple -1)* C_nk(4, 3)*C_nk(12, 2)*4*4
	n_base += C_nk(val_big_simple_card - 1, 2) * 16;
	n_base += (val_small_simple_card - 1) * 4;
	return n_base;
}

unsigned int Hand::value_straight() const {
	unsigned int n_base = 2579244; // = 1302540 + 1098240 + 123552 + 54912;
	unsigned int val_high = this->config[ID_STRAIGHT].back().get_rank();
	n_base += (val_high - 4) * 1020;
//	list<Card>::iterator iter_straight = this->config[0].end();
//	for (unsigned int i= 0; i<5;i++){
//		iter_straight--;
//		this->final_hand.push_back(*iter_straight);
//	}
	return n_base;
}

unsigned int Hand::value_flush()const {
	unsigned int n_base = 2589444; //=1302540 + 1098240 + 123552 + 54912 + 10200;
	for (unsigned int i = 0; i < 4; i++) {
		if (this->config[i + ID_FLUSH].size() >= 5) {
			list<Card>::const_iterator iter_suit = this->config[ID_FLUSH + i].end();
			for (unsigned int j = 0; j < 5; j++) {
				iter_suit--;
				n_base += 4 * C_nk(iter_suit->get_rank() - 1, 5 - j);
//				this->final_hand.push_back(*iter_suit);
			}
			n_base -= (this->config[ID_FLUSH + i].back().get_rank() - 5) * 4; //subtility if biggest card is As
		}
	}
	return n_base;
}

unsigned int Hand::value_fullhouse() const {
	unsigned int n_base = 2594552; // = 1302540 + 1098240 + 123552 + 54912 + 10200 + 5108;
	unsigned int val_triple = this->config[ID_TRIPPLE].back().get_rank();
	list<Card>::const_iterator iter_triple = this->config[ID_TRIPPLE].end();
	iter_triple--;
//	this->final_hand.push_back(*iter_triple);
	iter_triple--;
//	this->final_hand.push_back(*iter_triple);
	iter_triple--;
//	this->final_hand.push_back(*iter_triple);

	unsigned int val_double;
	if (this->config[ID_TRIPPLE].size() >= 6) {
		iter_triple--;
//		this->final_hand.push_back(*iter_triple);
//		iter_triple--;
//		this->final_hand.push_back(*iter_triple);
		val_double = iter_triple->get_rank();
	} else {
//		list<Card>::iterator iter_paire = this->config[2]->end();
//		iter_paire--;
//		this->final_hand.push_back(*iter_paire);
//		iter_paire--;
//		this->final_hand.push_back(*iter_paire);
		val_double = this->config[ID_PAIR].back().get_rank();
	}

	n_base += (val_triple - 1) * 288;
	if (val_double > val_triple) {
		n_base += (val_double - 2) * 6;
	} else {
		n_base += (val_double - 1) * 6;
	}
	return n_base;
}

unsigned int Hand::value_square() const {
	unsigned int n_base = 2598296; //=1302540 + 1098240 + 123552 + 54912 + 10200 + 5108 + 3744;

	unsigned int val_square = this->config[ID_SQUARE].back().get_rank();
	unsigned int val_single_card;
	if (this->config[ID_TRIPPLE].size() > 0) {
		val_single_card = this->config[3].back().get_rank();
//		this->final_hand.push_back(this->config[3].back());
	} else if (this->config[ID_PAIR].size() > 0) {
		if ((this->config[ID_SINGLE].size() > 0)) {
			if (this->config[ID_SINGLE].back().get_rank()
					> this->config[ID_PAIR].back().get_rank()) {
				val_single_card = this->config[ID_SINGLE].back().get_rank();
//				this->final_hand.push_back(this->config[1].back());
			} else {
				val_single_card = this->config[ID_PAIR].back().get_rank();
//				this->final_hand.push_back(this->config[2]->back());
			}
		} else {
			val_single_card = this->config[ID_PAIR].back().get_rank();
//			this->final_hand.push_back(this->config[2]->back());
		}
	} else {
		val_single_card = this->config[ID_SINGLE].back().get_rank();
//		this->final_hand.push_back(this->config[1].back());
	}

	n_base += (val_square - 1) * 48;
	if (val_square > val_single_card) {
		n_base += (val_single_card - 1) * 4;
	} else {
		n_base += (val_single_card - 2) * 4;
	}
	return n_base;
}

unsigned int Hand::value_quintflush() const {
	unsigned int n_base = 2598920; //=1302540 + 1098240 + 123552 + 54912 + 10200 + 5108 + 3744 + 624;
	unsigned int val_high = this->final_hand.back().get_rank();
	n_base += (val_high - 4) * 4;
	return n_base;
}

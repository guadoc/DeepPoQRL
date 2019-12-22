#include "HandTest.h"
#include <cmath>

#include "../utils/utils.h"
#include "toolbox.cpp"

HandTest::HandTest(){
	this->n_cards_eval = 7;
	list<Card*> empty_list;
	for (unsigned int i = 0; i < 10; i++) {
		this->config.push_back(empty_list);
	}
	this->n_monte_carlo_sampling = 1000;
	this->is_evaluated = false;
	this->evaluated_average_value = 0;
	this->value_map = NULL;
}

HandTest::HandTest(list<Card*> *cards):HandTest(){
	this->cards = cards;
}

HandTest::~HandTest() {
}

void HandTest::init_config() {
	for(auto& config_list : this->config){
		config_list.clear();
	}
}

list<Card*> HandTest::get_cards() const {
	return *this->cards;
}

void HandTest::clear() {
	this->cards->clear();
	this->is_evaluated = false;
}

void HandTest::set_cards(list<Card*> *cards) {
	this->cards = cards;
	this->is_evaluated = false;
}

void HandTest::push_back(Card *card) {
	this->cards->push_back(card);
	this->is_evaluated = false;
}

void HandTest::pop_back() {
	this->is_evaluated = false;
	this->cards->pop_back();
}

void HandTest::add_cards(list<Card*> &cards) {
	this->cards->insert(this->cards->end(), cards.begin(), cards.end());
	this->is_evaluated = false;
}

void HandTest::set_map(std::unordered_map<string, float> * map){
	this->value_map = map;
}

//bool HandTest::operator <(HandTest& Ha) {
//	bool ret = false;
//	float val1 = this->get_full_hand_average_value();
//	float val2 = Ha.get_full_hand_average_value();
//	if (val1 < val2) {
//		ret = true;
//	} else {
//		ret = false;
//	}
//	return ret;
//}

//string HandTest::card_list_to_str(const list<Card*> &card_list) {
//	list<Card*>::const_iterator j;
//	string hand_str = "";
//	for (j = card_list.begin(); j != card_list.end(); j++) {
//		hand_str += (*j)->to_str() + " ";
//	}
//	return hand_str;
//}

string HandTest::to_str() const {
	return "TODO";//card_list_to_str(*this->cards);
}

list<Card*> HandTest::get_final_hand() const {
	return this->final_hand;
}


//bool is_card_in_list(unsigned int card_id, list<Card> card_list) {
//	for (auto card = card_list.begin(); card != card_list.end(); card++) {
//		if (card_id == card->get_id()) {
//			return true;
//		}
//	}
//	return false;
//}

bool PComp(Card * a, Card * b)
{
   return *a < *b;
}

void HandTest::scan() {
	this->init_config();
	this->cards->sort(PComp);
	list<Card*> list_successive;
	list<Card*> list_similar;
	list<Card*>::iterator card_it = this->cards->begin();
	Card card = **card_it;
	while (card_it != this->cards->end()){
		list_similar.clear();
		unsigned int rank = card.get_rank();
		list_successive.push_back(*card_it);
		while (rank == card.get_rank() and card_it != this->cards->end()) {
			this->config[card.get_suit() + 5].push_back(*card_it);
			list_similar.push_back(*card_it);
			card_it++;
			if(card_it != this->cards->end()){
				card = **(card_it);
			}
		}
		this->config[list_similar.size()].merge(list_similar);
		if (card.get_rank() != rank + 1 or card_it == this->cards->end()) {
			if (list_successive.size() >= 5) {
				this->config[0].merge(list_successive);
			} else if (list_successive.size() == 4
					and (*(list_successive.back())).get_rank() == Card::Rank::_5
					and (*(this->cards->back())).get_rank() == Card::Rank::_A) {
				list_successive.push_front(this->cards->back());
				this->config[0].merge(list_successive);
			}
			list_successive.clear();
		}
	}
}

void HandTest::display_config() { //const {
	cout<<"Straight      : "<<HandTest(&this->config[0]).to_str()<<endl;
	cout<<"Single        : "<<HandTest(&this->config[1]).to_str()<<endl;
	cout<<"Paired        : "<<HandTest(&this->config[2]).to_str()<<endl;
	cout<<"Double Paired : "<<HandTest(&this->config[3]).to_str()<<endl;
	cout<<"Tripple       : "<<HandTest(&this->config[4]).to_str()<<endl;
	cout<<"Squared       : "<<HandTest(&this->config[5]).to_str()<<endl;
	cout<<"Flush 1       : "<<HandTest(&this->config[6]).to_str()<<endl;
	cout<<"Flush 2       : "<<HandTest(&this->config[7]).to_str()<<endl;
	cout<<"Flush 3       : "<<HandTest(&this->config[8]).to_str()<<endl;
	cout<<"Flush 4       : "<<HandTest(&this->config[9]).to_str()<<endl;
}

//unsigned int HandTest::evaluate() {
//	this->scan();
//	if (this->is_square()) {
//		this->evaluated_average_value = this->value_square();
//	} else if (this->is_full_house()) {
//		this->evaluated_average_value = this->value_fullhouse();
//	} else if (this->is_flush()) {
//		if (this->is_straight()) {
//			if (this->is_straight_flush()) {
//				this->evaluated_average_value = this->value_quintflush();
//			}
//		}
//		this->evaluated_average_value = this->value_flush();
//	} else if (this->is_straight()) {
//		this->evaluated_average_value = this->value_straight();
//	} else if (this->is_set()) {
//		this->evaluated_average_value = this->value_set();
//	} else if (this->is_2pairs()) {
//		this->evaluated_average_value = this->value_2pairs();
//	} else if (this->is_pair()) {
//		this->evaluated_average_value = this->value_pair();
//	} else {
//		this->evaluated_average_value = this->value_high_card();
//	}
//	this->is_evaluated = true;
//	return this->evaluated_average_value;
//}


string HandTest::hand_category_to_str(HandTestCategory category){
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

HandTest::HandTestCategory HandTest::get_category_from_scanned_hand() {
	if (this->is_square()) {
		return t_square;
	} else if (this->is_full_house()) {
		return t_fullhouse;
	} else if (this->is_flush()) {
		if (this->is_straight()) {
			if (this->is_straight_flush()) {
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


bool HandTest::is_high_card() {
	return (this->config[1].size() > 0);
}
bool HandTest::is_pair() {
	return (this->config[2].size() > 0);
}
bool HandTest::is_2pairs() {
	return (this->config[2].size() > 2);
}
bool HandTest::is_set() {
	return (this->config[3].size() > 0);
}
bool HandTest::is_straight() {
	return (this->config[0].size() >= 5);
}
bool HandTest::is_flush() {
	return (this->config[6].size() >= 5 or this->config[7].size() >= 5
			or this->config[8].size() >= 5 or this->config[9].size() >= 5);
}
bool HandTest::is_full_house() {
	bool full = (this->config[3].size() > 0 and this->config[2].size() > 0);
	full = full or (this->config[3].size() > 3);
	return full;
}
bool HandTest::is_square() {
	return (this->config[4].size() > 0);
}

bool HandTest::is_straight_flush() {
	list<Card*> list_straight;
	for (unsigned int suit = 1; suit <= 4; suit++) {
		if (this->config[suit + 5].size() >= 5) {
			//check if there is a straight within the flush
			list<Card*>::iterator card = this->config[suit + 5].begin();
			unsigned int rank = (*card)->get_rank() - 1;
			while (card != this->config[suit + 5].end()) {
				if (rank + 1 == (*card)->get_rank()) {
					list_straight.push_back(*card);
				} else {
					if (list_straight.size() >= 5) {
						this->final_hand = list_straight;
						return true;
					} else if (list_straight.size() == 4
							and (*(list_straight.back())).get_rank()
									== Card::Rank::_5
							and (*(this->config[suit + 5].back())).get_rank()
									== Card::Rank::_A) {
						this->final_hand = list_straight;
						return true;
					}
					list_straight.clear();
					list_straight.push_back(*card);
				}
				rank = (*card)->get_rank();
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
//unsigned int facto(unsigned int N) {
//	if (N <= 1) {
//		return 1;
//	} else {
//		unsigned int a = 1;
//		for (unsigned int i = 1; i <= N; i++) {
//			a *= i;
//		}
//		return a;
//	}
//}
//
////compute k among n
//unsigned int C_nk(unsigned int n, unsigned int k) {
//	if (k > n) {
//		return 0;
//	} else {
//		double a = (double) facto(n) / (double) (facto(n - k) * facto(k));
//		return (unsigned int) a;
//	}
//}
//
//unsigned int HandTest::get_value_from_category_and_scanned_hand(HandTest::HandTestCategory category){
//	switch(category){
//		case t_high:
//			return this->value_high_card();
//		case t_pair:
//			return this->value_pair();
//		case t_2pairs:
//			return this->value_2pairs();
//		case t_set:
//			return this->value_set();
//		case t_straight:
//			return this->value_straight();
//		case t_flush:
//			return this->value_flush();
//		case t_fullhouse:
//			return this->value_fullhouse();
//		case t_square:
//			return this->value_square();
//		case t_quintflush:
//			return this->value_quintflush();
//		default:
//			return -1;
//		}
//}

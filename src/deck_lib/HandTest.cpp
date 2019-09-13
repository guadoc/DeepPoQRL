//#include "Hand.h"
//
//Hand::Hand() {
//	this->is_evaluated = false;
//	this->evaluated_average_value = 0;
//	this->n_cards_eval = 7;
//	this->n_monte_carlo_sampling = 1000;
//	for (unsigned int i = 0; i < 10; i++) {
////		this->config.push_back(new list<Card>);
////		this->config[i].clear();
//	}
//}
//
//Hand::Hand(const list<Card> &cards) :
//		Hand() {
//	this->cards = cards;
//}
//
//Hand::Hand(Deck & deck, unsigned int hand_size) :
//		Hand() {
//	for (unsigned int i = 0; i < hand_size; i++) {
//		this->cards.push_back(deck.random_card());
//	}
//}
//
//Hand::~Hand() {
//	for (unsigned int i = 0; i < 10; i++) {
////		delete this->config[i];
//	}
//}
//
//void Hand::init_config() {
//	for (unsigned int i = 0; i < 10; i++) {
////		if(this->config[i] == NULL){
////			cout<<"null"<<endl;
//////			this->config[i] = new list<Card>;
////		}
////		else{
////			cout<<"exists"<<endl;
////			this->config[i]->clear();
////		}
////		this->config[i].clear();
//	}
//}
//
//list<Card> Hand::get_cards() const {
//	return this->cards;
//}
//
//void Hand::clear() {
//	this->cards.clear();
//	this->is_evaluated = false;
//}
//
//void Hand::set_cards(const list<Card> &cards) {
//	this->cards = cards;
//	this->is_evaluated = false;
////	this->init_config();
//}
//
//void Hand::push_back(const Card &card) {
//	this->cards.push_back(card);
//	this->is_evaluated = false;
////	this->init_config();
//}
//
//void Hand::remove_end() {
//	return this->cards.pop_back();
//	this->is_evaluated = false;
////	this->init_config();
//}
//
//void Hand::add_cards(list<Card> &cards) {
//	this->cards.insert(this->cards.end(), cards.begin(), cards.end());
//	this->is_evaluated = false;
////	this->init_config();
//}
//
//bool Hand::operator <(Hand& Ha) {
//	bool ret = false;
//	float val1 = this->get_average_full_hand_value();
//	float val2 = Ha.get_average_full_hand_value();
//	if (val1 < val2) {
//		ret = true;
//	} else {
//		ret = false;
//	}
//	return ret;
//}
//
//string Hand::card_list_to_str(const list<Card> &card_list) {
//	list<Card>::const_iterator j;
//	string hand_str = "";
//	for (j = card_list.begin(); j != card_list.end(); j++) {
//		hand_str += j->to_str() + " ";
//	}
//	return hand_str;
//}
//
//string Hand::to_str() const {
//	return this->card_list_to_str(this->cards);
//}
//
//vector<list<Card>> Hand::get_config() const {
//	return this->config;
//}
//
//list<Card> Hand::get_final_hand() const {
//	return this->final_hand;
//}
//
//unsigned int Hand::get_average_full_hand_value() {
//	if (!this->is_evaluated) {
//		if (this->cards.size() < this->n_cards_eval) {
//			this->evaluated_average_value =
////							this->monte_carlo_average_value(
////													this->n_cards_eval,
////													this->n_monte_carlo_sampling
////													);
//					this->combinatorial_average_value(this->n_cards_eval);
//		} else {
//			this->evaluated_average_value = this->evaluate();
//		}
//		this->is_evaluated = true;
//	}
//	return this->evaluated_average_value;
//}
//
//bool is_in_list(unsigned int card_id, list<Card> card_list) {
//	for (auto card = card_list.begin(); card != card_list.end(); card++) {
//		if (card_id == card->get_id()) {
//			return true;
//		}
//	}
//	return false;
//}
//
//unsigned int Hand::combinatorial_average_value(unsigned int n_total_cards) {
//	float average_value = 0;
//	unsigned int n_hand = 0;
//	list<Card> card_list = this->cards;
//	for (unsigned int i1 = 0; i1 < 52; i1++) {
//		if (!is_in_list(i1, card_list)) {
//			card_list.push_back(Card(i1));
//			for (unsigned int i2 = i1 + 1; i2 < 52; i2++) {
//				if (!is_in_list(i2, card_list)) {
//					card_list.push_back(Card(i2));
//					n_hand++;
//					average_value = 0; //average_value*((float)n_hand - 1)/(float)n_hand +  (float)Hand(card_list).evaluate()/ (float)n_hand;
//					card_list.pop_back();
//				}
//			}
//			card_list.pop_back();
//		}
//	}
////	cout<<n_hand<<endl;
//	return (unsigned int) average_value;
//}
//
//float Hand::monte_carlo_average_value(unsigned int n_total_cards,
//		unsigned int n_draws) {
//	float average_value = 0;
//	unsigned int n_card_to_add = n_total_cards - this->cards.size();
//	list<Card> temp_card_list = this->cards;
//	for (unsigned int i = 0; i < n_draws; i++) {
//		Deck deck = Deck(this->cards);
//		this->init_config();
//		for (unsigned int jj = 0; jj < n_card_to_add; jj++) {
//			this->cards.push_back(deck.random_card());
//		}
//		unsigned int value = this->evaluate();
//		average_value += (float) value / (float) n_draws;
////		cout<<this->to_str()<<endl;
//		this->cards = temp_card_list;
//	}
//	return average_value;
//}
//
//void Hand::scan() {
//	// TODO normally not deeded
//	list<Card> list_successive;
//	list<Card> list_similar;
//	list<Card>::iterator card = this->cards.begin();
//	while (card != this->cards.end()) {
//		list_similar.clear();
//		unsigned int rank = card->get_rank();
//		list_successive.push_back(*card);
//
//		while (rank == card->get_rank() and card != this->cards.end()) {
//			this->config[card->get_suit() + 4].push_back(*card);
//			list_similar.push_back(*card);
//			card++;
//		}
//		this->config[list_similar.size()].merge(list_similar);
//		if (card->get_rank() != rank + 1 or card == this->cards.end()) {
//			if (list_successive.size() >= 5) {
//				this->config[0].merge(list_successive);
//			} else if (list_successive.size() == 4
//					and list_successive.back().get_rank() == Card::Rank::_5
//					and this->cards.back().get_rank() == Card::Rank::_A) {
//				list_successive.push_front(this->cards.back());
//				this->config[0].merge(list_successive);
//			}
//			list_successive.clear();
//		}
//	}
//}
//
//void Hand::display_config() { //const {
////	vector<list<Card>*>::iteraror conf = this->config.begin();
////	cout<<"Straight      : "<<Hand(*this->config[0]).to_str()<<endl;
////	cout<<"Single        : "<<Hand(*this->config[1]).to_str()<<endl;
////	cout<<"Paired        : "<<Hand(*this->config[2]).to_str()<<endl;
////	cout<<"Double Paired : "<<Hand(*this->config[3]).to_str()<<endl;
////	cout<<"Tripple       : "<<Hand(*this->config[4]).to_str()<<endl;
////	cout<<"Squared       : "<<Hand(*this->config[5]).to_str()<<endl;
////	cout<<"Flush 1       : "<<Hand(*this->config[6]).to_str()<<endl;
////	cout<<"Flush 2       : "<<Hand(*this->config[7]).to_str()<<endl;
////	cout<<"Flush 3       : "<<Hand(*this->config[8]).to_str()<<endl;
////	cout<<"Flush 4       : "<<Hand(*this->config[9]).to_str()<<endl;
//}
//
//unsigned int Hand::evaluate() {
//	this->init_config();
//	this->scan();
//	if (this->is_square()) {
////		cout<<"SQUARE"<<endl;
//		this->evaluated_average_value = this->value_square();
//	} else if (this->is_full_house()) {
////		cout<<"FULL HOUSE"<<endl;
//		this->evaluated_average_value = this->value_full_house();
//	} else if (this->is_flush()) {
//		if (this->is_straight()) {
//			if (this->is_straight_flush()) {
////				cout<<"STRAIGHT FLUSH"<<endl;
//				this->evaluated_average_value = this->value_straight_flush();
//			}
//		}
////		cout<<"FLUSH"<<endl;
//		this->evaluated_average_value = this->value_flush();
//	} else if (this->is_straight()) {
////		cout<<"STRAIGHT"<<endl;
//		this->evaluated_average_value = this->value_straight();
//	} else if (this->is_set()) {
////		cout<<"SET"<<endl;
//		this->evaluated_average_value = this->value_set();
//	} else if (this->is_double_paire()) {
////		cout<<"DOUBLE PAIRE"<<endl;
//		this->evaluated_average_value = this->value_double_paire();
//	} else if (this->is_paire()) {
////		cout<<"PAIRE"<<endl;
//		this->evaluated_average_value = this->value_paire();
//	} else {
////		cout<<"HIGH CARD"<<endl;
//		this->evaluated_average_value = this->value_high_card();
//	}
//	this->is_evaluated = true;
//	return this->evaluated_average_value;
//}
//
//bool Hand::is_high_card() {
//	return (this->config[1].size() > 0);
//}
//bool Hand::is_paire() {
//	return (this->config[2].size() > 0);
//}
//bool Hand::is_double_paire() {
//	return (this->config[2].size() > 2);
//}
//bool Hand::is_set() {
//	return (this->config[3].size() > 0);
//}
//bool Hand::is_straight() {
//	return (this->config[0].size() >= 5);
//}
//bool Hand::is_flush() {
//	return (this->config[5].size() >= 5 or this->config[6].size() >= 5
//			or this->config[7].size() >= 5 or this->config[8].size() >= 5);
//}
//bool Hand::is_full_house() {
//	bool full = (this->config[3].size() > 0 and this->config[2].size() > 0);
//	full = full or (this->config[3].size() > 3);
//	return full;
//}
//bool Hand::is_square() {
//	return (this->config[4].size() > 0);
//}
//bool Hand::is_straight_flush() {
////	return false;
//	list<Card> list_straight;
//	for (unsigned int suit = 1; suit <= 4; suit++) {
//		if (this->config[suit + 4].size() >= 5) {
//			//check if there is a straight within the flush
//			list<Card>::iterator card = this->config[suit + 4].begin();
//			unsigned int rank = card->get_rank() - 1;
//			while (card != this->config[suit + 4].end()) {
//				if (rank + 1 == card->get_rank()) {
//					list_straight.push_back(*card);
//				} else {
//					if (list_straight.size() >= 5) {
//						this->final_hand = list_straight;
//						return true;
//					} else if (list_straight.size() == 4
//							and list_straight.back().get_rank()
//									== Card::Rank::_5
//							and this->config[suit + 4].back().get_rank()
//									== Card::Rank::_A) {
//						this->final_hand = list_straight;
//						return true;
//					}
//					list_straight.clear();
//					list_straight.push_back(*card);
//				}
//				rank = card->get_rank();
//				card++;
//			}
//			if (list_straight.size() >= 5) {
//				this->final_hand = list_straight;
//				return true;
//			}
//			list_straight.clear();
//		}
//	}
//	return false;
//}
//
//// factorial N
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
//unsigned int Hand::value_high_card() {
////	this->display_config();
//	unsigned int n_base = 0;
//	list<Card>::iterator card_iter = this->config[1].end();
//	for (unsigned int i = 0; i < 5; i++) {
//		card_iter--;
////		this->final_hand.push_back(*card_iter);
//		n_base += C_nk(card_iter->get_rank() - 1, 5 - i) * 1020;
//		;
//	}
//	n_base = n_base - (this->config[1].back().get_rank() - 5) * 1020; //subtility if biggest card is As
////	if (n_base < 0 or n_base > 1302540){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_high_card(): Value is not correct: "
////				+ to_string(0) +" < " + to_string(n_base) + " < " + to_string(1302540));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_paire() {
//	unsigned int n_base = 1302540;
//	unsigned int rank_paire = this->config[2].back().get_rank();
////	this->final_hand = *this->config[2];
//	n_base += (rank_paire - 1) * 84480; // = (rank_paire - 1)* C_nk(4, 2) * C_nk(12, 3) * (4*4*4);
//	list<Card>::iterator card_iter = this->config[1].end();
//	for (unsigned int i = 0; i < 3; i++) {
//		card_iter--;
//		n_base += C_nk(card_iter->get_rank() - 1, 3 - i) * pow(4, 3 - i);
//		//		this->final_hand.push_back(*card_iter);
//	}
////	if (n_base < 1302540 or n_base > 2400780){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_paire(): Value is not correct: "
////				+ to_string(1302540) +" < " + to_string(n_base) + " < " + to_string(2400780));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_double_paire() {
//	unsigned int n_base = 2400780; // =1302540 + 1098240;
//	list<Card>::iterator iter_paire = this->config[2].end();
//
//	iter_paire--;
////	this->final_hand.push_back(*iter_paire);
//	iter_paire--;
////	this->final_hand.push_back(*iter_paire);
//	iter_paire--;
////	this->final_hand.push_back(*iter_paire);
//	iter_paire--;
////	this->final_hand.push_back(*iter_paire);
//	unsigned int val_smallpaire = iter_paire->get_rank();
//	unsigned int val_bigpaire = this->config[2].back().get_rank(); //bigger paire
//
//	unsigned int val_simple_card = this->config[1].back().get_rank();
////	this->final_hand.push_back(this->config[1].back());
//
//	n_base += C_nk(val_bigpaire - 1, 2) * 1584; // = C_nk(val_bigpaire - 1, 2) * C_nk(4, 2) * C_nk(4, 2) * (13 -2)*4
//	n_base += (val_smallpaire - 1) * 264; // = (val_smallpaire - 1) * C_nk(4,2) * (13 -2)*4
//
//	if (val_simple_card > val_bigpaire) {
//		n_base += (val_simple_card - 3) * 4;
//	} else if (val_simple_card < val_smallpaire) {
//		n_base += (val_simple_card - 1) * 4;
//	} else {
//		n_base += (val_simple_card - 3) * 4;
//	}
//
////	if (n_base < 2400780 or n_base > 2524332){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_double_paire(): Value is not correct: "
////				+ to_string(2400780) +" < " + to_string(n_base) + " < " + to_string(2524332));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_set() {
//	unsigned int n_base = 2524332; //=1302540 + 1098240 + 123552;
//
////	list<Card>::iterator iter_triple = this->config[3].begin();
////	this->final_hand.push_back(*iter_triple);
////	iter_triple++;
////	this->final_hand.push_back(*iter_triple);
////	iter_triple++;
////	this->final_hand.push_back(*iter_triple);
//
//	unsigned int val_triple = this->config[3].back().get_rank();
//
//	list<Card>::iterator iter_simple = this->config[1].end();
//	iter_simple--;
//	unsigned int val_big_simple_card = iter_simple->get_rank();
//	//	this->final_hand.push_back(*iter_simple);
//
//	iter_simple--;
//	unsigned int val_small_simple_card = iter_simple->get_rank();
//	//	this->final_hand.push_back(*iter_simple);
//
//	n_base += (val_triple - 1) * 4224; // = (val_triple -1)* C_nk(4, 3)*C_nk(12, 2)*4*4
//	n_base += C_nk(val_big_simple_card - 1, 2) * 16;
//	n_base += (val_small_simple_card - 1) * 4;
//
////	if (n_base < 2524332 or n_base > 2579244){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_set(): Value is not correct: "
////				+ to_string(2524332) +" < " + to_string(n_base) + " < " + to_string(2579244));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_straight() {
//	unsigned int n_base = 2579244; // = 1302540 + 1098240 + 123552 + 54912;
//	unsigned int val_high = this->config[0].back().get_rank();
//	n_base += (val_high - 4) * 1020;
//
////	list<Card>::iterator iter_straight = this->config[0].end();
////	for (unsigned int i= 0; i<5;i++){
////		iter_straight--;
////		this->final_hand.push_back(*iter_straight);
////	}
//
////	if (n_base < 2579244 or n_base > 2589444){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_traight(): Value is not correct: "
////				+ to_string(2579244) +" < " + to_string(n_base) + " < " + to_string(2589444));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_flush() {
//	unsigned int n_base = 2589444; //=1302540 + 1098240 + 123552 + 54912 + 10200;
//	for (unsigned int i = 0; i < 4; i++) {
//		if (this->config[i + 5].size() >= 5) {
//			list<Card>::iterator iter_suit = this->config[5 + i].end();
//			for (unsigned int j = 0; j < 5; j++) {
//				iter_suit--;
//				n_base += 4 * C_nk(iter_suit->get_rank() - 1, 5 - j);
////				this->final_hand.push_back(*iter_suit);
//			}
//			n_base -= (this->config[5 + i].back().get_rank() - 5) * 4; //subtility if biggest card is As
//		}
//	}
//
////	if (n_base < 2589444 or n_base > 2594552){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_flush(): Value is not correct: "
////				+ to_string(2589444) +" < " + to_string(n_base) + " < " + to_string(2594552));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_full_house() {
//	unsigned int n_base = 2594552; // = 1302540 + 1098240 + 123552 + 54912 + 10200 + 5108;
//
//	unsigned int val_triple = this->config[3].back().get_rank();
//
//	list<Card>::iterator iter_triple = this->config[3].end();
//	iter_triple--;
////	this->final_hand.push_back(*iter_triple);
//	iter_triple--;
////	this->final_hand.push_back(*iter_triple);
//	iter_triple--;
////	this->final_hand.push_back(*iter_triple);
//
//	unsigned int val_double;
//	if (this->config[3].size() >= 6) {
//		iter_triple--;
////		this->final_hand.push_back(*iter_triple);
////		iter_triple--;
////		this->final_hand.push_back(*iter_triple);
//		val_double = iter_triple->get_rank();
//	} else {
////		list<Card>::iterator iter_paire = this->config[2]->end();
////		iter_paire--;
////		this->final_hand.push_back(*iter_paire);
////		iter_paire--;
////		this->final_hand.push_back(*iter_paire);
//		val_double = this->config[2].back().get_rank();
//	}
//
//	n_base += (val_triple - 1) * 288;
//	if (val_double > val_triple) {
//		n_base += (val_double - 2) * 6;
//	} else {
//		n_base += (val_double - 1) * 6;
//	}
//
////	if (n_base < 2594552 or n_base > 2598296){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_full_house(): Value is not correct: "
////				+ to_string(2594552) +" < " + to_string(n_base) + " < " + to_string(2598296));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_square() {
//	unsigned int n_base = 2598296; //=1302540 + 1098240 + 123552 + 54912 + 10200 + 5108 + 3744;
//
////	list<Card>::iterator iter_square = this->config[4]->end();
////	for (unsigned int j=0; j<4; j++){
////		iter_square--;
////		this->final_hand.push_back(*iter_square);
////	}
//
//	unsigned int val_square = this->config[4].back().get_rank();
//	unsigned int val_single_card;
//	if (this->config[3].size() > 0) {
//		val_single_card = this->config[3].back().get_rank();
////		this->final_hand.push_back(this->config[3].back());
//	} else if (this->config[2].size() > 0) {
//		if ((this->config[1].size() > 0)) {
//			if (this->config[1].back().get_rank()
//					> this->config[2].back().get_rank()) {
//				val_single_card = this->config[1].back().get_rank();
////				this->final_hand.push_back(this->config[1].back());
//			} else {
//				val_single_card = this->config[2].back().get_rank();
////				this->final_hand.push_back(this->config[2]->back());
//			}
//		} else {
//			val_single_card = this->config[2].back().get_rank();
////			this->final_hand.push_back(this->config[2]->back());
//		}
//	} else {
//		val_single_card = this->config[1].back().get_rank();
////		this->final_hand.push_back(this->config[1].back());
//	}
//
//	n_base += (val_square - 1) * 48;
//	if (val_square > val_single_card) {
//		n_base += (val_single_card - 1) * 4;
//	} else {
//		n_base += (val_single_card - 2) * 4;
//	}
//
////	if (n_base < 2598296 or n_base > 2598920){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_square(): Value is not correct: "
////				+ to_string(2598296) +" < " + to_string(n_base) + " < " + to_string(2598920));
////	}
//	return n_base;
//}
//
//unsigned int Hand::value_straight_flush() {
//	unsigned int n_base = 2598920; //=1302540 + 1098240 + 123552 + 54912 + 10200 + 5108 + 3744 + 624;
//	unsigned int val_high = this->final_hand.back().get_rank();
//	n_base += (val_high - 4) * 4;
////	if (n_base < 2598920 or n_base > 2598960){
////		cout<<this->card_list_to_str(this->final_hand);
////		throw runtime_error("Error in value_straight_flush(): Value is not correct: "
////				+ to_string(2598920) +" < " + to_string(n_base) + " < " + to_string(2598960));
////	}
//	return n_base;
//}
//
//namespace std {
//
//Hand_::Hand_() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Hand_::~Hand_() {
//	// TODO Auto-generated destructor stub
//}
//
//} /* namespace std */

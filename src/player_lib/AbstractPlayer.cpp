
#include "AbstractPlayer.h"
#include "../table_lib/AbstractTable.h"
#include <boost/filesystem.hpp>

#define BASE_STAKE 100
#define BANK_ROLL_INIT 100000

using namespace std;

AbstractPlayer::AbstractPlayer(void){
	this->initial_bank_roll = BANK_ROLL_INIT;
	this->base_stake = BASE_STAKE;
	this->id = "AbstractPlayer";
	this->init_bank_roll();
	this->hand = Hand();
	this->commitment = 0;
	this->table = NULL;
	this->pos_on_table = 0;
	this->_is_in_hand = true;
	this->open_hand = true;
	this->auto_rebuy = true;
	this->folder_to_save = "./bots/" + this->get_id();
}

AbstractPlayer::AbstractPlayer(string id):AbstractPlayer(){
	this->id = id;
}

AbstractPlayer::AbstractPlayer(AbstractTable *table, unsigned int position):AbstractPlayer(){
	this->table = table;
	this->pos_on_table = position;
	this->id = this->id + to_string(position); //TODO temporary
}

void AbstractPlayer::init_bank_roll(){
	this->stock = BANK_ROLL_INIT - BASE_STAKE;
	this->stake  = BASE_STAKE;
}

bool AbstractPlayer::operator>=(const AbstractPlayer &player){
	return (this->get_bank_roll()) >= (player.get_bank_roll());
}

bool AbstractPlayer::operator>(const AbstractPlayer &player){
	return (this->get_bank_roll()) > (player.get_bank_roll());
}

bool AbstractPlayer::operator==(const AbstractPlayer &player){
	return (this->get_bank_roll()) == (player.get_bank_roll());
}

bool AbstractPlayer::operator<=(const AbstractPlayer &player){
	return (this->get_bank_roll()) <= (player.get_bank_roll());
}

bool AbstractPlayer::operator<(const AbstractPlayer &player){
	return (this->get_bank_roll()) < (player.get_bank_roll());
}

unsigned int AbstractPlayer::get_initial_bank_roll() const{
	return this->initial_bank_roll;
}

unsigned int AbstractPlayer::get_stake() const {
	return this->stake;
}

unsigned int AbstractPlayer::get_base_stake() const{
	return this->base_stake;
}

bool AbstractPlayer::is_in_hand() const{
	return this->_is_in_hand;
}

bool AbstractPlayer::is_open_hand() const{
	return this->open_hand;
}

unsigned int AbstractPlayer::get_pos_on_table()const{
	return this->pos_on_table;
}

void AbstractPlayer::set_is_in_hand(bool player_status){
	this->_is_in_hand = player_status;
}

void AbstractPlayer::set_stake(unsigned int stake){
	this->stake = stake;
}

void AbstractPlayer::set_hand(list<Card>* hand){
	this->hand = Hand(hand);
}

void AbstractPlayer::set_hand(const Hand& hand){
	this->hand = hand;
}

void AbstractPlayer::set_auto_rebuy(bool rebuy){
	this->auto_rebuy = rebuy;
}

void AbstractPlayer::set_table(AbstractTable * table, unsigned int position){
	this->table = table;
	this->pos_on_table = position;
}

void AbstractPlayer::set_open_hand(bool open_hand){
	this->open_hand = open_hand;
}

void AbstractPlayer::clear_hand(void){
	this->hand.clear();
}

void AbstractPlayer::add_card_to_hand(Card card){
	this->hand.push_back(card);
}

void AbstractPlayer::add_cards_to_hand(list<Card> &cards){
	this->hand.add_cards(cards);
}

unsigned int AbstractPlayer::get_hand_value(){
	return this->hand.evaluate();
}

Hand::HandCategory AbstractPlayer::get_hand_category(){
	vector<list<Card>> config = hand.scan();
	cout<<this->hand.to_str()<<endl;
	return this->hand.get_category_from_config(config);
}

AbstractPlayer::~AbstractPlayer(void){
}

void AbstractPlayer::close_hand(){
}

string AbstractPlayer::save() const {
	return this->save_to_folder(this->folder_to_save);
}

string AbstractPlayer::save_to_folder(string foldername) const {
	cout<<"Saving "<<this->get_id()<<" in "<<foldername<<endl;
	string folder_to_save = foldername;// + "/" + this->get_id();
	boost::filesystem::path p(folder_to_save);
	boost::filesystem::create_directory(p);
	string filename = folder_to_save + "/setup.p";
	std::ofstream ofs(filename);
	boost::archive::binary_oarchive oa(ofs);
	this->transfert_out(oa);
	cout<<"Player saved in folder "<<folder_to_save<<endl;
	return folder_to_save;
}

void AbstractPlayer::transfert_out(boost::archive::binary_oarchive &oa) const{
	oa << *this;
}

void AbstractPlayer::transfert_in(boost::archive::binary_iarchive & iarch){
	iarch >> *this;
}

template<class Archive>
void AbstractPlayer::serialize(Archive & ar, const unsigned int version){
	ar & this->id;
}

string AbstractPlayer::load_from_folder(string model_folder){
	if(boost::filesystem::exists(model_folder)){
		cout<<"Loading "<<this->get_id()<<" from "<<model_folder<<endl;
		string setup_filename = model_folder + "/setup.p";
		if(boost::filesystem::exists(setup_filename)){
			ifstream ifs(setup_filename);
			boost::archive::binary_iarchive iarch(ifs);
			this->transfert_in(iarch);
		}
		else{
			throw std::invalid_argument("File "
										+ setup_filename
										+ " does not exist");
		}
		return model_folder;
	}
	else{
		throw std::invalid_argument("Folder "
									+ model_folder
									+ " does not exist");
	}
}

string AbstractPlayer::to_str(){
	string str = "Sit " + to_string(this->get_pos_on_table());
	str+= "(player " + this->get_id() + ")";
	str+=" [" + to_string(this->get_stake()) + " + (" + to_string(this->get_commitment()) + ") / " + to_string(this->get_bank_roll())+"] : ";
	str+= this->hand.to_str();
	return str;
}

void AbstractPlayer::commit_chips(unsigned int value){
	this->stake-=value;
	this->commitment += value;
}

void AbstractPlayer::set_commitment(int amount){
	this->commitment = amount;
}

unsigned int AbstractPlayer::get_commitment() const{
	return this->commitment;
}

Hand AbstractPlayer::get_hand() const {
	return this->hand;
}

unsigned int AbstractPlayer::get_bank_roll()const{
	return this->stock + this->stake;
}

string AbstractPlayer::get_id()const{
	return this->id;
}

bool AbstractPlayer::is_auto_rebuy() const{
	return this->auto_rebuy;
}


void AbstractPlayer::add_to_stake(unsigned int value) {
	this->stake += value;
}

void AbstractPlayer::init_hand(){
	this->commitment = 0;
	this->_is_in_hand = true;
	this->hand.clear();
	if(this->auto_rebuy){//rebuy if autorebuy and if needed
		int val = max((int)this->base_stake - (int)this->stake, 0);
		this->stake += val;
		this->stock -= val;
	}
	else{
		if(this->stake <= this->table->get_blend_value()){ //Rebuy only id stake < blend
			unsigned int refill = min(this->base_stake, this->stock);
			this->stake = refill ;
			this->stock -= refill ;
		}
	}
}

AbstractPlayer::Action AbstractPlayer::play_street(unsigned int street){
	switch(street){
	case AbstractTable::t_preflop:
		return this->play_preflop();
		break;
	case AbstractTable::t_flop:
		return this->play_flop();
		break;
	case AbstractTable::t_turn:
		return this->play_turn();
		break;
	case AbstractTable::t_river:
		AbstractPlayer::Action action = this->play_river();
		return action;
		break;
	}
	return AbstractPlayer::Action::t_fold;
}

AbstractPlayer::Action AbstractPlayer::raise_pot(unsigned int value){
	/* the raise value represents the total chips committed to the pot
	 * if a player already has chips committed,
	 * then only the difference between value and his commitment will be added to the pot
	 */
	if(value < this->stake + this->commitment){ //The player is not all in
		if (value  < this->table->get_diff_last_raises() + this->table->get_last_raise()){// the value of the raise is not standard
			throw std::invalid_argument("Error: invalid raise value from player "
										+ this->id
										+ "\n"
										+"Last raise/bet was "
										+ to_string(this->table->get_last_raise())
										+ ", before was "
										+ to_string(this->table->get_before_last_raise())
										+ ", intended raise is "
										+ to_string(value)
										+ ", should be at least "
										+ to_string(this->table->get_last_raise() + this->table->get_diff_last_raises())
										);
		}
	}
	else if (value > this->stake + this->commitment){// this stake of the player in not big enough to support the raise
		throw std::invalid_argument("Error: raise "
									+ to_string(value - this->commitment)
									+ " above stake "
									+ to_string(this->stake));
	}
	else{
		if (value  <= this->table->get_last_raise()){// the value of the raise is not standard
			throw std::invalid_argument("Error: invalid raise value from player "
										+ this->id
										+ "\n"
										+"Last raise/bet was "
										+ to_string(this->table->get_last_raise())
										+ ", before was "
										+ to_string(this->table->get_before_last_raise())
										+ ", total raise is "
										+ to_string(value)
										+ ", All in should just call "
										);
		}
	}
	this->commit_chips(value - this->commitment);
	this->table->update_current_raises(value);
	return AbstractPlayer::Action::t_raise;
}

AbstractPlayer::Action AbstractPlayer::bet_pot(unsigned int value){
	if(this->table->get_last_raise() != 0){//> this->commitment){
		throw std::invalid_argument("Last raise was "
									+ to_string(this->table->get_last_raise())
									+"\n Bet from player "
									+ this->id
									+" not compatible with street actions");
	}
	if (value > this->stake + this->commitment){
		throw std::invalid_argument("Error: bet "+ to_string(value) + " above stake " + to_string(this->stake));
	}
	if (value <= 0){
		throw std::invalid_argument("Error: bet "+ to_string(value) + ", should be over 0");
	}
	this->commit_chips(value - this->commitment);
	this->table->update_current_raises(value);
	return AbstractPlayer::Action::t_bet;
}

AbstractPlayer::Action AbstractPlayer::fold_pot(){
	if(this->table->get_last_raise() == this->commitment){
		throw std::invalid_argument("Fold not accepted from player "
									+ this->id
									+" , should have checked instead");
	}
	this->_is_in_hand = false;
	this->hand.clear();
	return AbstractPlayer::Action::t_fold;
}

AbstractPlayer::Action AbstractPlayer::check_pot(){
	if(this->table->get_last_raise() != 0 and this->table->get_last_raise() != this->commitment){
		throw std::invalid_argument("Last raise was "
									+ to_string(this->table->get_last_raise())
									+ "\n Check from sit "
									+ to_string(this->pos_on_table)
									+" not compatible with street actions");
	}
	return AbstractPlayer::Action::t_check;
}

AbstractPlayer::Action AbstractPlayer::call_pot(){
	unsigned int value = (int)this->table->get_last_raise() - (int)this->commitment;
	if(value == 0){
		throw std::invalid_argument("Call not necessary, last raise was"
									+ to_string(this->table->get_last_raise())
									+ "\n, commitment is "
									+ to_string(this->commitment));
	}
	unsigned int value_commited = min(value, this->stake);
	this->commit_chips(value_commited);
	return Action::t_call;
}

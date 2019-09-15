

#ifndef PLAYER_LIB_PLAYERBOTV1_H_
#define PLAYER_LIB_PLAYERBOTV1_H_


#include "PlayerBot.h"
#include "AbstractPlayer.h"
#include "../table_lib/AbstractTable.h"

#include <random>

using namespace std;
using ParentPlayerBotV1 = PlayerBot;

class PlayerBotV1 : public ParentPlayerBotV1{

public:
	PlayerBotV1(void);
	PlayerBotV1(string id, float);
	PlayerBotV1(string id);
	virtual ~PlayerBotV1();

	void set_learning_rate(float);


	void train();
	void init_macro_params();
	void init_macro_params(std::default_random_engine& generator);
	void init_params(std::default_random_engine& generator);
	void init_params();
	void mute_macro_params();
	void mute_macro_params(std::default_random_engine& generator);
	void init_learning_params();

	void mute_macro_params(list<PlayerBotV1*> &, default_random_engine& generator);

	float get_learning_rate();
	float get_param_reg();
	float get_param_lead();
	float get_param_foll();


	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();

	void transfert_in(boost::archive::binary_iarchive & iarch) override{iarch >> *this;}
	void transfert_out(boost::archive::binary_oarchive &oa) const override{oa <<*this;}
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<AbstractPlayer>(*this);
		ar & learning_rate;
		ar & param_reg;
		ar & param_lead;
		ar & param_foll;
	}


protected:
	float param_lead;
	float param_foll;
	float learning_rate;
	float param_reg;

	float param_stat; //can be a vector
	bool lead;
	bool invest;

};

#endif /* PLAYER_LIB_PLAYERBOTV1_H_ */

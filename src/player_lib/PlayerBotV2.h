

#ifndef PLAYER_LIB_PLAYERBOTV2_H_
#define PLAYER_LIB_PLAYERBOTV2_H_


#include "PlayerBot.h"

#include <torch/torch.h>
using namespace torch;

using ParentPlayerBotV2 = PlayerBot;

class PlayerBotV2 : public ParentPlayerBotV2{

public:
	PlayerBotV2(void);
	PlayerBotV2(string id);
	PlayerBotV2(AbstractTable * table);
	PlayerBotV2(AbstractTable * table, unsigned int);
	~PlayerBotV2();

	float get_coefficient_reg(){return this->coefficient_reg;}
	float get_learning_rate(){return this->learning_rate;}
	float get_bet_pot_percentage(){return this->bet_pot_percentage;}

	void display_learning_params();

//	void init_train_params();
	void train();

	virtual void init_learning_params() override;

	virtual void init_macro_params() override;
	virtual void init_macro_params(std::default_random_engine& generator) override;

	virtual void mute_macro_params();
	virtual void mute_macro_params(std::default_random_engine& generator);
	virtual void mute_macro_params(list<AbstractPlayer*> &, default_random_engine& generator) override;


	Action play_preflop();
	Action play_flop();
	Action play_turn();
	virtual Action play_river();


	void init_hand();
	virtual void zero_grad();
//	void close_hand();

	torch::Tensor build_input();
	Action select_action_from_distribution(Tensor&);
	virtual Action compute_rewards_and_select_action(Tensor&);

	string save_to_folder(string) const;
	string load_from_folder(string) ;
	string load_from_model(string) override;

	void transfert_in(boost::archive::binary_iarchive & iarch) override{iarch >> *this;}
	void transfert_out(boost::archive::binary_oarchive &oa) const override{oa <<*this;}
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<AbstractPlayer>(*this);
		ar & learning_rate;
		ar & bet_pot_percentage;
		ar & coefficient_reg;
	}


protected:

	unsigned int dim_input;
	unsigned int dim_output;
	torch::Tensor input;
	torch::Tensor output;
	torch::Tensor action_value;
	nn::Sequential river_net;
	torch::optim::SGD * optimizer;

	/* macro parameters */
	float learning_rate;
	float bet_pot_percentage;
	float coefficient_reg;

};

#endif /* PLAYER_LIB_PLAYERBOTV2_H_ */

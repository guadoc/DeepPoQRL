

#ifndef PLAYER_LIB_PLAYERBOTV2_H_
#define PLAYER_LIB_PLAYERBOTV2_H_


#include "../PlayerQlearner.h"

#include <torch/torch.h>
using namespace torch;

using ParentPlayerBotV2 = PlayerQlearner;

class PlayerBotV2 : public ParentPlayerBotV2{

public:
	PlayerBotV2(void);
	PlayerBotV2(string id);
	PlayerBotV2(AbstractTable * table, unsigned int);
	~PlayerBotV2();

	void set_greedy_mode(bool);

	float get_coefficient_reg() const {return this->coefficient_reg;}
	float get_learning_rate()const {return this->learning_rate;}
	float get_bet_pot_percentage()const{return this->bet_pot_percentage;}

	string training_params_to_str()const;

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

	torch::Tensor build_input();
	vector<float> compute_Qvalues(torch::Tensor);
//	Action select_action_from_Qvalues(vector<float>, AbstractTable::Street street);
	Action random_play(vector<float>, AbstractTable::Street street);
//	Action optimal_play_from_Qvalues(vector<float>, AbstractTable::Street street);
	torch::Tensor get_action_value(Action);
	void plot_monitoring();



//	string save_to_folder(string) const;
//	string load_from_folder(string) ;
//	string load_from_model(string) override;
//	void transfert_in(boost::archive::binary_iarchive & iarch) override{iarch >> *this;}
//	void transfert_out(boost::archive::binary_oarchive &oa) const override{oa <<*this;}
//	friend class boost::serialization::access;
//	template<class Archive>
//	void serialize(Archive & ar, const unsigned int version) {
//		ar & boost::serialization::base_object<AbstractPlayer>(*this);
//		ar & learning_rate;
//		ar & bet_pot_percentage;
//		ar & coefficient_reg;
//	}

protected:
	/* for DNN */
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

	/* decision mode */
	bool is_greedy;

};

#endif /* PLAYER_LIB_PLAYERBOTV2_H_ */

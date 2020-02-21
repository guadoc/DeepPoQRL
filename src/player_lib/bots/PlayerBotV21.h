

#ifndef PLAYER_LIB_PLAYERBOTV21_H_
#define PLAYER_LIB_PLAYERBOTV21_H_


#include "../PlayerQlearner.h"

#include <torch/torch.h>
using namespace torch;

using ParentPlayerBotV21 = PlayerQlearner;

class PlayerBotV21 : public ParentPlayerBotV21{
public:
	PlayerBotV21(void);
	PlayerBotV21(string id);
	PlayerBotV21(AbstractTable * table, unsigned int);
	~PlayerBotV21();

	void set_learning_rate(float lr);

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

	void init_hand();
	virtual void zero_grad();

	vector<float> build_input();
	vector<float> compute_Qvalues(vector<float>);
	float credit_action_value(Action);


	string save_to_folder(string) const;
	string load_from_folder(string);
	void transfert_in(boost::archive::binary_iarchive & iarch) override{iarch >> *this;}
	void transfert_out(boost::archive::binary_oarchive &oa) const override{oa <<*this;}
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version);

protected:
	/* for DNN declatation */
	unsigned int dim_input;
	unsigned int dim_output;

	/*to train the DNN*/
	list<torch::Tensor> output;
	nn::Sequential river_net;
	torch::optim::SGD * optimizer;
	vector<Tensor> hand_actions_Qvalue;

	/* macro parameters */
	float learning_rate;
	float bet_pot_percentage;
	float coefficient_reg;

};

#endif /* PLAYER_LIB_PLAYERBOTV21_H_ */

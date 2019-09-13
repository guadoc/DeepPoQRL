/*
 * GUI.h
 *
 *  Created on: May 12, 2019
 *      Author: michael blot
 */

#ifndef TABLE_LIB_GUI_H_
#define TABLE_LIB_GUI_H_


#include "../StdAfx.h"
#include "../deck_lib/Card.h"
#include "../player_lib/AbstractPlayer.h"

using namespace std;


#define WINDOW_SIZE_X 1024 + 100
#define WINDOW_SIZE_Y 640 + 100
#define CARD_SIZE_X 48
#define CARD_SIZE_Y 52
#define STAKE_SIZE_X 35
#define STAKE_SIZE_Y 40
#define SIT_SIZE_X 100
#define SIT_SIZE_Y 100
#define BUTTON_SIZE_X 55
#define BUTTON_SIZE_Y 55
#define POT_SIZE_X 85
#define POT_SIZE_Y 45
#define NAME_SIZE_X 61
#define NAME_SIZE_Y 41
#define BOARD_COORD_X 400
#define BOARD_COORD_Y 300
#define POT_COORD_X 450
#define POT_COORD_Y 350

#define STAKE_COLOR {0, 0, 0}
#define POT_COLOR {0, 0, 0}
#define ACTION_BUTTON_COLOR {125, 125, 125}

const string GRAPHIC_TOOL_FOLDER = "./src/utils/graphism_toolbox/";
const string TABLE_FILE="new_version/table2.png";
const string POT_FONT ="OpenSans-Semibold.ttf";
const string ACTIVE_SIT_FILE ="new_version/sit_active.png";
const string SIT_FILE ="new_version/sit.png";
const string CARD_FOLDER = "Cards/";
const string DEALER_BUTTON_FILE ="new_version/button2.png";
const string STAKE_FONT ="OpenSans-Semibold.ttf";


class GUI {
public:
	GUI();
	GUI(unsigned int);
	virtual ~GUI();
	void display_player(AbstractPlayer * player, unsigned int * coords, bool is_active, bool is_dealer);
	void display_table(unsigned int pot, list<Card> board, vector<AbstractPlayer*>, unsigned int dealer_position, unsigned int active_player);
	void display_card_list(list<Card> hand_cards, unsigned int updto_n, unsigned int coordX, unsigned  coordY, unsigned int sizeX, unsigned int sizeY);
	void display_card(Card card, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY);
	void display_image(string file_name, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY);
	void display_text(string text, TTF_Font* font, SDL_Color color, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY);
	SDL_Rect display_button(string text, TTF_Font* font, SDL_Color text_color, SDL_Color button_color, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY);
	SDL_Rect display_action_button(string text, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY) ;
	void display_action_buttons(bool has_raised);
	int check_click_in_rect(int x, int y, struct SDL_Rect &rect);
	string get_card_file_name(Card card);


	static unsigned int** sits_coord(unsigned int n_sits){
		unsigned int** coords = new unsigned int*[n_sits];
		coords[0] = new unsigned int[6];
		coords[0][0] = 66;
		coords[0][1] = 135;
		coords[0][2] = 205;
		coords[0][3] = 225;
		coords[0][4] = 205;
		coords[0][5] = 155;
		coords[1] = new unsigned int[6];
		coords[1][0] = 509;
		coords[1][1] = 63;
		coords[1][2] = 535;
		coords[1][3] = 185;
		coords[1][4] = 595;
		coords[1][5] = 185;
		coords[2] = new unsigned int[6];
		coords[2][0] = 950;
		coords[2][1] = 135;
		coords[2][2] = 870;
		coords[2][3] = 225;
		coords[2][4] = 870;
		coords[2][5] = 170;
		coords[3] = new unsigned [6];
		coords[3][0] = 950;
		coords[3][1] = 455;
		coords[3][2] = 870;
		coords[3][3] = 400;
		coords[3][4] = 835;
		coords[3][5] = 430;
		coords[4] = new unsigned int[6];
		coords[4][0] = 509;
		coords[4][1] = 520;
		coords[4][2] = 535;
		coords[4][3] = 420;
		coords[4][4] = 480;
		coords[4][5] = 400;
		coords[5] = new unsigned int[6];
		coords[5][0] = 66;
		coords[5][1] = 460;
		coords[5][2] = 205;
		coords[5][3] = 400;
		coords[5][4] = 205;
		coords[5][5] = 350;
		return coords;
	}


protected:
	SDL_Renderer * renderer;
	unsigned int ** players_coord;
};


#endif /* TABLE_LIB_GUI_H_ */

/*
 * GUI.cpp
 *
 *  Created on: May 12, 2019
 *      Author: walnutalgo
 */

#include "GUI.h"

using namespace std;

GUI::GUI(){
	SDL_Renderer * renderer;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Window * window = SDL_CreateWindow("Poker Table Simulation",
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										WINDOW_SIZE_X,
										WINDOW_SIZE_Y,
										SDL_WINDOW_SHOWN);
	if (window){
			renderer = SDL_CreateRenderer(window, -1, 0);
	}
	else {
		cout<<"ERROR with screen creation"<<endl;
	}
	this->renderer = renderer;
	this->players_coord = NULL;
}

GUI::GUI(unsigned int n_players):GUI(){
	this->players_coord = GUI::sits_coord(n_players);
}

GUI::~GUI() {
	delete this->players_coord ;
	// TODO Auto-generated destructor stub
	cout<<"DESTROYING"<<endl;
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

void GUI::display_image(string file_name, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY){
	SDL_Surface * image_surface = IMG_Load(file_name.c_str());
	if (image_surface){
		SDL_Texture * texture_sit = SDL_CreateTextureFromSurface(renderer, image_surface);
		if(texture_sit){
			SDL_Rect dstrect = { (int)coordX, (int)coordY, (int)sizeX, (int)sizeY};
			SDL_RenderCopy(this->renderer, texture_sit, NULL, &dstrect);
			SDL_DestroyTexture(texture_sit);
		}else{
			throw invalid_argument("Error: Image/texture "+file_name+" cannot be displayed");
		}
		SDL_FreeSurface(image_surface);
	}else{
		throw invalid_argument("Error: Image "+file_name+" cannot be loaded");
	}
}

void GUI::display_text(string text, TTF_Font* font, SDL_Color color, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY){
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str() , color);
	if (surfaceMessage){
		SDL_Texture* Message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
		if (Message ){
			SDL_Rect Message_rect = { (int)coordX, (int)coordY, (int)sizeX, (int)sizeY};
			SDL_RenderCopy(this->renderer, Message, NULL, &Message_rect);
			SDL_DestroyTexture(Message);
		}else{
			cout<<"Text "+text+" cannot be displayed"<<endl;
		}
		SDL_FreeSurface(surfaceMessage);
	}else{
		cout<<"Text "+text+" cannot be displayed"<<endl;
	}
}

void GUI::display_card_list(list<Card> card_list, unsigned int up_to_n, unsigned int coordX, unsigned int coordY, unsigned int sizeX , unsigned int sizeY) {
	if(card_list.size() > 0){
		unsigned int i =0;
		for(Card const card : card_list){
			this->display_card(card, coordX +i*sizeX+5 , coordY, sizeX, sizeY);
			i++;
			if (i >= up_to_n){
				break;
			}
		}
	}
}

void GUI::display_card(Card card, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY) {
	this->display_image(this->get_card_file_name(card), coordX, coordY, sizeX, sizeY);
}

string GUI::get_card_file_name(Card card){
	return GRAPHIC_TOOL_FOLDER + CARD_FOLDER + card.to_str() + ".png";
}

void GUI::display_table(unsigned int pot, list<Card> board, vector<AbstractPlayer *> players, unsigned int dealer_pos, unsigned int active_player){
	SDL_RenderClear(this->renderer);
	//display the table picture on the window
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	this->display_image(GRAPHIC_TOOL_FOLDER + TABLE_FILE,
						50,
						50,
						WINDOW_SIZE_X - 100,
						WINDOW_SIZE_Y - 100);
	SDL_Event event;
	SDL_WaitEvent(&event);
	// display all player on the sits in sits_coords
	for (unsigned int pos = 0; pos < players.size(); pos++){
		this->display_player(players[pos], this->players_coord[pos], active_player == pos, (dealer_pos == pos));
	}
	// display the pot value
	this->display_text("Pot: "+ to_string(pot),
						TTF_OpenFont((GRAPHIC_TOOL_FOLDER + POT_FONT).c_str(),32),
						POT_COLOR,
						POT_COORD_X,
						POT_COORD_Y,
						POT_SIZE_X,
						POT_SIZE_Y);
	//display the board on the table
	this->display_card_list(board,
						-1,
						BOARD_COORD_X,
						BOARD_COORD_Y,
						CARD_SIZE_X,
						CARD_SIZE_Y);
	SDL_RenderPresent(this->renderer);
}

void GUI::display_player(AbstractPlayer * player, unsigned int * coords, bool is_active, bool is_dealer){
	unsigned int coordX = coords[0];
	unsigned int coordY = coords[1];
	string file_name;
	if (is_active){
		file_name = GRAPHIC_TOOL_FOLDER + ACTIVE_SIT_FILE;
	}else{
		file_name = GRAPHIC_TOOL_FOLDER + SIT_FILE;
	}
	this->display_image(file_name,
						coordX,
						coordY,
						SIT_SIZE_X,
						SIT_SIZE_Y);
	this->display_text(player->get_id(),
						TTF_OpenFont((GRAPHIC_TOOL_FOLDER + STAKE_FONT).c_str(),32),
						STAKE_COLOR,
						coordX+20,
						coordY + 20,
						NAME_SIZE_X,
						NAME_SIZE_Y);
	this->display_text(to_string(player->get_stake()),
						TTF_OpenFont((GRAPHIC_TOOL_FOLDER + STAKE_FONT).c_str(),32),
						STAKE_COLOR,
						coordX+30,
						coordY + 50,
						STAKE_SIZE_X,
						STAKE_SIZE_Y);

	if(player->is_in_hand()){//this->commitment >= 0){
		list<Card> player_hand;
		unsigned int i = 0;
		for (auto& card: player->get_hand().get_cards()){
			player_hand.push_back(card);
			if(i == 1){break;}
			i++;
		}
		this->display_card_list(player->get_hand().get_cards(),
								2,
								coordX + 30,
								coordY - 30,
								CARD_SIZE_X,
								CARD_SIZE_Y);
		if(player->get_commitment() > 0){
			//TODO adapt font, size, color,....
			unsigned int coordX_invested_chips = coords[2];
			unsigned int coordY_invested_chips = coords[3];
			this->display_text(to_string(player->get_commitment()),
								TTF_OpenFont((GRAPHIC_TOOL_FOLDER + STAKE_FONT).c_str(),32),
								STAKE_COLOR,
								coordX_invested_chips,
								coordY_invested_chips,
								STAKE_SIZE_X,
								STAKE_SIZE_Y);
		}
	}
	if (is_dealer){
		unsigned int coordX_button = coords[4];
		unsigned int coordY_button = coords[5];
		this->display_image(GRAPHIC_TOOL_FOLDER + DEALER_BUTTON_FILE,
							coordX_button,
							coordY_button,
							BUTTON_SIZE_X,
							BUTTON_SIZE_Y);

	}
}


SDL_Rect GUI::display_button(string text, TTF_Font* font, SDL_Color text_color, SDL_Color button_color, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY){
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str() , text_color);
	SDL_Rect text_rect = {(int)coordX + 10, (int)coordY, (int)sizeX -20, (int)sizeY };
	SDL_Rect button_rect = { (int)coordX, (int)coordY, (int)sizeX, (int)sizeY};
	if (surfaceMessage){
		SDL_Texture* Message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
		if (Message){
			SDL_SetRenderDrawColor(this->renderer, 255, 0, 255, 255 );
			SDL_RenderFillRect(this->renderer, &button_rect);
			SDL_RenderCopy(this->renderer, Message, NULL, &text_rect);
			SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(this->renderer, &button_rect);
			SDL_DestroyTexture(Message);
		}else{
			cout<<"Text "+text+" cannot be displayed"<<endl;
		}
		SDL_FreeSurface(surfaceMessage);
	}else{
		cout<<"Text "+text+" cannot be displayed"<<endl;
	}
	return button_rect;
}


SDL_Rect GUI::display_action_button(string button_text, unsigned int coordX, unsigned int coordY, unsigned int sizeX, unsigned int sizeY) {
	TTF_Font* text_font = TTF_OpenFont((GRAPHIC_TOOL_FOLDER + STAKE_FONT).c_str(), 32);
	SDL_Color text_color = STAKE_COLOR;
	SDL_Color button_color = ACTION_BUTTON_COLOR;
	SDL_Rect button_rect = this->display_button(button_text,
												text_font,
												text_color,
												button_color,
												coordX,
												coordY,
												sizeX,
												sizeY);
	SDL_RenderPresent(this->renderer);
	return button_rect;

}

int GUI::check_click_in_rect(int x, int y, struct SDL_Rect &rect)
{
    /* Check X coordinate is within rectangle range */
    if (x >= rect.x && x < (rect.x + rect.w))
    {
        /* Check Y coordinate is within rectangle range */
        if (y >= rect.y && y < (rect.y + rect.h))
        {
            /* X and Y is inside the rectangle */
            return 1;
        }
    }
    /* X or Y is outside the rectangle */
    return 0;
}

void GUI::display_action_buttons(bool has_raised){
	unsigned int coordX = 650;
	unsigned int coordY = 635;
	unsigned int sizeX = 150;
	unsigned int sizeY = 100;
	unsigned int margin_value = 40;
	string amount_str = "";
	if (has_raised){
		this->display_action_button("FOLD",
									coordX,
									coordY,
									sizeX,
									sizeY);
		this->display_action_button("CALL",
									coordX + sizeX,
									coordY,
									sizeX,
									sizeY);
		this->display_action_button("RAISE",
									coordX + 2*sizeX,
									coordY,
									sizeX,
									sizeY);
		this->display_action_button(amount_str,
									coordX + 2*sizeX,
									coordY - margin_value,
									sizeX,
									margin_value);

//
	}
	else{// there is a no bet from another player: BET or CHECK
		this->display_action_button("CHECK",
									coordX,
									coordY,
									(int) (1.5* (float)sizeX),
									sizeY);
		this->display_action_button("BET",
									coordX + (int) (1.5* (float)sizeX),
									coordY,
									sizeX,
									sizeY);
		this->display_action_button(amount_str,
									coordX + (int) (1.5* (float)sizeX),
									coordY - margin_value,
									sizeX,
									margin_value);
	}
	SDL_Event event;
	SDL_WaitEvent(&event);
}

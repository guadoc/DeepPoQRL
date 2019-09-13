

#include "PlayerGUI.h"
#include "../table_lib/TableGUI.h"



AbstractPlayer::Action PlayerGUI::play_preflop(){
	int coordX = 650;
	int coordY = 635;
	int sizeX = 150;
	int sizeY = 100;
	int margin_value = 40;
	string amount_str = " ";
	GUI *gui = (dynamic_cast<TableGUI*>(this->table))->get_gui();
	if (this->table->get_last_raise() != 0 and this->table->get_last_raise() != this->commitment){
		// there is a bet from another player: raise_pot, call_pot or fold_pot

		SDL_Rect fold_button_rect = gui->display_action_button("FOLD",
																coordX,
																coordY,
																sizeX,
																sizeY);
		SDL_Rect call_button_rect = gui->display_action_button("CALL",
																coordX + sizeX,
																coordY,
																sizeX,
																sizeY);
		SDL_Rect raise_button_rect = gui->display_action_button("RAISE",
																coordX + 2*sizeX,
																coordY,
																sizeX,
																sizeY);
		gui->display_action_button(amount_str,
									coordX + 2*sizeX,
									coordY - margin_value,
									sizeX,
									margin_value);
		bool no_action = true;
		SDL_Event event;
		SDL_WaitEvent(&event);
		while (no_action){
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_MOUSEBUTTONDOWN){
					if(event.button.button == SDL_BUTTON_LEFT){
						int x;
						int y;
						SDL_GetMouseState(&x, &y);
						if (gui->check_click_in_rect(x, y, raise_button_rect)){
							unsigned int value_raise = atof(amount_str.c_str());
							return this->raise_pot(value_raise);
							break;
						}
						else if (gui->check_click_in_rect(x, y, call_button_rect)){
							return this->call_pot();
							break;
						}
						else if (gui->check_click_in_rect(x, y, fold_button_rect)){
							return this->fold_pot();
						}

					}
				}
				else if ( event.type == SDL_KEYDOWN ){
///////////////////////////////////////////////////////////////////////////////
					if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( amount_str.length() != 0 ) )
							{
							//Remove a character from the end
								amount_str.erase( amount_str.length() - 1 );
								gui->display_action_button(amount_str,
															coordX + 2*sizeX,
															coordY - margin_value,
															sizeX,
															margin_value);
							}
							else if (amount_str.length() <= 6){ //& check that a digit is given
								if( ( event.key.keysym.sym >= '0' ) && ( event.key.keysym.sym <= '9' ) ){
									amount_str += to_string(event.key.keysym.sym - SDLK_0);
									gui->display_action_button(amount_str,
																coordX + 2*sizeX,
																coordY - margin_value,
																sizeX,
																margin_value);
								}

							}
/////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
		}
	}
	else{// there is a no bet from another player: bet_pot or check_pot
		SDL_Rect check_button_rect = gui->display_action_button("CHECK",
																coordX,
																coordY,
																(int) (1.5* (float)sizeX),
																sizeY);
		SDL_Rect bet_button_rect = gui->display_action_button("BET",
																	coordX + (int) (1.5* (float)sizeX),
																	coordY,
																	sizeX,
																	sizeY);
		gui->display_action_button(amount_str,
									coordX + (int) (1.5* (float)sizeX),
									coordY -margin_value,
									sizeX,
									margin_value);
		bool no_action = true;
		SDL_Event event;
		SDL_WaitEvent(&event);
		while (no_action){
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_MOUSEBUTTONDOWN){
					if(event.button.button == SDL_BUTTON_LEFT){
						int x;
						int y;
						SDL_GetMouseState(&x, &y);
						if (gui->check_click_in_rect(x, y, bet_button_rect)){
							unsigned int value_bet = atof(amount_str.c_str());
							return this->bet_pot(value_bet);
							break;
						}
						else if (gui->check_click_in_rect(x, y, check_button_rect)){
							return this->check_pot();
							break;

						}
					}
				}
				else if ( event.type == SDL_KEYDOWN ){
///////////////////////////////////////////////////////////////////////////////
					if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( amount_str.length() != 0 ) )
							{
							//Remove a character from the end
								amount_str.erase( amount_str.length() - 1 );
								gui->display_action_button(amount_str,
															coordX + (int) (1.5* (float)sizeX),
															coordY - margin_value,
															sizeX,
															margin_value);
							}
							else if (amount_str.length() <= 6){ // si on est dans les chiffres
								if( ( event.key.keysym.sym >= '0' ) && ( event.key.keysym.sym <= '9' ) ){
									amount_str += to_string(event.key.keysym.sym - SDLK_0);
									gui->display_action_button(amount_str,
																coordX + (int) (1.5* (float)sizeX),
																coordY - margin_value,
																sizeX,
																margin_value);
								}
							}
/////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
		}
	}
	return this->fold_pot();
}

AbstractPlayer::Action PlayerGUI::play_flop(){
	return this->play_preflop();
}

AbstractPlayer::Action PlayerGUI::play_turn(){
	return this->play_preflop();
}

AbstractPlayer::Action PlayerGUI::play_river(){
	return this->play_preflop();
}



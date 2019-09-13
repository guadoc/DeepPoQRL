/*
 * PlayerGUI.h
 *
 *  Created on: Jan 23, 2019
 *      Author: walnutalgo
 */

#ifndef PLAYER_LIB_PLAYERGUI_H_
#define PLAYER_LIB_PLAYERGUI_H_

//#include "../StdAfx.h"
#include "AbstractPlayer.h"
#include "PlayerLogs.h"
#include "../utils/utils.h"

using ParentPlayerGUI = PlayerLogs;

class PlayerGUI : public ParentPlayerGUI{
public:
	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();

//	SDL_Rect display_action_buttons(string button_text, int coordX ,int coordY, int sizeX, int sizeY) const;
protected:
//	util_graphic graphic_tools;
};

#endif /* PLAYER_LIB_PLAYERGUI_H_ */

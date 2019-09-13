

#ifndef TABLE_LIB_TABLEGUI_H_
#define TABLE_LIB_TABLEGUI_H_



//#pragma once
#include "../StdAfx.h"
#include "../deck_lib/Deck.h"
#include "../deck_lib/Card.h"
#include "../deck_lib/Hand.h"
#include "../player_lib/PlayerRandom.h"
#include "../player_lib/PlayerGUI.h"
#include "TableLogs.h"
//#include "AbstractTable.h"
#include "../utils/utils.h"
#include "GUI.h"

using namespace std;
using ParentTableGUI = TableLogs;

class TableGUI : public ParentTableGUI{
public:
	TableGUI();
	TableGUI(unsigned int n_players);
	TableGUI(vector<AbstractPlayer*> &);
	~TableGUI(void);

	void display_table(unsigned int);
	GUI * get_gui() const;


protected:
	GUI *gui;
};



#endif /* TABLE_LIB_TABLEGUI_H_ */

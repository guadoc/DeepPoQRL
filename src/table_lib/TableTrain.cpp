/*
 * TableTrain.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Michael Blot
 */

#include "TableTrain.h"


TableTrain::TableTrain(): ParentTableTrain(){

}


TableTrain::TableTrain(unsigned int n_players):ParentTableTrain(n_players){
}

TableTrain::TableTrain(vector<AbstractPlayer*> & players):ParentTableTrain(players){
}

TableTrain::~TableTrain(void){

}





/*
 * Card.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Rainily
 */

#include "Card.h"
#include "Utilities.h"

Card::Card(cardType thisCardType) {

	this->thisCardType = thisCardType;

}
Card::Card() {

	this->thisCardType = INFANTRY;

}

void Card::setType(cardType thisCardType) {

	this->thisCardType = thisCardType;

}

void Card::printType() {

	if(this->thisCardType == INFANTRY) {
		cout << "This is an Infantry Card." << endl;
	}
	else if (this->thisCardType == ARTILLERY) {
		cout << "This is an Artillery Card." << endl;
	}
	else {
		cout << "This is an Cavalry Card." << endl;
	}

}

cardType Card::getType() {


	return this->thisCardType;

}




/*
 * Card.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#include "Card.h"
#include "Utilities.h"

/* Default Constructor */
Card::Card() {

	this->thisCardType = INFANTRY;
}

/* Card constructor that sets a card's type */
Card::Card(cardType thisCardType) {

	this->thisCardType = thisCardType;

}

/* Setter function for a card's type */
void Card::setType(cardType thisCardType) {

	this->thisCardType = thisCardType;

}

/* Function that prints card's type*/
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

/* Getter function for a card's type */
cardType Card::getType() {
	return this->thisCardType;
}




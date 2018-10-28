/*
 * Card.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#include "Card.h"
#include "Utilities.h"

int Card::CardId = 0;

ostream& operator<<(ostream& output, Card &c)
{
	output << "CARD: ";

	if (c.thisCardType == INFANTRY)
	{
		output << "INFANTRY";


	}
	else if (c.thisCardType == ARTILLERY)
	{
		output << "ARTILLERY";
	}
	else if (c.thisCardType == CAVALRY)
	{
		output << "CAVALRY";
	}

	return output;
}


/** Gets the card id */
int Card::card_getId()
{
	return this->id;
}


/* Default Constructor */
Card::Card() {

	this->id = Card::CardId++;
	this->thisCardType = INFANTRY;
}

/* Card constructor that sets a card's type */
Card::Card(cardType thisCardType) {

	this->id = Card::CardId++;
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




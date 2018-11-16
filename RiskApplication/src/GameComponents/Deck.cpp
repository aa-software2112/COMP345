/*
 * Deck.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#include "Deck.h"
#include "Card.h"
#include <algorithm>
#include <array>


Deck::Deck(int numOfCountries) {

	numCards = numOfCountries;

	cards = new Card*[numOfCountries];

	for(unsigned int i = 0; i < numOfCountries; i++)
	{
		cards[i] = new Card;
	}

	cardType type[3] = { INFANTRY, ARTILLERY, CAVALRY };

	std::random_shuffle(std::begin(type), std::end(type));

	int typeIterator = 0;

	for(unsigned int i = 0; i < numOfCountries; i++)
	{
		cards[i]->card_setType(type[typeIterator]);
		typeIterator++;
		if(typeIterator == 3)
			typeIterator = 0;
	}

	std::random_shuffle(cards, cards+numOfCountries);
}

int Deck::deck_getDeckSize() {

	return numCards;

}

Card* Deck::deck_draw() {

	numCards = numCards - 1;
	return cards[numCards];
}


Card** Deck::deck_getDeck(){
	return this->cards;
}

ostream& operator<<(ostream& output, Deck &d)
{
	/** Iterate over all deck cards */
	for( int i = 0; i<d.numCards; i++)
	{

		output << "\t" << " ID_" << d.cards[i]->card_getId() << " Type: " << d.cards[i]->card_getType() << endl;

	}

	return output;
}

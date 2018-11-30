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

Deck::~Deck()
{
	cout << "Number of cards to delete " << this->totalCards << endl;

	/** Remove all cards */
	for(UINT cardIndex = 0; cardIndex < this->totalCards; cardIndex++)
	{
		/** Each index refers to a Card pointer that must be deleted */
		delete this->cards[cardIndex];

	}

	this->numCards = 0;

	this->totalCards = 0;

	/** Cards are indexed at zero again */
	Card::CardId = 0;

}

Deck::Deck(int numOfCountries) {

	this->totalCards = numOfCountries;

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

	if (numCards < 0)
	{
		return NULL;
	}
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

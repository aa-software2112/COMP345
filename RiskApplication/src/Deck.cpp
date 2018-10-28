/*
 * Deck.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#include "Deck.h"
#include "Card.h"


int Deck::get_numCards() {

	return numCards;

}

Card Deck::draw() {

	numCards = numCards - 1;
	return cards[numCards];


}
void Deck::set_cards(Card *deck) {

	cards = deck;

}

Card* Deck::get_deck(){
	return this->cards;
}

ostream& operator<<(ostream& output, Deck &d)
{
	/** Iterate over all deck cards */
	for( int i = 0; i<d.numCards; i++)
	{

		output << "\t" << d.cards[i] << " ID_" << d.cards[i].card_getId() << endl;

	}

	return output;
}

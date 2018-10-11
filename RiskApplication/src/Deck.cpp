/*
 * Deck.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Rainily
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


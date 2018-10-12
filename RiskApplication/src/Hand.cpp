/*
 * Hand.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */


#include "Hand.h"
#include "Card.h"
#include "Utilities.h"

/* Hand default constructor */
Hand::Hand(){

}

/* Function that adds a card to a player's hand */
void Hand::addCardToHand(Card* cardToAdd) {
	handOfCards.push_back(cardToAdd);
}

/* Function that removes a card from a player's hand */
void Hand::removeCardFromHand(Card* cardToRemove) {
	for(unsigned int i = 0; i < handOfCards.size(); i++) {
		if(cardToRemove == handOfCards[i]) {
			handOfCards.erase(handOfCards.begin() + i);
		}
	}
}

/* Function that returns a player's hand (vector of Card object references) */
vector<Card *> Hand::getHandOfCards() {
	return handOfCards;
}

/* Function that returns the number of cards in a player's hand */
int Hand::getNumberOfCards() {
	return handOfCards.size();
}

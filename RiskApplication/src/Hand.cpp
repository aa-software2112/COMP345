/*
 * Hand.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Rainily
 */


#include "Hand.h"
#include "Card.h"

Hand::Hand(){

}

void Hand::addCardToHand(Card* cardToAdd) {
	handOfCards.push_back(cardToAdd);
}

void Hand::removeCardFromHand(Card* cardToRemove) {
	for(unsigned int i = 0; i < handOfCards.size(); i++) {
		if(cardToRemove == handOfCards[i]) {
			handOfCards.erase(handOfCards.begin() + i);
		}
	}
}

vector<Card *> Hand::getHandOfCards() {
	return handOfCards;
}

int Hand::getNumberOfCards() {
	return handOfCards.size();
}

/*
 * Hand.h
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#ifndef RISKAPPLICATION_H_HAND_H_
#define RISKAPPLICATION_H_HAND_H_

#include <vector>
#include "Card.h"

class RiskGame;
class Hand{
public:
	Hand();
	void hand_addCardToHand(Card* cardToAdd);
	void hand_removeCardFromHand(Card* cardToRemove);
	vector<Card*> hand_getHandOfCards();
	int hand_getNumberOfCards();
	int hand_exchange(RiskGame* currentGame);
	void hand_showHand();
private:
	std::vector<Card*> handOfCards;

};



#endif /* RISKAPPLICATION_H_HAND_H_ */

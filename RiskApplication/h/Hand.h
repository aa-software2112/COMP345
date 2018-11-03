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
	void addCardToHand(Card* cardToAdd);
	void removeCardFromHand(Card* cardToRemove);
	vector<Card*> getHandOfCards();
	int getNumberOfCards();
	int exchange(RiskGame* currentGame);
	void hand_showHand();
private:
	std::vector<Card*> handOfCards;

};



#endif /* RISKAPPLICATION_H_HAND_H_ */

/*
 * Hand.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */


#include "Hand.h"
#include "Card.h"
#include "Utilities.h"
#include "UserInterface.h"
#include "RiskGame.h"

/* Hand default constructor */
Hand::Hand(){

}

/* Function that adds a card to a player's hand */
void Hand::hand_addCardToHand(Card* cardToAdd) {
	handOfCards.push_back(cardToAdd);
}

/* Function that removes a card from a player's hand */
void Hand::hand_removeCardFromHand(Card* cardToRemove) {
	for(unsigned int i = 0; i < handOfCards.size(); i++) {
		if(cardToRemove == handOfCards[i]) {
			handOfCards.erase(handOfCards.begin() + i);
		}
	}
}

/* Function that returns a player's hand (vector of Card object references) */
vector<Card *> Hand::hand_getHandOfCards() {
	return handOfCards;
}

/* Function that returns the number of cards in a player's hand */
int Hand::hand_getNumberOfCards() {
	return handOfCards.size();
}

void Hand::hand_showHand() {
	cout << "Current Hand:" << endl;
	cout << endl;

	for(int w = 0; w < handOfCards.size(); w++) {
		cout << "[" << w << "] ";
		handOfCards[w]->card_printType();
	}
	cout << endl;
}

int Hand::hand_exchange(RiskGame *currentGame) {

	/* Display player's hand */

	int armyBonus = 0;

	bool doneExchanging = false;

	int infantryCountHand = 0;
	int cavalryCountHand = 0;
	int artilleryCountHand = 0;

	for(int i = 0; i < handOfCards.size(); i++) {
		if(handOfCards[i]->card_getType() == INFANTRY)
			infantryCountHand++;
		else if(handOfCards[i]->card_getType() == CAVALRY)
			cavalryCountHand++;
		else
			artilleryCountHand++;
	}

	if((infantryCountHand < 1 || cavalryCountHand < 1 || artilleryCountHand < 1) && ((infantryCountHand < 3) && (cavalryCountHand < 3) && (artilleryCountHand < 3)))
	{
		doneExchanging = true;
		cout << "ERROR: You do not have any valid sets!"<< endl;
	}

	while (!doneExchanging)
	{
		hand_showHand();

		string selectFirstCardMessage = "Enter the index of the first card you would like to exchange.";

		int firstCardIndex = UserInterface::userInterface_getIntegerBetweenRange(selectFirstCardMessage, 0, handOfCards.size());

		string selectSecondCardMessage = "Enter the index of  the second card you would like to exchange. (Must be different from the first card!)";

		int secondCardIndex = UserInterface::userInterface_getIntegerBetweenRange(selectSecondCardMessage, 0, handOfCards.size());

		string selectThirdCardMessage = "Enter the index of  the third card you would like to exchange. (Must be different from the first card and the second card!)";

		int thirdCardIndex = UserInterface::userInterface_getIntegerBetweenRange(selectThirdCardMessage, 0, handOfCards.size());

		if((firstCardIndex == secondCardIndex) || firstCardIndex == thirdCardIndex || secondCardIndex == thirdCardIndex)
			cout << "ERROR: Please make sure you enter a different index for every card!" << endl;
		else if(((handOfCards[firstCardIndex]->card_getType() != handOfCards[secondCardIndex]->card_getType()) && (handOfCards[firstCardIndex]->card_getType() != handOfCards[thirdCardIndex]->card_getType()) && (handOfCards[secondCardIndex]->card_getType() != handOfCards[thirdCardIndex]->card_getType())) ||
				(handOfCards[firstCardIndex]->card_getType() == INFANTRY && handOfCards[secondCardIndex]->card_getType() == CAVALRY && handOfCards[thirdCardIndex]->card_getType() == ARTILLERY) ||
				(handOfCards[firstCardIndex]->card_getType() == INFANTRY && handOfCards[secondCardIndex]->card_getType() == ARTILLERY && handOfCards[thirdCardIndex]->card_getType() == CAVALRY) ||
				(handOfCards[firstCardIndex]->card_getType() == ARTILLERY && handOfCards[secondCardIndex]->card_getType() == INFANTRY && handOfCards[thirdCardIndex]->card_getType() == CAVALRY) ||
				(handOfCards[firstCardIndex]->card_getType() == ARTILLERY && handOfCards[secondCardIndex]->card_getType() == CAVALRY && handOfCards[thirdCardIndex]->card_getType() == INFANTRY) ||
				(handOfCards[firstCardIndex]->card_getType() == CAVALRY && handOfCards[secondCardIndex]->card_getType() == INFANTRY && handOfCards[thirdCardIndex]->card_getType() == ARTILLERY) ||
				(handOfCards[firstCardIndex]->card_getType() == CAVALRY && handOfCards[secondCardIndex]->card_getType() == ARTILLERY && handOfCards[thirdCardIndex]->card_getType() == ARTILLERY))
		{
			/* Algorithm needed to remove the cards from the player's hand (highest index first to avoid index issues) */

			int highestIndex;
			int midIndex;
			int lowestIndex;

			if(firstCardIndex > secondCardIndex && firstCardIndex > thirdCardIndex)
			{
				highestIndex = firstCardIndex;
				if(secondCardIndex > thirdCardIndex)
				{
					midIndex = secondCardIndex;
					lowestIndex = thirdCardIndex;
				}
				else
				{
					midIndex = thirdCardIndex;
					lowestIndex = secondCardIndex;
				}
			}
			else if(secondCardIndex > firstCardIndex && secondCardIndex > thirdCardIndex)
			{
				highestIndex = secondCardIndex;
				if(firstCardIndex > thirdCardIndex)
				{
					midIndex = firstCardIndex;
					lowestIndex = thirdCardIndex;
				}
				else
				{
					midIndex = thirdCardIndex;
					lowestIndex = firstCardIndex;
				}
			}

			else if(thirdCardIndex > firstCardIndex && thirdCardIndex > secondCardIndex)
			{
				highestIndex = thirdCardIndex;
				if(firstCardIndex > secondCardIndex)
				{
					midIndex = firstCardIndex;
					lowestIndex = secondCardIndex;
				}
				else
				{
					midIndex = secondCardIndex;
					lowestIndex = firstCardIndex;
				}
			}

			handOfCards.erase(handOfCards.begin() + highestIndex);
			handOfCards.erase(handOfCards.begin() + midIndex);
			handOfCards.erase(handOfCards.begin() + lowestIndex);

			/* Recount cards */

			infantryCountHand = 0;
			cavalryCountHand = 0;
			artilleryCountHand = 0;

			for(unsigned int i = 0; i < handOfCards.size(); i++) {
				if(handOfCards[i]->card_getType() == INFANTRY)
					infantryCountHand++;
				else if(handOfCards[i]->card_getType() == CAVALRY)
					cavalryCountHand++;
				else
					artilleryCountHand++;
			}
			cout << endl;
			currentGame->riskGame_incrementCardSetsTraded();
			int bonusFromTrade = 5 * currentGame->riskGame_getCardSetsTraded();
			armyBonus = armyBonus + bonusFromTrade;
			cout << "Reinforcement Army Bonus! " << bonusFromTrade << " additional army units for exchanging a set of cards." << endl;

			if((infantryCountHand > 0 && cavalryCountHand > 0 && artilleryCountHand > 0) || ((infantryCountHand > 3) || (cavalryCountHand > 3) || (artilleryCountHand > 3)))
			{
				string exchangeAgainMessage = "Would you like to exchange another set of cards? (Enter 1 for yes or 0 for no)";

				int exchangeAgain = UserInterface::userInterface_getIntegerBetweenRange(exchangeAgainMessage, 0, 1);

				if(exchangeAgain == 0)
					doneExchanging = true;
				else
					doneExchanging = false;
			}
			else
				doneExchanging = true;
			cout << endl;
		}
		else
			cout << "ERROR: This is not a valid combination of cards!" << endl << endl;
	}
	return armyBonus;
}

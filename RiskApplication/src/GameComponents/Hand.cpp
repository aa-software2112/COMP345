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

/** Resets the hand; clears all cards from deck */
void Hand::hand_Reset(void)
{
	/** Clear entire hand */
	while(this->handOfCards.size() > 0)
	{
		this->handOfCards.erase(this->handOfCards.begin());
	}

}

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

	int armyBonus = 0;	// initialize army bonus

	bool doneExchanging = false;	// flag used to perform continuous exchanges (if possible)

	/* Variables that store the number of each type of card in the current player's hand */
	int infantryCountHand = 0;
	int cavalryCountHand = 0;
	int artilleryCountHand = 0;

	/* Counting cards... */
	for(int i = 0; i < handOfCards.size(); i++) {
		if(handOfCards[i]->card_getType() == INFANTRY)
			infantryCountHand++;
		else if(handOfCards[i]->card_getType() == CAVALRY)
			cavalryCountHand++;
		else
			artilleryCountHand++;
	}

	/* Condition used to assure that a player has a possible exchange */
	if((infantryCountHand < 1 || cavalryCountHand < 1 || artilleryCountHand < 1) && ((infantryCountHand < 3) && (cavalryCountHand < 3) && (artilleryCountHand < 3)))
	{
		/* If the they get here, that means they have no possible set to trade in */
		doneExchanging = true;
		cout << "ERROR: You do not have any valid sets!"<< endl;
	}

	while (!doneExchanging)
	{
		/* Display the player's hand */
		hand_showHand();

		/* Prompt the player for the first card */
		string selectFirstCardMessage = "Enter the index of the first card you would like to exchange.";
		int firstCardIndex = UserInterface::userInterface_getIntegerBetweenRange(selectFirstCardMessage, 0, handOfCards.size());

		/* Prompt the player for the second card */
		string selectSecondCardMessage = "Enter the index of  the second card you would like to exchange. (Must be different from the first card!)";
		int secondCardIndex = UserInterface::userInterface_getIntegerBetweenRange(selectSecondCardMessage, 0, handOfCards.size());

		/* Prompt the player for the third card */
		string selectThirdCardMessage = "Enter the index of  the third card you would like to exchange. (Must be different from the first card and the second card!)";
		int thirdCardIndex = UserInterface::userInterface_getIntegerBetweenRange(selectThirdCardMessage, 0, handOfCards.size());

		/* Condition used to check whether all the indexes are different */
		if((firstCardIndex == secondCardIndex) || firstCardIndex == thirdCardIndex || secondCardIndex == thirdCardIndex)
			cout << "ERROR: Please make sure you enter a different index for every card!" << endl;
		/* Condition used to check whether all the given combination of indexes give a valid set of cards to exchange */
		else if(((handOfCards[firstCardIndex]->card_getType() != handOfCards[secondCardIndex]->card_getType()) && (handOfCards[firstCardIndex]->card_getType() != handOfCards[thirdCardIndex]->card_getType()) && (handOfCards[secondCardIndex]->card_getType() != handOfCards[thirdCardIndex]->card_getType())) ||
				(handOfCards[firstCardIndex]->card_getType() == INFANTRY && handOfCards[secondCardIndex]->card_getType() == CAVALRY && handOfCards[thirdCardIndex]->card_getType() == ARTILLERY) ||
				(handOfCards[firstCardIndex]->card_getType() == INFANTRY && handOfCards[secondCardIndex]->card_getType() == ARTILLERY && handOfCards[thirdCardIndex]->card_getType() == CAVALRY) ||
				(handOfCards[firstCardIndex]->card_getType() == ARTILLERY && handOfCards[secondCardIndex]->card_getType() == INFANTRY && handOfCards[thirdCardIndex]->card_getType() == CAVALRY) ||
				(handOfCards[firstCardIndex]->card_getType() == ARTILLERY && handOfCards[secondCardIndex]->card_getType() == CAVALRY && handOfCards[thirdCardIndex]->card_getType() == INFANTRY) ||
				(handOfCards[firstCardIndex]->card_getType() == CAVALRY && handOfCards[secondCardIndex]->card_getType() == INFANTRY && handOfCards[thirdCardIndex]->card_getType() == ARTILLERY) ||
				(handOfCards[firstCardIndex]->card_getType() == CAVALRY && handOfCards[secondCardIndex]->card_getType() == ARTILLERY && handOfCards[thirdCardIndex]->card_getType() == ARTILLERY))
		{
			/* Algorithm needed to remove the cards from the player's hand (highest index first to avoid index issues) */
			/***********************************************************************************************************/
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

			/***********************************************************************************************************/

			/* Recount cards */
			infantryCountHand = 0;
			cavalryCountHand = 0;
			artilleryCountHand = 0;

			/* Recounting... */
			for(unsigned int i = 0; i < handOfCards.size(); i++) {
				if(handOfCards[i]->card_getType() == INFANTRY)
					infantryCountHand++;
				else if(handOfCards[i]->card_getType() == CAVALRY)
					cavalryCountHand++;
				else
					artilleryCountHand++;
			}

			cout << endl;

			currentGame->riskGame_incrementCardSetsTraded(); // increment global sets traded counter

			int bonusFromTrade = 5 * currentGame->riskGame_getCardSetsTraded(); // calculate the army bonus from the exchange (different variable because multiple trades can happen during one session)
			armyBonus = armyBonus + bonusFromTrade;
			cout << "Reinforcement Army Bonus! " << bonusFromTrade << " additional army units for exchanging a set of cards." << endl;

			/* Condition that checks whether the player has a possible exchange with their new hand*/
			if((infantryCountHand > 0 && cavalryCountHand > 0 && artilleryCountHand > 0) || ((infantryCountHand > 3) || (cavalryCountHand > 3) || (artilleryCountHand > 3)))
			{
				/* If so, prompt if they want to make anotehr trade */
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
		/* If code gets to this else statement, the combination of indexes do not represent a valid set to trade-in */
		else
			cout << "ERROR: This is not a valid combination of cards!" << endl << endl;
	}
	return armyBonus;
}
int Hand::hand_autoExchange(RiskGame *currentGame) {

	int armyBonus = 0;	// initialize army bonus

	/* Variables that store the number of each type of card in the current player's hand */
	int infantryCountHand = 0;
	int cavalryCountHand = 0;
	int artilleryCountHand = 0;
	vector <int> indexInfantry;
	vector <int> indexCalvary;
	vector <int> indexArtillery;
	bool doneExchanging = false;

	/* Counting cards... */
	for(int i = 0; i < handOfCards.size(); i++) {
		if(handOfCards[i]->card_getType() == INFANTRY){
			infantryCountHand++;
			indexInfantry.push_back(i);
		}
		else if(handOfCards[i]->card_getType() == CAVALRY){
			cavalryCountHand++;
			indexCalvary.push_back(i);
		}
		else{
			artilleryCountHand++;
			indexArtillery.push_back(i);
		}
	}
	if((infantryCountHand < 1 || cavalryCountHand < 1 || artilleryCountHand < 1) && ((infantryCountHand < 3) && (cavalryCountHand < 3) && (artilleryCountHand < 3)))
	{
		cout << "ERROR: You do not have any valid sets!"<< endl;
		doneExchanging = true;
	}
	else if(infantryCountHand == 1 || cavalryCountHand == 1 || artilleryCountHand == 1)
	{
		handOfCards.erase(handOfCards.begin() + indexInfantry[0]);
		handOfCards.erase(handOfCards.begin() + indexCalvary[0]);
		handOfCards.erase(handOfCards.begin() + indexArtillery[0]);
		indexInfantry.erase(indexInfantry.begin());
		indexCalvary.erase(indexCalvary.begin());
		indexArtillery.erase(indexArtillery.begin());

	}
	else if(infantryCountHand == 3)
	{
		handOfCards.erase(handOfCards.begin() + indexInfantry[0]);
		indexInfantry.erase(indexInfantry.begin());
		handOfCards.erase(handOfCards.begin() + indexInfantry[0]);
		indexInfantry.erase(indexInfantry.begin());
		handOfCards.erase(handOfCards.begin() + indexInfantry[0]);
		indexInfantry.erase(indexInfantry.begin());
	}
	else if(cavalryCountHand == 3)
	{
		handOfCards.erase(handOfCards.begin() + indexCalvary[0]);
		indexCalvary.erase(indexCalvary.begin());
		handOfCards.erase(handOfCards.begin() + indexCalvary[0]);
		indexCalvary.erase(indexCalvary.begin());
		handOfCards.erase(handOfCards.begin() + indexCalvary[0]);
		indexCalvary.erase(indexCalvary.begin());
	}
	else if(artilleryCountHand == 3)
	{
		handOfCards.erase(handOfCards.begin() + indexArtillery[0]);
		indexArtillery.erase(indexArtillery.begin());
		handOfCards.erase(handOfCards.begin() + indexArtillery[0]);
		indexArtillery.erase(indexArtillery.begin());
		handOfCards.erase(handOfCards.begin() + indexArtillery[0]);
		indexArtillery.erase(indexArtillery.begin());
	}
	cout << endl;
	if(doneExchanging == false){
		currentGame->riskGame_incrementCardSetsTraded(); // increment global sets traded counter

		int bonusFromTrade = 5 * currentGame->riskGame_getCardSetsTraded(); // calculate the army bonus from the exchange (different variable because multiple trades can happen during one session)
		armyBonus = armyBonus + bonusFromTrade;
		cout << "Reinforcement Army Bonus! " << bonusFromTrade << " additional army units for exchanging a set of cards." << endl;
	}
	return armyBonus;
}

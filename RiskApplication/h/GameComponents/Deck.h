/*
 * Deck.h
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#ifndef RISKAPPLICATION_H_DECK_H_
#define RISKAPPLICATION_H_DECK_H_

#include "Utilities.h"
#include "Card.h"
#include <cstdio>
#include <algorithm>
#include "Map.h"
#include <time.h>
using namespace std;

class Deck {
private:
	/** The number of cards left to deal to all players */
	int numCards;

	/** The number of cards in memory - for deletion purposes*/
	int totalCards;
	Card** cards;

public:
	Deck(int numOfCountries);
	~Deck();
	Card** deck_getDeck();
	int deck_getDeckSize();
	Card* deck_draw();
	friend ostream& operator<<(ostream& output, Deck& d);

};


#endif /* RISKAPPLICATION_H_DECK_H_ */
